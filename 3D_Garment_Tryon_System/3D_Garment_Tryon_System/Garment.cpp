/***************************
	类名	Garment
	作者	喻斌强
	作用	弹簧类
	日期	10.06.2012
*****************************/

#include "StdAfx.h"
#include "Garment.h"
#include "math.h"
//缝合力大小									//debug
#define SEAMFORCE 1000.0f   //mass.cpp
//重力大小									//debug
#define zhongli 1000.0f 
//后期迭代次数——加上重力碰撞					//debug
#define numdiedadi 50
//后期弹簧弹性系数		可以不改					//debug
#define tanhuang 10.0f


extern vector<vector<Mass*>> showMass_larm;
extern vector<vector<Mass*>> showMass_rarm;
extern vector<vector<Mass*>*> showMass_body_down;

extern vector<vector<Mass*>> showMass_body_centerf;
extern vector<vector<Mass*>> showMass_body_centerb;

extern vector<vector<Mass*>> showMass_body_ling1;
extern vector<vector<Mass*>> showMass_body_ling2;
extern vector<vector<Mass*>> showMass_body_ling3;





extern int isIn[180][80][180];

/**构造函数*/
Garment::Garment(void){
	allCloth = vector<Cloth>();
}
/**析构函数*/
Garment::~Garment(void){

}

/**读取函数  写入所有的读取函数 一次调用*/
bool Garment::garmentRead(){
	if(!readCloth("ff")){
		perror("Garment readCloth() 错误\n");
		return false;
	}
	if(!readSeam("dd")){
		perror("Garment readSeam() 错误\n");
		return false;
	}

	//添加弹簧
	setSpringAll();
	return true;
}


