/***************************
	类名	Force
	作者	喻斌强
	作用	力的类
	日期	10.04.2012
*****************************/


#include "StdAfx.h"
#include "Force.h"
#include <math.h>


/***构造函数*/
Force::Force(void)
{
	x=0;
	y=0;
	z=0;
	strength = 0;
}
/**重载构造函数	赋予力的方向 自动计算大小*/
Force::Force(float _x,float _y,float _z){
	x=_x;
	y=_y;
	z=_z;
	strength = sqrt(x*x + y*y + z*z);
}
/**析构函数*/
Force::~Force(void)
{
}
/**获取x参数值*/
float Force::getX(){
	return x;
}
/**获取y参数值*/
float Force::getY(){
	return y; 
}
/**获取z参数值*/
float Force::getZ(){
	return z;
}
/**获取力的大小*/
float Force::getStrength(){
return strength;
}
/**更新力的值*/
void Force::updateStrength(){
	strength = sqrt(x*x + y*y + z*z);
}
/**设置x参数值*/
void Force::setX(float _x){
	x = _x;
}
/**设置y参数值*/
void Force::setY(float _y){
	y = _y;
}
/**设置z参数值*/
void Force::setZ(float _z){
	z = _z;
}
/**根据strength的值改变strength三方向的值 此时方向不变*/
void Force::setStrength(float _strength){
	float tmpSwap = _strength/strength;
	x=x * tmpSwap;
	y=y * tmpSwap;
	z=z * tmpSwap;
}
 /**重载加法*/
Force Force::operator+(Force force){
	Force tmpforce = Force(x+force.x,y+force.y,z+force.z);
	return tmpforce; 
}
/**重载力之间减法*/
Force Force::operator-(Force force){
	Force tmpforce = Force(x-force.x,y-force.y,z-force.z);
	return tmpforce; 
}
