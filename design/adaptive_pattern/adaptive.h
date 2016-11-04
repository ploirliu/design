#include<iostream>
using namespace std;

class add{
public:
	virtual int get_add_ans(int a, int b){
		return a + b;
	}
};

class multi{
public:
	virtual int get_multi_ans(int a, int b){
		return a*b;
	}
};

class adaptive_interface :public multi{
	add *now;
public:
	adaptive_interface(add* _now) :now(_now){}
	int get_multi_ans(int a, int b){
		int out = 0;
		for (int i = 0; i < b; ++i){
			out = now->get_add_ans(out, a);
		}
		return out;
	}
};

class adaptive_class :public multi, public add{
public:
	int get_multi_ans(int a, int b){
		int out = 0;
		for (int i = 0; i < b; ++i){
			out = get_add_ans(out, a);
		}
		return out; 
	}
};

void test(){
	int a = 100, b = 40;
	cout << "test interface adaptive:" << endl;
	add* myadd = new add();
	multi* interface_multi = new adaptive_interface(myadd);
	cout << a << "*" << b << "=" << interface_multi->get_multi_ans(a, b) << endl;
	delete myadd; delete interface_multi;


	cout << "test class adaptive:" << endl;
	multi* class_multi = new adaptive_class();
	cout << a << "*" << b << "=" << class_multi->get_multi_ans(a, b) << endl;
	delete class_multi;
}