#include<iostream>
#include<string>
#include<queue>
using namespace std;
int con_char(char num) {//将单个字符转化为整型
    return int(num - '0');
}
char con_int(int num) {//将单个数字转化为字符型
    return '0' + num;
}
long long con_string(string num) {//将长数据字符串转化为long long
    int count = num.size();
    long long res = 0;
    long long ten_time = 1;
    for (int i = 0; i < count; i++) {
        res += ten_time * con_char(num[count - i - 1]);
        ten_time *= 10;
    }
    return res;
}
void reverseStr(string& str)//翻转字符串
{
    int n = str.length();
    // Swap character starting from two 
    // corners 
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}
string plusStr(string num1, string num2) {//得到两个数字字符串的和，转化为字符串
    string res;
    int n1 = num1.size();
    int n2 = num2.size();
    int tmp_ten = 0;
    int n = n1 > n2 ? n1 : n2;
    char x1, x2;
    for (int i = 0; i < n; i++) {//按位计算
        if (n > n1 && i >= n1) {
            x1 = '0';
            x2 = num2[n2 - 1 - i];
        }
        else if (n > n2 && i >= n2) {
            x2 = '0';
            x1 = num1[n1 - 1 - i];
        }
        else {
            x1 = num1[n1 - 1 - i];
            x2 = num2[n2 - 1 - i];
        }
        int tmp = con_char(x1) + con_char(x2) + tmp_ten;//保存当前和，用于进位
        res += con_int(tmp % 10);//个位直接操作
        tmp_ten = tmp / 10;//十位留存
    }
    if (tmp_ten > 0)
        res += con_int(tmp_ten);
    reverseStr(res);
    return res;
}
string reduceStr(string num1, string num2) {
    string res;
    int n1 = num1.size();
    int n2 = num2.size();
    int tmp_ten = 0;
    int n = n1 > n2 ? n1 : n2;
    char x1, x2;
    for (int i = 0; i < n; i++) {//按位计算
        if (n > n1 && i >= n1) {
            x1 = '0';
            x2 = num2[n2 - 1 - i];
        }
        else if (n > n2 && i >= n2) {
            x2 = '0';
            x1 = num1[n1 - 1 - i];
        }
        else {
            x1 = num1[n1 - 1 - i];
            x2 = num2[n2 - 1 - i];
        }
        int tmp = con_char(x1) - con_char(x2) + tmp_ten;//保存当前和，用于进位
        if (tmp >= 0) {
            res += con_int(tmp);//个位直接操作
            tmp_ten = 0;
        }
        else {
            tmp_ten = -1;
            res += con_int(10 + tmp);
        }
    }
    if (tmp_ten == -1) {
        return '-' + reduceStr(num2, num1);
    }
    reverseStr(res);
    while (res[0] == '0') {
        res.erase(0, 1);
    }
    if (res == "")
        res = "0";
    return res;
}
string product(string num1, string num2) {
    int n1 = num1.size();
    int n2 = num2.size();
    bool j1 = true;//用于判断正负
    bool j2 = true;
    if (num1[0] == '-') 
        j1 = false;
    if (num2[0] == '-') 
        j2 = false;
    string res = "0";
    for (int i = 0; i < n2; i++) {
        if (num2[n2 - i - 1]=='-')
            break;
        string tmp_product = "";
        int tmp_ten = 0;
        for (int j = 0; j < n1; j++) {
            if (num1[n1 - 1 - j] == '-')
                continue;
            int tmp_res = con_char(num2[n2-i-1]) * con_char(num1[n1-1-j])+tmp_ten;
            tmp_product += con_int(tmp_res % 10 );
            tmp_ten = tmp_res / 10;
        }
        if (tmp_ten != 0)
            tmp_product += con_int(tmp_ten);
        reverseStr(tmp_product);
        int count = i;
        while (count) {
            tmp_product += '0';
            count--;
        }
        res=plusStr(res, tmp_product);
    }
    if (j1 == false && j2 == true || j1 == true && j2 == false) {
        res = '-' + res;
    }
    return res;
}
string division(string be_di, string di) {
    int n1 = be_di.size();
    int n2 = di.size();
    string res = "";
    long long d = con_string(di);
    long long b = con_string(be_di.substr(0, n2));
    int count = n1 - n2+1;
    while (count) {
        res += con_int(b / d);
        b = b % d;
        count--;
        b = b * 10 + con_char(be_di[n1 - count]);
    }
    if (res[0] == '0')
        res.erase(0, 1);
    return res;
}
string powStr(string num, string index) {
    string tmp = "1";
    for (int i = 0; i < con_string(index); i++) {
        tmp = product(num, tmp);
    }
    return tmp;
}
struct item {
    string coe_x = "0";//X的系数
    string coe_y = "0";//y的系数
    string coe;//总的系数
    string index_x;//x的次数
    string index_y;//y的次数
}basic;
string C(string id, string index) {
    if (id == "0")
        return "1";
    string res = "1";
    string tmp = "1";
    for (int i = 0; i < con_string(id); i++) {
        res = product(reduceStr(index, to_string(i)), res);
    }
    for (int i = 0; i < con_string(id); i++) {
        tmp = product(tmp, plusStr(to_string(i), "1"));
    }
    //需要除法操作
    return division(res, tmp);
}//二项式计算函数
item cal_coe(string id, string index, item basic) {
    struct item tmp;
    tmp.index_x = reduceStr(index, id);
    tmp.index_y = id;
    tmp.coe = product(product(powStr(basic.coe_x, reduceStr(index, id)),powStr(basic.coe_y, id) ), C(id, index));
    return tmp;
}//求某一项
string explain(item tmp) {
    string res;
    if (tmp.coe == "1");
    else if (tmp.coe == " - 1")
        res += '-';
    else
        res += tmp.coe;
    if (tmp.index_x == "1")
        res += 'x';
    else if (tmp.index_x == "0");
    else {
        res += "x^";
        res += tmp.index_x;
    }
    if (tmp.index_y == "1")
        res += 'y';
    else if (tmp.index_y == "0");
    else {
        res += "y^";
        res += tmp.index_y;
    }
    return res;
}//将一项解析为字符串
int main() {
    //string num1, num2,index;
    //cin >> num1 >> num2;
    //cin>> index;
    //cout << num1.size() << ' ' << num2.size() << endl;
    //cout << plusStr(num1, num2) << endl;
    //cout << reduceStr(num1, num2) << endl;
    //cout << product(num1, num2)<<endl;
    //cout << division(num1, num2) << endl;
    //cout << powStr(num1, "2") << endl;
    //cout << powStr(num2, "13") << endl;
    //cout << C("13", "15");

    string index;
    cin >> basic.coe_x >> basic.coe_y >> index;
    queue<item> q;
    for (int i = 0; i <= con_string(index); i++) {
        struct item tmp = cal_coe(to_string(i), index, basic);
        q.push(tmp);
    }
    string res = explain(q.front());
    q.pop();
    for (int i = 1; i <= con_string(index); i++) {
        if (q.front().coe[0] != '-')
            res += '+';
        res += explain(q.front());
        q.pop();
    }
    cout << res;
    return 0;
}