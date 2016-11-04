#pragma once
#include "stdafx.h"
class quark
{
public:
	quark();
	~quark();
	virtual void myquark();
};


class wang_quark :public quark{
public:
	void myquark();
};

class miao_quark :public quark{
public:
	void myquark();
};
