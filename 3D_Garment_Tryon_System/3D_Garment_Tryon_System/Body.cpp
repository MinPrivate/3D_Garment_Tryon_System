#include "StdAfx.h"
#include "Body.h"
#include "MyMathFormula.h"

Body::Body(void)
{
	//将身体的每一个部分放到一个集合PartCollection当中
	PartCollection = vector<BodyPart *>();
	PartCollectionX = vector<BodyPart *>();
	PartCollectionY = vector<BodyPart *>();
	PartCollectionZ = vector<BodyPart *>();

	//PartCollection中元素0~19
	PartCollection.push_back(&head);	//0
	PartCollection.push_back(&neck);	//1

	PartCollection.push_back(&lhand);		//2
	PartCollection.push_back(&lforearm);
	PartCollection.push_back(&lshoulder);
	PartCollection.push_back(&lcollar);		//5
	PartCollection.push_back(&rcollar);
	PartCollection.push_back(&rshoulder);
	PartCollection.push_back(&rforearm);
	PartCollection.push_back(&rhand);		//9

	PartCollection.push_back(&chest);		//10
	PartCollection.push_back(&abdomen);
	PartCollection.push_back(&hip);		//12

	PartCollection.push_back(&lthigh);	//13
	PartCollection.push_back(&rthigh);
	PartCollection.push_back(&lshin);
	PartCollection.push_back(&rshin);	//16

	PartCollection.push_back(&lfoot);	//17
	PartCollection.push_back(&rfoot);	//18
}

Body::~Body(void)
{

}

bool Body::readOBJFile()
{
	char * filename;
	if(sex==1)	filename = "./res/1.obj";
	if(sex==0)	filename = "./res/0.obj";

/*
	读取obj文件的顶点坐标		Start
*/



	FILE *dataFile;				//读入的文件
    int count;					//输入数量的计数器
    char inputLine[512];	
    int ilLen;					//线的长度
    float x, y, z;			    //顶点坐标
	dataFile = fopen(filename, "r");
    if (dataFile == NULL) {
		perror(filename);
		return false;
    }

	BodyPart * tmpvect = new BodyPart();

	for(;;) {
		if (fgets(inputLine, 500, dataFile) == NULL)
			break;			//文件结尾

		//获得线的长度
		ilLen = strlen(inputLine);

		while ((ilLen > 0) && ((inputLine[ilLen - 1] == ' ') || (inputLine[ilLen - 1] == '\n')))
			ilLen--;
		

		if (inputLine[0] == 'v') {
			//读入一个顶点，并将其保存到点的数组中

			if (inputLine[1] == ' ') {
			//一个顶点
			count = sscanf(inputLine, "v %f %f %f", &x, &y, &z);
			if (count != 3)
				continue;
				
				Dot *tmp = new Dot(x,y,z);
				tmpvect->dotCollection.push_back(*tmp);

			}
		}
		else if(inputLine[0] == '#'){
			if(strstr(inputLine,"InternalName")){
				if(strstr(inputLine,"hip")){
						tmpvect = &hip;
				} else if(strstr(inputLine,"abdomen")){
						tmpvect = &abdomen;
				}else
					if(strstr(inputLine,"chest")){
										tmpvect = &chest;
				}else
					if(strstr(inputLine,"neck")){
										tmpvect = &neck;
				}else
					if(strstr(inputLine,"head")){
										tmpvect = &head;
				}else
					if(strstr(inputLine,"lCollar")){
										tmpvect = &lcollar;
				}else
					if(strstr(inputLine,"lForeArm")){
										tmpvect = &lforearm;
				}else
					if(strstr(inputLine,"lHand")){
										tmpvect = &lhand;
				}else
					if(strstr(inputLine,"rCollar")){
										tmpvect = &rcollar;
				}else
					if(strstr(inputLine,"rForeArm")){
										tmpvect = &rforearm;
				}else
					if(strstr(inputLine,"rHand")){
										tmpvect = &rhand;
				}else
					if(strstr(inputLine,"lThigh")){
										tmpvect = &lthigh;
				}else
					if(strstr(inputLine,"lShin")){
										tmpvect = &lshin;
				}else
					if(strstr(inputLine,"lFoot")){
										tmpvect = &lfoot;
				}else
					if(strstr(inputLine,"rThigh")){
										tmpvect = &rthigh;
				}else
					if(strstr(inputLine,"rShin")){
										tmpvect = &rshin;
				}else
					if(strstr(inputLine,"rFoot")){
										tmpvect = &rfoot;
				}else
					if(strstr(inputLine,"rShldr")){
										tmpvect = &rshoulder;
				}else
					if(strstr(inputLine,"lShldr")){
										tmpvect = &lshoulder;
				}else{
					exit(-1);
				}

			}
		}
	}
	fclose(dataFile);
	


/*
	读取obj文件的顶点坐标		End
*/


/*
	按照身高比例缩放到相应坐标	Start
*/

	float yMax = 0.0;
	for(int i=0;i<PartCollection.size() ;i++)
	{
		for(int j=0;j<PartCollection.at(i)->dotCollection.size() ;j++)
		{
			if(yMax<PartCollection.at(i)->dotCollection.at(j).y)
			{
				yMax = PartCollection.at(i)->dotCollection.at(j).y;
			}
		}
	}

	for(int i=0;i<PartCollection.size() ;i++)
	{
		for(int j=0;j<PartCollection.at(i)->dotCollection.size() ;j++)
		{
			PartCollection.at(i)->dotCollection.at(j).x = height*PartCollection.at(i)->dotCollection.at(j).x; 
			PartCollection.at(i)->dotCollection.at(j).y = height*PartCollection.at(i)->dotCollection.at(j).y;
			PartCollection.at(i)->dotCollection.at(j).z = height*PartCollection.at(i)->dotCollection.at(j).z;
		}
	}

	for(int i=0;i<PartCollection.size() ;i++)
	{
		for(int j=0;j<PartCollection.at(i)->dotCollection.size() ;j++)
		{
			PartCollection.at(i)->dotCollection.at(j).x = PartCollection.at(i)->dotCollection.at(j).x/yMax; 
			PartCollection.at(i)->dotCollection.at(j).y = PartCollection.at(i)->dotCollection.at(j).y/yMax;
			PartCollection.at(i)->dotCollection.at(j).z = PartCollection.at(i)->dotCollection.at(j).z/yMax;
		}
	}


/*
	按照身高比例缩放到相应坐标	End
*/

	return true;
}

void Body::triangulate()
{
	triangulateX(&rhand,30,20,10);
	triangulateX(&lhand,30,20,10);
	triangulateX(&rforearm,30,20,10);
	triangulateX(&lforearm,30,20,10);
	triangulateX(&rshoulder,30,20,10);
	triangulateX(&lshoulder,30,20,10);

	triangulateY(&abdomen,30,20,5);
	triangulateY(&head,30,20,10);
	triangulateY(&neck,30,20,10);
	triangulateY(&chest,30,20,10);
	triangulateY(&hip,30,20,5);
	triangulateY(&rcollar,30,20,10);
	triangulateY(&lcollar,30,20,10);
	triangulateY(&rthigh,30,20,10);
	triangulateY(&lthigh,30,20,10);
	triangulateY(&rshin,30,20,10);
	triangulateY(&lshin,30,20,10);

	triangulateZ(&lfoot,30,20,10);
	triangulateZ(&rfoot,30,20,10);
}

int cmpX(const Dot &a, const Dot &b)
{
	if(a.x<b.x)
		return 1;
	else
		return 0;
}
int cmpY(const Dot &a, const Dot &b)
{
	if(a.y<b.y)
		return 1;
	else
		return 0;
}
int cmpZ(const Dot &a, const Dot &b)
{
	if(a.z<b.z)
		return 1;
	else
		return 0;
}

