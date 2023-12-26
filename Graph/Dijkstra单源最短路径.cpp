#include <iostream>
#include <stack>
using namespace std;
#define MAX 25
#define INF 10000
int main() {
    int n, m, start, end, d, p;
    cin >> n >> m;
    int map[MAX][MAX];
    //初始化矩阵
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            map[i][j] = INF;
    }
    //输入距离值
    for (int i = 0; i < m; i++) {
        cin >> start >> end >> d;
        map[start][end] = d;
    }
    cin >> p;
    int head = p;
    int* distance = new int[n + 1];//距离数组
    for (int i = 1; i <= n; i++)
        distance[i] = INF;
    distance[p] = 0;
    int* path = new int[n + 1] {0};//路径数组
    bool* visited = new bool[n + 1] {false};//是否被访问过
    int count = 0;
    visited[p] = true;
    while (true) {
        bool judge = false;
        for (int i = 1; i < n + 1; i++) {
            if (map[p][i] > 100) continue;
            else {
                if (distance[i] > map[p][i] + distance[p]) {
                    distance[i] = map[p][i] + distance[p];
                    path[i] = p;
                    judge = true;
                }
            }
        }
        if (!judge)break;
        int min = INF, index = 0;
        for (int i = 1; i <= n; i++) {
            if (!visited[i] && distance[i] < min) {
                min = distance[i];
                index = i;
            }
        }
        visited[index] = true;
        count++;
        p = index;
    }
    for (int j = 0; j < count; j++) {
        int min_distance = INF, index_mom = 0;
        for (int i = 1; i <= n; i++) {
            if (distance[i]!=0 && min_distance > distance[i]) {
                min_distance = distance[i];
                index_mom = i;
            }
        }
        stack<int> s;
        s.push(index_mom);
        int copy = index_mom;
        while (index_mom!=head) {
            s.push(path[index_mom]);
            index_mom = path[index_mom];
        }
        cout << "NO." << j + 1 << " : " << head;
        s.pop();
        int num = s.size();
        for (int i = 0; i < num; i++) {
            cout << " -> " << s.top();
            s.pop();
        }
        cout << " , d = " << distance[copy]<<endl;
        distance[copy] = INF;
        
    }
    if (count < n-1) {
        cout << "No." << count + 1 << " : No Path to";
        for (int i = 1; i <= n; i++) {
            if (!visited[i])
                cout << ' ' << i;
        }
    }
    return 0;
}