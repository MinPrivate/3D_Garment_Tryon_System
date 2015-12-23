/***************************
	类名	Spring
	作者	喻斌强
	作用	弹簧类
	日期	10.05.2012
*****************************/

#pragma once


////////////////////////////////////////
//		注意需要添加类
#include "Force.h"

#include "Mass.h"

//定义结构弹簧原长
#define STRUCTLENGTH 1.8f       //要改cloth 的网格大小

class Mass;



class Spring
{
public:
	/**构造函数*/
	Spring(Mass * _current);
	/**重载构造函数	赋予弹簧种类 1 2 3*/
	Spring(int _kind,Mass * _current);
	/**设置弹簧相连的点*/
	void setConnectedMass(Mass * _ConnectedMass);
	/**获得相连的点指针*/
	Mass * getConnectedMass();
	/**获取弹性系数*/
	float getFactor();
	/**获取当前弹簧力*/
	Force getForce();
	/**析构函数*/
	~Spring(void);
	int getkind();
	/**弹性系数*/
	float kFactor;
	/**获取弹簧长度*/
	float getLength();
private:
	//void init();
	/**计算弹簧当前的弹性系数   需要是在写*/
	float computeFactor();
	/**弹簧种类 	1拉升弹簧 2 剪切弹簧 3 弯曲弹簧*/
	int kind;
	/**弹簧现在长度	*/
	float length;
	/**弹簧现在长度	*/
	float nowlength;
	
	/**当前点的地址*/
	Mass * currentMass;
	/**相连点的地址*/
	Mass * connectedMass;
};