void Body::sortAsClockX(vector<Dot> * currentcircle)
{
	//确定中心点 Start
	Dot centerdot(0.0,0.0,0.0);
	for(int k=0;k<currentcircle->size();k++)
	{
		//centerdot.x = centerdot.x + currentcircle->at(k).x;
		centerdot.y = centerdot.y + currentcircle->at(k).y;
		centerdot.z = centerdot.z + currentcircle->at(k).z;
	}
	centerdot.x = currentcircle->at(0).x;
	centerdot.y = centerdot.y/currentcircle->size();
	centerdot.z = centerdot.z/currentcircle->size();
	//确定中心点 End


	//确定首点
	Dot firstDot1 = Dot(currentcircle->at(0).x,currentcircle->at(0).y,currentcircle->at(0).z);
	//确定首向量
	Dot datumvector1 = Dot(currentcircle->at(0).x-centerdot.x,currentcircle->at(0).y-centerdot.y,currentcircle->at(0).z-centerdot.z);
	//确定首点的对应点
	Dot firstDot2 = CalculateCorrespondDot(firstDot1,centerdot);
	//确定首点的对应点的向量
	Dot datumvector2 = Dot(firstDot2.x-centerdot.x,firstDot2.y-centerdot.y,firstDot2.z-centerdot.z);


	//确定相应的从中心点发出的向量 Start
	vector<Dot> center_vector;
	for(int k=0;k<currentcircle->size();k++)
	{
		Dot *tmpDot = new Dot(currentcircle->at(k).x-centerdot.x,currentcircle->at(k).y-centerdot.y,currentcircle->at(k).z-centerdot.z);
		center_vector.push_back(*tmpDot);
	}
	//确定相应的从中心点发出的向量 End


	vector<float> center_arc;	//确定相应的从中心点发出的向量间的角度的cos值 Start

	for(int k=0;k<currentcircle->size();k++)
	{
		float tmparc;
		if( UpOrDownX(firstDot1,firstDot2,currentcircle->at(k)) ==1)		//在上
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector1) + 2;
		}
		else	//在下
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector2);
		}

		center_arc.push_back(tmparc);
	}
	//确定相应的从中心点发出的向量间的角度的cos值 End



	//根据center_arc的相应的值，cos值从高到低，即是，距离基准点顺时针的从远到近 Start
	

	//冒泡排序，大者在前，小者在后，每一轮将最小元素排至最后
	for(int i=0;i<center_arc.size()-1;i++)	//每一轮的循环
	{
		for(int j=0;j<center_arc.size()-i-1;j++)	//每轮中的对两者比较的循环
		{
			//如小于则相换
			if(center_arc.at(j)<center_arc.at(j+1))
			{
				float tmparc = 0.0;
				Dot tmpdot = Dot(0.0,0.0,0.0);
				tmparc = center_arc.at(j+1);
				center_arc.at(j+1) = center_arc.at(j);
				center_arc.at(j) = tmparc;
				tmpdot = currentcircle->at(j);
				currentcircle->at(j) = currentcircle->at(j+1);
				currentcircle->at(j+1) = tmpdot;
			}
		}
	}


	//根据center_arc的相应的值，cos值从高到低，即是，距离基准点顺时针的从远到近 End


}
void Body::sortAsClockY(vector<Dot> * currentcircle)
{
	//确定中心点 Start
	Dot centerdot(0.0,0.0,0.0);
	for(int k=0;k<currentcircle->size();k++)
	{
		centerdot.x = centerdot.x + currentcircle->at(k).x;
		//centerdot.y = centerdot.y + currentcircle->at(k).y;
		centerdot.z = centerdot.z + currentcircle->at(k).z;
	}
	centerdot.x = centerdot.x/currentcircle->size();
	centerdot.y = currentcircle->at(0).y;
	centerdot.z = centerdot.z/currentcircle->size();
	//确定中心点 End


	//确定首点
	Dot firstDot1 = Dot(currentcircle->at(0).x,currentcircle->at(0).y,currentcircle->at(0).z);
	//确定首向量
	Dot datumvector1 = Dot(currentcircle->at(0).x-centerdot.x,currentcircle->at(0).y-centerdot.y,currentcircle->at(0).z-centerdot.z);
	//确定首点的对应点
	Dot firstDot2 = CalculateCorrespondDot(firstDot1,centerdot);
	//确定首点的对应点的向量
	Dot datumvector2 = Dot(firstDot2.x-centerdot.x,firstDot2.y-centerdot.y,firstDot2.z-centerdot.z);


	//确定相应的从中心点发出的向量 Start
	vector<Dot> center_vector;
	for(int k=0;k<currentcircle->size();k++)
	{
		Dot *tmpDot = new Dot(currentcircle->at(k).x-centerdot.x,currentcircle->at(k).y-centerdot.y,currentcircle->at(k).z-centerdot.z);
		center_vector.push_back(*tmpDot);
	}
	//确定相应的从中心点发出的向量 End


	vector<float> center_arc;	//确定相应的从中心点发出的向量间的角度的cos值 Start

	for(int k=0;k<currentcircle->size();k++)
	{
		float tmparc;
		if( UpOrDownY(firstDot1,firstDot2,currentcircle->at(k)) ==1)		//在上
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector1) + 2;
		}
		else	//在下
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector2);
		}

		center_arc.push_back(tmparc);
	}
	//确定相应的从中心点发出的向量间的角度的cos值 End



	//根据center_arc的相应的值，cos值从高到低，即是，距离基准点顺时针的从远到近 Start
	

	//冒泡排序，大者在前，小者在后，每一轮将最小元素排至最后
	for(int i=0;i<center_arc.size()-1;i++)	//每一轮的循环
	{
		for(int j=0;j<center_arc.size()-i-1;j++)	//每轮中的对两者比较的循环
		{
			//如小于则相换
			if(center_arc.at(j)<center_arc.at(j+1))
			{
				float tmparc = 0.0;
				Dot tmpdot = Dot(0.0,0.0,0.0);
				tmparc = center_arc.at(j+1);
				center_arc.at(j+1) = center_arc.at(j);
				center_arc.at(j) = tmparc;
				tmpdot = currentcircle->at(j);
				currentcircle->at(j) = currentcircle->at(j+1);
				currentcircle->at(j+1) = tmpdot;
			}
		}
	}


	//根据center_arc的相应的值，cos值从高到低，即是，距离基准点顺时针的从远到近 End


}
void Body::sortAsClockZ(vector<Dot> * currentcircle)
{
	//确定中心点 Start
	Dot centerdot(0.0,0.0,0.0);
	for(int k=0;k<currentcircle->size();k++)
	{
		centerdot.x = centerdot.x + currentcircle->at(k).x;
		centerdot.y = centerdot.y + currentcircle->at(k).y;
		//centerdot.z = centerdot.z + currentcircle->at(k).z;
	}
	centerdot.x = centerdot.x/currentcircle->size();
	centerdot.y = centerdot.z/currentcircle->size();
	centerdot.z = currentcircle->at(0).z;
	//确定中心点 End


	//确定首点
	Dot firstDot1 = Dot(currentcircle->at(0).x,currentcircle->at(0).y,currentcircle->at(0).z);
	//确定首向量
	Dot datumvector1 = Dot(currentcircle->at(0).x-centerdot.x,currentcircle->at(0).y-centerdot.y,currentcircle->at(0).z-centerdot.z);
	//确定首点的对应点
	Dot firstDot2 = CalculateCorrespondDot(firstDot1,centerdot);
	//确定首点的对应点的向量
	Dot datumvector2 = Dot(firstDot2.x-centerdot.x,firstDot2.y-centerdot.y,firstDot2.z-centerdot.z);


	//确定相应的从中心点发出的向量 Start
	vector<Dot> center_vector;
	for(int k=0;k<currentcircle->size();k++)
	{
		Dot *tmpDot = new Dot(currentcircle->at(k).x-centerdot.x,currentcircle->at(k).y-centerdot.y,currentcircle->at(k).z-centerdot.z);
		center_vector.push_back(*tmpDot);
	}
	//确定相应的从中心点发出的向量 End


	vector<float> center_arc;	//确定相应的从中心点发出的向量间的角度的cos值 Start

	for(int k=0;k<currentcircle->size();k++)
	{
		float tmparc;
		if( UpOrDownZ(firstDot1,firstDot2,currentcircle->at(k)) ==1)		//在上
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector1) + 2;
		}
		else	//在下
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector2);
		}

		center_arc.push_back(tmparc);
	}
	//确定相应的从中心点发出的向量间的角度的cos值 End



	//根据center_arc的相应的值，cos值从高到低，即是，距离基准点顺时针的从远到近 Start
	

	//冒泡排序，大者在前，小者在后，每一轮将最小元素排至最后
	for(int i=0;i<center_arc.size()-1;i++)	//每一轮的循环
	{
		for(int j=0;j<center_arc.size()-i-1;j++)	//每轮中的对两者比较的循环
		{
			//如小于则相换
			if(center_arc.at(j)<center_arc.at(j+1))
			{
				float tmparc = 0.0;
				Dot tmpdot = Dot(0.0,0.0,0.0);
				tmparc = center_arc.at(j+1);
				center_arc.at(j+1) = center_arc.at(j);
				center_arc.at(j) = tmparc;
				tmpdot = currentcircle->at(j);
				currentcircle->at(j) = currentcircle->at(j+1);
				currentcircle->at(j+1) = tmpdot;
			}
		}
	}


	//根据center_arc的相应的值，cos值从高到低，即是，距离基准点顺时针的从远到近 End


}