/**读取衣片  目前是直接写入 loc当前衣服种类*/
bool Garment::readCloth(char * loc){
	//自己写入   allCloth  PXWIDTH
	
	Cloth *tmp = new Cloth();
	if(!tmp->readClothFile(1)){
		perror("Cloth readClothFile 错误\n");
	}
	allCloth.push_back(*tmp);

	tmp = new Cloth();
	if(!tmp->readClothFile(2)){
		perror("Cloth readClothFile 错误\n");	
	}
	allCloth.push_back(*tmp);


	tmp = new Cloth();
	if(!tmp->readClothFile(3)){
		perror("Cloth readClothFile 错误\n");	
	}
	allCloth.push_back(*tmp);


	tmp = new Cloth();
	if(!tmp->readClothFile(4)){
		perror("Cloth readClothFile 错误\n");	
	}
	allCloth.push_back(*tmp);
	
	tmp = new Cloth();
	if(!tmp->readClothFile(5)){
		perror("Cloth readClothFile 错误\n");	
	}
	allCloth.push_back(*tmp);
	
	tmp = new Cloth();
	if(!tmp->readClothFile(6)){
		perror("Cloth readClothFile 错误\n");	
	}
	allCloth.push_back(*tmp);

	return true;
}
/**读入缝*/
bool Garment::readSeam(char * loc){
	int sizeCloth = allCloth.size()/2;


	for(int i = 0;i < sizeCloth/2; i ++){
		for(int j = 0; j < allCloth.at(i).massCloth.size();j ++){

			allCloth.at(i*2).getVectorMass()->at(j)->seamForce = Force(0,0,-SEAMFORCE);

			allCloth.at(i*2 + 1).getVectorMass()->at(j)->seamForce = Force(0,0,SEAMFORCE);
			//
		}
	}


	for(int i = 0;i < sizeCloth; i ++){
		for(int j = 0; j < allCloth.at(2*i).massSeam.size();j ++){
			allCloth.at(2*i).massSeam.at(j)->seamMassPoint=(allCloth.at(2*i+1).massSeam.at(j));
			allCloth.at(2*i).massSeam.at(j)->seamForce = Force(0,0,-SEAMFORCE);
			allCloth.at(2*i+1).massSeam.at(j)->seamMassPoint=(allCloth.at(2*i).massSeam.at(j));
			allCloth.at(2*i+1).massSeam.at(j)->seamForce = Force(0,0,SEAMFORCE);

			Spring *tmpSring = new Spring(1,allCloth.at(2*i).massSeam.at(j));
			tmpSring->setConnectedMass(allCloth.at(2*i+1).massSeam.at(j));
			allCloth.at(2*i).massSeam.at(j)->massSpring.push_back(tmpSring);
			allCloth.at(2*i).massSeam.at(j)->massSpring.push_back(tmpSring);

			tmpSring = new Spring(1,allCloth.at(2*i+1).massSeam.at(j));
			tmpSring->setConnectedMass(allCloth.at(2*i).massSeam.at(j));
			allCloth.at(2*i+1).massSeam.at(j)->massSpring.push_back(tmpSring);
			allCloth.at(2*i+1).massSeam.at(j)->massSpring.push_back(tmpSring);
			//
		}
	}
	

	//for(int i = 0;i < sizeCloth; i ++){
	//	for(int j = 0; j < allCloth.at(2*i).massSeam1.size();j ++){
	//		allCloth.at(2*i).massSeam1.at(j)->setSeamPoint(allCloth.at(2*i+1).massSeam1.at(j));
	//		allCloth.at(2*i+1).massSeam1.at(j)->setSeamPoint(allCloth.at(2*i).massSeam1.at(j));
	//	}
	//}

	int sizearmwidth = allCloth.at(2).massSeam1.size();
	
	int bodysize =allCloth.at(0).massSeam1.size()/2;

	for(int i = 0;i < sizearmwidth; i ++){
		/*allCloth.at(0).massSeam1.at(i)->setSeamPoint(allCloth.at(2).massSeam1.at(i));
		allCloth.at(0).massSeam1.at(i+bodysize)->setSeamPoint(allCloth.at(4).massSeam1.at(i));*/


		Spring *tmpSring = new Spring(1,allCloth.at(0).massSeam1.at(i));
		tmpSring->setConnectedMass(allCloth.at(2).massSeam1.at(i));
		allCloth.at(0).massSeam1.at(i)->massSpring.push_back(tmpSring);
		allCloth.at(0).massSeam1.at(i)->massSpring.push_back(tmpSring);

		tmpSring = new Spring(1,allCloth.at(0).massSeam1.at(i+bodysize));
		tmpSring->setConnectedMass(allCloth.at(4).massSeam1.at(i));
		allCloth.at(0).massSeam1.at(i+bodysize)->massSpring.push_back(tmpSring);
		allCloth.at(0).massSeam1.at(i+bodysize)->massSpring.push_back(tmpSring);

		/*allCloth.at(2).massSeam1.at(i)->setSeamPoint(allCloth.at(0).massSeam1.at(i));
		allCloth.at(4).massSeam1.at(i)->setSeamPoint(allCloth.at(0).massSeam1.at(i+bodysize));*/


		tmpSring = new Spring(1,allCloth.at(2).massSeam1.at(i));
		tmpSring->setConnectedMass(allCloth.at(0).massSeam1.at(i));
		allCloth.at(2).massSeam1.at(i)->massSpring.push_back(tmpSring);
		allCloth.at(2).massSeam1.at(i)->massSpring.push_back(tmpSring);

		tmpSring = new Spring(1,allCloth.at(4).massSeam1.at(i));
		tmpSring->setConnectedMass(allCloth.at(0).massSeam1.at(i+bodysize));
		allCloth.at(4).massSeam1.at(i)->massSpring.push_back(tmpSring);
		allCloth.at(4).massSeam1.at(i)->massSpring.push_back(tmpSring);

		/*allCloth.at(1).massSeam1.at(i)->setSeamPoint(allCloth.at(3).massSeam1.at(i));
		allCloth.at(1).massSeam1.at(i+bodysize)->setSeamPoint(allCloth.at(5).massSeam1.at(i));*/

		tmpSring = new Spring(1,allCloth.at(1).massSeam1.at(i));
		tmpSring->setConnectedMass(allCloth.at(3).massSeam1.at(i));
		allCloth.at(1).massSeam1.at(i)->massSpring.push_back(tmpSring);
		allCloth.at(1).massSeam1.at(i)->massSpring.push_back(tmpSring);

		tmpSring = new Spring(1,allCloth.at(1).massSeam1.at(i+bodysize));
		tmpSring->setConnectedMass(allCloth.at(5).massSeam1.at(i));
		allCloth.at(1).massSeam1.at(i+bodysize)->massSpring.push_back(tmpSring);
		allCloth.at(1).massSeam1.at(i+bodysize)->massSpring.push_back(tmpSring);

		/*allCloth.at(3).massSeam1.at(i)->setSeamPoint(allCloth.at(1).massSeam1.at(i));
		allCloth.at(5).massSeam1.at(i)->setSeamPoint(allCloth.at(1).massSeam1.at(i+bodysize));*/

		tmpSring = new Spring(1,allCloth.at(3).massSeam1.at(i));
		tmpSring->setConnectedMass(allCloth.at(1).massSeam1.at(i));
		allCloth.at(3).massSeam1.at(i)->massSpring.push_back(tmpSring);
		allCloth.at(3).massSeam1.at(i)->massSpring.push_back(tmpSring);

		tmpSring = new Spring(1,allCloth.at(5).massSeam1.at(i));
		tmpSring->setConnectedMass(allCloth.at(1).massSeam1.at(i+bodysize));
		allCloth.at(5).massSeam1.at(i)->massSpring.push_back(tmpSring);
		allCloth.at(5).massSeam1.at(i)->massSpring.push_back(tmpSring);
	}

	//sizearmwidth = bodysize -sizearmwidth;

	for(int i = sizearmwidth;i < bodysize; i ++){
		allCloth.at(0).massSeam1.at(i)->setSeamPoint(allCloth.at(1).massSeam1.at(i));
		allCloth.at(0).massSeam1.at(i+bodysize)->setSeamPoint(allCloth.at(1).massSeam1.at(i+bodysize));
		allCloth.at(0).massSeam1.at(i)->seamForce = Force(0,0,-SEAMFORCE);
		allCloth.at(0).massSeam1.at(i+bodysize)->seamForce = Force(0,0,-SEAMFORCE);

		allCloth.at(1).massSeam1.at(i)->setSeamPoint(allCloth.at(0).massSeam1.at(i));
		allCloth.at(1).massSeam1.at(i+bodysize)->setSeamPoint(allCloth.at(0).massSeam1.at(i+bodysize));
		allCloth.at(1).massSeam1.at(i)->seamForce = Force(0,0,SEAMFORCE);
		allCloth.at(1).massSeam1.at(i+bodysize)->seamForce = Force(0,0,SEAMFORCE);

		Spring *tmpSring = new Spring(1,allCloth.at(0).massSeam1.at(i));
		tmpSring->setConnectedMass(allCloth.at(1).massSeam1.at(i));
		allCloth.at(0).massSeam1.at(i)->massSpring.push_back(tmpSring);
		allCloth.at(0).massSeam1.at(i)->massSpring.push_back(tmpSring);

		tmpSring = new Spring(1,allCloth.at(0).massSeam1.at(i+bodysize));
		tmpSring->setConnectedMass(allCloth.at(1).massSeam1.at(i+bodysize));
		allCloth.at(0).massSeam1.at(i+bodysize)->massSpring.push_back(tmpSring);
		allCloth.at(0).massSeam1.at(i+bodysize)->massSpring.push_back(tmpSring);

		tmpSring = new Spring(1,allCloth.at(1).massSeam1.at(i));
		tmpSring->setConnectedMass(allCloth.at(0).massSeam1.at(i));
		allCloth.at(1).massSeam1.at(i)->massSpring.push_back(tmpSring);
		allCloth.at(1).massSeam1.at(i)->massSpring.push_back(tmpSring);

		tmpSring = new Spring(1,allCloth.at(1).massSeam1.at(i+bodysize));
		tmpSring->setConnectedMass(allCloth.at(0).massSeam1.at(i+bodysize));
		allCloth.at(1).massSeam1.at(i+bodysize)->massSpring.push_back(tmpSring);
		allCloth.at(1).massSeam1.at(i+bodysize)->massSpring.push_back(tmpSring);
	}

	return true;
}

