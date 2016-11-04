#pragma once

#ifndef SUBJECT
#define SUBJECT
class observer;
class subject
{
protected:
	unordered_set<observer*> all;
public:
	subject();
	~subject();
	void addObserver(observer *);
	void removeObserver(observer *);
	virtual void notify();
	void notify(subject* _s);
	
};




class int_subject :public subject  {
	int ival;
	double dval;
	int stu;
public:
	int_subject() :stu(0){};
	virtual void notify();

	int get_ival(){
		return ival;
	}
	int get_dval(){
		return dval;
	}

	void setFunction(int _stu){
		stu = _stu;
	}

	void setChanged(){
		if (stu == 0){
			notify();
		}
		else{
			subject::notify(this);
		}
	}
	void setData(int _i, double _d){
		ival = _i;
		dval = _d;
		setChanged();
	}
};


#endif