void Body::triangulateX(BodyPart * currentBodyPart,int max,int min,int circleNum)
{
	//对某一个方向排序
	sort(currentBodyPart->dotCollection.begin(),currentBodyPart->dotCollection.end(),cmpX);

	


	//分成圈
	//按照应分的圈数=circleNum
	float gap = (fabs(currentBodyPart->dotCollection.at(0).x - currentBodyPart->dotCollection.at(currentBodyPart->dotCollection.size()-1).x))/circleNum;
	float boundary1 =  currentBodyPart->dotCollection.at(0).x;
	float boundary2 =  currentBodyPart->dotCollection.at(currentBodyPart->dotCollection.size()-1).x;
	//因为按升序排了，所以boundary2必定大于boundary1，boundary2在右，boundary1在左
	float newboundary1 = boundary1 - gap/2;
	float newboundary2 = boundary1 + gap/2;
	float circlevalue = boundary1;

	vector<Dot> * tmpvector = new vector<Dot>();
	for(int i=0;i<currentBodyPart->dotCollection.size();i++)
	{
		if(currentBodyPart->dotCollection.at(i).x>=newboundary1 && currentBodyPart->dotCollection.at(i).x<=newboundary2)	
		//尚在此层中
		{
			//生成一个点，其点的坐标x在圈上，其余yz与本循环的点相同
			Dot * tmpdot = new Dot(circlevalue,currentBodyPart->dotCollection.at(i).y,currentBodyPart->dotCollection.at(i).z);
			tmpvector->push_back(*tmpdot);
			//不能在此处delete指针
		}
		//需进入下一层，且需移动一个gap
		else if((tmpvector->size()) >= min)
		{
			currentBodyPart->circleCollection.push_back(*tmpvector);
			tmpvector = new vector<Dot>();

			newboundary1 = newboundary1 + gap;
	        newboundary2 = newboundary2 + gap;
			circlevalue = circlevalue + gap;
		}
		//需移动一个gap，但因最小值要求，不进入下一层
		else
		{
			newboundary1 = newboundary1 + gap;
	        newboundary2 = newboundary2 + gap;
			circlevalue = circlevalue + gap;

			//修改上层[没满min的层]的x为下层的circlevalue
			for(int j=0;j<tmpvector->size();j++)
			{
				tmpvector->at(j).x = circlevalue;
			}
		}
	}
	
	




	//按最大值，调整圈中点数
	for(int i=0;i<currentBodyPart->circleCollection.size();i++)	
	{
		if(currentBodyPart->circleCollection.at(i).size()>max)
		{
			//删除多余点，按多出的点数，确定间隔来删
			float deleteNum = currentBodyPart->circleCollection.at(i).size() - max + 1;
			float deleteGap = currentBodyPart->circleCollection.at(i).size()/deleteNum;
			float deleteCurrent = 0.0;
			
			for(int k=deleteNum;k>0;k--)
			{
				deleteCurrent += deleteGap;
				if(deleteCurrent>currentBodyPart->circleCollection.at(i).size())
				{
					deleteCurrent -= currentBodyPart->circleCollection.at(i).size();
				}

				//将vector待删点后面的值往前赋
				for(int r=int(deleteCurrent);r<currentBodyPart->circleCollection.at(i).size()-1;r++)
				{
					currentBodyPart->circleCollection.at(i).at(r) = currentBodyPart->circleCollection.at(i).at(r+1);
				}
				//删除最后一个元素
				currentBodyPart->circleCollection.at(i).pop_back();
			}
		}
	}


	circleNum = currentBodyPart->circleCollection.size();


	//将每一圈的首点调整为最近距离
	//确定基准点
	Dot datumDot = currentBodyPart->circleCollection.at(0).at(0);
	int nearest = 0;	//最近点的索引
	float minest_distance = 0.0;
	for(int i=0;i<currentBodyPart->circleCollection.size();i++)	//对圈循环
	{
		minest_distance = (currentBodyPart->circleCollection.at(i).at(0).x - datumDot.x)*(currentBodyPart->circleCollection.at(i).at(0).x - datumDot.x)+(currentBodyPart->circleCollection.at(i).at(0).y - datumDot.y)*(currentBodyPart->circleCollection.at(i).at(0).y - datumDot.y)+(currentBodyPart->circleCollection.at(i).at(0).z - datumDot.z)*(currentBodyPart->circleCollection.at(i).at(0).z - datumDot.z);

		for(int j=0;j<currentBodyPart->circleCollection.at(i).size();j++)	//对圈中点循环找出最近的点
		{
			if(minest_distance>(currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)*(currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)+(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)*(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)+(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z)*(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z))
			{
				nearest = j;
				minest_distance = (currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)*(currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)+(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)*(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)+(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z)*(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z);
			}
		}
		//将最近点放到圈首
		Dot tmpDot(currentBodyPart->circleCollection.at(i).at(nearest).x,currentBodyPart->circleCollection.at(i).at(nearest).y,currentBodyPart->circleCollection.at(i).at(nearest).z);
		currentBodyPart->circleCollection.at(i).at(nearest).x = currentBodyPart->circleCollection.at(i).at(0).x;
		currentBodyPart->circleCollection.at(i).at(nearest).y = currentBodyPart->circleCollection.at(i).at(0).y;
		currentBodyPart->circleCollection.at(i).at(nearest).z = currentBodyPart->circleCollection.at(i).at(0).z;
		currentBodyPart->circleCollection.at(i).at(0).x = tmpDot.x;
		currentBodyPart->circleCollection.at(i).at(0).y = tmpDot.y;
		currentBodyPart->circleCollection.at(i).at(0).z = tmpDot.z;

		//修改循环量
		nearest = 0;
		datumDot = currentBodyPart->circleCollection.at(i).at(0);
	}





	//按同一时针方向排序点
	for(int i=0;i<currentBodyPart->circleCollection.size();i++)	//对圈循环
	{
		//针对一圈进行按时针方向排序点
		sortAsClockX(&currentBodyPart->circleCollection.at(i));
	}





	//circleCollection中是三角剖分好的点集，dotCollection仍是原先的点集


}
void Body::triangulateY(BodyPart * currentBodyPart,int max,int min,int circleNum)
{
	sort(currentBodyPart->dotCollection.begin(),currentBodyPart->dotCollection.end(),cmpY);
	
	


	//分成圈
	//按照应分的圈数=circleNum
	float gap = (fabs(currentBodyPart->dotCollection.at(0).y - currentBodyPart->dotCollection.at(currentBodyPart->dotCollection.size()-1).y))/circleNum;
	float boundary1 =  currentBodyPart->dotCollection.at(0).y;
	float boundary2 =  currentBodyPart->dotCollection.at(currentBodyPart->dotCollection.size()-1).y;
	//因为按升序排了，所以boundary2必定大于boundary1，boundary2在右，boundary1在左
	float newboundary1 = boundary1 - gap/2;
	float newboundary2 = boundary1 + gap/2;
	float circlevalue = boundary1;

	vector<Dot> * tmpvector = new vector<Dot>();
	for(int i=0;i<currentBodyPart->dotCollection.size();i++)
	{
		if(currentBodyPart->dotCollection.at(i).y>=newboundary1 && currentBodyPart->dotCollection.at(i).y<=newboundary2)	
		//尚在此层中
		{
			//生成一个点，其点的坐标x在圈上，其余yz与本循环的点相同
			Dot * tmpdot = new Dot(currentBodyPart->dotCollection.at(i).x,circlevalue,currentBodyPart->dotCollection.at(i).z);
			tmpvector->push_back(*tmpdot);
			//不能在此处delete指针
		}
		//需进入下一层，且需移动一个gap
		else if((tmpvector->size()) >= min)
		{
			currentBodyPart->circleCollection.push_back(*tmpvector);
			tmpvector = new vector<Dot>();

			newboundary1 = newboundary1 + gap;
	        newboundary2 = newboundary2 + gap;
			circlevalue = circlevalue + gap;
		}
		//需移动一个gap，但因最小值要求，不进入下一层
		else
		{
			newboundary1 = newboundary1 + gap;
	        newboundary2 = newboundary2 + gap;
			circlevalue = circlevalue + gap;

			//修改上层[没满min的层]的x为下层的circlevalue
			for(int j=0;j<tmpvector->size();j++)
			{
				tmpvector->at(j).y = circlevalue;
			}
		}
	}
	
	




	//按最大值，调整圈中点数
	for(int i=0;i<currentBodyPart->circleCollection.size();i++)	
	{
		if(currentBodyPart->circleCollection.at(i).size()>max)
		{
			//删除多余点，按多出的点数，确定间隔来删
			float deleteNum = currentBodyPart->circleCollection.at(i).size() - max + 1;
			float deleteGap = currentBodyPart->circleCollection.at(i).size()/deleteNum;
			float deleteCurrent = 0.0;
			
			for(int k=deleteNum;k>0;k--)
			{
				deleteCurrent += deleteGap;
				if(deleteCurrent>currentBodyPart->circleCollection.at(i).size())
				{
					deleteCurrent -= currentBodyPart->circleCollection.at(i).size();
				}

				//将vector待删点后面的值往前赋
				for(int r=int(deleteCurrent);r<currentBodyPart->circleCollection.at(i).size()-1;r++)
				{
					currentBodyPart->circleCollection.at(i).at(r) = currentBodyPart->circleCollection.at(i).at(r+1);
				}
				//删除最后一个元素
				currentBodyPart->circleCollection.at(i).pop_back();
			}
		}
	}


	circleNum = currentBodyPart->circleCollection.size();


	//将每一圈的首点调整为最近距离
	//确定基准点
	Dot datumDot = currentBodyPart->circleCollection.at(0).at(0);
	int nearest = 0;	//最近点的索引
	float minest_distance = 0.0;
	for(int i=0;i<currentBodyPart->circleCollection.size();i++)	//对圈循环
	{
		minest_distance = (currentBodyPart->circleCollection.at(i).at(0).x - datumDot.x)*(currentBodyPart->circleCollection.at(i).at(0).x - datumDot.x)+(currentBodyPart->circleCollection.at(i).at(0).y - datumDot.y)*(currentBodyPart->circleCollection.at(i).at(0).y - datumDot.y)+(currentBodyPart->circleCollection.at(i).at(0).z - datumDot.z)*(currentBodyPart->circleCollection.at(i).at(0).z - datumDot.z);

		for(int j=0;j<currentBodyPart->circleCollection.at(i).size();j++)	//对圈中点循环找出最近的点
		{
			if(minest_distance>(currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)*(currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)+(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)*(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)+(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z)*(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z))
			{
				nearest = j;
				minest_distance = (currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)*(currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)+(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)*(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)+(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z)*(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z);
			}
		}
		//将最近点放到圈首
		Dot tmpDot(currentBodyPart->circleCollection.at(i).at(nearest).x,currentBodyPart->circleCollection.at(i).at(nearest).y,currentBodyPart->circleCollection.at(i).at(nearest).z);
		currentBodyPart->circleCollection.at(i).at(nearest).x = currentBodyPart->circleCollection.at(i).at(0).x;
		currentBodyPart->circleCollection.at(i).at(nearest).y = currentBodyPart->circleCollection.at(i).at(0).y;
		currentBodyPart->circleCollection.at(i).at(nearest).z = currentBodyPart->circleCollection.at(i).at(0).z;
		currentBodyPart->circleCollection.at(i).at(0).x = tmpDot.x;
		currentBodyPart->circleCollection.at(i).at(0).y = tmpDot.y;
		currentBodyPart->circleCollection.at(i).at(0).z = tmpDot.z;

		//修改循环量
		nearest = 0;
		datumDot = currentBodyPart->circleCollection.at(i).at(0);
	}





	//按同一时针方向排序点
	for(int i=0;i<currentBodyPart->circleCollection.size();i++)	//对圈循环
	{
		//针对一圈进行按时针方向排序点
		sortAsClockY(&currentBodyPart->circleCollection.at(i));
	}





	//circleCollection中是三角剖分好的点集，dotCollection仍是原先的点集


}
void Body::triangulateZ(BodyPart * currentBodyPart,int max,int min,int circleNum)
{
	sort(currentBodyPart->dotCollection.begin(),currentBodyPart->dotCollection.end(),cmpZ);
	
	


	//分成圈
	//按照应分的圈数=circleNum
	float gap = (fabs(currentBodyPart->dotCollection.at(0).z - currentBodyPart->dotCollection.at(currentBodyPart->dotCollection.size()-1).z))/circleNum;
	float boundary1 =  currentBodyPart->dotCollection.at(0).z;
	float boundary2 =  currentBodyPart->dotCollection.at(currentBodyPart->dotCollection.size()-1).z;
	//因为按升序排了，所以boundary2必定大于boundary1，boundary2在右，boundary1在左
	float newboundary1 = boundary1 - gap/2;
	float newboundary2 = boundary1 + gap/2;
	float circlevalue = boundary1;

	vector<Dot> * tmpvector = new vector<Dot>();
	for(int i=0;i<currentBodyPart->dotCollection.size();i++)
	{
		if(currentBodyPart->dotCollection.at(i).z>=newboundary1 && currentBodyPart->dotCollection.at(i).z<=newboundary2)	
		//尚在此层中
		{
			//生成一个点，其点的坐标x在圈上，其余yz与本循环的点相同
			Dot * tmpdot = new Dot(currentBodyPart->dotCollection.at(i).x,currentBodyPart->dotCollection.at(i).y,circlevalue);
			tmpvector->push_back(*tmpdot);
			//不能在此处delete指针
		}
		//需进入下一层，且需移动一个gap
		else if((tmpvector->size()) >= min)
		{
			currentBodyPart->circleCollection.push_back(*tmpvector);
			tmpvector = new vector<Dot>();

			newboundary1 = newboundary1 + gap;
	        newboundary2 = newboundary2 + gap;
			circlevalue = circlevalue + gap;
		}
		//需移动一个gap，但因最小值要求，不进入下一层
		else
		{
			newboundary1 = newboundary1 + gap;
	        newboundary2 = newboundary2 + gap;
			circlevalue = circlevalue + gap;

			//修改上层[没满min的层]的x为下层的circlevalue
			for(int j=0;j<tmpvector->size();j++)
			{
				tmpvector->at(j).z = circlevalue;
			}
		}
	}
	
	




	//按最大值，调整圈中点数
	for(int i=0;i<currentBodyPart->circleCollection.size();i++)	
	{
		if(currentBodyPart->circleCollection.at(i).size()>max)
		{
			//删除多余点，按多出的点数，确定间隔来删
			float deleteNum = currentBodyPart->circleCollection.at(i).size() - max + 1;
			float deleteGap = currentBodyPart->circleCollection.at(i).size()/deleteNum;
			float deleteCurrent = 0.0;
			
			for(int k=deleteNum;k>0;k--)
			{
				deleteCurrent += deleteGap;
				if(deleteCurrent>currentBodyPart->circleCollection.at(i).size())
				{
					deleteCurrent -= currentBodyPart->circleCollection.at(i).size();
				}

				//将vector待删点后面的值往前赋
				for(int r=int(deleteCurrent);r<currentBodyPart->circleCollection.at(i).size()-1;r++)
				{
					currentBodyPart->circleCollection.at(i).at(r) = currentBodyPart->circleCollection.at(i).at(r+1);
				}
				//删除最后一个元素
				currentBodyPart->circleCollection.at(i).pop_back();
			}
		}
	}


	circleNum = currentBodyPart->circleCollection.size();


	//将每一圈的首点调整为最近距离
	//确定基准点
	Dot datumDot = currentBodyPart->circleCollection.at(0).at(0);
	int nearest = 0;	//最近点的索引
	float minest_distance = 0.0;
	for(int i=0;i<currentBodyPart->circleCollection.size();i++)	//对圈循环
	{
		minest_distance = (currentBodyPart->circleCollection.at(i).at(0).x - datumDot.x)*(currentBodyPart->circleCollection.at(i).at(0).x - datumDot.x)+(currentBodyPart->circleCollection.at(i).at(0).y - datumDot.y)*(currentBodyPart->circleCollection.at(i).at(0).y - datumDot.y)+(currentBodyPart->circleCollection.at(i).at(0).z - datumDot.z)*(currentBodyPart->circleCollection.at(i).at(0).z - datumDot.z);

		for(int j=0;j<currentBodyPart->circleCollection.at(i).size();j++)	//对圈中点循环找出最近的点
		{
			if(minest_distance>(currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)*(currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)+(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)*(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)+(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z)*(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z))
			{
				nearest = j;
				minest_distance = (currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)*(currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)+(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)*(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)+(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z)*(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z);
			}
		}
		//将最近点放到圈首
		Dot tmpDot(currentBodyPart->circleCollection.at(i).at(nearest).x,currentBodyPart->circleCollection.at(i).at(nearest).y,currentBodyPart->circleCollection.at(i).at(nearest).z);
		currentBodyPart->circleCollection.at(i).at(nearest).x = currentBodyPart->circleCollection.at(i).at(0).x;
		currentBodyPart->circleCollection.at(i).at(nearest).y = currentBodyPart->circleCollection.at(i).at(0).y;
		currentBodyPart->circleCollection.at(i).at(nearest).z = currentBodyPart->circleCollection.at(i).at(0).z;
		currentBodyPart->circleCollection.at(i).at(0).x = tmpDot.x;
		currentBodyPart->circleCollection.at(i).at(0).y = tmpDot.y;
		currentBodyPart->circleCollection.at(i).at(0).z = tmpDot.z;

		//修改循环量
		nearest = 0;
		datumDot = currentBodyPart->circleCollection.at(i).at(0);
	}





	//按同一时针方向排序点
	for(int i=0;i<currentBodyPart->circleCollection.size();i++)	//对圈循环
	{
		//针对一圈进行按时针方向排序点
		sortAsClockZ(&currentBodyPart->circleCollection.at(i));
	}





	//circleCollection中是三角剖分好的点集，dotCollection仍是原先的点集


}