/**为所有的质点添加弹簧*///计算点到本质点距离  添加上去
void Garment::setSpringAll(){
	int allClothLength = allCloth.size();
	int clothLength =0;
	float tmpx;
	float tmpy;
	float tmpz;

	for(int i = 0;i < allClothLength; i ++){
		clothLength = allCloth.at(i).getVectorMass()->size();
		for(int j = 0;j < clothLength;j ++){
			for(int k = 0;k < clothLength;k ++){

				if(j == k){
					continue;
				}

				tmpx = allCloth.at(i).getVectorMass()->at(j)->x  -  allCloth.at(i).getVectorMass()->at(k)->x;
				if(tmpx > STRUCTLENGTH * 2.0f  + STRUCTLENGTH * 2.0f / 10.0f){
					continue;
				}
				tmpy = allCloth.at(i).getVectorMass()->at(j)->y  -  allCloth.at(i).getVectorMass()->at(k)->y;
				if(tmpy > STRUCTLENGTH * 2.0f  + STRUCTLENGTH * 2.0f / 10.0f){
					continue;
				}
				tmpz = allCloth.at(i).getVectorMass()->at(j)->z  -  allCloth.at(i).getVectorMass()->at(k)->z;
				if(tmpz > STRUCTLENGTH * 2.0f  + STRUCTLENGTH * 2.0f / 10.0f){
					continue;
				}

				float tmplength = sqrt(
									tmpx * tmpx + tmpy * tmpy + tmpz * tmpz
								);

				if(tmplength < STRUCTLENGTH  + STRUCTLENGTH / 10.0f){
					Spring *tmpSring = new Spring(1,allCloth.at(i).getVectorMass()->at(j));

					tmpSring->setConnectedMass(allCloth.at(i).getVectorMass()->at(k));

					allCloth.at(i).getVectorMass()->at(j)->massSpring.push_back(tmpSring);

				}else if(tmplength < STRUCTLENGTH * 1.4142135623f  + STRUCTLENGTH * 1.4142135623f / 10.0f){
					Spring *tmpSring = new Spring(2,allCloth.at(i).getVectorMass()->at(j));

					tmpSring->setConnectedMass(allCloth.at(i).getVectorMass()->at(k));

					allCloth.at(i).getVectorMass()->at(j)->massSpring.push_back(tmpSring);

				}else if(tmplength < STRUCTLENGTH * 2.0f  + STRUCTLENGTH * 2.0f / 10.0f){
					Spring *tmpSring = new Spring(3,allCloth.at(i).getVectorMass()->at(j));

					tmpSring->setConnectedMass(allCloth.at(i).getVectorMass()->at(k));

					allCloth.at(i).getVectorMass()->at(j)->massSpring.push_back(tmpSring);

				}
				
			}

		}
	}
}

