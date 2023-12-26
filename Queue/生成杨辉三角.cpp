#include<iostream>
#include<queue>
using namespace std;
int main() {
    int size;
    cin >> size;
    queue <int> q;
    q.push(1);
    q.push(1);
    q.push(0);//0用来相加得到1
    for (int i = 0; i < size;i++) {    
        int tmp = q.front();
        q.push(tmp);//将队首的1复制一份压入队尾
        while (q.front() != 0) {//队首不为0
            tmp = q.front();//把队首元素输出
            cout << q.front()<<' ' ;
            q.pop();
            tmp += q.front();//保存前后两个的和再压入队尾
            q.push(tmp);
        }
        cout << endl;
        tmp = q.front();
        q.pop();
        q.push(tmp);
    }
    return 0;
}