#include <fstream>
#include <string.h>
#include <malloc.h>
#include <iostream>
#include "point.h"
#include "math.h"
#define pi 3.141592657
using namespace std;

Arm_point::Arm_point(void)
{
	self.len = 80;
	self.pen = 20;
	self.bot = 50;
}

float radians(float angle)
{
	return angle/180*pi;
}
void Arm_point::update(float alpha, float beta)
{	
	self.alpha = radians(alpha);
	self.beta = radians(beta);
	// printf("%f\n",alpha);
	// printf("%f\n",self.alpha);
	if(alpha != 90)
	{ 	
		self.cos_alpha = cos(self.alpha);
		self.sin_alpha = sin(self.alpha);
	}
	else
	{
		self.cos_alpha = 0;
		self.sin_alpha = 1;
	}
	if(beta != 90)
	{
		self.cos_beta = cos(self.beta);
		self.sin_beta = sin(self.beta);
	}
	else
	{
		self.cos_beta = 0;
		self.sin_beta = 1;
	}
	self.a_x = self.cos_alpha * self.len;
	self.a_y = self.sin_alpha * self.len - self.len;
	self.b_x = self.cos_beta * self.len + self.bot;
	self.b_y = self.sin_beta * self.len - self.len;
	// printf("a_x:%f\na_y:%f\nb_x:%f\nb_y:%f\n",self.a_x,self.a_y,self.b_x,self.b_y);
	self.len_ab = dis(self.a_x,self.a_y,self.b_x,self.b_y);
	// printf("cos_beta:%f\nsin_beta:%f\n",self.cos_beta,self.sin_beta);
	// printf("cos_alpha:%f\n",self.cos_alpha);
	// printf("sin_alpha:%f\n",self.alpha);
	// printf("len_ab:%f \n",self.len_ab);
	// b_x:%f\nb_y:%f\n  ,self.b_x,self.b_y
}

float Arm_point::dis(float x1, float y1, float x2, float y2)
{
	 float a,b,c;
	c = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	// printf("a:%f\nb:%f\n",a,b);
	// printf("x1:%f\ny1:%f\nx2:%f\ny2:%f\n",x1,y1,x2,y2);

	// def dis(self,x1,y1,x2,y2):
	// 	a = (y2 - y1)*(y2 - y1)
	// 	b = (x2 - x1)*(x2 - x1)
	// 	c = sqrt(a+b)	
	// printf("c:%f\n",c);
	return c;
}
Error Arm_point::ErrorTest(void)
{
	Error statu;
	int angle_a,angle_b;
	// printf("self.len_ab:%f    ",self.len_ab);
	if(self.len_ab >= 2*self.len)
	{
		// printf("11111111\n");
		statu = StretchOver;
		return statu;
	}
	// printf("fabs(self.alpha-self.beta):%f    ",fabs(self.alpha-self.beta));
	if(fabs(self.alpha-self.beta) >= radians(100))
	{
		// printf("222222222\n");
		statu = StretchOver;
		return statu;
	}
	angle_a = (pi - self.alpha)/pi*180 + acos(self.len_ab/2/self.len)/pi*180;
	angle_b = (pi -  self.beta)/pi*180 + acos(self.len_ab/2/self.len)/pi*180;
	
	// printf("self.b_x:%f    self.a_x:%f    ",self.b_x,self.a_x);
	if(self.len_ab <= 25 || self.b_x <= self.a_x)
	{
		// printf("33333333333\n");
		statu = ContractOver;
		return statu;
	}
	// printf("angle_a:%f    angle_b:%f    ",angle_a,angle_b);
	// printf("\n");
	if(angle_a >= 180 || angle_b >= 180)
	{
		// printf("444444444444\n");
		statu = ContractOver;
		return statu;
	}
	
	// printf("555555555555\n");
	statu = NOError;
	return statu;
	
}


struct Point Arm_point::first_conver(void)
{
	struct Point point;

	point.x = self.len_ab/2;
	point.y = sqrt(self.len*self.len-(self.len_ab/2)*(self.len_ab/2)/4);
	return point;
}

struct Point Arm_point::second_conver(struct Point point)
{
	float x_temp,y_temp;
	float radians;
	if(self.a_y != self.b_y)
	{
		radians = atan((self.b_y - self.a_y)/(self.b_x - self.a_x));
	}
	else
	{
		radians = 0;
	}

	x_temp = point.x;
	y_temp = point.y;
	point.x = x_temp*cos(radians) - y_temp*sin(radians);
	point.y = x_temp*sin(radians) + y_temp*cos(radians);

	return point;
}

struct Point Arm_point::third_conver(struct Point point)
{		
	point.x += self.a_x;
	point.y += self.a_y;
	return point;
}

struct Point Arm_point::fourth_conver(struct Point point)
{
	float sin_a,cos_a;
	sin_a = (self.a_y - self.b_y)/self.len_ab;
	cos_a = (self.b_x - self.a_x)/self.len_ab;
	point.x += self.pen * sin_a;
	point.y += self.pen * cos_a;
	
	return point;
}

