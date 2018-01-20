#include "/root/Codes/robot/arm/photo/include/includes.h"

#define SET_ROW_START()\
		row_start.x = j;\
		row_start.y = i;\
		row_line_sign = 1;\

#define SET_ROW_END()\
		row_end.x = j;\
		row_end.y = i;\
		row_line_sign = 0;

#define ROW_PUSH_POINT()\
		row_one_line.start = row_start;\
		row_one_line.end = row_end;\
		row_lines.push_back(row_one_line);\
		row_line_count += 1;

#define SET_LIST_START()\
		list_start.x = j;\
		list_start.y = i;\
		list_line_sign = 1;\

#define SET_LIST_END()\
		list_end.x = j;\
		list_end.y = i;\
		list_line_sign = 0;

#define LIST_PUSH_POINT()\
		list_one_line.start = list_start;\
		list_one_line.end = list_end;\
		list_lines.push_back(list_one_line);\
		list_line_count += 1;

#define SET_MIDDLE()\
		middle.x = j;\
		middle.y = i;\
		middle_points.push_back(middle);\
		middle_cout += 1;

#define SET_SINGLE()\
		single.x = j;\
		single.y = i;\
		single_points.push_back(single);\
		single_cout += 1;

#define GET_NEIG()\
		px1 = (int)(uchar)src->imageData[_width*(i-1) + j-1];  
		px2 = (int)(uchar)src->imageData[_width*(i-1) + j];  
		px3 = (int)(uchar)src->imageData[_width*(i-1) + j+1];  
		px4 = (int)(uchar)src->imageData[_width*i + j-1];  
		px5 = (int)(uchar)src->imageData[_width*i + j+1];  
		px6 = (int)(uchar)src->imageData[_width*(i+1) + j-1];  
		px7 = (int)(uchar)src->imageData[_width*(i+1) + j];  
		px8 = (int)(uchar)src->imageData[_width*(i+1) + j+1];  
using namespace std;

Edge::Edge(IplImage* _src)
{
	src = _src;
    _width = src->width;
	_height = src->height;
}

std::vector<Black_line> row_lines;
std::vector<Black_line> list_lines;
int Edge::sweep(void)
{
	int px,px_pre,px_next,px_pre_2,px_next_2;
	int row_line_sign,row_line_count,list_line_sign,list_line_count,middle_cout,single_cout;
	Black_line row_one_line,list_one_line;
	struct Point row_start,row_end,list_start,list_end,single,middle;
	std::vector<struct Point> row_start_points,list_start_points;
	std::vector<struct Point> row_end_points,list_end_points;
	std::vector<struct Point> middle_points;
	std::vector<struct Point> single_points;
	for(int i=0; i<_height; i++)
	{
		for(int j=0; j<_width; j++)
		{
			px = src->imageData[_width*i + j];
			if((int)(uchar)px == BLACK)
			{
				if(j <= 1 || j >= _width-2)
					src->imageData[j + _width*i] = 0xff;

				else if(j >= 2 && j <= _width-3)
				{
					px_pre_2  = (int)(uchar)src->imageData[_width*i + j-2];  
					px_pre    = (int)(uchar)src->imageData[_width*i + j-1];
					px_next   = (int)(uchar)src->imageData[_width*i + j+1];
					px_next_2 = (int)(uchar)src->imageData[_width*i + j+2];
					if(px_pre == 255 && px_next == 0)
					{
						if(px_next_2 == 0)
						{
							SET_ROW_START();
						}	
					}
					else if(px_pre == 0 && px_next == 255)
					{
						if(row_line_sign == 1)
						{
							if(px_pre_2 == 0)
							{
								SET_ROW_END();
								ROW_PUSH_POINT();
							}
						}
					}
					else if(px_pre == 0 && px_next == 0)
					{
						SET_MIDDLE();
					}
					else if(px_pre == 255 && px_next == 255)
					{
						SET_SINGLE();					
					}
				}
			}
		}
	}
	for(int j=0; j<_width; j++)
	{
		for(int i=0; i<_height; i++)
		{
			px = src->imageData[_width*i + j];
			if((int)(uchar)px == 0)
			{
				if(i <= 1 || i >= _height-2)
				{	
					px = src->imageData[_width*i + j];
				}
				else if(i >= 2 && i <= _height-3)
				{
					px_pre_2  = (int)(uchar)src->imageData[_width*(i-2) + j];  
					px_pre    = (int)(uchar)src->imageData[_width*(i-1) + j];
					px_next   = (int)(uchar)src->imageData[_width*(i+1) + j];
					px_next_2 = (int)(uchar)src->imageData[_width*(i+2) + j];
					if(px_pre == 255 && px_next == 0)
					{
						if(px_next_2 == 0)
						{
							SET_LIST_START();
						}	
					}
					else if(px_pre == 0 && px_next == 255)
					{
						if(list_line_sign == 1)
						{
							if(px_pre_2 == 0)
							{
								SET_LIST_END();
								LIST_PUSH_POINT();
							}
						}
					}
					else if(px_pre == 0 && px_next == 0)
					{
						SET_MIDDLE();
					}
					else if(px_pre == 255 && px_next == 255)
					{
						SET_SINGLE();					
					}
				}
			}
		}
	}
}