/**迭代控制次数*/
void Garment::numIteration(int number,NetGrid * netGrid){
	//int num = 0;
	while(!Iteration(netGrid)){
		//num++;
	}
	//num++;

	int i = numdiedadi;
	while(i--){
		CollisonIteration(netGrid);
	}


	/*//////////////////////////////////////////////////////////////////////////////////////////////////////

										读衣服的下半部分

	///////////////////////////////////////////////////////////////////////////////////////////////////////*/
	
	//FILE *dataFile1d;				//读入的文件showMass_body_down
	//dataFile1d = fopen("bodydown_out.txt", "w");
	//
	//fprintf(dataFile1d,"#  ----------------------------------------------------------\n");

	//fprintf(dataFile1d,"#  Num verts:  %d\n",showMass_body_down.size()*showMass_body_down.at(0)->size()+showMass_body_down.size());
	//fprintf(dataFile1d,"#  Num rc: %d %d\n",showMass_body_down.size(),showMass_body_down.at(0)->size()+1);
	//fprintf(dataFile1d,"#  Num tElems: 8\n");

	//for(int i = 0; i < showMass_body_down.size(); i++)			//长
	//{
	//	for(int j = 0; j < showMass_body_down.at(i)->size(); j++)		//宽
	//	{
	//		fprintf(dataFile1d,"v %f %f %f\n",showMass_body_down.at(i)->at(j)->x,showMass_body_down.at(i)->at(j)->y,showMass_body_down.at(i)->at(j)->z);
	//	}
	//	fprintf(dataFile1d,"v %f %f %f\n",showMass_body_down.at(i)->at(0)->x,showMass_body_down.at(i)->at(0)->y,showMass_body_down.at(i)->at(0)->z);
	//}


	//fclose(dataFile1d);


	/*//////////////////////////////////////////////////////////////////////////////////////////////////////

										读衣服的中间前半部分

	///////////////////////////////////////////////////////////////////////////////////////////////////////*/
	
	
	//FILE *dataFile1centerf;				//读入的文件showMass_body_centerf
	//dataFile1centerf = fopen("bodycenterf_out.txt", "w");
	//
	//fprintf(dataFile1centerf,"#  ----------------------------------------------------------\n");

	//fprintf(dataFile1centerf,"#  Num verts:  %d\n",showMass_body_centerf.size()*showMass_body_centerf.at(0).size());
	//fprintf(dataFile1centerf,"#  Num rc: %d %d\n",showMass_body_centerf.size(),showMass_body_centerf.at(0).size());
	//fprintf(dataFile1centerf,"#  Num tElems: 8\n");

	//for(int i = 0; i < showMass_body_centerf.size(); i++)			//长
	//{
	//	for(int j = 0; j < showMass_body_centerf.at(i).size(); j++)		//宽
	//	{
	//		fprintf(dataFile1centerf,"v %f %f %f\n",showMass_body_centerf.at(i).at(j)->x,showMass_body_centerf.at(i).at(j)->y,showMass_body_centerf.at(i).at(j)->z);
	//	}
	//}


	//fclose(dataFile1centerf);

	/*//////////////////////////////////////////////////////////////////////////////////////////////////////

										读衣服的中间前半部分

	///////////////////////////////////////////////////////////////////////////////////////////////////////*/
	
	//FILE *dataFile1centerb;				//读入的文件showMass_body_centerf
	//dataFile1centerb = fopen("bodycenterb_out.txt", "w");
	//
	//fprintf(dataFile1centerb,"#  ----------------------------------------------------------\n");

	//fprintf(dataFile1centerb,"#  Num verts:  %d\n",showMass_body_centerb.size()*showMass_body_centerb.at(0).size());
	//fprintf(dataFile1centerb,"#  Num rc: %d %d\n",showMass_body_centerb.size(),showMass_body_centerb.at(0).size());
	//fprintf(dataFile1centerb,"#  Num tElems: 8\n");

	//for(int i = 0; i < showMass_body_centerb.size(); i++)			//长
	//{
	//	for(int j = 0; j < showMass_body_centerb.at(i).size(); j++)		//宽
	//	{
	//		fprintf(dataFile1centerb,"v %f %f %f\n",showMass_body_centerb.at(i).at(j)->x,showMass_body_centerb.at(i).at(j)->y,showMass_body_centerb.at(i).at(j)->z);
	//	}
	//}


	//fclose(dataFile1centerb);


	

	/*//////////////////////////////////////////////////////////////////////////////////////////////////////

										读左手臂

	///////////////////////////////////////////////////////////////////////////////////////////////////////*/
	
	//FILE *dataFile2;				//读入的文件
	//dataFile2 = fopen("arml_out.txt", "w");
	//
	//fprintf(dataFile2,"#  ----------------------------------------------------------\n");

	//fprintf(dataFile2,"#  Num verts:  %d\n",showMass_larm.size()*showMass_larm.at(0).size()+showMass_rarm.size());
	//fprintf(dataFile2,"#  Num rc: %d %d\n",showMass_larm.size(),showMass_larm.at(0).size()+1);
	//fprintf(dataFile2,"#  Num tElems: 8\n");

	//for(int i = 0; i < showMass_larm.size(); i++)			//长
	//{
	//	for(int j = 0; j < showMass_larm.at(i).size(); j++)		//宽
	//	{
	//		fprintf(dataFile2,"v %f %f %f\n",showMass_larm.at(i).at(j)->x,showMass_larm.at(i).at(j)->y,showMass_larm.at(i).at(j)->z);
	//	}
	//	fprintf(dataFile2,"v %f %f %f\n",showMass_larm.at(i).at(0)->x,showMass_larm.at(i).at(0)->y,showMass_larm.at(i).at(0)->z);
	//}


	//fclose(dataFile2);



	/*//////////////////////////////////////////////////////////////////////////////////////////////////////

										读右手臂

	///////////////////////////////////////////////////////////////////////////////////////////////////////*/
	
	//FILE *dataFile3;				//读入的文件
	//dataFile3 = fopen("armr_out.txt", "w");
	//
	//fprintf(dataFile3,"#  ----------------------------------------------------------\n");

	//fprintf(dataFile3,"#  Num verts:  %d\n",showMass_rarm.size()*showMass_rarm.at(0).size()+showMass_rarm.size());
	//fprintf(dataFile3,"#  Num rc: %d %d\n",showMass_rarm.size(),showMass_rarm.at(0).size()+1);
	//fprintf(dataFile3,"#  Num tElems: 8\n");

	//for(int i = 0; i < showMass_rarm.size(); i++)			//长
	//{
	//	for(int j = 0; j < showMass_rarm.at(i).size(); j++)		//宽
	//	{
	//		fprintf(dataFile3,"v %f %f %f\n",showMass_rarm.at(i).at(j)->x,showMass_rarm.at(i).at(j)->y,showMass_rarm.at(i).at(j)->z);
	//	}
	//	fprintf(dataFile3,"v %f %f %f\n",showMass_rarm.at(i).at(0)->x,showMass_rarm.at(i).at(0)->y,showMass_rarm.at(i).at(0)->z);
	//}


	//fclose(dataFile3);

}

