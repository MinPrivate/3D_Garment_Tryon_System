#pragma once
#include "Surface.h"

class BodyPart
{
public:
	vector<Dot> dotCollection;		//存放每个部件的点的集合
	vector<Surface> surfaceCollection;		//存放每个部件的面的集合
	vector<vector<Dot>> circleCollection;	//用一个圈存放三角剖分后的一个圈的点，这个圈是vector<Dot>类型的
											//一个circleCollection是所有圈的集合

public:
	BodyPart(void);
	~BodyPart(void);
};

