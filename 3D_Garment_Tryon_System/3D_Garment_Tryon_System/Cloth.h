/***************************
	类名	cloth
	作者	喻斌强
	作用	衣片的类
	日期	10.04.2012
*****************************/



#pragma once


//////////////////////////////////////////
//		注意	需要引入类
#include "Mass.h" 
//#include "BoxCloth.h"

//#include <vector>
//using namespace std;


class Cloth
{
public:
	/**构造函数*/
	Cloth(void);
//	/**根据衣片类型 获取衣片*/
//	Cloth(int _clothflag);
	/**析构函数*/
	~Cloth(void);
	/**读取衣片*/
	bool readClothFile(int loc);
	/**获取衣服的质点集合*/
	vector<Mass*> * getVectorMass();
	/**缝合点*/
	vector<Mass*> massSeam;
	/**缝合点*/
	vector<Mass*> massSeam1;
	/**衣片存放的质点集合*/
	vector<Mass*> massCloth;
private:
	//标志位
	int clothflag;
};