IplImage* Edge::paint(void)
{
	struct Point start, end;
	cout<<"list_lines:"<<list_lines.size()<<endl;
	for(int i=0; i < list_lines.size(); i++)
	{
		// cout<<row_templet(list_lines[i])<<endl;
		if(row_templet(list_lines[i]))
		{
			src->imageData[list_lines[i].start.x + _width*list_lines[i].start.y] = 0xff;
			src->imageData[list_lines[i].end.x + _width*list_lines[i].end.y] = 0xff;
		}
	}
	for(int j=0; j < row_lines.size(); j++)
	{
		// cout<<row_templet(list_lines[j])<<endl;
		if(list_templet(row_lines[j]))
		{
			src->imageData[row_lines[j].start.x + _width*row_lines[j].start.y] = 0xff;
			src->imageData[row_lines[j].end.x + _width*row_lines[j].end.y] = 0xff;
		}
	}
	cvSaveImage("/root/for_test/EdgeImg.jpg",src,0);
	return src;
}

//use to row scan
int Edge::list_templet(Black_line line)
{
	int px_f,px_b,px_ff,px_bb;
	int single_point_in_row = 1;
	for(int i=line.start.x; i<line.end.x; i++)
	{
		px_ff = (int)(uchar)src->imageData[i + _width*(line.end.y-2)];
		px_f  = (int)(uchar)src->imageData[i + _width*(line.end.y-1)];
		px_b  = (int)(uchar)src->imageData[i + _width*(line.end.y+1)];
		px_bb = (int)(uchar)src->imageData[i + _width*(line.end.y+2)];	
		if(px_ff == 255 && px_bb == 255 && px_f + px_b >= 255)
			single_point_in_row = 1;
		else
		{
			single_point_in_row = 0;
			break;
		}
	}
	if(single_point_in_row == 1)
		return 0; // this line's start and end point can not be cleared
	else
		return 1; // this line's start and end point can be cleared
}

//use to list scan
int Edge::row_templet(Black_line line)
{

	int px_l,px_r,px_ll,px_rr;
	int single_point_in_list = 1;
	for(int i=line.start.y; i<line.end.y; i++)
	{
		cout<<"line.start.x:"<<line.start.x<<endl;
		px_ll = (int)(uchar)src->imageData[(line.start.x-2) + _width*i];
		px_l  = (int)(uchar)src->imageData[(line.start.x-1) + _width*i];
		px_r  = (int)(uchar)src->imageData[(line.start.x+1) + _width*i];
		px_rr = (int)(uchar)src->imageData[(line.start.x+2) + _width*i];	
		if(px_ll == 255 && px_rr == 255 && px_l + px_r >= 255)
			single_point_in_list = 1;
		else
		{
			single_point_in_list = 0;
			break;
		}
	}
	if(single_point_in_list == 1)
		return 0; // this line's start and end point can not be cleared
	else
		return 1; // this line's start and end point can be cleared
}

int Edge::Reconnect(struct Point center)
{
	vector<struct Point> balck_neigh;
	vector<struct Point> neigh;
	struct Point neigh_index;
	
	if(IsSignle(center))
	{
		black_neigh = Neigh_detect(5,center);
		if(IsContinue(black_neigh))
		{
			
		}
	}
	balck_neigh = Neigh_detect(center, neigh);
}
