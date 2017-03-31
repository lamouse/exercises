#include <iostream>
#include <utility>
#include <random>
#include <stack>
#include <algorithm>
#include <iterator>
#include <functional>
template<typename T>
void qsort(T arr[], const int& start, const int& end){
	if(start >= end) return;
	T mid = arr[end];
	int left = start, right = end - 1;
	while(left < right){
		while(arr[left] < mid && left < right) left++;
		while(arr[right] >= mid && left < right) right--;
		std::swap(arr[left], arr[right]);
	}
	if(arr[left] >= arr[end])
		std::swap(arr[left], arr[end]);
	else
		left++;
	qsort(arr, start, left - 1);
	qsort(arr, left + 1, end);
}
template<typename T>
void qsort(T arr[], int len){
	qsort(arr, 0, len - 1);
}

struct Range {
	int start, end;
	Range(int s = 0, int e = 0) {start = s, end = e;}
};

template<typename T>
void iteraQsort(T arr[], const int& len){
if (len <= 0) return; 
	Range r[len]; int p = 0;
	r[p++] = Range(0, len - 1);
	while (p) {
		Range range = r[--p];
		if(range.start >= range.end) continue;
		T mid = arr[range.end];
		int left = range.start, right = range.end - 1;
		while (left < right) {
			while (arr[left] < mid && left < right) left++;
			while (arr[right] >= mid && left < right) right--;
			std::swap(arr[left], arr[right]);
		}
		if (arr[left] >= arr[range.end])
			std::swap(arr[left], arr[range.end]);
		else
			left++;
		r[p++] = Range(range.start, left - 1);
		r[p++] = Range(left + 1, range.end);
	}
}

template<typename T, typename C>
void iteraQsort(T arr[], const int& len, C cmp){
if (len <= 0) return; 
	Range r[len]; int p = 0;
	r[p++] = Range(0, len - 1);
	while (p) {
		Range range = r[--p];
		if(range.start >= range.end) continue;
		T mid = arr[range.end];
		int left = range.start, right = range.end - 1;
		while (left < right) {
			while (cmp(arr[left], mid) && left < right) left++;
			while (!cmp(arr[right], mid) && left < right) right--;
			std::swap(arr[left], arr[right]);
		}
		if (!cmp(arr[left], arr[range.end]))
			std::swap(arr[left], arr[range.end]);
		else
			left++;
		r[p++] = Range(range.start, left - 1);
		r[p++] = Range(left + 1, range.end);
	}
}

template<typename T>
void iteraQsort(T arr[], int len, std::function<bool(T, T)> cmp) {
	if (len <= 0) return;
	Range r[len]; int p = 0;
	r[p++] = Range(0, len - 1);
	while (p) {
		Range range = r[--p];
		if (range.start >= range.end) continue;
		T mid = arr[range.end];
		int left = range.start, right = range.end - 1;
		while (left < right) {
			while (cmp(arr[left], mid) && left < right) left++;
			while (!cmp(arr[right], mid) && left < right) right--;
			std::swap(arr[left], arr[right]);
		}
		if (!cmp(arr[left], arr[range.end]))
			std::swap(arr[left], arr[range.end]);
		else
			left++;
		r[p++] = Range(range.start, left - 1);
		r[p++] = Range(left + 1, range.end);
	}
}

template<typename T>
void stackQsort(T arr[], const int& len){
	std::cout << std::endl; 
	if(len <= 1)
		return;
	int left = 0, right = len - 1;
	std::stack<int> range;
	range.push(left);
	range.push(right);
	while(!range.empty()){
		int tright = right = range.top(); range.pop();
		int tleft = left = range.top(); range.pop();
		if(tleft > tright) continue;
		T mid = arr[tright];
		right = tright - 1;
		while(left < right){
			while(arr[left] < mid && left < right) left++;
			while(arr[right] >= mid && left < right) right--;
			std::swap(arr[left], arr[right]);
		}
		if(arr[left] >= arr[tright])
			std::swap(arr[left], arr[tright]);
		else
			left++;
		range.push(tleft); range.push(left - 1);
		range.push(left + 1); range.push(tright);
	}
}

int main(int argc, char const *argv[])
{
	using namespace std;
	default_random_engine e;
	int arr[20];
	for(int i = 0; i < 20; i++){
		arr[i] = e() % 20;
	}
	for_each(begin(arr), end(arr), [](const int& i){cout << i << " ";});
	cout << endl;
	//stackQsort(arr, sizeof(arr)/sizeof(arr[0]));
	iteraQsort(arr, sizeof(arr)/sizeof(arr[0]), less<int>());
	cout << boolalpha <<"递归快速排序, 是否完成排序: " 
		<< is_sorted(begin(arr), end(arr)) << endl;
/*	stackQsort(arr, sizeof(arr)/sizeof(arr[0]));
	cout << "使用栈快速排序, 是否完成排序: " 
		<< is_sorted(begin(arr), end(arr)) << endl;*/
/*	iteraQsort(arr, sizeof(arr)/sizeof(arr[0]);
	cout << "迭代快速排序, 是否完成排序: " 
		<< is_sorted(begin(arr), end(arr)) << endl;*/
/*	iteraQsort(arr, sizeof(arr), [](const int& i, const int& j){
		return i > j;
	});*/
	for_each(begin(arr), end(arr), [](const int& i){cout << i << " ";});
	cout << endl;
	return 0;
}
