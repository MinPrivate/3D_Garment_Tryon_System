#include "StdAfx.h"
#include "BodyPart.h"


BodyPart::BodyPart(void)
{
	dotCollection = vector<Dot>();
	surfaceCollection = vector<Surface>();
	circleCollection = vector<vector<Dot>>();
}


BodyPart::~BodyPart(void)
{
}
