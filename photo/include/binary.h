#ifndef A_H__
#define A_H__

class binary
{
public:
	int take_photo(); 
	int GetThreshold(void);
	IplImage* Grayscale(void);
	IplImage* Histogram(IplImage * src);
	IplImage* GetPos(IplImage* gray_dst);
	IplImage* Binarization(int pos, IplImage* GrayImg);
	int Adaptive_threshold(int* gray_count, double* gray_probility);

private:
	IplImage* src;
};
#endif