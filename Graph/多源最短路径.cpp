#include<iostream>
#include<cmath>
using namespace std;
#define INF 20000
#define MAX 25
void print(int a) {
	if (a == INF)cout << -1;
	else cout << a;
}
int main() {
	int n, m,start,end,d;
	cin >> n >> m;
	int map[MAX][MAX];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				map[i][j] = 0;
			else
				map[i][j] = INF;
		}
	}
	for (int i = 0; i < m; i++) {
		cin >> start >> end>>d;
		map[start][end] = d;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (j == i || k == i);
				else {
					map[j][k] = min(map[j][k], map[j][i] + map[i][k]);
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			print(map[i][j]);
			if (j != n - 1) cout << ' ';
		}
		cout << endl;
	}
	return 0;
}