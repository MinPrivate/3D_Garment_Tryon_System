/***************************
	类名	Spring
	作者	喻斌强
	作用	弹簧类
	日期	10.05.2012
*****************************/

#include "StdAfx.h"
#include "Spring.h"
#include "math.h"


//弹簧当前的弹性系数									//debug
#define FAVTOR 10.0f 


/**构造函数*/
Spring::Spring(Mass * _current){
	kind = 1;
	//length = 0.0f;
	length = STRUCTLENGTH;
	
	kFactor = FAVTOR;
	currentMass = _current;
}
/**重载构造函数	赋予弹簧种类 1 2 3*/
Spring::Spring(int _kind,Mass * _current){
	kind = _kind;
	//length = 0.0f;
	if(kind == 1){
		length  = STRUCTLENGTH;
	}else if(kind == 2){
		length = STRUCTLENGTH * 1.4142135623f;
	}else if(kind == 3){
		length = STRUCTLENGTH * 2.0f;
	}else{
		perror("Spring构造错误！kind值不再弹簧种类内");
	}
	kFactor = FAVTOR;
	currentMass = _current;
	//connectedMass = _ConnectedMass;
}
/**设置弹簧相连的点*/
void Spring::setConnectedMass(Mass * _ConnectedMass){
	connectedMass = _ConnectedMass;
}
/**获取当前弹簧力*/
Force Spring::getForce(){
	if(connectedMass == NULL){
		perror("spring 相连点的地址为空！");
	}
	//计算弹性系数
	computeFactor();
	//弹簧力
	Force tmpForce=Force();
	//弹簧长度
	float tmpSprLength = getLength();
	//判断两弹簧的改变距离是否过小  过小则返回值 0
	if(tmpSprLength - length < (length/1000.0f) 
			&& tmpSprLength - length > - (length/1000.0f))
			{
		return tmpForce;
	}
	if(tmpSprLength > 5*length){
		kFactor = 10*FAVTOR;
	}else if(tmpSprLength > 3*length){
		kFactor = 5*FAVTOR;
	}else{
		kFactor = FAVTOR;
	}

	//设置力
	//tmpForce.setStrength(abs(kFactor * (tmpSprLength - length)));

	//获得弹簧力的方向
	float changeInt = kFactor* (tmpSprLength - length)/tmpSprLength ;
	tmpForce = Force(
			(connectedMass->x-currentMass->x)*changeInt
			,(connectedMass->y-currentMass->y)*changeInt 
			,(connectedMass->z-currentMass->z)*changeInt );
	return tmpForce;
}
/**获得相连的点指针*/
Mass * Spring::getConnectedMass(){
	if(connectedMass == NULL){
		perror("spring 相连点的地址为空！");
	}
	return connectedMass;
}
int Spring::getkind(){
	return kind;
}
/**获取弹性系数*/
float Spring::getFactor(){
	//先计算现在弹簧的值;在返回
	computeFactor();
	return kFactor;
}
/**弹簧现在长度*/
float Spring::getLength(){
	if(connectedMass == NULL){
		perror("spring 相连点的地址为空！");
	}

	nowlength = sqrt(
				(connectedMass->x-currentMass->x)*(connectedMass->x-currentMass->x)+
				(connectedMass->y-currentMass->y)*(connectedMass->y-currentMass->y)+
				(connectedMass->z-currentMass->z)*(connectedMass->z-currentMass->z)
				);
	return nowlength;
}
/**析构函数*/
Spring::~Spring(void){
	if(connectedMass!=NULL){
		delete connectedMass;
	}
	if(currentMass!=NULL){
		delete currentMass;
	}
}
/**计算弹簧当前的弹性系数	需要是在写*/
float Spring::computeFactor(){
	if(connectedMass == NULL){
		perror("spring 相连点的地址为空！");
	}
	return 0.0f;
}