/**迭代函数*/
bool Garment::Iteration(NetGrid * netGrid){
	
	//改变

	int allClothLength = allCloth.size();
	int clothLength =0;
	//改变质点受力
	for(int i = 0;i < allClothLength; i ++){
		clothLength = allCloth.at(i).getVectorMass()->size();
		for(int j = 0;j < clothLength;j ++){
			allCloth.at(i).getVectorMass()->at(j)->changeAll();
		}
	}


	/**检查碰撞*/
	/*if(isCollision(netGrid)){
		return false;
	}*/
	collision(netGrid);
	//设置碰撞力
	//碰撞的点  不运动
	


	/**检查符合是否缝合结束  改变的质点受力*/
	//判断
	if(isOverSeam()){
		for(int i = 0;i < allClothLength; i ++){
			clothLength = allCloth.at(i).getVectorMass()->size();
			for(int j = 0;j < clothLength;j ++){
				allCloth.at(i).getVectorMass()->at(j)->seamMassPoint = NULL;
				allCloth.at(i).getVectorMass()->at(j)->seamForce = Force();
				//allCloth.at(i).getVectorMass()->at(j)->resetVelocity();
				allCloth.at(i).getVectorMass()->at(j)->galavity = Force(0,zhongli,0);
				for(int k = 0;k < allCloth.at(i).getVectorMass()->at(j)->massSpring.size();k ++ ){
					allCloth.at(i).getVectorMass()->at(j)->massSpring.at(k)->kFactor = tanhuang;
				}
			}
		}
		return true;
	}else{
		//改变站点位置
		for(int i = 0;i < allClothLength; i ++){
			clothLength = allCloth.at(i).getVectorMass()->size();
			for(int j = 0;j < clothLength;j ++){
				allCloth.at(i).getVectorMass()->at(j)->changeLocation();
				//allCloth.at(i).getVectorMass()->at(j)->resetVelocity();
			}
		}
		return false;
	}
}



