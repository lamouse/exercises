#include <future>
#include <thread>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <chrono>
using namespace std;

int queryNumber(){
	//read number
	cout << "read number: ";
	int num;
	cin >> num;
	//throw exception if none
	if(!cin){
		throw runtime_error("no number read");
	}
	return num;
}

void doSomething(char c, shared_future<int> f){
	try{
		//wait fornumber of character to print
		int num = f.get();	//get result of queryNumber()
		for (int i = 0; i < num; ++i)
		{
			this_thread::sleep_for(chrono::milliseconds(100));
			cout.put(c).flush();
		}
	}catch(const exception& e){
		cerr << "EXCEPTION in thread " << this_thread::get_id()
			 << ": " << e.what() << endl;
	}
}

int main(int argc, char const *argv[])
{
	try{
		//start one thread to query a number
		shared_future<int> f = async(queryNumber);
		//start three threads each processing this number int a loop
		auto f1 = async(launch::async, doSomething, ',', f);
		auto f2 = async(launch::async, doSomething, '+', f);
		auto f3 = async(launch::async, doSomething, '*', f);
		//wait for all loops to be finshed
		f1.get();
		f2.get();
		f3.get();
	}catch(const exception& e){
		cout << "EXCEPTION: " << e.what() << endl;
	}
	cout << "\ndone" << endl;
	return 0;
}