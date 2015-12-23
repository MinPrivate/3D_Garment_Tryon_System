/***************************
	类名	Mass
	作者	喻斌强
	作用	弹簧类
	日期	10.05.2012
*****************************/

#include "StdAfx.h"
#include "Mass.h"
//重力大小									//debug
#define GALAVITY 10.0f
//重力加速度   不能为 0 .。。。。。。。
#define GRAVITYACCEL 10.0F
//迭代时间									//debug
#define TIME 0.005f
//缝合力大小										//debug
#define SEAMFORCE 1000.0f  //garment.cpp



/**构造函数*/
Mass::Mass(void){
	/**重力*/
	galavity = Force();
	/**弹簧合力*/
	 springForce = Force();
	/**缝合力*/
	 seamForce = Force();
	/**合力*/
	 allForce = Force();
	/**弹簧集合*/
	massSpring = vector<Spring*>();
	/**速度集合*/
	massSpeed = Velocity();
	//指点坐标x
	 x = 0.0f;
	//指点坐标y
	 y = 0.0f;
	//指点坐标z
	 z = 0.0f;
	 seamMassPoint=NULL;

}

/**构造函数 传入坐标  */
Mass::Mass(float _x,float _y,float _z){
	/**重力*/
	galavity = Force();
	/**弹簧合力*/
	 springForce = Force();
	/**缝合力*/
	 seamForce = Force();
	/**合力*/
	 allForce = Force();
	/**弹簧集合*/
	massSpring = vector<Spring*>();
	/**速度集合*/
	massSpeed = Velocity();
	//指点坐标x
	 x = _x;
	//指点坐标y
	 y = _y;
	//指点坐标z
	 z = _z;
	 seamMassPoint=NULL;
}

/**计算弹簧合力*/
void Mass::computeSpringForce(){
	int iTmpSize = massSpring.size();

	if(!seamMassPoint && iTmpSize){
		for(int i = 0;i < iTmpSize;i ++){
			springForce = springForce + massSpring.at(i)->getForce();
		}
	}else{
		springForce = Force();
	}
}

/**计算速度*/
void Mass::changeVelocity(){
	//计算质量		方向y负 定制
	float quality = GALAVITY/GRAVITYACCEL;
	//加速度
	float ax = allForce.getX()/quality;
	float ay = allForce.getY()/quality;
	float az = allForce.getZ()/quality;
	//迭代时间内增加的速度
	Velocity tmpVol = Velocity(ax*TIME,ay*TIME,az*TIME);
	massSpeed = massSpeed+  tmpVol;
}


void Mass::resetVelocity(){
	massSpeed = Velocity();
}


/**改变位置*/
void Mass::changeLocation(){
	x += massSpeed.getX() * TIME;
	y += massSpeed.getY() * TIME;
	z += massSpeed.getZ() * TIME;
}

/**设置缝合点*/
void Mass::setSeamPoint(Mass * _seamMassPoint){
	seamMassPoint =_seamMassPoint;
}

/**设置弹缝合力*/
void Mass::computeSeamForce(){
	//暂时为恒定值
	//if(seamMassPoint){
	//	 
	//}
}
/**计算合力*/
 void Mass::computeAllForce(){
	allForce = springForce  + galavity + seamForce;
	//if(allForce.getStrength() > 100.0){
	//	perror("fuck");
	//}
}

/**完成所有改变*/
void Mass::changeAll(){
	//计算弹簧合力
	computeSpringForce();
	//计算弹缝合力

	//computeSeamForce();
	//计算合力
	computeAllForce();
	//改变速度
	changeVelocity();
	//改变位置
	//changeLocation();
}

/**析构函数*/
Mass::~Mass(void){
	massSpring.clear();
	delete seamMassPoint;
}