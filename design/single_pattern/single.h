#include <iostream>
#include <mutex>
using namespace std;

class single{
public:
	static  single* getInstance(){
		static single *unique_single = NULL;
		if (unique_single == NULL){
			static mutex mx;
			mx.lock();
			if (unique_single == NULL){
				unique_single = new single();
			}
			mx.unlock();
		}
		return unique_single;
	}
	void show(){
		cout <<"I am single" << endl;
	}
private:
	single(){
		static int i = 0;
		cout << "Num:" << ++i << endl;
	}
};