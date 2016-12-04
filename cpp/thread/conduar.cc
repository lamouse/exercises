#include <condition_variable>
#include <mutex>
#include <iostream>
#include <future>
bool readFlag;
std::mutex readMutex;
std::condition_variable readCondVar;

void thread1(){
	//do something thread2 needs as preparation
	std::cout << "return" << std::endl;
	std::cin.get();
	//signal that thread1 has prepared a condition
	{
		std::lock_guard<std::mutex> lg(readMutex);
		readFlag = true;
	}//release lock
	readCondVar.notify_one();
}

void thread2(){
	//wait until thread1 is ready (readyFlag is true)
	{
		std::unique_lock<std::mutex> ul(readMutex);
		readCondVar.wait(ul, []{ std::cout << "week up" << std::endl; 
							return readFlag;});
	}//release lock
	//do whatever shall happen after thread1 has prepared things
	std::cout << "done" << std::endl;
}

int main(int argc, char const *argv[])
{
	auto f1 = std::async(std::launch::async, thread1);
	auto f2 = std::async(std::launch::async, thread2);
	return 0;
}