void Body::creatSurface()
{
	creatSurfaceX();
	creatSurfaceY();
	creatSurfaceZ();
}

void Body::adjust()
{

}

void Body::creatSurfaceX()
{
	//rhand
	//lhand
	//rforearm
	//lforearm
	//rshoulder
	//lshoulder
	vector<Dot> *circle1 = NULL;
	vector<Dot> *circle2 = NULL;

	//rhand		右手
	for(int i = 0; i < rhand.circleCollection.size() - 1; i++)
	{
		//第一个圈
		circle1 = &rhand.circleCollection.at(i);	
		//第二个圈
		circle2 = &rhand.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		
		creatPartSurfaceX(circle1, circle2, &rhand.surfaceCollection);
	}


	//右手与右前臂连接	保存在右前臂中
	//右手的最后一个圈
	circle1 = &rhand.circleCollection.at(rhand.circleCollection.size() - 1);	
	//右前臂的第一个圈
	circle2 = &rforearm.circleCollection.at(0);
	//创建Surface并加入到SurfaceCollection
	creatPartSurfaceX(circle1, circle2, &rforearm.surfaceCollection);


	//rforearm		右前臂
	for(int i = 0; i < rforearm.circleCollection.size() - 1; i++)
	{
		//第一个圈
		circle1 = &rforearm.circleCollection.at(i);	
		//第二个圈
		circle2 = &rforearm.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		creatPartSurfaceX(circle1, circle2, &rforearm.surfaceCollection);
	}


	//右前臂与右肩部连接		保存在右前臂
	//右前臂的最后一个圈
	circle1 = &rforearm.circleCollection.at(rforearm.circleCollection.size() - 1);	
	//右肩部的第一个圈
	circle2 = &rshoulder.circleCollection.at(0);
	//创建Surface并加入到SurfaceCollection
	creatPartSurfaceX(circle1, circle2, &rforearm.surfaceCollection);

	//rshoulder		右肩部
	for(int i = 0; i < rshoulder.circleCollection.size() - 1; i++)
	{
		//第一个圈
		circle1 = &rshoulder.circleCollection.at(i);	
		//第二个圈
		circle2 = &rshoulder.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		creatPartSurfaceX(circle1, circle2, &rshoulder.surfaceCollection);
	}

	//lshoulder		左肩部
	for(int i = 0; i < lshoulder.circleCollection.size() - 1; i++)
	{
		//第一个圈
		circle1 = &lshoulder.circleCollection.at(i);	
		//第二个圈
		circle2 = &lshoulder.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		creatPartSurfaceX(circle1, circle2, &lshoulder.surfaceCollection);
	}


	//左肩部与左前臂连接		保存在左前臂
	//左肩部的最后一个圈
	circle1 = &lshoulder.circleCollection.at(lshoulder.circleCollection.size() - 1);	
	//左前臂的第一个圈
	circle2 = &lforearm.circleCollection.at(0);
	//创建Surface并加入到SurfaceCollection
	creatPartSurfaceX(circle1, circle2, &lforearm.surfaceCollection);


	//lforearm		左前臂
	for(int i = 0; i < lforearm.circleCollection.size() - 1; i++)
	{
		//第一个圈
		circle1 = &lforearm.circleCollection.at(i);	
		//第二个圈
		circle2 = &lforearm.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		creatPartSurfaceX(circle1, circle2, &lforearm.surfaceCollection);
	}


	//左前臂与左手的连接		保存在左前臂
	//左前臂的最后一个圈
	circle1 = &lforearm.circleCollection.at(lforearm.circleCollection.size() - 1);	
	//左手臂的第一个圈
	circle2 = &lhand.circleCollection.at(0);
	//创建Surface并加入到SurfaceCollection
	creatPartSurfaceX(circle1, circle2, &lforearm.surfaceCollection);


	//lhand		左手
	for(int i = 0; i < lhand.circleCollection.size() - 1; i++)
	{
		//第一个圈
		circle1 = &lhand.circleCollection.at(i);	
		//第二个圈
		circle2 = &lhand.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		creatPartSurfaceX(circle1, circle2, &lhand.surfaceCollection);
	}
}

