/***************************
	类名	cloth
	作者	喻斌强
	作用	衣片的类
	日期	10.04.2012
*****************************/


#include "StdAfx.h"
#include "Cloth.h"


#define PXWIDTH 1.8f      //要改弹簧原长




#define NECKWIDTH 6
#define NECKHEIGHT 33
#define BODYWIDTH 12
#define BODYHEIGHT 30

#define BODYTHIN 15

#define ARMWIDTH 43
#define ARMHEIGHT 7

////////////////////////////////////////////////////display

vector<vector<Mass*>> showMass_larm = vector<vector<Mass*>> ();
vector<vector<Mass*>> showMass_rarm = vector<vector<Mass*>> ();
vector<vector<Mass*>*> showMass_body_down = vector<vector<Mass*>*> ();
vector<vector<Mass*>> showMass_body_centerf = vector<vector<Mass*>> ();
vector<vector<Mass*>> showMass_body_centerb = vector<vector<Mass*>> ();

vector<vector<Mass*>> showMass_body_ling1 = vector<vector<Mass*>> ();
vector<vector<Mass*>> showMass_body_ling2 = vector<vector<Mass*>> ();
vector<vector<Mass*>> showMass_body_ling3 = vector<vector<Mass*>> ();

/***构造函数*/
Cloth::Cloth(void)
{
	//初始化衣片存放的质点集合
	massCloth = vector<Mass*>();
	massSeam = vector<Mass *>();
	massSeam1 = vector<Mass *>();

	//if(!readClothFile("rr")){
	//	perror("Cloth readClothFile 错误\n");	
	//}
}
///**根据衣片类型 获取衣片*/
//Cloth::Cloth(int _clothflag){
//	clothflag = _clothflag;
//}
/**析构函数*/
Cloth::~Cloth(void)
{

}
/**读取衣片*//////////////////////////////////////暂时不写  靠自己手动写入
bool Cloth::readClothFile(int loc){
	//根据clothflag写入读文件 或 数据库代码   
	Mass * tmpMass;

	if(loc == 1){////////////////衣服中间前
		//bottom
		Mass * ttt = new Mass();
		vector<Mass*> *tmpvector;
		for(int i=0;i< 23;i++){
			tmpvector = new vector<Mass*>();
			for(int j = 0; j < 46;j++){
				tmpvector->push_back(ttt);
			}
			showMass_body_down.push_back(tmpvector);
		}
		//center
		for(int i=0;i< 8;i++){
			tmpvector = new vector<Mass*>();
			for(int j = 0; j < 23;j++){
				tmpvector->push_back(ttt);
			}
			showMass_body_centerf.push_back(*tmpvector);
			showMass_body_centerb.push_back(*tmpvector);
		}
		//ling



		tmpvector = NULL;


		for(int j = 0;j < NECKWIDTH+1;j++){
			for(int i = 0;i < NECKHEIGHT;i ++){
				tmpMass = new Mass(j* PXWIDTH,i * PXWIDTH,BODYTHIN);
				massCloth.push_back(tmpMass);




				if(i < 4){

				}
				if(i > 2 && i < 11){
					showMass_body_centerf.at(i-3).at(j+11) = tmpMass;
					//showMass_body_centerb
				}
				
				if(i > 9){
					showMass_body_down.at(i-10)->at(j+11) = tmpMass;
				}
			}
		}

		

		for(int j = NECKWIDTH+1;j < NECKWIDTH+3;j++){
			//int k = 0;
			for(int i = 1;i < NECKHEIGHT;i ++){
				tmpMass = new Mass(j* PXWIDTH,i * PXWIDTH,BODYTHIN);
				massCloth.push_back(tmpMass);

				if(i == 1){
					massSeam.push_back(tmpMass);
				}




				if(i < 4){

				}
				if(i > 2 && i < 11){
					showMass_body_centerf.at(i-3).at(j+11) = tmpMass;
					//showMass_body_centerb
				}
				if(i > 9){
					showMass_body_down.at(i-10)->at(j+11 ) = tmpMass;
					////k++;
				}

			}
		}
		for(int j = NECKWIDTH+3;j < NECKWIDTH+5;j++){
			//int k = 0;
			for(int i = 2;i < NECKHEIGHT;i ++){
				tmpMass = new Mass(j* PXWIDTH,i * PXWIDTH,BODYTHIN);
				massCloth.push_back(tmpMass);

				if(i == 2){
					massSeam.push_back(tmpMass);
				}



				if(i < 4){

				}
				if(i > 2 && i < 11){
					showMass_body_centerf.at(i-3).at(j+11) = tmpMass;
					//showMass_body_centerb
				}
				if(i > 9){
					showMass_body_down.at(i-10)->at(j+11 ) = tmpMass;
					//k++;
				}
			}
		}
		for(int j = NECKWIDTH+5;j < BODYWIDTH;j++){
			for(int i = 3;i < NECKHEIGHT;i ++){
				tmpMass = new Mass(j* PXWIDTH,i * PXWIDTH,BODYTHIN);
				massCloth.push_back(tmpMass);

				if(i == 3){
					massSeam.push_back(tmpMass);
				}

				if(j == BODYWIDTH - 1 ){
					massSeam1.push_back(tmpMass);
				}



				if(i < 4){

				}
				if(i > 2 && i < 11){
					showMass_body_centerf.at(i-3).at(j+11) = tmpMass;
					//showMass_body_centerb
				}
				if(i > 9){
					showMass_body_down.at(i-10)->at(j+11 ) = tmpMass;
					//k++;
				}
			}
		}
		////////////////////////////////////////////////////////////////////////////
		for(int j = 1;j < NECKWIDTH+1;j++){
			for(int i = 0;i < NECKHEIGHT;i ++){
				tmpMass = new Mass(-j* PXWIDTH,i * PXWIDTH,BODYTHIN);
				massCloth.push_back(tmpMass);



				if(i < 4){

				}
				if(i > 2 && i < 11){
					showMass_body_centerf.at(i-3).at(11-j) = tmpMass;
					//showMass_body_centerb
				}
				if(i > 9){
					showMass_body_down.at(i-10)->at(11-j) = tmpMass;
				}
			}
		}
		for(int j = NECKWIDTH+1;j < NECKWIDTH+3;j++)
			for(int i = 1;i < NECKHEIGHT;i ++){
				tmpMass = new Mass(-j* PXWIDTH,i * PXWIDTH,BODYTHIN);
				massCloth.push_back(tmpMass);

				if(i == 1){
					massSeam.push_back(tmpMass);
				}


				if(i < 4){

				}
				if(i > 2 && i < 11){
					showMass_body_centerf.at(i-3).at(11-j) = tmpMass;
					//showMass_body_centerb
				}
				if(i > 9){
					showMass_body_down.at(i-10)->at(11-j) = tmpMass;
				}
			}
		for(int j = NECKWIDTH+3;j < NECKWIDTH+5;j++)
			for(int i = 2;i < NECKHEIGHT;i ++){
				tmpMass = new Mass(-j* PXWIDTH,i * PXWIDTH,BODYTHIN);
				massCloth.push_back(tmpMass);

				if(i == 2){
					massSeam.push_back(tmpMass);
				}



				if(i < 4){

				}
				if(i > 2 && i < 11){
					showMass_body_centerf.at(i-3).at(11-j) = tmpMass;
					//showMass_body_centerb
				}
				if(i > 9){
					showMass_body_down.at(i-10)->at(11-j) = tmpMass;
				}
			}
		for(int j = NECKWIDTH+5;j < BODYWIDTH;j++)
			for(int i = 3;i < NECKHEIGHT;i ++){
				tmpMass = new Mass(-j* PXWIDTH,i * PXWIDTH,BODYTHIN);
				massCloth.push_back(tmpMass);

				if(i == 3){
					massSeam.push_back(tmpMass);
				}

				if(j == BODYWIDTH - 1 ){
					massSeam1.push_back(tmpMass);
				}



				if(i < 4){

				}
				if(i > 2 && i < 11){
					showMass_body_centerf.at(i-3).at(11-j) = tmpMass;
					//showMass_body_centerb
				}
				if(i > 9){
					showMass_body_down.at(i-10)->at(11-j) = tmpMass;
				}
			}

		delete ttt;
	}else if(loc == 2){///////////////////衣服中间后
		for(int j = 0;j < NECKWIDTH+1;j++)
			for(int i = 0;i < NECKHEIGHT;i ++){
				tmpMass = new Mass(j* PXWIDTH,i * PXWIDTH,-BODYTHIN);
				massCloth.push_back(tmpMass);




				if(i < 4){

				}
				if(i > 2 && i < 11){
					showMass_body_centerb.at(i-3).at(j+11) = tmpMass;
					//showMass_body_centerb
				}
				if(i > 9){
					showMass_body_down.at(i-10)->at(34-j) = tmpMass;
				}

			}
		for(int j = NECKWIDTH+1;j < NECKWIDTH+3;j++)
			for(int i = 1;i < NECKHEIGHT;i ++){
				tmpMass = new Mass(j* PXWIDTH,i * PXWIDTH,-BODYTHIN);
				massCloth.push_back(tmpMass);
				
				if(i == 1){
					massSeam.push_back(tmpMass);
				}



				if(i < 4){

				}
				if(i > 2 && i < 11){
					showMass_body_centerb.at(i-3).at(j+11) = tmpMass;
					//showMass_body_centerb
				}
				if(i > 9){
					showMass_body_down.at(i-10)->at(34-j) = tmpMass;
				}
			}
		for(int j = NECKWIDTH+3;j < NECKWIDTH+5;j++)
			for(int i = 2;i < NECKHEIGHT;i ++){
				tmpMass = new Mass(j* PXWIDTH,i * PXWIDTH,-BODYTHIN);
				massCloth.push_back(tmpMass);
				
				if(i == 2){
					massSeam.push_back(tmpMass);
				}



				if(i < 4){

				}
				if(i > 2 && i < 11){
					showMass_body_centerb.at(i-3).at(j+11) = tmpMass;
					//showMass_body_centerb
				}
				if(i > 9){
					showMass_body_down.at(i-10)->at(34-j) = tmpMass;
				}
			}
		for(int j = NECKWIDTH+5;j < BODYWIDTH;j++)
			for(int i = 3;i < NECKHEIGHT;i ++){
				tmpMass = new Mass(j* PXWIDTH,i * PXWIDTH,-BODYTHIN);
				massCloth.push_back(tmpMass);
				
				if(i == 3){
					massSeam.push_back(tmpMass);
				}

				if(j == BODYWIDTH - 1 ){
					massSeam1.push_back(tmpMass);
				}



				if(i < 4){

				}
				if(i > 2 && i < 11){
					showMass_body_centerb.at(i-3).at(j+11) = tmpMass;
					//showMass_body_centerb
				}
				if(i > 9){
					showMass_body_down.at(i-10)->at(34-j) = tmpMass;
				}
			}
		////////////////////////////////////////////////////////////////////////////
		for(int j = 1;j < NECKWIDTH+1;j++)
			for(int i = 0;i < NECKHEIGHT;i ++){
				tmpMass = new Mass(-j* PXWIDTH,i * PXWIDTH,-BODYTHIN);
				massCloth.push_back(tmpMass);
				



				if(i < 4){

				}
				if(i > 2 && i < 11){
					showMass_body_centerb.at(i-3).at(11-j) = tmpMass;
					//showMass_body_centerb
				}
				if(i > 9){
					showMass_body_down.at(i-10)->at(34+j) = tmpMass;
				}
			}
		for(int j = NECKWIDTH+1;j < NECKWIDTH+3;j++)
			for(int i = 1;i < NECKHEIGHT;i ++){
				tmpMass = new Mass(-j* PXWIDTH,i * PXWIDTH,-BODYTHIN);
				massCloth.push_back(tmpMass);
				
				if(i == 1){
					massSeam.push_back(tmpMass);
				}


				if(i < 4){

				}
				if(i > 2 && i < 11){
					showMass_body_centerb.at(i-3).at(11-j) = tmpMass;
					//showMass_body_centerb
				}
				if(i > 9){
					showMass_body_down.at(i-10)->at(34+j) = tmpMass;
				}
			}
		for(int j = NECKWIDTH+3;j < NECKWIDTH+5;j++)
			for(int i = 2;i < NECKHEIGHT;i ++){
				tmpMass = new Mass(-j* PXWIDTH,i * PXWIDTH,-BODYTHIN);
				massCloth.push_back(tmpMass);
				
				if(i == 2){
					massSeam.push_back(tmpMass);
				}



				if(i < 4){

				}
				if(i > 2 && i < 11){
					showMass_body_centerb.at(i-3).at(11-j) = tmpMass;
					//showMass_body_centerb
				}
				if(i > 9){
					showMass_body_down.at(i-10)->at(34+j) = tmpMass;
				}
			}
		for(int j = NECKWIDTH+5;j < BODYWIDTH;j++)
			for(int i = 3;i < NECKHEIGHT;i ++){
				tmpMass = new Mass(-j* PXWIDTH,i * PXWIDTH,-BODYTHIN);
				massCloth.push_back(tmpMass);
				
				if(i == 3){
					massSeam.push_back(tmpMass);
				}

				if(j == BODYWIDTH - 1 ){
					massSeam1.push_back(tmpMass);
				}



				if(i < 4){

				}
				if(i > 2 && i < 11){
					showMass_body_centerb.at(i-3).at(11-j) = tmpMass;
					//showMass_body_centerb
				}
				if(i > 9){
					showMass_body_down.at(i-10)->at(34+j) = tmpMass;
				}
			}
	}else if(loc == 3){///////////////////左手臂前
		vector<Mass*> tmpShowLA;

		for(int j = BODYWIDTH;j < ARMWIDTH;j++){
			tmpShowLA = vector<Mass*>();
			for(int i = 0;i < ARMHEIGHT;i ++){
				tmpMass = new Mass( j* PXWIDTH,i * PXWIDTH + 3*PXWIDTH,BODYTHIN );
				massCloth.push_back(tmpMass);

				tmpShowLA.push_back(tmpMass);

				if(i == 0){
					massSeam.push_back(tmpMass);
				}

				if(j == BODYWIDTH ){
					massSeam1.push_back(tmpMass);
				}

				if(i == ARMHEIGHT-1){
					massSeam.push_back(tmpMass);
				}
			}
			showMass_larm.push_back(tmpShowLA);
		}
	}else if(loc == 4){///////////////////写左手臂后
		vector<Mass*>  tmpShowLA;
		int z = 0;
		for(int j = BODYWIDTH;j < ARMWIDTH;j++){
			tmpShowLA = vector<Mass*>();
			for(int i = 0;i < ARMHEIGHT;i ++){
				tmpMass = new Mass(j* PXWIDTH,i * PXWIDTH + 3*PXWIDTH,-BODYTHIN);
				massCloth.push_back(tmpMass);


				tmpShowLA.push_back(tmpMass);


				if(i == 0){
					massSeam.push_back(tmpMass);
				}

				if(j == BODYWIDTH ){
					massSeam1.push_back(tmpMass);
				}

				if(i == ARMHEIGHT-1){
					massSeam.push_back(tmpMass);
				}
			}
			for(int kkk = tmpShowLA.size()-1; kkk >= 0;kkk --){
				showMass_larm.at(z).push_back(tmpShowLA.at(kkk));
			}
			z++;
		}
	}else if(loc == 5){///////////////////右手臂前
		vector<Mass*> tmpShowLA;
		for(int j = BODYWIDTH;j < ARMWIDTH;j++){
			tmpShowLA = vector<Mass*>();
			for(int i = 0;i < ARMHEIGHT;i ++){
				tmpMass = new Mass(-j* PXWIDTH,i * PXWIDTH + 3*PXWIDTH,BODYTHIN );
				massCloth.push_back(tmpMass);
				tmpShowLA.push_back(tmpMass);


				if(i == 0){
					massSeam.push_back(tmpMass);
				}

				if(j == BODYWIDTH){
					massSeam1.push_back(tmpMass);
				}

				if(i == ARMHEIGHT-1){
					massSeam.push_back(tmpMass);
				}
			}
			showMass_rarm.push_back(tmpShowLA);
		}
	}else if(loc == 6){///////////////////右手臂后
		vector<Mass*>  tmpShowLA;
		int z = 0;
		for(int j = BODYWIDTH;j < ARMWIDTH;j++){
			tmpShowLA = vector<Mass*>();
			for(int i = 0;i < ARMHEIGHT;i ++){
				tmpMass = new Mass(-j* PXWIDTH,i * PXWIDTH + 3*PXWIDTH,-BODYTHIN);
				massCloth.push_back(tmpMass);
				tmpShowLA.push_back(tmpMass);


				if(i == 0){
					massSeam.push_back(tmpMass);
				}

				if(j == BODYWIDTH ){
					massSeam1.push_back(tmpMass);
				}

				if(i == ARMHEIGHT-1){
					massSeam.push_back(tmpMass);
				}
			}
			for(int kkk = tmpShowLA.size()-1; kkk >= 0;kkk --){
				showMass_rarm.at(z).push_back(tmpShowLA.at(kkk));
			}
			z++;

		}

	}else{
		perror("Cloth readClothFile 读取衣片错误\n");
		return false;
	}
	
	return true;
}
/**获取衣服的质点集合*/
vector<Mass*> * Cloth::getVectorMass(){
	return &massCloth;
}