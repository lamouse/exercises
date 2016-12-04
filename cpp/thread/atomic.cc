#include <atomic>
#include <future>
#include <thread>
#include <chrono>
#include <cstdio>
#include <iostream>
long data;
std::atomic<bool> readFlag(false);
void provider(){
	//after reading a character
	printf("<return>\n");
	std::cin.get();
	//provide some data
	data = 42;
	//and signal readiness
	readFlag.store(true);
}

void consumer(){
	//wait for readines and do somthing else
	while(!readFlag.load()){
		std::cout.put(',').flush();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	//and process provided data
	printf("\nvalue : %ld\n", data);
}

int main(int argc, char const *argv[])
{
	auto p = std::async(std::launch::async, provider);
	auto c = std::async(std::launch::async, consumer);
	return 0;
}