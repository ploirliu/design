#pragma once
class update
{
public:
	update();
	~update();
	virtual void com(int _v);
};

class double_update :public update{
	void com(int _v);
};

class square_update :public update{
	void com(int _v);
};