/**碰撞迭代函数*/
void Garment::CollisonIteration(NetGrid * netGrid){
	
	int allClothLength = allCloth.size();
	int clothLength =0;
	//改变质点受力
	for(int i = 0;i < allClothLength; i ++){
		clothLength = allCloth.at(i).getVectorMass()->size();
		for(int j = 0;j < clothLength;j ++){
			allCloth.at(i).getVectorMass()->at(j)->changeAll();
		}
	}
	
	/**检查碰撞*/
	/*if(isCollision(netGrid)){
		return;
	}*/
	collision(netGrid);
	//设置碰撞力
	//碰撞的点  不运动速度反向
	

	//改变站点位置
	for(int i = 0;i < allClothLength; i ++){
		clothLength = allCloth.at(i).getVectorMass()->size();
		for(int j = 0;j < clothLength;j ++){
			allCloth.at(i).getVectorMass()->at(j)->changeLocation();
			allCloth.at(i).getVectorMass()->at(j)->resetVelocity();
		}
	}
	
}



/**缝合是否结束*/
bool Garment::isOverSeam(){
	int allClothLength = allCloth.size();
	int clothLength =0;
	Mass * tmpMass;
	bool isover = true;
	int tmpum=0;
	for(int i = 0;i < allClothLength; i ++){
		clothLength = allCloth.at(i).getVectorMass()->size();
		for(int j = 0;j < clothLength;j ++){
			tmpMass = allCloth.at(i).getVectorMass()->at(j);
			if(tmpMass->seamMassPoint){
				float tmpX = tmpMass->x - tmpMass->seamMassPoint->x;
				float tmpY = tmpMass->y - tmpMass->seamMassPoint->y;
				float tmpZ = tmpMass->z - tmpMass->seamMassPoint->z;

				if(sqrt(tmpX*tmpX + tmpY*tmpY + tmpZ * tmpZ) < 3.0)
				{
					tmpum ++;
					//isover = false;
				}
			}
		}
	}

	if(tmpum < 5){
		isover = false;
	}
	return isover;
}



