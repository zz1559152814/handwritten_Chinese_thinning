#include "math.h"
#include <stdio.h>

using namespace std;

enum Error {NOError=0, StretchOver=1, ContractOver=2};
struct Private_data
{
	float alpha;
	float beta;
	int len;
	int pen;
	int bot;
	
	float cos_alpha;
	float sin_alpha;		
	float cos_beta;
	float sin_beta;
		
	float a_x;
	float a_y;
	float b_x;
	float b_y;
	float len_ab;
};
struct Point
{
	float x;
	float y;
};
class Arm_point
{
private:
	struct Private_data self;

public:
	Arm_point(void);
	void update(float alpha, float beta);
	Error ErrorTest(void);
	float dis(float x1, float y1, float x2, float y2);
	struct Point first_conver(void);
	struct Point second_conver(struct Point point);
	struct Point third_conver(struct Point point);
	struct Point fourth_conver(struct Point point);	
};

