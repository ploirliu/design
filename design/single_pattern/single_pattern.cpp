// single_pattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <thread>
#include "single.h"

void myprint(){
	single *tmp = single::getInstance();
	tmp->show();
}

int _tmain(int argc, _TCHAR* argv[])
{

	thread t[10];
	for (int i = 0; i < 10; ++i){
		t[i] = thread(myprint);
		t[i].join();
	}
	return 0;
}

