#ifndef CHENLEECV_H   
#define CHENLEECV_H   
  
typedef struct  
{  
    //unsigned short    bfType;   
    unsigned long    bfSize;  
    unsigned short    bfReserved1;  
    unsigned short    bfReserved2;  
    unsigned long    bfOffBits;  
} ClBitMapFileHeader;  
  
typedef struct  
{  
    unsigned long  biSize;   
    long   biWidth;   
    long   biHeight;   
    unsigned short   biPlanes;   
    unsigned short   biBitCount;  
    unsigned long  biCompression;   
    unsigned long  biSizeImage;   
    long   biXPelsPerMeter;   
    long   biYPelsPerMeter;   
    unsigned long   biClrUsed;   
    unsigned long   biClrImportant;   
} ClBitMapInfoHeader;  
  
typedef struct   
{  
    unsigned char rgbBlue; //该颜色的蓝色分量   
    unsigned char rgbGreen; //该颜色的绿色分量   
    unsigned char rgbRed; //该颜色的红色分量   
    unsigned char rgbReserved; //保留值   
} ClRgbQuad;  
  
typedef struct  
{  
    int width;  
    int height;  
    int channels;  
    unsigned char* imageData;  
}ClImage;  
  
ClImage* clLoadImage(char* path);  
bool clSaveImage(char* path, ClImage* bmpImg);  
  
#endif   