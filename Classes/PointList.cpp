#include "PointList.h"
#include "GameScene.h"
#include "common.h"
void PointList::findPath(vector<vector<int>> a, int i1, int j1, int i2, int j2)
{
	
	int u[] = { 1, 0, -1, 0 };
	int v[] = { 0, 1, 0, -1 };

	int fist = 0, last = 0;

	int x, y, xx, yy, i, j, k;
	
	this->len = 0;
	for (x = 0; x < w; x++)
	{ 
		for (y = 0; y < h; y++)
		{ 
		dadi[x][y]=-1;
		}		
	}
	queuei[0]=i2;
	queuej[0]=j2;
	dadi[i2][j2]=-2;

	while (fist <= last)
	{
		x = queuei[fist];
		y = queuej[fist];
		fist++;
		for (k = 0; k < 4; k++)
		{
			xx = x + u[k];
			yy = y + v[k];
			if (xx == i1 && yy == j1)
			{
				dadi[i1][j1]=x;
				dadj[i1][j1]=y;
				i = 0;
				while (1)
				{
					this->point[i].x = i1;
					this->point[i].y = j1;
					i++;
					k = i1;
					i1 = dadi[i1][j1];
					if (i1 == -2) break;
					j1 = dadj[k][j1];
				}
				this->len = i;
				
				return ;
			}

			if (!isInside(xx, yy)) continue;

			if (dadi[xx][yy]== -1 && ((a[xx][yy]== empty)))
			{
				last++;
				queuei[last]=xx;
				queuej[last]=yy;
				dadi[xx][yy]=x;
				dadj[xx][yy]=y;
			}
		}
	}	
	return ;
}
int PointList::isInside(int i, int j)
{
	return (i >= 0 && i < w && j >= 0 && j < h);
}

PointList* PointList::create(int _w,int _h)
{
	PointList * pointlist=new PointList();
	if (pointlist&&pointlist->init(_w,_h))
	{
		pointlist->autorelease();
		return pointlist;
	}
	CC_SAFE_DELETE(pointlist);
	return NULL;
}

bool PointList::init(int _w, int _h)
{
	bool bRet = false;
	do
	{
		point = MyPoint::create();		
		point->retain();
		w = _w;
		h = _h;			
		dadi.resize(w);
		for (int i = 0; i < w; ++i)
			dadi[i].resize(h);

		dadj.resize(w);
		for (int i = 0; i < w; ++i)
			dadj[i].resize(h);

		queuei.resize(h*w);
		queuej.resize(h*w);
		bRet = true;
	} while (0);
	return bRet;
}
