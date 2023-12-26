#include <iostream>
#include <string>
#include <stack>
using namespace std;
bool judge(char a, char b) {
    if (abs((int)(a - b)) == 32)
        return true;//需要删去
    return false;
}
int main() {
    string str;
    cin >> str;
    stack<char> s;
    for (char ch : str) {
        if (s.empty()) {//栈为空，直接压入，然后下一轮循环
            s.push(ch);
            continue;
        }
        if (judge(s.top(), ch)) {
            s.pop();
        }
        else {
            s.push(ch);
        }
    }
    if (s.empty())
        cout << -1;
    else {
        char res[1000]{ '\0' };
        int num = s.size();
        for (int i = 0; i < num; i++) {
            res[i] = s.top();
            s.pop();
        }
        for (int i = num - 1; i >= 0; i--)
            cout << res[i];
    }
    return 0;
}