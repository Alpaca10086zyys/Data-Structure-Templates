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
    if (ch >= '0' && ch <= '9')
        return  true;
    return false;
}
string convert(string& equation) {
    string res;
    stack<char> ope;//用来放运算符
    char tmp='\0';
    for (char ch : equation) {
        if (judgeNumber(ch)) {
            if (judgeNumber(tmp)) {
                res = "ERROR IN INFIX NOTATION";
                return res;
            }
            res += ch;
        }
        else if (judgeOperator(ch) && ch != ')') {//这是个运算符，但不是)
            if (ch != '(' && judgeOperator(tmp)&&tmp!=')') {//在上一个已经是运算符的情况下，ch也不是左括号,且tmp不是右括号
                res = "ERROR IN INFIX NOTATION";
                return res;
            }
            if (ope.empty())
                ope.push(ch);
            else {
                while(level[ch] <=level[ope.top()]) {
                    if (ch == '^'||ch=='(')break;
                    else {
                        res += ope.top();
                        ope.pop();
                        if (ope.empty())
                            break;//如果ope已经空了，就跳出循环
                    }
                }
                ope.push(ch);
            }
        }
        else if (ch == ')') {
            if (ope.empty()) {
                res = "ERROR IN INFIX NOTATION";
                return res;
            }
            while (ope.top() != '(') {
                res += ope.top();
                ope.pop();//一直弹出，直至左括号
                if (ope.empty()) {
                    res = "ERROR IN INFIX NOTATION";
                    return res;
                }
            }
            if (ope.top() == '(')
                ope.pop();
        }
        tmp = ch;
    }
    while (!ope.empty()) {
        if (ope.top() == '(') {
            res = "ERROR IN INFIX NOTATION";
            return res;
        }

        res += ope.top();
        ope.pop();
    }
    return res;
}
double forceD(int num){//数据类型转换
    return static_cast<double>(num);
}
int forceI(double num){
    return static_cast<int>(num);
}
int getChar(char ch){//取出一个数字来
    return  ch-'0';
}
double calculate(string sec){
    stack<double> NumStack;
    for(char ch:sec){
        double tmp;
        if(judgeNumber(ch)){
            tmp=forceD(getChar(ch));//转化成double
            NumStack.push(tmp);//double类型数据入栈
        }
        else if(judgeOperator(ch)){
            switch(ch){
                case '+':
                    double n1=NumStack.top();
                    NumStack.pop();
                    NumStack.top()+=n1;
                    break;
                case '-':
                    double n1=NumStack.top();
                    NumStack.pop();
                    NumStack.top()-=n1;
                    break;
                case '*':
                    double n1=NumStack.top();
                    NumStack.pop();
                    NumStack.top()*=n1;
                    break;
                case '/':
                    double n1=NumStack.top();
                    NumStack.pop();
                    NumStack.top()/=n1;
                    break;
                case '%':
                    int n=forceI(NumStack.top());
                    NumStack.pop();
                    NumStack.top()=forceD((forceI(NumStack.top()))%n);
                    break;
                case '^':
                    double n1=NumStack.top();
                    NumStack.pop();
                    NumStack.top()=pow(NumStack.top(),n1);
                    break;
            }
        }
    }
    return NumStack.top();
}
int main() {
    string equation;
    while (cin >> equation) {
        string sec = convert(equation);
        if (sec=="ERROR IN INFIX NOTATION")
            cout << sec;
        else
            cout<< fixed << setprecision(2) <<calculate(sec);
    }
    return 0;
}