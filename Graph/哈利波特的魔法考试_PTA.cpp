#include <iostream>
#include <cmath>
using namespace std;
#define INF 5000000
#define MAX 101
int main() {
	int n, m,begin,end,d;
	cin >> n >> m;
	int map[MAX][MAX];
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= n; j++) {
			map[i][j] = INF;
			if (i == j)
				map[i][j] = 0;
		}
	
	for (int i = 0; i < m; i++) {
		cin >> begin >> end >> d;
		map[begin][end] = d;
		map[end][begin] = d;
	}
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= n; j++) 
			for (int k = 1; k <= n; k++) {
				map[j][k] = min(map[j][k], map[i][k] + map[j][i]);
				map[k][j] = map[j][k];
			}
	int index=0,min_dis=INF;
	for (int i = 1; i <= n;i++) {
		int max_dis_ = 0;
		for (int j = 1; j <= n; j++) {
			if (map[i][j] == INF) {
				index = -1;
				break;
			}
			if (map[i][j] > max_dis_)
				max_dis_ = map[i][j];
		}
		if (index == -1) {
			index = 0;
			break;
		}
		if (max_dis_ < min_dis) {
			min_dis = max_dis_;
			index = i;
		}
	}
	cout << index;
	if (index != 0)
		cout << ' ' << min_dis;
	return 0;
}