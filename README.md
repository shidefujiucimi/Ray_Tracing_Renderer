# Ray_Tracing_Renderer
This is a ray tracing renderer,which is just a small attempt for me to learn compute graphics.  
This project is based on [Ray Tracing in One Weekend series](https://raytracing.github.io/) and [GAMES 202](https://www.bilibili.com/video/BV1YK4y1T7yY?spm_id_from=333.788.videopod.episodes&vd_source=0b161e5216bf8f030851d89416923a9f&p=12). Their tutorials did help me a lot.  
The only external library I used is [GLM](https://glm.g-truc.net/0.9.8/index.html).
## How To Render
You can check the main function,there are some examples.  
What you need to do is to set the scene,camera and light,and the result will be output to the location you specify.  
The format of the outimage is PPM.
## Recommended parameter
My recommended parameters are:  
samples_per_pixel = 50;  
max_depth = 50;  
It might take you one minute or two to render a image,if you start with the parameters above.
## Some Render Results 
![example image1](https://github.com/shidefujiucimi/Ray_Tracing_Renderer/blob/master/example%20image/outimage1.png)
![example image2](https://github.com/shidefujiucimi/Ray_Tracing_Renderer/blob/master/example%20image/outimage2.png)
![example image4](https://github.com/shidefujiucimi/Ray_Tracing_Renderer/blob/master/example%20image/outimage4.png)
![example image5](https://github.com/shidefujiucimi/Ray_Tracing_Renderer/blob/master/example%20image/outimage5.png)
![example image6](https://github.com/shidefujiucimi/Ray_Tracing_Renderer/blob/master/example%20image/outimage6.png)
![example image7](https://github.com/shidefujiucimi/Ray_Tracing_Renderer/blob/master/example%20image/outimage7.png)


