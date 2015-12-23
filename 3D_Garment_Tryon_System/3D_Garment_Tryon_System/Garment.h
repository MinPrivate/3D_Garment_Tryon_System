/***************************
	类名	Garment
	作者	喻斌强
	作用	弹簧类
	日期	10.06.2012
*****************************/



#pragma once

////////////////////////////////////////
//		注意需要添加类
//#include "Seam.h"
#include "Cloth.h"

#include "NetGrid.h"


class Garment
{
public:
	/**构造函数*/
	Garment(void);
	/**析构函数*/
	~Garment(void);
	/**迭代控制次数*/
	void numIteration(int number,NetGrid * netGrid);
	void CollisonIteration(NetGrid * netGrid);
		/**所有衣片*/
	vector<Cloth> allCloth;
	/**读取函数  写入所有的读取函数 一次调用*/
	bool garmentRead();
	private:
	/**为所有的质点添加弹簧*/
	void setSpringAll();
	/**缝合是否结束*/
	bool isOverSeam();
	/**检查碰撞*/
	bool collision(NetGrid * netGrid);
	/**迭代函数*/
	bool Iteration(NetGrid * netGrid);
	/**读入缝*/
	bool readSeam(char * loc);
	/**读取衣片  目前是直接写入*/
	bool readCloth(char * loc);
};