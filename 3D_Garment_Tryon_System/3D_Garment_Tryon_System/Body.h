#pragma once
#include "BodyPart.h"
#include <algorithm> 
#include <math.h>

class Body
{
public:
	//目标人体参数
	int sex;	//1男0女
	float height;
	float c_neck;
	float c_collar;
	float c_chest;
	float c_waist;
	float c_hip;
	float l_upbody;
	float l_downbody;

	//身体部分
	vector<BodyPart *> PartCollection;
	vector<BodyPart *> PartCollectionX;
	vector<BodyPart *> PartCollectionY;
	vector<BodyPart *> PartCollectionZ;

	BodyPart head;
	BodyPart neck;
	BodyPart rcollar;
	BodyPart lcollar;
	BodyPart chest;
	BodyPart abdomen;
	BodyPart hip;
	BodyPart rshoulder;
	BodyPart lshoulder;
	BodyPart rforearm;
	BodyPart lforearm;
	BodyPart rhand;
	BodyPart lhand;
	BodyPart rthigh;
	BodyPart lthigh;
	BodyPart rshin;
	BodyPart lshin;
	BodyPart rfoot;
	BodyPart lfoot;
	
	
public:
	Body(void);
	~Body(void);
	bool readOBJFile();
	void bodyDisplay();

	void triangulate();	//三角剖分
	void sortAsClockX(vector<Dot> * currentcircle);
	void sortAsClockY(vector<Dot> * currentcircle);
	void sortAsClockZ(vector<Dot> * currentcircle);
	void triangulateX(BodyPart * currentBodyPart,int max,int min,int circleNum);
	void triangulateY(BodyPart * currentBodyPart,int max,int min,int circleNum);
	void triangulateZ(BodyPart * currentBodyPart,int max,int min,int circleNum);

	void creatSurface();
	void adjust();

private:
	
	void creatPartSurfaceX(vector<Dot> *circle1, vector<Dot> *circle2, vector<Surface> *surfaceCollection);
	void calculArcX(vector<Dot> * currentcircle, vector<float> &center_arc);
	void Body::creatSurfaceX();

	void creatSurfaceY();
	void creatPartSurfaceY(vector<Dot> *circle1, vector<Dot> *circle2, vector<Surface> *surfaceCollection);
	void calculArcY(vector<Dot> * currentcircle, vector<float> &center_arc);

	void creatSurfaceZ();
	void creatPartSurfaceZ(vector<Dot> *circle1, vector<Dot> *circle2, vector<Surface> *surfaceCollection);
	void calculArcZ(vector<Dot> * currentcircle, vector<float> &center_arc);
};