void Body::creatSurfaceY()
{
	//abdomen	腹部 下腹
	//head		头
	//neck		脖子
	//chest		胸部
	//hip		臀部
	//rcollar	颈圈
	//lcollar	颈圈
	//rthigh	大腿
	//lthigh
	//rshin		小腿
	//lshin
	vector<Dot> *circle1 = NULL;	
	vector<Dot> *circle2 = NULL;

	//lshin		左小腿
	for(int i = 0; i < lshin.circleCollection.size() - 1; i++)
	{
		//第一个圈
		circle1 = &lshin.circleCollection.at(i);	
		//第二个圈
		circle2 = &lshin.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &lshin.surfaceCollection);
	}


	//左小腿与左大腿连接		保存在左小腿
	//左小腿最后一个圈
	circle1 = &lshin.circleCollection.at(lshin.circleCollection.size() - 1);	
	//左大腿的第一个圈
	circle2 = &lthigh.circleCollection.at(0);

	//创建Surface并加入到SurfaceCollection
	creatPartSurfaceY(circle1, circle2, &lshin.surfaceCollection);


	//lthigh		左大腿
	for(int i = 0; i < lthigh.circleCollection.size() - 1; i++)
	{
		//第一个圈
		circle1 = &lthigh.circleCollection.at(i);	
		//第二个圈
		circle2 = &lthigh.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &lthigh.surfaceCollection);
	}


	//rshin		右小腿
	for(int i = 0; i < rshin.circleCollection.size() - 1; i++)
	{
		//第一个圈
		circle1 = &rshin.circleCollection.at(i);	
		//第二个圈
		circle2 = &rshin.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &rshin.surfaceCollection);
	}


	//右小腿与右大腿连接	保存在右小腿
	//右小腿最后一个圈
	circle1 = &rshin.circleCollection.at(rshin.circleCollection.size() - 1);	
	//右大腿的第一个圈
	circle2 = &rthigh.circleCollection.at(0);

	//创建Surface并加入到SurfaceCollection
	creatPartSurfaceY(circle1, circle2, &rshin.surfaceCollection);


	//rthigh		右大腿
	for(int i = 0; i < rthigh.circleCollection.size() - 1; i++)
	{
		//第一个圈
		circle1 = &rthigh.circleCollection.at(i);	
		//第二个圈
		circle2 = &rthigh.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &rthigh.surfaceCollection);
	}

	
	//hip		臀部
	for(int i = 0; i < hip.circleCollection.size() - 1; i++)
	{
		//第一个圈
		circle1 = &hip.circleCollection.at(i);	
		//第二个圈
		circle2 = &hip.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &hip.surfaceCollection);
	}
	

	//臀部与小腹连接		保存在小腹
	//臀部最后一个圈
	circle1 = &hip.circleCollection.at(hip.circleCollection.size() - 1);	
	//小腹的第一个圈
	circle2 = &abdomen.circleCollection.at(0);

	//创建Surface并加入到SurfaceCollection
	creatPartSurfaceY(circle1, circle2, &abdomen.surfaceCollection);


	//abdomen	小腹
	for(int i = 0; i < abdomen.circleCollection.size() - 1; i++)
	{
		//第一个圈
		circle1 = &abdomen.circleCollection.at(i);	
		//第二个圈
		circle2 = &abdomen.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &abdomen.surfaceCollection);
	}


	//小腹与胸部连接		保存在小腹
	//小腹最后一个圈
	circle1 = &abdomen.circleCollection.at(abdomen.circleCollection.size() - 1);	
	//胸部的第一个圈
	circle2 = &chest.circleCollection.at(0);

	//创建Surface并加入到SurfaceCollection
	creatPartSurfaceY(circle1, circle2, &abdomen.surfaceCollection);


	//chest		胸部
	for(int i = 0; i < chest.circleCollection.size() - 1; i++)
	{
		//第一个圈
		circle1 = &chest.circleCollection.at(i);	
		//第二个圈
		circle2 = &chest.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &chest.surfaceCollection);
	}


	//rcollar
	for(int i = 0; i < rcollar.circleCollection.size() - 1; i++)
	{
		//第一个圈
		circle1 = &rcollar.circleCollection.at(i);	
		//第二个圈
		circle2 = &rcollar.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &rcollar.surfaceCollection);
	}


	//lcollar
	for(int i = 0; i < lcollar.circleCollection.size() - 1; i++)
	{
		//第一个圈
		circle1 = &lcollar.circleCollection.at(i);	
		//第二个圈
		circle2 = &lcollar.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &lcollar.surfaceCollection);
	}


	//neck		颈部
	for(int i = 0; i < neck.circleCollection.size() - 1; i++)
	{
		//第一个圈
		circle1 = &neck.circleCollection.at(i);	
		//第二个圈
		circle2 = &neck.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &neck.surfaceCollection);
	}

	//颈部与头部的连接		保存在颈部
	//颈部最后一个圈
	circle1 = &neck.circleCollection.at(neck.circleCollection.size() - 1);	
	//头部的第一个圈
	circle2 = &head.circleCollection.at(0);

	//创建Surface并加入到SurfaceCollection
	creatPartSurfaceY(circle1, circle2, &neck.surfaceCollection);

	//head		头部
	for(int i = 0; i < head.circleCollection.size() - 1; i++)
	{
		//第一个圈
		circle1 = &head.circleCollection.at(i);	
		//第二个圈
		circle2 = &head.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &head.surfaceCollection);
	}
}

