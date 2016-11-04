#include <iostream>
#include <string>
using namespace std;
 class tea{
protected:
	string tea_name;
	string water_name;
	string cup_name;
public:
	virtual void prepare(){
		cout << "prepare tea:" << tea_name << endl;
		cout << "prepare water:" << water_name << endl;
		cout << "prepare cup:" << cup_name << endl;
	}
	virtual void boil(){
		cout << "boil water" << endl;
	}
	virtual void add_tea_water(){
		cout << "add tea and hot water" << endl;
	}
	virtual void wash_cup(){
		cout << "wash the cup" << endl;
	}
	virtual void pull_cup(){
		cout << "all is done" << endl;
	}
};

class low_green_tea :public tea{
public:
	low_green_tea(){
		tea_name = "green tea";
		water_name = "normal water";
		cup_name = "normal cup";
	};
	void boil(){
		cout << "boil to 90 degree" << endl;
	}
};

class high_green_tea :public tea{
public:
	high_green_tea(){
		tea_name = "green tea";
		water_name = "spring water";
		cup_name = "ceramics· cup";
	};
	void boil(){
		cout << "boil to 90 degree" << endl;
	}
};

class low_red_tea :public tea{
public:
	low_red_tea(){
		tea_name = "red tea";
		water_name = "normal water";
		cup_name = "normal cup";
	};
};

class high_red_tea :public tea{
public:
	high_red_tea(){
		tea_name = "red tea";
		water_name = "spring water";
		cup_name = "ceramics cup";
	};
};


class tea_store{
public:
	tea* order_tea(string type){
		tea *out = create_tea(type);
		out->prepare();
		out->boil();
		out->add_tea_water();
		out->wash_cup();
		out->pull_cup();
		return out;
	}
	virtual tea* create_tea(string tea_level)=0;
};

class green_tea_store :public tea_store{
public:
	tea* create_tea(string tea_level){
		if(tea_level== "high")
			return new high_green_tea();
		else
			return new low_green_tea();
	}
};

class red_tea_store :public tea_store{
public:
	tea* create_tea(string tea_level){
		if (tea_level=="high")
			return new high_red_tea();
		else
			return new low_red_tea();
	}
};