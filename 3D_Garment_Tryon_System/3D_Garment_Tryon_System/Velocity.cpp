/***************************
	类名	Velocity
	作者	喻斌强
	作用	速度的类
	日期	10.04.2012
*****************************/

#include "StdAfx.h"
#include "Velocity.h"
#include <math.h>

/***构造函数*/
Velocity::Velocity(void)
{
	x=0;
	y=0;
	z=0;
	speed = 0;
}
/**重载构造函数	赋予力的方向 自动计算大小*/
Velocity::Velocity(float _x,float _y,float _z){
	x=_x;
	y=_y;
	z=_z;
	speed = sqrt(x*x + y*y + z*z);
}
/**析构函数*/
Velocity::~Velocity(void)
{
}
/**获取x参数值*/
float Velocity::getX(){
	return x;
}
/**获取y参数值*/
float Velocity::getY(){
	return y; 
}
/**获取z参数值*/
float Velocity::getZ(){
	return z;
}
/**获取力的大小*/
float Velocity::getSpeed(){
return speed;
}
/**设置x参数值*/
void Velocity::setX(float _x){
	x = _x;
}
/**设置y参数值*/
void Velocity::setY(float _y){
	y = _y;
}
/**设置z参数值*/
void Velocity::setZ(float _z){
	z = _z;
}
/**根据speed的值改变速度三方向的值 此时方向不变*/
void Velocity::setSpeed(float _speed){
	float tmpSwap = _speed/speed;
	x=x * tmpSwap;
	y=y * tmpSwap;
	z=z * tmpSwap;
}
 /**重载加法*/
Velocity Velocity::operator+(Velocity vel){
	Velocity tmpforce = Velocity(x+vel.x,y+vel.y,z+vel.z);
	return tmpforce; 
}
/**重载力之间减法*/
Velocity Velocity::operator-(Velocity vel){
	Velocity tmpforce = Velocity(x-vel.x,y-vel.y,z-vel.z);
	return tmpforce; 
}


