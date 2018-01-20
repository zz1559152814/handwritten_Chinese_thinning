#include "/root/Codes/robot/arm/photo/include/includes.h"
using namespace std;

std::vector<struct Point> b_to_w;
std::vector<struct Point> w_to_b;

Deonising::Deonising(IplImage* Img)
{
	_src = Img;
	_width = Img->width;
	_height = Img->height;
}

int Deonising::update(IplImage* Img)
{
	_src = Img;
	_width = Img->width;
	_height = Img->height;
}

IplImage* Deonising::deonise(void)
{
	struct Point elem;
  	int i,j;
  	IplImage* DeonImg;
	cout<<"height:"<<_height<<"   "<<"width:"<<_width<<endl;
	for(int m=0; m<10; m++)
	{
		for(i=0; i<_height; i++)
		{
			for(j=0; j<_width; j++)	
			{
				elem.x = j;
				elem.y = i;
				extract_point(elem);
			}	
		}
		smooth();
		update(_src);
	}
	cout<<"deonising over......"<<endl;
	return _src;
	// show();
}

int Deonising::extract_point(struct Point elem)
{
	struct Point b_w;
	struct Point w_b;
	int px;
	int elem_nei[8]; 
	int elem_neih;
	if(elem.x == 0 || elem.y == 0 || elem.x == _width-1 || elem.y == _height-1)
		// _src->imageData[_width*elem.y + elem.x] = 0;
		return 1;
	elem_nei[0] = (int)(uchar)_src->imageData[_width*(elem.y-1) + elem.x-1]; 
	elem_nei[1] = (int)(uchar)_src->imageData[_width*(elem.y-1) + elem.x];
	elem_nei[2] = (int)(uchar)_src->imageData[_width*(elem.y-1) + elem.x+1];
	elem_nei[3] = (int)(uchar)_src->imageData[_width*elem.y + elem.x - 1];
	elem_nei[4] = (int)(uchar)_src->imageData[_width*elem.y + elem.x + 1];
	elem_nei[5] = (int)(uchar)_src->imageData[_width*(elem.y+1) + elem.x - 1];
	elem_nei[6] = (int)(uchar)_src->imageData[_width*(elem.y+1) + elem.x];
	elem_nei[7] = (int)(uchar)_src->imageData[_width*(elem.y+1) + elem.x+1];

	px = _src->imageData[_width*elem.y + elem.x];
	if((int)(uchar)px == 255)
		px = 1;

	if((int)(uchar)px == 1)
	{
		if(elem_nei[1] + elem_nei[3] + elem_nei[4] + elem_nei[6] <= 1)
		{	
			w_b.x = elem.x;
			w_b.y = elem.y;
			w_to_b.push_back(w_b);
			return 1;
		}
	}
	else if((int)(uchar)px == 0)
	{

		for(int i=0; i < 8; i++)
		{
			elem_neih += elem_nei[i];
		}

		if(elem_neih == 7*255)
		{
			b_w.x = elem.x;
			b_w.y = elem.y;
			b_to_w.push_back(b_w);
			return 1;
		}
		else 
		{
			if(elem_nei[0] == 255 && elem_nei[1] == 255 && elem_nei[2] == 255 && elem_nei[3] == 255 && elem_nei[4] == 255)
			{
				b_w.x = elem.x;
				b_w.y = elem.y;
				b_to_w.push_back(b_w);
				return 1;	
			}
			else if(elem_nei[1] == 255 && elem_nei[2] == 255 && elem_nei[4] == 255 && elem_nei[6] == 255 && elem_nei[7] == 255)
			{
				b_w.x = elem.x;
				b_w.y = elem.y;
				b_to_w.push_back(b_w);
				return 1;
			}
			else if(elem_nei[3] == 255 && elem_nei[4] == 255 && elem_nei[5] == 255 && elem_nei[6] == 255 && elem_nei[7] == 255)
			{
				b_w.x = elem.x;
				b_w.y = elem.y;
				b_to_w.push_back(b_w);
				return 1;
			}
			else if(elem_nei[0] == 255 && elem_nei[1] == 255 && elem_nei[3] == 255 && elem_nei[5] == 255 && elem_nei[6] == 255)
			{
				b_w.x = elem.x;
				b_w.y = elem.y;
				b_to_w.push_back(b_w);
				return 1;
			}
		}
	}
	return 1;
}
IplImage* Deonising::smooth(void)
{
	int x,y;
	int size1,size2;
	size1 = b_to_w.size();
	size2 = w_to_b.size();
	// _width = _src->width;
	// _height = _src->height;
	cout<<"size1:"<<size1<<endl;
	cout<<"size2:"<<size2<<endl;
	for(int i=0; i < size1; i++)
	{
		x = b_to_w[i].x;
		y = b_to_w[i].y;
		cout<<"_width:"<<_width<<endl;
		cout<<"imageData[_width*y + x]:"<<(int)(uchar)(int)_src->imageData[_width*y + x]<<endl;
		_src->imageData[_width*y + x] = (uchar)255;
	}
	for(int j=0; j < size2; j++)
	{
		x = w_to_b[j].x;
		y = w_to_b[j].y;
		_src->imageData[_width*y + x] = (uchar)0;		
	}
	return _src;
}

int Deonising::show(void)
{
	cvShowImage("after denoising", _src);
	cvSaveImage("/root/for_test/deonising.jpg",_src,0);
	cvReleaseImage(&_src);
    cvWaitKey(0);
	return 1;
}