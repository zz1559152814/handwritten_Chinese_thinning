# import MySQLdb
from math import *
from db import *
from sys import *
# from numpy import *

sin_beta = sin_alpha = 0
cos_beta = cos_alpha = 0

def enum(**enums):
    return type('Enum', (), enums)

def my_radians(angle):
	return radians(angle)

class Arm_point():
	def __init__(self,alpha,beta):
		self.alpha = my_radians(alpha)
		self.beta = my_radians(beta)
		self.len = 80;             
		self.pen = 20;             
		self.bot = 50;
		# print alpha
		# print self.alpha
		if alpha != 90:
			self.cos_alpha = cos(self.alpha)
			# print self.cos_alpha
			self.sin_alpha = sin(self.alpha)
		else:
			self.cos_alpha = 0
			self.sin_alpha = 1

		if beta != 90:
			self.cos_beta = cos(self.beta)
			self.sin_beta = sin(self.beta)
		else:
			self.cos_beta = 0
			self.sin_beta = 1
		
		self.a_x = self.cos_alpha * self.len
		self.a_y = self.sin_alpha * self.len - self.len
		self.b_x = self.cos_beta * self.len + self.bot
		self.b_y = self.sin_beta * self.len - self.len
		# print 'a_x:',self.a_x
		# print 'a_y:',self.a_y
		# print 'b_x:',self.b_x
		# print 'b_y:',self.b_y
		self.len_ab = self.dis(self.a_x,self.a_y,self.b_x,self.b_y)
		self.statu = enum(NOError=0, StretchOver=1, ContractOver=2)
		# print 'cos_beta:',self.cos_beta
		# print 'sin_beta:',self.sin_beta
		# print 'len_ab:',self.len_ab

	def	ErrorTest(self):	
		if self.len_ab >= 2*self.len:
			# print 111111111
			return self.statu.StretchOver
		
		if abs(self.alpha-self.beta) >= my_radians(100):
			# print 222222222
			return self.statu.StretchOver

		angle_a = (pi - self.alpha)/pi*180 + acos(self.len_ab/2/self.len)/pi*180
		angle_b = (pi -  self.beta)/pi*180 + acos(self.len_ab/2/self.len)/pi*180		

		# print angle_a_temp
		if self.len_ab <= 25 or self.b_x <= self.a_x:
			# print 3333333333333
			return self.statu.ContractOver

		if angle_a >= 180 or angle_b >= 180:
			# print 444444444444444
			return self.statu.ContractOver
		
		# print 55555555555
		return self.statu.NOError

	def dis(self,x1,y1,x2,y2):
		# a = (y2 - y1)*(y2 - y1)
		# b = (x2 - x1)*(x2 - x1)
		# c = sqrt(a+b)
		# print 'a:',a
		# print 'b:',b
		# print 'x1:',x1	
		# print 'y1:',y1
		# print 'x2:',x2	
		# print 'y2:',y2
		# print ((x1 - x2) ** 2 + (y1 - y2) ** 2) ** 0.5
		return ((x1 - x2) ** 2 + (y1 - y2) ** 2) ** 0.5

		# return c

	def first_conver(self):
		# a_x = self.cos_alpha * self.len
		# a_y = self.sin_alpha * self.len - self.len
		# b_x = self.cos_beta * self.len + self.bot
		# b_y = self.sin_beta * self.len - self.len

		# self.len_ab = self.dis(self.a_x,self.a_y,self.b_x,self.b_y)
		x = self.len_ab/2
		y = sqrt(self.len*self.len-(self.len_ab/2)*(self.len_ab/2)/4) 
		return (x,y)
	
	def second_conver(self,(x,y)):
		# a_x = self.cos_alpha * self.len
		# a_y = self.sin_alpha * self.len - self.len
		# b_x = self.cos_beta * self.len + self.bot
		# b_y = self.sin_beta * self.len - self.len

		if self.a_y != self.b_y:
			my_radians = atan((self.b_y-self.a_y)/(self.b_x-self.a_x))
		else:
			my_radians = 0

		x_temp = x
		y_temp = y
		x = x_temp*cos(my_radians) - y_temp*sin(my_radians)
		y = x_temp*sin(my_radians) + y_temp*cos(my_radians)

		return (x,y)

	def third_conver(self,(x,y)):
		a_x = self.cos_alpha * self.len
		a_y = self.sin_alpha * self.len - self.len
		
		x = x + a_x
		y = y + a_y
		d = sqrt(x*x+y*y)
		return (x,y)

	def fourth_conver(self,(x,y)):
		sin_a = (self.a_y - self.b_y)/self.len_ab
		cos_a = (self.b_x - self.a_x)/self.len_ab
		x = x + self.pen * sin_a
		y = y + self.pen * cos_a
		print x,'    ',y
		return (x,y)