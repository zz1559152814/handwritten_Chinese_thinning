#include "li_bitmap.h"
#include <memory.h>
#include <stdlib.h>  
#include <stdio.h>
//生成BMP图片(无颜色表的位图):在RGB(A)位图数据的基础上加上文件信息头和位图信息头
int GenBmpFile(U8 *pData, U8 bitCountPerPix, U32 width, U32 height, const char *filename);
//获取BMP文件的位图数据(无颜色表的位图):丢掉BMP文件的文件信息头和位图信息头，获取其RGB(A)位图数据
U8* GetBmpData(U8 *bitCountPerPix, U32 *width, U32 *height, const char* filename);
//释放GetBmpData分配的空间
void FreeBmpData(U8 *pdata);
//生成BMP图片(无颜色表的位图):在RGB(A)位图数据的基础上加上文件信息头和位图信息头  
int GenBmpFile(U8 *pData, U8 bitCountPerPix, U32 width, U32 height, const char *filename)  
{  
    FILE *fp = fopen(filename, "wb");  
    if(!fp)  
    {  
        printf("fopen failed : %s, %d\n", __FILE__, __LINE__);  
        return 0;  
    }  
  
    U32 bmppitch = ((width*bitCountPerPix + 31) >> 5) << 2;  
    U32 filesize = bmppitch*height;  
  
    BITMAPFILE bmpfile;  
  
    bmpfile.bfHeader.bfType = 0x4D42;  
    // bmpfile.bfHeader.bfSize = filesize + 2*4 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);  
    bmpfile.bfHeader.bfSize = filesize + 2*4 + bmppitch;  
    bmpfile.bfHeader.bfReserved1 = 0;  
    bmpfile.bfHeader.bfReserved2 = 0;  
    bmpfile.bfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 2*sizeof(RGBQUAD);  
    printf("%d",bmppitch );
    bmpfile.biInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);  
    bmpfile.biInfo.bmiHeader.biWidth = width;  
    bmpfile.biInfo.bmiHeader.biHeight = height;  
    bmpfile.biInfo.bmiHeader.biPlanes = 1;  
    bmpfile.biInfo.bmiHeader.biBitCount = bitCountPerPix;  
    bmpfile.biInfo.bmiHeader.biCompression = 0;  
    bmpfile.biInfo.bmiHeader.biSizeImage = bmppitch*height;  
    bmpfile.biInfo.bmiHeader.biXPelsPerMeter = 0;  
    bmpfile.biInfo.bmiHeader.biYPelsPerMeter = 0;  
    bmpfile.biInfo.bmiHeader.biClrUsed = 2;  
    bmpfile.biInfo.bmiHeader.biClrImportant = 2;  


    fwrite(&(bmpfile.bfHeader), sizeof(BITMAPFILEHEADER), 1, fp);  
    fwrite(&(bmpfile.biInfo.bmiHeader), sizeof(BITMAPINFOHEADER), 1, fp);  
    
    RGBQUAD* quad;
    quad = (RGBQUAD*)malloc(sizeof(RGBQUAD)*2);  
    quad[0].rgbBlue = 32;
    quad[0].rgbGreen = 32;
    quad[0].rgbRed = 32;
    quad[0].rgbReserved = 0;
    quad[1].rgbBlue = 200;
    quad[1].rgbGreen = 200;
    quad[1].rgbRed = 200;
    quad[1].rgbReserved = 0;
    if(bitCountPerPix == 24)
    {
        U8 *pEachLinBuf = (U8*)malloc(bmppitch);  
        memset(pEachLinBuf, 0, bmppitch);  
        U8 BytePerPix = bitCountPerPix >> 3;  
        U32 pitch = width * BytePerPix;  
        if(pEachLinBuf)  
        {  
            int h,w;  
            for(h = height-1; h >= 0; h--)  
            {  
                for(w = 0; w < width; w++)  
                {  
                    //copy by a pixel  
                    pEachLinBuf[w*BytePerPix+0] = pData[h*pitch + w*BytePerPix + 0];  
                    pEachLinBuf[w*BytePerPix+1] = pData[h*pitch + w*BytePerPix + 1];  
                    pEachLinBuf[w*BytePerPix+2] = pData[h*pitch + w*BytePerPix + 2];  
                }  
                fwrite(pEachLinBuf, bmppitch, 1, fp);  
                  
            }  
            free(pEachLinBuf);  
        }
    }
    else if(bitCountPerPix == 1)  
    {
        U8 *pEachLinBuf = (U8*)malloc(bmppitch);  
        memset(pEachLinBuf, 0, bmppitch); 
        U8 m,n;
        U8 x;
        // fwrite(bmpfile.biInfo.bmiColors, 8, 1, fp);  
        fwrite(bmpfile.biInfo.bmiColors, sizeof(RGBQUAD), 2, fp);  
        free(quad);
        if(pEachLinBuf)  
        {  
            int h,w;
            U8 w_p,d;  
            w_p = width/8;
            printf("%d  %d  ",height,width);
            for(h = height-1; h >= 0; h--)  
            {  
                for(w = 0; w < w_p; w++)
                {  
                    // for(d = 0; d < 8; d++)
                    // {
                        pEachLinBuf[h*bmppitch + w] |= pData[h*bmppitch + w*8];
                        printf("%d  ",pData[h*bmppitch + w]);

                }  
                fwrite(pEachLinBuf, bmppitch, 1, fp);  
            }  
            free(pEachLinBuf);  
        }   
    }
    fclose(fp);  
    return 1;  
}  
  
  
//释放GetBmpData分配的空间  
void FreeBmpData(U8 *pdata)  
{  
    if(pdata)  
    {  
        free(pdata);  
        pdata = NULL;  
    }  
}  
  
