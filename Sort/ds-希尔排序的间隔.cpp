#include<iostream>
using namespace std;
bool is_sorted(int* data, int d,int n) {//判断组内间隔是否有序
	for (int g = 0; g < d; g++) {
		int pos = g;
		while (pos + d < n) {
			if (data[pos] > data[pos + d])
				return false;
			pos += d;
		}
		
	}
	return true;
}
int main() {
	int n, d = 1;
	cin >> n;
	int* data = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> data[i];
	}
	while (d < n) {
		if (is_sorted(data, d, n))
			break;
		d++;
	}
	cout << d;
	return 0;
}


#include<iostream>
using namespace std;
int check(int* arr, int n) {
	int dist = 1;
	while (true) {
		bool judge = true;
		for (int i = 0; i < n - dist; i++) {
			if (arr[i] > arr[i + dist]) {
				judge = false;// 这个distance不行
				break;
			}
		}
		if (judge)return dist;
		else
			dist++;
		if (dist >= n)
			return n;
	}
}
int main(){
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
		cin >> arr[i];
		
	cout << check(arr, n);
		
	delete[]arr;
	return 0;
}