#include "/root/Codes/robot/arm/photo/include/includes.h"
using namespace std;

int binary::take_photo()  
{  
    //声明IplImage指针  
    IplImage* pFrame=NULL;  
    IplImage* pSaveFrame=NULL;  
    CvCapture* pCapture=NULL;  
    static char filename[100];  
    struct tm * tm_ptr;  
    struct timeb tp;  
    int p[3];  
    p[0] = CV_IMWRITE_JPEG_QUALITY;  
    p[1] = 100;  //质量值  
    p[2] = 0;  
    //创建窗口  
    cvNamedWindow("video",1);  
    //打开摄像头  
    if( !(pCapture=cvCaptureFromCAM(-1)) ) //此处值为-1表示自动搜索到的第一个摄象头，而0则表示第一个，1则表示第2个，以此类推。  
    {  
        fprintf(stderr,"Can not open camera.\n");  
        return -1;  
    }    
    if(mkdir("/root/for_test",0755)==-1)  
    {  
      //创建时存在该目录会返回错误码，如不存在则创建它，但由于我们需要该目录，则出错也不处理  
    }  
    //逐帧读取视频  
    while(pFrame=cvQueryFrame(pCapture))  
    {  
      cvShowImage("video",pFrame);  
      if(cvWaitKey(2)>=0) 
      {
        pSaveFrame=cvCreateImage(cvSize(640,480),pFrame->depth,pFrame->nChannels);  
      //get file name  
        ftime(&tp);  
        tm_ptr=localtime(&tp.time);  
        snprintf(filename, 40, "/root/for_test/SrcImg.jpg",tm_ptr->tm_year-100+2000,    tm_ptr->tm_mon + 1, tm_ptr->tm_mday, tm_ptr->tm_hour,tm_ptr->tm_min, tm_ptr->tm_sec,tp.millitm);  
        cvResize(pFrame,pSaveFrame,CV_INTER_LINEAR);  
        cvSaveImage(filename,pSaveFrame,p);  
        src = pSaveFrame;
        break;  
      }
    }  
    cvDestroyWindow("video");  
    cvReleaseCapture(&pCapture);  
    return 0;  
}  

IplImage* binary::Grayscale(void)
{
  IplImage* GrayImg =  cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
  cvCvtColor(src, GrayImg, CV_BGR2GRAY);
  cvShowImage("gray", src);
  cvWaitKey(0);
  cvSaveImage("/root/for_test/GrayImg.jpg",GrayImg,0);
  src = GrayImg;
  return GrayImg;
}


IplImage* binary::Binarization(int pos, IplImage* GrayImg) 
{
  IplImage *g_pBinaryImage = NULL;
  const char *name = "二值图";
  // creat image
  cout<<cvGetSize(GrayImg).width<<"   "<<cvGetSize(GrayImg).height<<endl;
  g_pBinaryImage = cvCreateImage(cvGetSize(GrayImg), IPL_DEPTH_8U, 1);
  cvThreshold(GrayImg, g_pBinaryImage, pos, 255, CV_THRESH_BINARY);
  cvShowImage(name, g_pBinaryImage);
  cvWaitKey(0);
  cvSaveImage("/root/for_test/BinaImg.jpg",g_pBinaryImage,0);
  cvReleaseImage(&GrayImg);
  return g_pBinaryImage;
}

int binary::GetThreshold(void)
{
  //获取gray值计数以及每个值所占百分比
  int gray_count[255]={0};
  double gray_probility[255]={0};
  int best_threshold;
  uchar gray;

  for(int i=0; i<src->width; i++)
  {
    for(int j=0; j<src->height; j++) 
    {
      gray = (uchar)(int)src->imageData[j*src->width + i];
      gray_count[gray]++;
    }
  }

  double he;
  for(int j=0; j<255; j++)
  {
    // gray_probility[j] = gray_count[j]/(640*480);
    gray_probility[j] = (double)gray_count[j]/640/480;
    he+=gray_probility[j];
  }
  cout<<"he:"<<he<<endl;

  best_threshold = Adaptive_threshold(gray_count, gray_probility);
  cout<<best_threshold<<endl;
  return best_threshold;
}

// typedef struct adaptive_threshold_need
// {
//   int threshold;
//   float class_distance;
//   float class_probility1;
//   float class_probility2;
//   float divergence1;
//   float divergence2;
//   float goal;
// }ATN;