/**检查碰撞*/
bool Garment::collision(NetGrid * netGrid){
	float gap = netGrid->gap;
	float tmplength = netGrid->length;
	float tmpwidth = netGrid->width;
	float tmpheight = netGrid->height;
	//先求出当前点在netgrid中的位置  在判断该位置是否为1
	int allClothLength = allCloth.size();
	int clothLength =0;
	//判断是否碰撞   碰了重置速度  
	Mass * tmpMass;


	//FILE *dataFile2;				//读入的文件
	//dataFile2 = fopen("gai_out.txt", "w");
	for(int i = 0;i < allClothLength; i ++){
		clothLength = allCloth.at(i).getVectorMass()->size();
		for(int j = 0;j < clothLength;j ++){
			tmpMass = allCloth.at(i).getVectorMass()->at(j);

			float x =allCloth.at(i).getVectorMass()->at(j)->x + allCloth.at(i).getVectorMass()->at(j)->massSpeed.getX() * 0.005f;
			float y =allCloth.at(i).getVectorMass()->at(j)->y + allCloth.at(i).getVectorMass()->at(j)->massSpeed.getY() * 0.005f;
			float z =allCloth.at(i).getVectorMass()->at(j)->z + allCloth.at(i).getVectorMass()->at(j)->massSpeed.getZ() * 0.005f;

			int tmpx = (x + tmplength/2 )/gap;
			int tmpy = (156- y)/gap;
			int tmpz = (tmpwidth/2 - z)/gap;
			if(isIn[tmpx][tmpz][tmpy]){
				//重置速度
				tmpMass->resetVelocity();
				
			}
		}
	}
	/*fprintf(dataFile2,"\n\n\n");
	fclose(dataFile2);*/
	return false;
}