void Body::creatSurfaceZ()
{
	//lfoot
	for(int i = 0; i < lfoot.circleCollection.size() - 1; i++)
	{
		//第一个圈
		vector<Dot> *circle1 = &lfoot.circleCollection.at(i);	
		//第二个圈
		vector<Dot> *circle2 = &lfoot.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		creatPartSurfaceZ(circle1, circle2, &lfoot.surfaceCollection);
	}

	//rfoot
	for(int i = 0; i < rfoot.circleCollection.size() - 1; i++)
	{
		//第一个圈
		vector<Dot> *circle1 = &rfoot.circleCollection.at(i);	
		//第二个圈
		vector<Dot> *circle2 = &rfoot.circleCollection.at(i + 1);

		//创建Surface并加入到SurfaceCollection
		creatPartSurfaceZ(circle1, circle2, &rfoot.surfaceCollection);
	}
}

/*****************************************************
 *把circle1 和 circle2 中数据创建Surface 并加入到SurfaceCollection
 ****************************************************/
void Body::creatPartSurfaceX(vector<Dot> *circle1, vector<Dot> *circle2, vector<Surface> *surfaceCollection)
{
	if( !circle1 || !circle2)
		return;             ////////////////////////////此处出现错误

	vector<float> tempArc1 = vector<float>();											//角度1
	vector<float> tempArc2 = vector<float>();											//角度2

	//计算角度1
	calculArcX(circle1, tempArc1);
	//计算角度2
	calculArcX(circle2, tempArc2);

	//int minNum = tempArc1.size() <= tempArc2.size() ? tempArc1.size() : tempArc2.size();	//两个角度中最少数量
	int p1 = 0;			//圈1 的指示 指向下一个未使用的点
	int p2 = 0;			//圈2 的指示
	int arc1 = 1;		//角度1 中的指示 指向下一个未用的角度
	int arc2 = 1;
	Dot A;				//三角形的三个点 A  B  C
	Dot B;
	Dot C;
	
	//两个圈都有数据的部分
	//取第一第二个点
	A = circle1->at(p1);	p1++;
	B = circle2->at(p2);	p2++;
	while((arc1 < tempArc1.size() - 1) && (arc2 < tempArc2.size() - 1))
	{
		bool inOne = true;
		
		//取第三个点
		if(tempArc1.at(arc1) >= tempArc2.at(arc2))
		{
			C = circle1->at(p1); p1++;
			inOne = true;
			arc1++;
		}
		else
		{
			C = circle2->at(p2); p2++;
			inOne = false;
			arc2++;
		}
		//生成Surface
		Surface creatSur = Surface(A, B, C);
		surfaceCollection->push_back(creatSur);

		//为下一个取点做准备
		if(inOne)
		{
			A = C;
		}
		else
		{
			B = C;
		}
	}
	
	//两个圈只有一个圈有数据的部分
	if((arc1 >= tempArc1.size() - 1))
	{
		//剩下的只有circle2有数据
		//A C 都在circle1上
		A = C;
		while(p2 < circle2->size())
		{
			C = B;
			B = circle2->at(p2);	p2++;
			//生成Surface
			Surface creatSur = Surface(A, B, C);
			surfaceCollection->push_back(creatSur);

		}
		//最后一个Surface
		C = circle1->at(p1);///*circle1->size() - 1*/);		//最后一次 p1可以不自增
		//生成Surface
		Surface creatSur = Surface(A, B, C);
		surfaceCollection->push_back(creatSur);
	}else
	{
		//剩下的只有circle1中有数据
		//B C 都在circle2上
		B = C;
		while(p1 < circle1->size())
		{
			C = A;
			A = circle1->at(p1);	p1++;
			//生成Surface
			Surface creatSur = Surface(A, B, C);
			surfaceCollection->push_back(creatSur);
		}
		//最后一个Surface
		C = circle2->at(p2);			//最后一次 p2可以不自增
		//生成Surface
		Surface creatSur = Surface(A, B, C);
		surfaceCollection->push_back(creatSur);
	}
}

