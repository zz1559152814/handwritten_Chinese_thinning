from sys import *
# from numpy import *
# from point import *
from atp.point import *

def single(a,b):
	arm = Arm_point(a,b)
	if arm.ErrorTest() == 0:
		print 111111
	else:
		print arm.ErrorTest()
	one = arm.first_conver()
	two = arm.second_conver(one)
	print arm.third_conver(two)

	# db_data = dict(alpha=0,beta=0,real_x=0,real_y=0)
	# init()
	# delete_table()
	# create_table()
def all():
	alpha = 0
	beta = 0
	id = 0
	all_data = []
	point_x = []
	point_y = []
	# mat = zeros((500,500),dtype=int8)
	while(alpha<=180):
		while(beta<=180):
			arm = Arm_point(alpha,beta)		
			if arm.ErrorTest() == 0:
				one = arm.first_conver()
				two = arm.second_conver(one)
				three = arm.third_conver(two)
				four = arm.fourth_conver(three)
				# db_data['id'] = id
				# db_data['alpha'] = alpha
				# db_data['beta'] = beta
				# db_data['real_x'] = three[0]
				# db_data['real_y'] = three[1]
				# all_data.append(db_data)	
				point_x.append(four[0])
				point_y.append(four[1])
				print four[0],'   ',four[1]
			beta = beta + 1
		beta = 0
		alpha = alpha + 1
	# point_x.sort()
	# point_y.sort()
	# # print id
	# # print mat
	# min_x = point_x[0]
	# max_x = point_x[-1]
	# min_y = point_y[0]
	# max_y = point_y[-1]
	# range_x = max_x - min_x
	# range_y = max_y - min_y
	# range = max(range_x,range_y)
	# print 

all()
