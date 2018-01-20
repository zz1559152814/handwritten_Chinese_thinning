#include <opencv2/opencv.hpp>
#include <stdio.h>  
#include <sys/stat.h>  
#include <sys/types.h>  
#include <sys/timeb.h>  
#include <stdlib.h>  
#include <cv.h>  
#include "deonising.h"
#include <vector>
typedef struct black_line
{
	struct Point start;
	struct Point end;
}Black_line;

class Edge
{
public:
	Edge(IplImage* _src);
	int _width;
	int _height;
	int sweep(void);
	IplImage* paint(void);
	int list_templet(Black_line line);
	int row_templet(Black_line line);

private:
	IplImage* src;

};

extern std::vector<Black_line> row_lines;
extern std::vector<Black_line> list_lines;
