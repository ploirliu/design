#pragma once
#include "quark.h"
class duck
{
public:
	duck();
	duck(quark *_q);
	~duck();
	void display();
	void make_quark();
	void set_quark(quark *_q);
protected:
	quark *q;
};

class w_duck :public duck{
public:
	w_duck();
	~w_duck();
};


class m_duck :public duck{
public:
	m_duck();
	~m_duck();
};