#pragma once
#include <algorithm> 
#include <math.h>
#include "Dot.h"

//计算一个点关于一个中点的对应点，并返回这个对应点
Dot CalculateCorrespondDot(Dot i,Dot j)
{
	//i关于中点j的对应点
	Dot tmp;
	tmp.x = j.x-i.x;
	tmp.y = j.y-i.y;
	tmp.z = j.z-i.z;

	tmp.x = tmp.x + j.x;
	tmp.y = tmp.y + j.y;
	tmp.z = tmp.z + j.z;

	return tmp;
}


int UpOrDownX(Dot d1,Dot d2,Dot d3)	//d3是待判断在上还是在下的点
{
	//返回1说明在上，返回0说明在下
	int k = (d1.y-d2.y)/(d1.z-d2.z);
	int b = d1.y*d2.z-d2.y*d1.z;
	
	int tmpy = k*d3.z+b;
	if(d3.y>tmpy) return 1;
	else return 0;
}

int UpOrDownY(Dot d1,Dot d2,Dot d3)	//d3是待判断在上还是在下的点
{
	//返回1说明在上，返回0说明在下
	int k = (d1.x-d2.x)/(d1.z-d2.z);
	int b = d1.x*d2.z-d2.x*d1.z;
	
	int tmpx = k*d3.z+b;
	if(d3.x>tmpx) return 1;
	else return 0;
}


int UpOrDownZ(Dot d1,Dot d2,Dot d3)	//d3是待判断在上还是在下的点
{
	//返回1说明在上，返回0说明在下
	int k = (d1.y-d2.y)/(d1.z-d2.x);
	int b = d1.y*d2.x-d2.y*d1.x;
	
	int tmpy = k*d3.x+b;
	if(d3.y>tmpy) return 1;
	else return 0;
}


float CalculateVectorCos(Dot i,Dot j)
{
	return (i.x*j.x+i.y*j.y+i.z*j.z)/sqrt( (i.x*i.x+i.y*i.y+i.z*i.z) * (j.x*j.x+j.y*j.y+j.z*j.z) );
}

