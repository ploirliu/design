// factoty_pattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "virtual_pattern.h"

int _tmain(int argc, _TCHAR* argv[])
{
	tea_store *gts=new green_tea_store();
	tea_store *rts=new red_tea_store();

	drink_tea *g1 = gts->orderTea("high");
	cout << "high green tea is ok" << endl << endl;
	drink_tea *g2 = gts->orderTea("low");
	cout << "low green tea is ok" << endl << endl;


	drink_tea *r1 = rts->orderTea("high");
	cout << "high red tea is ok" << endl << endl;
	drink_tea *r2 = rts->orderTea("low");
	cout << "low red tea is ok" << endl << endl;

	delete gts;
	delete rts;
	delete g1;
	delete g2;
	delete r1;
	delete r2;
	return 0;
}

