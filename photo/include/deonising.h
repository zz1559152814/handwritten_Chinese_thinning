#ifndef THIN_H__
#define THIN_H__
#include <vector>

struct Point 
{
	int x;
	int y;
};
class Deonising
{
public:
	Deonising(IplImage* Img);
	int _width;
	int _height;
	int extract_point(struct Point elem);
	int update(IplImage* Img);
	int show(void);
	IplImage* smooth(void);
	IplImage* deonise(void);

private:
	IplImage* _src;
};

extern std::vector<struct Point> b_to_w;
extern std::vector<struct Point> w_to_b;
#endif