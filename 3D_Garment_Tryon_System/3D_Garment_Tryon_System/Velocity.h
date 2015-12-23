/***************************
	类名	Velocity
	作者	喻斌强
	作用	速度的类
	日期	10.04.2012
*****************************/

#pragma once
class Velocity
{
public:
	/**构造函数*/
	Velocity(void);
	/**重载构造函数	赋予力的方向 自动计算大小*/
	Velocity(float _x,float _y,float _z);
	/**重载力之间加法*/
	Velocity operator+(Velocity vel);
	/**重载力之间减法*/
	Velocity operator-(Velocity vel);
	/**获取x参数值*/
	float getX();
	/**获取y参数值*/
	float getY();
	/**获取z参数值*/
	float getZ();
	/**获取力的大小*/
	float getSpeed();
	/**设置x参数值*/
	void setX(float _x);
	/**设置y参数值*/
	void setY(float _y);
	/**设置z参数值*/
	void setZ(float _z);
	/**根据strength的值改变strength三方向的值*/
	void setSpeed(float _speed);
	/**析构函数*/
	~Velocity(void);
	//速度值
	float speed;
	//方向
	float x;
	float y;
	float z;
};

