#include "/root/Codes/robot/arm/photo/include/includes.h"


//detect the point in point set is it a continue unit
int DivUnit(vector<struct Point> point_set)
{
	//利用quick find方法来划分出不同的线条单元
	struct PointIndex
	{
		struct Point point;
		int index;		
	};

	//邻接表
	vector<vector<struct Point>> adjacency_list;
	vector<struct Point> edge;
	vector<struct Point>::iterator src_it;
	vector<struct Point>::iterator black_neigh_it;
	vector<struct Point> black_neigh;
	vector<struct PointIndex> AllPoint;
	struct PointIndex OnePoint;
	int count = 1;
	for(src_it = point_set.begin(); src_it != point_set.end(); src_it++)
	{
		//制作邻接表
		edge.push_back(*it);
		black_neigh = Neigh_detect(3,(*it));
		for(black_neigh_it = black_neigh.begin(); black_neigh_it != black_neigh.end(); black_neigh_it++)	
			edge.push_back(*black_neigh_it);
		adjacency_list.push_back(edge);

		//给每一个black point做标记,quick find初始化
		OnePoint.point = (*it);
		OnePoint.index = count;
		count++;
	}


}

int IsSignle(struct Point center)
{
	vector<struct Point> black_neigh;
	black_neigh = Neigh_detect(3,center);
	
	if(black_neigh.size() == 0)
		return NOTEXIST;
	else
		return EXIST;
}

//return the array of black point in the range about the center
vector<struct Point> Neigh_detect(int range, struct Point center)
{
	struct Point neigh_index;
	vector<struct Point> neigh;
	for(int i = -(range/2); i <= range/2; i++)
	{
		for(int j = -(range/2); j <= range/2; j++)
		{
			if(i != 0 && j != 0)
			{
				neigh_index.x = i;
				neigh_index.y = j;
			}
			neigh.push_back(neigh_index);
		}
	}

	vector<struct Point>::iterator it;
	vector<struct Point> black_neigh;
	int x,y;
	for(it = neigh.begin(); it!=neigh.end(); it++)
	{
		static int px;
		x = (*it).x+center.x;
		y = (*it).y+center.y;
		if(x >= 0 && x < _width && y >= 0 && y <= _height)
		{
			px = (uchar)(int)src->imageData[y*_width + x];
			if(px == 0)
				black_neigh.push_back((*it));
		}
	}
	return black_neigh;
}
