#include<iostream>
#include<stack>
#include<string>
#include<map>
#include<cmath>
#include<iomanip>
using namespace std;
map<char, int>level{
    {'(',0},
    {'+',1},
    {'-',1},
    {'*',2},
    {'/',2},
    {'%',2},
    {'^',3},
};
bool judgeOperator(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '(' || ch == ')')
        return  true;
    return false;
}
bool judgeNumber(char ch) {
    if (ch >= '0' && ch <= '9' || ch == '.')
        return  true;
    return false;
}
bool Num_allowed(string number) {
    if (number.at(number.size() - 1) == '.' || number.at(0) == '.')
        return true;
    int count=0;
    for (char ch : number) {
        if (ch == '.')
            count++;
        if (count > 1)
            return true;
    }
    return false;
}
double forceD(int num) {//数据类型转换
    return static_cast<double>(num);
}
int forceI(double num) {
    return static_cast<int>(num);
}
int getChar(char ch) {//取出一个数字来
    return  ch - '0';
}
double str_num(string num) {//解析字符串为数字
    int n = num.size();
    bool judge = true;
    int power = 0;
    double number = 0.00;
    for (int i = 0; i < n; i++) {
        if (num.at(i) == '.') {
            number /= pow(10, n - i);
            judge = false;
        }
        else {
            if(judge)
                number += pow(10, n - 1 - i) * forceD(getChar(num.at(i)));
            else
                number += pow(0.1, ++power) * forceD(getChar(num.at(i)));
        }
    }
    return number;
}
double calculate(double n1, double n2, char ope) {//n1是先拿出来的，n2是后拿出来的
    switch (ope) {
    case '+':
        n2 += n1;
        break;
    case '-':
        n2 -= n1;
        break;
    case '*':
        n2 *= n1;
        break;
    case '/':
        n2 /= n1;
        break;
    case '%':
        n2 = forceD((forceI(n2)) % forceI(n1));
        break;
    case '^':
        n2 = pow(n2, n1);
        break;
    }
    return n2;
}
string convert(string& equation,double& answer) {
    string res;
    string number;//字符串
    stack<char> ope;//用来放运算符
    stack<double> num;//用来放操作数
    char tmp = '\0';
    for (char ch : equation) {
        if (judgeNumber(ch)) {
            number += ch;
        }
        else if (judgeOperator(ch)) {
            if (number.length() >= 1) {
                if (Num_allowed(number)) {//数字违法
                    res = "ERROR IN INFIX NOTATION";
                    return res;
                }
                num.push(str_num(number));//将数字解析出来并放入double数栈
                res += number;
                res += ' ';//连接到后缀表达式后
                number.erase(0, number.size());//清除操作数
            }
            if (ch != ')') {//这是个运算符，但不是)
                if (ch != '(' && judgeOperator(tmp) && tmp != ')') {//在上一个已经是运算符的情况下，ch也不是左括号,且tmp不是右括号
                    res = "ERROR IN INFIX NOTATION";
                    return res;
                }
                if (ope.empty())
                    ope.push(ch);
                else {
                    while (level[ch] <= level[ope.top()]) {
                        if (ch == '^' || ch == '(')break;
                        else {
                            res += ope.top();
                            res += ' ';
                            double n1 = num.top();
                            num.pop();
                            num.top() = calculate(n1, num.top(), ope.top());//算出来放回去
                            ope.pop();
                            if (ope.empty())
                                break;//如果ope已经空了，就跳出循环
                        }
                    }
                    ope.push(ch);
                }
            }
            else{//if (ch == ')')
                if (ope.empty()) {
                    res = "ERROR IN INFIX NOTATION";
                    return res;
                }
                while (ope.top() != '(') {
                    res += ope.top();
                    res += ' ';
                    double n1 = num.top();
                    num.pop();
                    num.top() = calculate(n1, num.top(), ope.top());//算出来放回去
                    ope.pop();//一直弹出，直至左括号
                    if (ope.empty()) {
                        res = "ERROR IN INFIX NOTATION";
                        return res;
                    }
                }
                if (ope.top() == '(')
                    ope.pop();
            }
        }
        else {
            res = "ERROR IN INFIX NOTATION";
            return res;
        }
        tmp = ch;
    }
    if (number.size() >= 1) {
        if (number.at(number.size() - 1) == '.' || number.at(0) == '.') {//数字违法
            res = "ERROR IN INFIX NOTATION";
            return res;
        }
        num.push(str_num(number));//将数字解析出来并放入double数栈
        res += number;
        res += ' ';//连接到后缀表达式后
        number.erase(0, number.size());//清除操作数
    }
    while (!ope.empty()) {
        if (ope.top() == '(') {
            res = "ERROR IN INFIX NOTATION";
            return res;
        }
        res += ope.top();
        res += ' ';
        double n1 = num.top();
        num.pop();
        num.top() = calculate(n1, num.top(), ope.top());//算出来放回去
        ope.pop();
    }
    answer = num.top();
    return res;
}

int main() {
    string equation;
    double answer;
    while (cin >> equation) {
        string sec = convert(equation,answer);
        if (sec == "ERROR IN INFIX NOTATION")
            cout << sec;
        else {
            cout << sec << endl;
            cout << fixed << setprecision(2) << answer;
        }
    }
    return 0;
}