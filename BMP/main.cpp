// #include "stdafx.h"   
#include "bmp.h"   
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "/home/dream/Codes/robot/arm/atp/point.h"
int main()  
{  
    // ClImage* img = clLoadImage("/home/dream/out2.bmp");  
    ClImage img;
    img.channels = 1;
    img.width = 122;
    img.height = 122;
    int w,h;
    // img->imageData = (unsigned char*)malloc(sizeof(char)*20*20);  
    img.imageData = (unsigned char*)malloc(sizeof(unsigned char)*img.width*img.height);  
    for(h=img.height-1; h>-1; h--)
    {
        for(w = 0; w < img.width-1; w++)   
        {
            img.imageData[h*img.width + w] = 255;
        }
    }
    bool flag = clSaveImage("/home/dream/resul1.bmp", &img);
    if(flag)  
    {  
        printf("save ok... \n");  
    }  
    while(1);  
    return 0;  
}  
// #include "/usr/include/python2.7/Python.h"

// int main(void)
// {
//     int alpha = 0, beta = 0;
//     char *mat;
//     Arm_point point;
//     struct Point one, two, three, four;
//     printf("\n");
//     printf("\n");
//     printf("\n");
//     while(alpha <= 180)
//     {
//         while(beta <= 180)
//         {
//             point.update(alpha,beta);
//             // printf("%d",point.ErrorTest());
//             if(point.ErrorTest() == 0)
//             {
//                 one = point.first_conver();
//                 two = point.second_conver(one);
//                 three = point.third_conver(two);
//                 four = point.fourth_conver(three);
//                 printf("%f  %f'\n",four.x,four.y);
//                 // printf("\n");
//             }
//             beta = beta + 1;
//         }
//         beta = 0;
//         alpha = alpha + 1;
//     }
//     return 0;
// }