/*****************************************************
 *把circle1 和 circle2 中数据创建Surface 并加入到SurfaceCollection
 ****************************************************/
void Body::creatPartSurfaceY(vector<Dot> *circle1, vector<Dot> *circle2, vector<Surface> *surfaceCollection)
{
	if( !circle1 || !circle2)
		return;             ////////////////////////////此处出现错误

	vector<float> tempArc1 = vector<float>();											//角度1
	vector<float> tempArc2 = vector<float>();											//角度2

	//计算角度1
	calculArcY(circle1, tempArc1);
	//计算角度2
	calculArcY(circle2, tempArc2);

	//int minNum = tempArc1.size() <= tempArc2.size() ? tempArc1.size() : tempArc2.size();	//两个角度中最少数量
	int p1 = 0;			//圈1 的指示 指向下一个未使用的点
	int p2 = 0;			//圈2 的指示
	int arc1 = 1;		//角度1 中的指示 指向下一个未用的角度
	int arc2 = 1;
	Dot A;				//三角形的三个点 A  B  C
	Dot B;
	Dot C;
	
	//两个圈都有数据的部分
	//取第一第二个点
	A = circle1->at(p1);	p1++;
	B = circle2->at(p2);	p2++;
	while((arc1 < tempArc1.size() - 1) && (arc2 < tempArc2.size() - 1))
	{
		bool inOne = true;
		
		//取第三个点
		if(tempArc1.at(arc1) >= tempArc2.at(arc2))
		{
			C = circle1->at(p1); p1++;
			inOne = true;
			arc1++;
		}
		else
		{
			C = circle2->at(p2); p2++;
			inOne = false;
			arc2++;
		}
		//生成Surface
		Surface creatSur = Surface(A, B, C);
		surfaceCollection->push_back(creatSur);

		//为下一个取点做准备
		if(inOne)
		{
			A = C;
		}
		else
		{
			B = C;
		}
	}
	
	//两个圈只有一个圈有数据的部分
	if((arc1 >= tempArc1.size() - 1))
	{
		//剩下的只有circle2有数据
		//A C 都在circle1上
		A = C;
		while(p2 < circle2->size())
		{
			C = B;
			B = circle2->at(p2);	p2++;
			//生成Surface
			Surface creatSur = Surface(A, B, C);
			surfaceCollection->push_back(creatSur);

		}
		//最后一个Surface
		C = circle1->at(p1);///*circle1->size() - 1*/);		//最后一次 p1可以不自增
		//生成Surface
		Surface creatSur = Surface(A, B, C);
		surfaceCollection->push_back(creatSur);
	}else
	{
		//剩下的只有circle1中有数据
		//B C 都在circle2上
		B = C;
		while(p1 < circle1->size())
		{
			C = A;
			A = circle1->at(p1);	p1++;
			//生成Surface
			Surface creatSur = Surface(A, B, C);
			surfaceCollection->push_back(creatSur);
		}
		//最后一个Surface
		C = circle2->at(p2);			//最后一次 p2可以不自增
		//生成Surface
		Surface creatSur = Surface(A, B, C);
		surfaceCollection->push_back(creatSur);
	}
}

/*****************************************************
 *把circle1 和 circle2 中数据创建Surface 并加入到SurfaceCollection
 ****************************************************/
void Body::creatPartSurfaceZ(vector<Dot> *circle1, vector<Dot> *circle2, vector<Surface> *surfaceCollection)
{
	if( !circle1 || !circle2)
		return;             ////////////////////////////此处出现错误

	vector<float> tempArc1 = vector<float>();											//角度1
	vector<float> tempArc2 = vector<float>();											//角度2

	//计算角度1
	calculArcZ(circle1, tempArc1);
	//计算角度2
	calculArcZ(circle2, tempArc2);

	//int minNum = tempArc1.size() <= tempArc2.size() ? tempArc1.size() : tempArc2.size();	//两个角度中最少数量
	int p1 = 0;			//圈1 的指示 指向下一个未使用的点
	int p2 = 0;			//圈2 的指示
	int arc1 = 1;		//角度1 中的指示 指向下一个未用的角度
	int arc2 = 1;
	Dot A;				//三角形的三个点 A  B  C
	Dot B;
	Dot C;
	
	//两个圈都有数据的部分
	//取第一第二个点
	A = circle1->at(p1);	p1++;
	B = circle2->at(p2);	p2++;
	while((arc1 < tempArc1.size() - 1) && (arc2 < tempArc2.size() - 1))
	{
		bool inOne = true;
		
		//取第三个点
		if(tempArc1.at(arc1) >= tempArc2.at(arc2))
		{
			C = circle1->at(p1); p1++;
			inOne = true;
			arc1++;
		}
		else
		{
			C = circle2->at(p2); p2++;
			inOne = false;
			arc2++;
		}
		//生成Surface
		Surface creatSur = Surface(A, B, C);
		surfaceCollection->push_back(creatSur);

		//为下一个取点做准备
		if(inOne)
		{
			A = C;
		}
		else
		{
			B = C;
		}
	}
	
	//两个圈只有一个圈有数据的部分
	if((arc1 >= tempArc1.size() - 1))
	{
		//剩下的只有circle2有数据
		//A C 都在circle1上
		A = C;
		while(p2 < circle2->size())
		{
			C = B;
			B = circle2->at(p2);	p2++;
			//生成Surface
			Surface creatSur = Surface(A, B, C);
			surfaceCollection->push_back(creatSur);

		}
		//最后一个Surface
		C = circle1->at(p1);///*circle1->size() - 1*/);		//最后一次 p1可以不自增
		//生成Surface
		Surface creatSur = Surface(A, B, C);
		surfaceCollection->push_back(creatSur);
	}else
	{
		//剩下的只有circle1中有数据
		//B C 都在circle2上
		B = C;
		while(p1 < circle1->size())
		{
			C = A;
			A = circle1->at(p1);	p1++;
			//生成Surface
			Surface creatSur = Surface(A, B, C);
			surfaceCollection->push_back(creatSur);
		}
		//最后一个Surface
		C = circle2->at(p2);			//最后一次 p2可以不自增
		//生成Surface
		Surface creatSur = Surface(A, B, C);
		surfaceCollection->push_back(creatSur);
	}
}

void Body::calculArcX(vector<Dot> * currentcircle, vector<float> &center_arc)
{
	if( !currentcircle)
		return;					//函数输入错误

	//确定中心点 Start
	Dot centerdot(0.0,0.0,0.0);
	for(int k=0;k<currentcircle->size();k++)
	{
		//centerdot.x = centerdot.x + currentcircle->at(k).x;
		centerdot.y = centerdot.y + currentcircle->at(k).y;
		centerdot.z = centerdot.z + currentcircle->at(k).z;
	}
	centerdot.x = currentcircle->at(0).x;
	centerdot.y = centerdot.y/currentcircle->size();
	centerdot.z = centerdot.z/currentcircle->size();
	//确定中心点 End


	//确定首点
	Dot firstDot1 = Dot(currentcircle->at(0).x,currentcircle->at(0).y,currentcircle->at(0).z);
	//确定首向量
	Dot datumvector1 = Dot(currentcircle->at(0).x-centerdot.x,currentcircle->at(0).y-centerdot.y,currentcircle->at(0).z-centerdot.z);
	//确定首点的对应点
	Dot firstDot2 = CalculateCorrespondDot(firstDot1,centerdot);
	//确定首点的对应点的向量
	Dot datumvector2 = Dot(firstDot2.x-centerdot.x,firstDot2.y-centerdot.y,firstDot2.z-centerdot.z);


	//确定相应的从中心点发出的向量 Start
	vector<Dot> center_vector;
	for(int k=0;k<currentcircle->size();k++)
	{
		Dot *tmpDot = new Dot(currentcircle->at(k).x-centerdot.x,currentcircle->at(k).y-centerdot.y,currentcircle->at(k).z-centerdot.z);
		center_vector.push_back(*tmpDot);
	}
	//确定相应的从中心点发出的向量 End


	//vector<float> center_arc;	//确定相应的从中心点发出的向量间的角度的cos值 Start

	for(int k=0;k<currentcircle->size();k++)
	{
		float tmparc;
		if( UpOrDownX(firstDot1,firstDot2,currentcircle->at(k)) ==1)		//在上
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector1) + 2;
		}
		else	//在下
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector2);
		}

		center_arc.push_back(tmparc);
	}
	//确定相应的从中心点发出的向量间的角度的cos值 End



	//根据center_arc的相应的值，cos值从高到低，即是，距离基准点顺时针的从远到近 Start
	

	//冒泡排序，大者在前，小者在后，每一轮将最小元素排至最后
	for(int i=0;i<center_arc.size()-1;i++)	//每一轮的循环
	{
		for(int j=0;j<center_arc.size()-i-1;j++)	//每轮中的对两者比较的循环
		{
			//如小于则相换
			if(center_arc.at(j)<center_arc.at(j+1))
			{
				float tmparc = 0.0;
				Dot tmpdot = Dot(0.0,0.0,0.0);
				tmparc = center_arc.at(j+1);
				center_arc.at(j+1) = center_arc.at(j);
				center_arc.at(j) = tmparc;
				tmpdot = currentcircle->at(j);
				currentcircle->at(j) = currentcircle->at(j+1);
				currentcircle->at(j+1) = tmpdot;
			}
		}
	}


	//根据center_arc的相应的值，cos值从高到低，即是，距离基准点顺时针的从远到近 End

}

