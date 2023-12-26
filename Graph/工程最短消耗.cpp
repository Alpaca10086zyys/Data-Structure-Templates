#include<iostream>
#include<string>
#include<cmath>
#include<queue>
using namespace std;
#define MAX 21
#define INF 999999
int matrix[MAX][MAX]{0};
int indegree[MAX]{ 0 };
int cost[MAX]{ 0 };
int N;
int id[MAX]{ 0 };
char str[MAX][12]{ '\0' };//前驱字符串
int string_to_int(string a) {
	int length = a.length();
	int res=0;
	for (int i = 0; i < length; i++) 
		res += int(pow(10, length - i - 1)) * (a[i]-'0');
	return res;
}
void convert(char* str,int id) {
	int length = 0;
	indegree[id] = 0;//入度
	while (str[length] != '\0') {
		length++;
	}
	int judge = 2;//1意为数字中,2意为数字重新开始
	if (length == 0) {
		return;
	}
	int before = 0;
	string number = "";
	for (int i = 1; i < length; i++) {//遍历
		if (judge == 1) {
			if (str[i] == ';') {
				judge = 2;
				indegree[id]++;
				before = string_to_int(number);//计算出前驱before
				matrix[before][id] = 1;
				before = 0;
			}
			else {
				number += str[i];
			}
		}
		else if (judge == 2) {
			number = "";
			number += str[i];
			judge = 1;
		}
	}
}
void TopSort() {
	queue<int> q;
	int least_cost[MAX]{0};
	for (int i = 1; i <= N; i++)
		least_cost[i] = INF;
	for (int i = 1; i <= N;i++) {
		if (indegree[id[i]] == 0) {
			q.push(id[i]);
			least_cost[id[i]] = 0;
		}
	}
	int cnt=0,last;
	while (!q.empty()) {
		int V = q.front(),W;
		q.pop();
		for (int i = 1; i <= N; i++) {
			if (matrix[i][V]) {//找到V的前驱i
				
				if (least_cost[i] + cost[i] > least_cost[V]||least_cost[V]==INF) {
					least_cost[V] = least_cost[i] + cost[i];//更新最小的值
				}
			}
		}
		if (cnt == N - 1)last = V;
		cnt++;
		for (int i = 1; i <= N; i++) {
			if (matrix[V][i]) {//如果有邻接点
				W = i;
				if (--indegree[W] == 0)
					q.push(W);
			}
		}
	}
	if (cnt != N) {
		cout << "error";
	}
	else {
		/*int max = 0;
		for (int i = 1; i <= N; i++) {
			if (least_cost[i] > max)
				max = least_cost[i];
		}
		cout << max;*/
		cout << least_cost[last] + cost[last];
	}
}
int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> id[i];
		cin>> cost[id[i]];
		cin.getline(str[id[i]], 12);
		convert(str[id[i]], id[i]);//构造好了邻接矩阵，同时入度数组构造完毕
	}
	TopSort();
	//尼玛什么破代码我真的会谢
	return 0;
}

