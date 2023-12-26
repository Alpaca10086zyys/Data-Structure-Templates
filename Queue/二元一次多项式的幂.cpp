#include<iostream>
#include<queue>
#include<cmath>
#include<string>
using namespace std;
struct item {
    long coe_x = 0;//X的系数
    long coe_y = 0;//y的系数
    long coe;//总的系数
    long index_x;//x的次数
    long index_y;//y的次数
}basic;
long C(int id, int index) {
    if (id == 0)
        return 1;
    long res = 1;
    long tmp = 1;
    for (int i = 0; i < id; i++) {
        res *= (index - i);
    }
    for (int i = 0; i < id; i++) {
        tmp *= (i + 1);
    }
    return res / tmp;
}//二项式计算函数
item cal_coe(long id, long index, item basic) {
    struct item tmp;
    tmp.index_x = index - id;
    tmp.index_y = id;
    tmp.coe = long(pow(basic.coe_x, index - id) * pow(basic.coe_y, id) * C(id, index));
    return tmp;
}//求某一项
string explain(item tmp) {
    string res;
    if (tmp.coe == 1);
    else if (tmp.coe == -1)
        res += '-';
    else 
        res += to_string(tmp.coe);
    if (tmp.index_x == 1)
        res += 'x';
    else if (tmp.index_x == 0);
    else {
        res += "x^";
        res += to_string(tmp.index_x);
    }
    if (tmp.index_y == 1)
        res += 'y';
    else if (tmp.index_y == 0);
    else {
        res += "y^";
        res += to_string(tmp.index_y);
    }
    return res;
}//将一项解析为字符串
int main() {
    int index;
    cin >> basic.coe_x >> basic.coe_y >> index;
    queue<item> q;
    for (int i = 0; i <= index; i++) {
        struct item tmp = cal_coe(i, index, basic);
        q.push(tmp);
    }
    string res = explain(q.front());
    q.pop();
    for (int i = 1; i <= index; i++) {
        if(q.front().coe>0)
            res += '+';
        res += explain(q.front());
        q.pop();
    }
    cout << res;
    return 0;
}
