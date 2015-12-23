#include "StdAfx.h"
#include "Surface.h"


Surface::Surface(void)
{
	nv.x = 0;
	nv.y = 0;
	nv.z = 0;
}


Surface::~Surface(void)
{
}


Surface::Surface(Dot tmpp1,Dot tmpp2,Dot tmpp3)
{
	p1 = tmpp1;
	p2 = tmpp2;
	p3 = tmpp3;
	
	Dot tmpp1p2 = Dot(p1.x-p2.x,p1.y-p2.y,p1.z-p2.z);
	Dot tmpp1p3 = Dot(p1.x-p3.x,p1.y-p3.y,p1.z-p3.z);

	nv.x = tmpp1p2.y*tmpp1p3.z-tmpp1p2.z*tmpp1p3.y;
	nv.y = tmpp1p2.z*tmpp1p3.x-tmpp1p2.x*tmpp1p3.z;
	nv.z = tmpp1p2.y*tmpp1p3.z-tmpp1p2.y*tmpp1p3.x;
}