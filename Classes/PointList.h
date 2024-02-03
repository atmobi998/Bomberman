#pragma once
#include "MyPoint.h"
using namespace std;
class PointList :public MyPoint
{
public:
	int len;
	int w;
	int h;
	static PointList* create(int _w,int _h);
	bool init(int _w, int _h);
	MyPoint *point;	
	void findPath(vector<vector<int>> a, int i1, int j1, int i2, int j2);
	int isInside(int i, int j);
private:
	vector<vector<double> > dadi;
	vector<vector<int>> dadj;
	vector<int>queuei;
	vector<int>queuej;	
};