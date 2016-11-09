#include<iostream>
using namespace std;

class gumMachine;

class state{
	void showError(){
		cout << "error operation" << endl;
	}
protected:
	gumMachine* gum;
public:
	state(gumMachine* _gum) :gum(_gum){};
	virtual void insertCoin(){
		showError();
	}
	virtual void ejectCoin(){
		showError();
	}
	virtual bool turnCrank(){
		showError();
		return false;
	}
	virtual void dispence() {
		showError();
	}
	virtual void refill(int count){
		showError();
	}
};

class soldout_state :public state{
public:
	soldout_state(gumMachine* _gum) :state(_gum){};
	void refill(int count);
};

class nocoin_state :public state{
public:
	nocoin_state(gumMachine* _gum) :state(_gum){};
	void insertCoin();
	void refill(int count);
};

class hascoin_state :public state{
public:
	hascoin_state(gumMachine* _gum) :state(_gum){};
	void ejectCoin();
	bool turnCrank();
	void refill(int count);
};

class sold_state :public state{
public:
	sold_state(gumMachine* _gum) :state(_gum){};
	void dispence();
	void refill(int count);
};

class winner_state :public state{
public:
	winner_state(gumMachine * _gum) :state(_gum){};
	void dispence();
	void refill(int count);
};

class gumMachine{
	state* soldout;
	state* nocoin;
	state* hascoin;
	state* selling;
	state* winner;
	int count;
	state* now;
public:
	gumMachine(int _count):
		soldout(new soldout_state(this)),
		nocoin (new nocoin_state(this)),
		hascoin (new hascoin_state(this)),
		selling (new sold_state(this)),
		winner(new winner_state(this)),
		count(_count),
		now(NULL){
		if (_count > 0){
			now = nocoin;
		}
		else
			now = soldout;
	}
	void insertCoin(){
		now->insertCoin();
	}
	void ejectCoin(){
		now->ejectCoin();
	}
	void turnCrank(){
		//return now->turnCrank();
		if(now->turnCrank())
			now->dispence();
	}
	//void dispence(){
	//	now->dispence();
	//}
	void push_gum(){
		cout << "push out gum" << endl;
		if (count){
			count -= 1;
		}
		cout << "left " << count << " gums" << endl;
	}
	int getCount(){
		return count;
	}
	state* getSoldoutState(){
		return soldout;
	}
	state* getSellingState(){
		return selling;
	}
	state* getNocoinState(){
		return nocoin;
	}
	state* getHascoinState(){
		return hascoin;
	}
	state* getWinnerState(){
		return winner;
	}
	void addCount(int _count){
		count += _count;
	}
	void setState(state* _s){
		now = _s;
	}
};

void soldout_state::refill(int count){
	cout << "refilling " << count << endl;
	gum->addCount(count);
	gum->setState(gum->getSellingState());
}

void nocoin_state::insertCoin(){
	cout << "insert coin" << endl;
	gum->setState(gum ->getHascoinState());
}
void nocoin_state::refill(int count){
	cout << "refilling " << count << endl;
	gum->addCount(count);
}

void hascoin_state::ejectCoin(){
	cout << "ejecting" << endl;
	gum->setState(gum->getNocoinState());
}
bool hascoin_state::turnCrank(){
	cout << "wait a moment" << endl;
	if (gum->getCount()>2){
		int tmp = rand() % 5;
		if (tmp == 0){
			gum->setState(gum->getWinnerState());
		}
		else{
			gum->setState(gum->getSellingState());
		}

		return true;
	}
	else if (gum->getCount()){
		gum->setState(gum->getSellingState());
		return true;
	}
	else{
		cout << "not enough gum" << endl;
		return false;
	}
}
void hascoin_state::refill(int count){
	cout << "refilling " << count << endl;
	gum->addCount(count);
}

void sold_state::dispence(){
	if (gum->getCount()){
		gum->push_gum();
		if (gum->getCount()){
			gum->setState(gum->getNocoinState());
		}
		else{
			gum->setState(gum->getSoldoutState());
		}
	}
	else{
		cout << "there is not enough gum, please eject the coin";
		gum->setState(gum->getHascoinState());
	}
}
void sold_state::refill(int count){
	cout << "refilling " << count << endl;
	gum->addCount(count);
}


void winner_state::dispence(){
	cout << "you are a lucky person, you get two gum" << endl;
	gum->push_gum();
	gum->push_gum();
	if (gum->getCount()){
		gum->setState(gum->getNocoinState());
	}
	else{
		gum->setState(gum->getSoldoutState());
	}
}
void winner_state::refill(int count){
	cout << "refilling " << count << endl;
	gum->addCount(count);
}

void test(){
	gumMachine *g = new gumMachine(15);
	g->insertCoin(); g->ejectCoin();
	g->insertCoin(); g->turnCrank();
	g->insertCoin(); g->turnCrank();
	g->insertCoin(); g->turnCrank();
	g->insertCoin(); g->turnCrank();
	g->insertCoin(); g->turnCrank();
	g->insertCoin(); g->turnCrank();
	g->insertCoin(); g->ejectCoin();
	g->insertCoin(); g->turnCrank();
	g->insertCoin(); g->turnCrank();
	g->insertCoin(); g->turnCrank();
	g->insertCoin(); g->turnCrank();
	g->insertCoin(); g->turnCrank();
	g->insertCoin(); g->turnCrank();
	g->insertCoin(); g->ejectCoin();
	g->insertCoin(); g->turnCrank();
	g->insertCoin(); g->turnCrank();
	g->insertCoin(); g->turnCrank();
	g->insertCoin(); g->turnCrank();
	g->insertCoin(); g->turnCrank();
	g->insertCoin(); g->turnCrank();
}