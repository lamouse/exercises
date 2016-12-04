#include <condition_variable>
#include <mutex>
#include <thread>
#include <cstdio>
#include <queue>
#include <chrono>
#include <future>
std::queue<int> queue;
std::mutex queueMutex;
std::condition_variable queueConVar;
void provider(int val){
	//push different valus(val til val+5 with timeouts of val milliseconds into the queue)
	for (int i = 0; i < 6; ++i){
		std::lock_guard<std::mutex> lg(queueMutex);
		queue.push(val + 1);
	}//release lock
	queueConVar.notify_one();
	std::this_thread::sleep_for(std::chrono::milliseconds(val));
}

void consumer(int num){
	//pop valus if available (num identifies the consumer)
	while(true){
		int val;
		{
			std::unique_lock<std::mutex> ul(queueMutex);
			queueConVar.wait(ul, []{return !queue.empty();});
			val = queue.front();
			queue.pop();
		}//release lock
		printf("consumer %d : %d,\n", num, val);
	}
}

int main(int argc, char const *argv[])
{
	//start three providers for values 100+, 300+, and 500+
	auto p1 = std::async(std::launch::async, provider, 100);
	auto p2 = std::async(std::launch::async, provider, 300);
	auto p3 = std::async(std::launch::async, provider, 500);
	//start two consumers printing the values
	auto c1 = std::async(std::launch::async, consumer, 1);
	auto c2 = std::async(std::launch::async, consumer, 2);
	return 0;
}