void Body::calculArcY(vector<Dot> * currentcircle, vector<float> &center_arc)
{
	if( !currentcircle)
		return;					//函数输入错误

	//确定中心点 Start
	Dot centerdot(0.0,0.0,0.0);
	for(int k=0;k<currentcircle->size();k++)
	{
		centerdot.x = centerdot.x + currentcircle->at(k).x;
		//centerdot.y = centerdot.y + currentcircle->at(k).y;
		centerdot.z = centerdot.z + currentcircle->at(k).z;
	}
	centerdot.x = centerdot.x/currentcircle->size();
	centerdot.y = currentcircle->at(0).y;
	centerdot.z = centerdot.z/currentcircle->size();
	//确定中心点 End


	//确定首点
	Dot firstDot1 = Dot(currentcircle->at(0).x,currentcircle->at(0).y,currentcircle->at(0).z);
	//确定首向量
	Dot datumvector1 = Dot(currentcircle->at(0).x-centerdot.x,currentcircle->at(0).y-centerdot.y,currentcircle->at(0).z-centerdot.z);
	//确定首点的对应点
	Dot firstDot2 = CalculateCorrespondDot(firstDot1,centerdot);
	//确定首点的对应点的向量
	Dot datumvector2 = Dot(firstDot2.x-centerdot.x,firstDot2.y-centerdot.y,firstDot2.z-centerdot.z);


	//确定相应的从中心点发出的向量 Start
	vector<Dot> center_vector;
	for(int k=0;k<currentcircle->size();k++)
	{
		Dot *tmpDot = new Dot(currentcircle->at(k).x-centerdot.x,currentcircle->at(k).y-centerdot.y,currentcircle->at(k).z-centerdot.z);
		center_vector.push_back(*tmpDot);
	}
	//确定相应的从中心点发出的向量 End


	//vector<float> center_arc;	//确定相应的从中心点发出的向量间的角度的cos值 Start

	for(int k=0;k<currentcircle->size();k++)
	{
		float tmparc;
		if( UpOrDownY(firstDot1,firstDot2,currentcircle->at(k)) ==1)		//在上
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector1) + 2;
		}
		else	//在下
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector2);
		}

		center_arc.push_back(tmparc);
	}
	//确定相应的从中心点发出的向量间的角度的cos值 End



	//根据center_arc的相应的值，cos值从高到低，即是，距离基准点顺时针的从远到近 Start
	

	//冒泡排序，大者在前，小者在后，每一轮将最小元素排至最后
	for(int i=0;i<center_arc.size()-1;i++)	//每一轮的循环
	{
		for(int j=0;j<center_arc.size()-i-1;j++)	//每轮中的对两者比较的循环
		{
			//如小于则相换
			if(center_arc.at(j)<center_arc.at(j+1))
			{
				float tmparc = 0.0;
				Dot tmpdot = Dot(0.0,0.0,0.0);
				tmparc = center_arc.at(j+1);
				center_arc.at(j+1) = center_arc.at(j);
				center_arc.at(j) = tmparc;
				tmpdot = currentcircle->at(j);
				currentcircle->at(j) = currentcircle->at(j+1);
				currentcircle->at(j+1) = tmpdot;
			}
		}
	}


	//根据center_arc的相应的值，cos值从高到低，即是，距离基准点顺时针的从远到近 End

}

void Body::calculArcZ(vector<Dot> * currentcircle, vector<float> &center_arc)
{
	if( !currentcircle)
		return;					//函数输入错误

	//确定中心点 Start
	Dot centerdot(0.0,0.0,0.0);
	for(int k=0;k<currentcircle->size();k++)
	{
		centerdot.x = centerdot.x + currentcircle->at(k).x;
		centerdot.y = centerdot.y + currentcircle->at(k).y;
		//centerdot.z = centerdot.z + currentcircle->at(k).z;
	}
	centerdot.x = centerdot.x/currentcircle->size();
	centerdot.y = centerdot.z/currentcircle->size();
	centerdot.z = currentcircle->at(0).z;
	//确定中心点 End


	//确定首点
	Dot firstDot1 = Dot(currentcircle->at(0).x,currentcircle->at(0).y,currentcircle->at(0).z);
	//确定首向量
	Dot datumvector1 = Dot(currentcircle->at(0).x-centerdot.x,currentcircle->at(0).y-centerdot.y,currentcircle->at(0).z-centerdot.z);
	//确定首点的对应点
	Dot firstDot2 = CalculateCorrespondDot(firstDot1,centerdot);
	//确定首点的对应点的向量
	Dot datumvector2 = Dot(firstDot2.x-centerdot.x,firstDot2.y-centerdot.y,firstDot2.z-centerdot.z);


	//确定相应的从中心点发出的向量 Start
	vector<Dot> center_vector;
	for(int k=0;k<currentcircle->size();k++)
	{
		Dot *tmpDot = new Dot(currentcircle->at(k).x-centerdot.x,currentcircle->at(k).y-centerdot.y,currentcircle->at(k).z-centerdot.z);
		center_vector.push_back(*tmpDot);
	}
	//确定相应的从中心点发出的向量 End


	//vector<float> center_arc;	//确定相应的从中心点发出的向量间的角度的cos值 Start

	for(int k=0;k<currentcircle->size();k++)
	{
		float tmparc;
		if( UpOrDownZ(firstDot1,firstDot2,currentcircle->at(k)) ==1)		//在上
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector1) + 2;
		}
		else	//在下
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector2);
		}

		center_arc.push_back(tmparc);
	}
	//确定相应的从中心点发出的向量间的角度的cos值 End



	//根据center_arc的相应的值，cos值从高到低，即是，距离基准点顺时针的从远到近 Start
	

	//冒泡排序，大者在前，小者在后，每一轮将最小元素排至最后
	for(int i=0;i<center_arc.size()-1;i++)	//每一轮的循环
	{
		for(int j=0;j<center_arc.size()-i-1;j++)	//每轮中的对两者比较的循环
		{
			//如小于则相换
			if(center_arc.at(j)<center_arc.at(j+1))
			{
				float tmparc = 0.0;
				Dot tmpdot = Dot(0.0,0.0,0.0);
				tmparc = center_arc.at(j+1);
				center_arc.at(j+1) = center_arc.at(j);
				center_arc.at(j) = tmparc;
				tmpdot = currentcircle->at(j);
				currentcircle->at(j) = currentcircle->at(j+1);
				currentcircle->at(j+1) = tmpdot;
			}
		}
	}


	//根据center_arc的相应的值，cos值从高到低，即是，距离基准点顺时针的从远到近 End


}