int binary::Adaptive_threshold(int* gray_count, double* gray_probility)
{
    double class_center1 = 0;     //分开后  前景像素点的平均灰度
    double class_center2 = 0;     //分开后  后景像素点的平均灰度
    double class_distance = 0;
    double class_probility1 = 0;  //分开后  前景像素点数占图像的比例
    double class_probility2 = 0;  //分开后  后景像素点数占图像的比例
    double divergence1 = 0;
    double divergence2 = 0;
    double goal = 0;
    double max_goal = 0;
    double average_gray = 0;      //图像总平均灰度
    int best_threshold;

    for(int j=0; j<255; j++)
    {
      for(int i=0; i<j-1; i++)
      {
        class_probility1 += gray_probility[i];
        class_center1 += gray_count[i]*gray_probility[i];
      }
      for(int i=j; i<255; i++)
      {
        class_probility2 += gray_probility[i];
        class_center2 += gray_count[i]*gray_probility[i];
      }
      class_center1 /= class_probility1;
      class_center2 /= class_probility2;  
      
      //new_add
      class_distance = fabs(class_center1 - class_center2);
      average_gray = class_probility1 * class_center1 + class_probility2 * class_center2;

      goal = class_probility1 * (class_center1 - average_gray) + class_probility2 * (class_center2 - average_gray) * (class_center2 - average_gray);
      // for(int i=0; i<j-1; i++)
      // {
      //   divergence1 += fabs(j - class_center1) * gray_count[j] / gray_probility[j] / class_probility1;
      // }
      // for(int i=j; i<255; i++)
      // {
      //   divergence2 += fabs(j - class_center2) * gray_count[j] / gray_probility[j] / class_probility2;
      // }
      // goal = (class_probility1*class_probility2*class_distance)/((class_probility1*divergence1)+(class_probility2*divergence2));

      cout<<"goal:"<<goal<<endl;

      if(goal >= max_goal)
      {
        max_goal = goal;
        best_threshold = j;
      }

      class_center1 = 0;
      class_center2 = 0;
      class_distance = 0;
      class_probility1 = 0;
      class_probility2 = 0;
      divergence1 = 0;
      divergence2 = 0;
      goal = 0;
    }
    return best_threshold-33;
}

//Frequency histogram of gray level images
IplImage* binary::Histogram(IplImage * gray_dst)  
{  
  //一维维数
  int dims= 1;
  //直方图的尺寸
  int size= 256;
  //直方图的高度
  int height = 256;
  //灰度图的范围0到255
  float range[]= {0, 256};
  float *ranges[]= {range}; 
    
  //创建一维直方图
  CvHistogram* hist;
  hist= cvCreateHist(dims, &size, CV_HIST_ARRAY, ranges, 1);      

  //计算灰度图的一维直方图
  cvCalcHist(&gray_dst, hist, 0, 0);
    //归一化直方图
  cvNormalizeHist(hist, 1.0);
  int scale= 2;
  //创建图像，用于显示直方图
  IplImage* hist_img= cvCreateImage(cvSize(size* scale, height), 8, 1);
  //图像置零
  cvZero(hist_img);

  //计算直方图的最大方块值,初始化为0
  float max_value= 0;
  cvGetMinMaxHistValue(hist, 0, &max_value, 0, 0);

   //绘制直方图
  for(int i=0; i<size; i++)
  {
    float bin_val= cvQueryHistValue_1D(hist,i);   //像素i的概率
    int intensity = cvRound(bin_val* height/ max_value);  // 绘制的高度
    cvRectangle(hist_img,
                cvPoint(i* scale, height- 1),
                cvPoint((i+1)* scale- 1, height- intensity),
                CV_RGB(255, 255, 255));
   }

  cvNamedWindow("Histogram");
  cvShowImage("Histogram", hist_img);
  cvSaveImage("/root/for_test/HistImg.jpg",hist_img,0);
  cvWaitKey(0);

  // cvReleaseImage(&src);
  cvReleaseImage(&gray_dst);
  cvReleaseImage(&hist_img);

  cvDestroyWindow("gray");
  cvDestroyWindow("Histogram");

  return 0;
}


IplImage* binary::GetPos(IplImage* gray_dst) 
{
  uchar ImgData;
  // get the cout of index 
  int grayvalue[256] = {0};
  for(int i = 0; i < gray_dst->height; i++)
  {
    for(int j = 0; j < gray_dst->width; j++) 
    {
      ImgData = gray_dst->imageData[i*gray_dst->height+j];
      grayvalue[(int)ImgData] += 1;
    }
  }
  int pro_mean,temp_pro_mean; // probility mean value
  int open = 1;               // skip pix high which value is low
  int min_n;                  // record the index of the min_pos
  for(int n = 255; n-3 > 20; n--)
  {
    pro_mean = grayvalue[n] + grayvalue[n-1] + grayvalue[n-2];
    pro_mean /= 3;

    if(open = 1)
    {
      if(pro_mean >= 1000)
      {
        open = 0;
        min_n = n;
      }
    }
    else
    {
      if(pro_mean <= temp_pro_mean)
      {
        min_n = n;
      }
    }
    temp_pro_mean = pro_mean;
  }
  cout<<"the best threshold is "<<min_n;

  IplImage *g_pBinaryImage = NULL;
  const char *pstrWindowsBinaryTitle = "二值图";
  // creat image
  g_pBinaryImage = cvCreateImage(cvGetSize(gray_dst), IPL_DEPTH_8U, 1);
  // 对单通道数组应用固定阈值操作。该函数的典型应用是对灰度图像进行阈值操作得到二值图像
  cvThreshold(gray_dst, g_pBinaryImage, min_n+25, 255, CV_THRESH_BINARY);
  cvShowImage(pstrWindowsBinaryTitle, g_pBinaryImage);
  cvWaitKey(0);
  cvSaveImage("/root/for_test/BinaImg.jpg",g_pBinaryImage,0);
  cvReleaseImage(&gray_dst);
  return g_pBinaryImage;
} 

