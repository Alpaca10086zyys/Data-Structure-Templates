#include<iostream>
#include<string>
using namespace std;
void GetTarget(int n, string &p) {
    int* next = new int[n];//创建大小为n的next数组
    for (int i = 0; i < n; i++)
        cin >> next[i];
    if (next[0] != -1||next[1]!=0) {
        p = "ERROR";
        return ;//不符合，跳出
    }
    int j = 0;//用于做模板串的下标，遍历
    int count = 1;//用来计数,匹配前缀的长度
    for (int i = 2; i < n; i++) {
        if (next[i] == count) {
            p += p[j];
            count++;
            j++;
        }
        else if (next[i] < count&&next[i]>0) {//匹配的子串突然变小
            //检查是否确实不匹配了
            if (p[next[i] - 1] == p[count - 1]) {
                p = "ERROR";
                return;
            }
            j = next[i] - 1;
            p += p[j++];
            count = next[i]+1;
        }
        else if (next[i] == 0) {
            count = 1;
            j = 0;
            if (p[0] == '0') {
                p += '1';
            }
            else if (p[0] == '1') {
                p += '0';
            }
        }
        else {
            p = "ERROR";
            return;
        }
    }
}
int main() {
    int n;
    char begin, end;
    cin >> begin>> end >> n;
    string target="";
    target+= begin;
    GetTarget(n, target);
    if(target[0] == begin)
        target += end;
    cout << target;
    return 0;
}