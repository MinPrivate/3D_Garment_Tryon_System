
/***************************
	类名	Force
	作者	喻斌强
	作用	力的类
	日期	10.04.2012
*****************************/

#pragma once



class Force
{
public:
	/**构造函数*/
	Force(void);
	/**重载构造函数	赋予力的方向 自动计算大小*/
	Force(float _x,float _y,float _z);
	/**重载力之间加法*/
	Force operator+(Force strg);
	/**重载力之间减法*/
	Force operator-(Force strg);
	/**获取x参数值*/
	float getX();
	/**获取y参数值*/
	float getY();
	/**获取z参数值*/
	float getZ();
	/**获取力的大小*/
	float getStrength();
	/**设置x参数值*/
	void setX(float _x);
	/**设置y参数值*/
	void setY(float _y);
	/**设置z参数值*/
	void setZ(float _z);
	/**根据strength的值改变strength三方向的值*/
	void setStrength(float _strength);
	/**更新力的值*/
	void updateStrength();
	/**析构函数*/
	~Force(void);
	//力量值
	float strength;
	//方向
	float x;
	float y;
	float z;
};