typedef struct _LI_RGB  
{  
    U8 b;  
    U8 g;  
    U8 r;  
}LI_RGB; 
  
#define WIDTH   200
#define HEIGHT  200 

int main(int argc, char *argv[])  
{ 
    #if 1  
    //test one  
    U8 pRGB[WIDTH][HEIGHT];  // 定义位图数据  
    memset(pRGB, 0, sizeof(pRGB) ); // 设置背景为黑色  
    // 在中间画一个10*10的矩形  
    int i=0, j=0;  
    for(i = 0; i < HEIGHT; i++)  
    {  
        for( j = 0; j < WIDTH; j++)  
        {  
            pRGB[i][j]= 1;  
        }  
    }  
    GenBmpFile((U8*)pRGB, 1, WIDTH, HEIGHT, "/home/dream/program/robot/arm/BMP/out1.bmp");//生成BMP文件 
    #endif 
  
    // #if 1  
    // //test two  
    // U8 bitCountPerPix;  
    // U32 width, height;  
    // U8 *pdata = GetBmpData(&bitCountPerPix, &width, &height, "in.bmp");  
    // if(pdata)  
    // {  
    //     GenBmpFile(pdata, bitCountPerPix, width, height, "out1.bmp");  
    //     FreeBmpData(pdata);  
    // } 
    // #endif  
       
    return 0;  
} 
//获取BMP文件的位图数据(无颜色表的位图):丢掉BMP文件的文件信息头和位图信息头，获取其RGB(A)位图数据  
// U8* GetBmpData(U8 *bitCountPerPix, U32 *width, U32 *height, const char* filename)  
// {  
//     FILE *pf = fopen(filename, "rb");  
//     if(!pf)  
//     {  
//         printf("fopen failed : %s, %d\n", __FILE__, __LINE__);  
//         return NULL;  
//     }  

//     BITMAPFILE bmpfile;  
//     fread(&(bmpfile.bfHeader), sizeof(BITMAPFILEHEADER), 1, pf);  
//     fread(&(bmpfile.biInfo.bmiHeader), sizeof(BITMAPINFOHEADER), 1, pf);  

//     print_bmfh(bmpfile.bfHeader);  
//     print_bmih(bmpfile.biInfo.bmiHeader);  
   
//     if(bitCountPerPix)  
//     {  
//         *bitCountPerPix = bmpfile.biInfo.bmiHeader.biBitCount;  
//     }  
//     if(width)  
//     {  
//         *width = bmpfile.biInfo.bmiHeader.biWidth;  
//     }  
//     if(height)  
//     {  
//         *height = bmpfile.biInfo.bmiHeader.biHeight;  
//     }  

//     U32 bmppicth = (((*width)*(*bitCountPerPix) + 31) >> 5) << 2;  
//     U8 *pdata = (U8*)malloc((*height)*bmppicth);  
   
//     U8 *pEachLinBuf = (U8*)malloc(bmppicth);  
//     memset(pEachLinBuf, 0, bmppicth);  
//     U8 BytePerPix = (*bitCountPerPix) >> 3;  
//     U32 pitch = (*width) * BytePerPix;  

//     if(pdata && pEachLinBuf)  
//     {  
//         int w, h;  
//         for(h = (*height) - 1; h >= 0; h--)  
//         {  
//             fread(pEachLinBuf, bmppicth, 1, pf);  
//             for(w = 0; w < (*width); w++)  
//             {  
//                 pdata[h*pitch + w*BytePerPix + 0] = pEachLinBuf[w*BytePerPix+0];  
//                 pdata[h*pitch + w*BytePerPix + 1] = pEachLinBuf[w*BytePerPix+1];  
//                 pdata[h*pitch + w*BytePerPix + 2] = pEachLinBuf[w*BytePerPix+2];  
//             }  
//         }  
//         free(pEachLinBuf);  
//     }  
//     fclose(pf);  
   
//     return pdata;  
// }  
