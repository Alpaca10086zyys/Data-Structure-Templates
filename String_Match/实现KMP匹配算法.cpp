#include<iostream>
#include<string>
using namespace std;
void MakeNext(int* next,string P) {//准备next数组
    int j = 1;
    next[0] = 0;
    int count = 0;
    while (j < P.size()) {
        if (P[j] == P[count]) {
            next[j] = ++count;
            j++;
        }
        else {
            if (count == 0) {
                next[j] = 0;
                j++;
            }
            else
                count = next[count - 1];
        }
    }
}
int KMPFind(int* next,string T,string P) {//寻找位置
    int i = 0;//主串T的指针
    int j = 0;//模板串的指针
    while(i<T.size()) {
        if (T[i] == P[j]) {
            i++;
            j++;
            if (j == P.size())
                return i - j;
        }
        else if (j > 0)
            j = next[j - 1];
        else
            i += 1;//字串第一个字符就失配
    }
    return -1;
}
int main() {
    string T, P;
    cin >> T>>P;
    int* next = new int[P.size()];
    next[0] = -1;
    MakeNext(next, P);
    if (KMPFind(next, T, P) == -1)
        cout << "no";
    else
        cout << KMPFind(next, T, P);
    return 0;
}

