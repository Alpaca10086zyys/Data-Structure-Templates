#include <iostream>
#include<cmath>
using namespace std;
#define SIZE 102
struct Node {
    int Val;//值
    //Node *Right;//指向下一行的结点
    //Node *Down;//指向上一行的结点
    bool Unvisited = false;//被访问过
};
Node matrix[SIZE][SIZE];
int main() {
    int m, n;
    cin >> m >> n;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> matrix[i][j].Val;//输入结点的值
            matrix[i][j].Unvisited = true;
        }
    }
    int count = m * n;
    int col=1, row=1,dire=1;
    while (true) {
        while(!matrix[row][col].Unvisited) {
            if (dire == 1) {
                row++;
                col--;
            }
            else if (dire == 2) {
                row--;
                col--;
            }
            else if (dire == 3) {
                row--;
                col++;
            }
            else if (dire == 4) {
                row++;
                col++;
            }
            else if (dire == -1) {
                row++;
                col++;
            }
            else if (dire == -2) {
                row++;
                col--;
            }
            else if (dire == -3) {
                row--;
                col--;
            }
            else if (dire == -4) {
                row--;
                col++;
            }
            if (dire == 4||dire==-1)
                dire *= (-1);
            else {
                dire++;
            }
        }
        if (abs(dire) == 1) {//向右&左
            cout << matrix[row][col].Val;
            matrix[row][col].Unvisited = false;
            if (dire > 0)
                col++;
            else
                col--;
        }
        else if (abs(dire) == 2) {
            cout << matrix[row][col].Val;
            matrix[row][col].Unvisited = false;
            if (dire > 0)
                row++;
            else
                row--;
        }
        if (abs(dire) == 3) {//向上&下
            cout << matrix[row][col].Val;
            matrix[row][col].Unvisited = false;
            if (dire > 0)
                col--;
            else
                col++;
        }
        else if (abs(dire) == 4) {
            cout << matrix[row][col].Val;
            matrix[row][col].Unvisited = false;
            if (dire > 0)
                row--;
            else
                row++;
        }
        cout << ' ';
        count--;
        if (count == 0)
            break;
    }
    return 0;
}