/***************************
	类名	Mass
	作者	喻斌强
	作用	弹簧类
	日期	10.05.2012
	注意	使用时，设置缝合力
			然后在changeAll（）完成改变
*****************************/

#pragma once

////////////////////////////////////////
//		注意需要添加类

//#include "Force.h"
#include "Velocity.h"

#include <vector>
using namespace std;

#include "Spring.h"
class Spring;


class Mass
{
public:
	/**构造函数 默认坐标为0，0，0 另外调用setSeamGorce()设置缝合力*/
	Mass(void);
	/**构造函数 传入坐标另外调用setSeamGorce()设置缝合力*/
	Mass(float _x,float _y,float _z);
	/**完成所有改变*/
	void changeAll();
	/**改变位置*/
	void changeLocation();
	/**析构函数*/
	~Mass(void);
	//指点坐标x
	float x;
	//指点坐标y
	float y;
	//指点坐标z
	float z;
	/**设置缝合点*/
	void setSeamPoint(Mass * _seamMassPoint);
	/**缝合点*/
	Mass * seamMassPoint;
	/**弹簧集合*/
	vector<Spring*> massSpring;
	/**缝合力*/
	Force seamForce;
	void resetVelocity();
//private:
	/**设置弹缝合力*/
	void computeSeamForce();
	/**计算合力*/
	void computeAllForce();
	/**计算弹簧合力*/
	void computeSpringForce();
	/**计算速度*/
	void changeVelocity();


	/**重力*/
	Force galavity;
	/**弹簧合力*/
	Force springForce;
	/**合力*/
	Force allForce;
	/**速度集合*/
	Velocity massSpeed;
};