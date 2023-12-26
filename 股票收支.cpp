#include<iostream>
using namespace std;
int main() {
	int N;
	cin >> N;
	int price_dis[100];
	int last,moment;
	cin >> price_dis[0];
	last = price_dis[0];
	for (int i = 1; i < N; i++) {
		cin >> moment;
		price_dis[i] = moment - last;
		last = moment;
	}
	int tmp = 0,max=0;
	for (int i = 1; i < N; i++) {
		tmp += price_dis[i];
		if (tmp > max)
			max = tmp;
		else if (tmp < 0)
			tmp = 0;
	}
	cout << max;
	return 0;
}