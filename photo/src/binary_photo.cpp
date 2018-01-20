#include "/root/Codes/robot/arm/photo/include/includes.h"
using namespace std;


IplImage *g_pGrayImage = NULL;
IplImage *g_pBinaryImage = NULL;
const char *pstrWindowsBinaryTitle = "二值图(http://blog.csdn.net/MoreWindows)";


void on_trackbar(int pos)
{
	// 转为二值图
  //cvThreshold 对单通道数组应用固定阈值操作。该函数的典型应用是对灰度图像进行阈值操作得到二值图像
	cvThreshold(g_pGrayImage, g_pBinaryImage, pos, 255, CV_THRESH_BINARY);
	// 显示二值图
	// cvShowImage(pstrWindowsBinaryTitle, g_pBinaryImage);
  cvShowImage(pstrWindowsBinaryTitle, g_pGrayImage);
}

int main( int argc, char** argv )
{	
	const char *pstrWindowsSrcTitle = "原图";  
	const char *pstrWindowsToolBarName = "二值图阈值";
  	binary photo;
  	int threshold;

	IplImage* GrayImg;
  	IplImage* BinaImg;
  	photo.take_photo();
	GrayImg   = photo.Grayscale();
 	threshold = photo.GetThreshold();
	BinaImg   = photo.Binarization(threshold,GrayImg);
	// BinaImg = cvCreateImage(cvSize(GrayImg->width, GrayImg->height),IPL_DEPTH_8U, 1); 
 	// cvAdaptiveThreshold(GrayImg, BinaImg, 255,  CV_ADAPTIVE_THRESH_MEAN_C , CV_THRESH_BINARY, 3, 5);

  	//desimosing
  	IplImage* DeonImg;
	Deonising deonising(BinaImg);
	DeonImg = deonising.deonise();

	//find edge
	Edge edge(DeonImg);
	for(int m=0; m<15; m++)
	{
		edge.sweep();
		edge.paint();
	}

	return 0;
}
