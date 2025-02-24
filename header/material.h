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
//D,���߷ֲ�����,Trowbridge-Reitz GGX
//�ڼ����ڱκ����ͷ��߷ֲ������в��ôֲڶȵ�ƽ�����ù��տ�����������Ȼ
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

//F,���������̣�ʹ��Fresnel-Schlick���Ʒ���ý��ƽ�
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
	return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}
//G,���κ���,����Schlick-GGX�������Smith��s method
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
	vec3 H = normalize(V + L);//����������
	// ����f_cooktorrance
	//----------
	float NDF = DistributionGGX(N, H, roughness);

	//Fresnel-Schlick���Ʒ�����һ������F0������Ϊ0������ǵķ����ʣ�
	//��ʾֱ��(��ֱ)�۲����ʱ�ж��ٹ��߻ᱻ���䡣 �������F0����Ϊ���ϲ�ͬ����ͬ�����Ҷ��ڽ������ʻ������ɫ��
	//��PBR�����������Ǽ򵥵���Ϊ������ľ�Ե����F0Ϊ0.04��ʱ�������Ӿ�������ȷ�ģ����ڽ����������Ǹ��ݷ������ر��ָ��F0
	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);
	vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);

	float G = GeometrySmith(N, V, L, roughness);

	vec3 nominator = NDF * G * F;
	float denominator = 4.0 * max(dot(N, V), 0.0f) * max(dot(N, L), 0.0f) + 0.001; //Ϊ�˱�����ֳ������,����0.001
	vec3 f_cooktorrance = nominator / denominator;
	//------------

	//����f_lambert
	vec3 f_lambert = vec3(albedo.r / PI, albedo.g / PI, albedo.b / PI);

	//����kD��kS
	//---------
	vec3 kS = F;//��Ϊ����������ֱ�Ӹ�����kS,���ǿ���ʹ��F��ʾ���д�����������ϵľ��淴���Ĺ���
	vec3 kD = vec3(1.0) - kS;//��kS���Ǻ����׼�������ı�ֵkD
	kD *= 1.0 - metallic;
	//----------

	vec3 fr = kD * f_lambert + kS * f_cooktorrance;
	return fr;
}
#endif
