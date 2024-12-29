#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
using namespace glm;
#define PI 3.1415926

class Material {



};
//D,法线分布函数,Trowbridge-Reitz GGX
//在几何遮蔽函数和法线分布函数中采用粗糙度的平方会让光照看起来更加自然
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
	float a = roughness * roughness;
	float a2 = a * a;
	float NdotH = max(dot(N, H), 0.0f);
	float NdotH2 = NdotH * NdotH;

	float num = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;

	return num / denom;
}

//F,菲涅尔方程，使用Fresnel-Schlick近似法求得近似解
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
	return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}
//G,几何函数,基于Schlick-GGX，并结合Smith’s method
float GeometrySchlickGGX(float NdotV, float roughness)
{
	float r = (roughness + 1.0);
	float k = (r * r) / 8.0;

	float num = NdotV;
	float denom = NdotV * (1.0 - k) + k;

	return num / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
	float NdotV = max(dot(N, V), 0.0f);
	float NdotL = max(dot(N, L), 0.0f);
	float ggx2 = GeometrySchlickGGX(NdotV, roughness);
	float ggx1 = GeometrySchlickGGX(NdotL, roughness);

	return ggx1 * ggx2;
}


vec3 calBRDF(vec3 P, vec3 V, vec3 L, vec3 albedo, float roughness, float metallic, vec3 N) {
	vec3 H = normalize(V + L);//计算半程向量
	// 计算f_cooktorrance
	//----------
	float NDF = DistributionGGX(N, H, roughness);

	//Fresnel-Schlick近似法接收一个参数F0，被称为0°入射角的反射率，
	//表示直接(垂直)观察表面时有多少光线会被反射。 这个参数F0会因为材料不同而不同，而且对于金属材质会带有颜色。
	//在PBR金属流中我们简单地认为大多数的绝缘体在F0为0.04的时候看起来视觉上是正确的，对于金属表面我们根据反射率特别地指定F0
	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);
	vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);

	float G = GeometrySmith(N, V, L, roughness);

	vec3 nominator = NDF * G * F;
	float denominator = 4.0 * max(dot(N, V), 0.0f) * max(dot(N, L), 0.0f) + 0.001; //为了避免出现除零错误,加了0.001
	vec3 f_cooktorrance = nominator / denominator;
	//------------

	//计算f_lambert
	vec3 f_lambert = vec3(albedo.r / PI, albedo.g / PI, albedo.b / PI);

	//计算kD、kS
	//---------
	vec3 kS = F;//因为菲涅尔方程直接给出了kS,我们可以使用F表示所有打在物体表面上的镜面反射光的贡献
	vec3 kD = vec3(1.0) - kS;//从kS我们很容易计算折射的比值kD
	kD *= 1.0 - metallic;
	//----------

	vec3 fr = kD * f_lambert + kS * f_cooktorrance;
	return fr;
}
#endif
