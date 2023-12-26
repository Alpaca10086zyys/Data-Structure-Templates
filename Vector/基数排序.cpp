#include <iostream>
#include <vector>
using namespace std;
int Max(vector<int> input) {    //本函数的返回数组中最大位数
    int max_num = input[0];
    for (int i = 0; i < input.size(); i++) {
        if (input[i] > max_num)
            max_num = input[i];
    }
    int p = 0;//位数
    while (max_num > 0) {
        p++;
        max_num /= 10;   //每次除以10取整，即可去掉最低位
    }
    return p;
}
int GetNum(int num, int d) {//本函数用于取出当前位的数，d指位数
    int p = 1;
    while (d - 1 > 0) {
        p *= 10;
        d--;
    }
    return num / p % 10;
}
//基数排序
vector<int> RadixSort(vector<int> input, int length) {//数据个数
    vector<int> bucket(length);   //创建临时存放排序过程中的数据
    vector<int> count(10);   //创建按位计数的技术容器，即记录排序中按个位、十位...各个数的位置的个数

    for (int d = 1; d <= Max(input); d++) {
        // 计数器清0
        for (int i = 0; i < 10; i++) {
            count[i] = 0;
        }

        // 统计各个桶中的个数
        for (int i = 0; i < length; i++) {
            count[GetNum(input[i], d)]++;//第i个数的第d位放进对应数字的桶，数量加一
        }

        for (int i = 1; i < 10; i++) {   //得到每个数应该放入bucket中的位置
            count[i] += count[i - 1];//因为从小到大入桶，所以前面需要叠加
        }

        for (int i = length - 1; i >= 0; i--) {  //采用倒序进行排序是为了不打乱已经排好的顺序
            int k = GetNum(input[i], d);
            bucket[count[k] - 1] = input[i];//在桶里排
            count[k]--;//放好了就减掉一个
        }
        for (int j = 0; j < length; j++) {  // 临时数组复制到 input 中
            input[j] = bucket[j];
            if (j == 0)
                cout << input[j];
            else {
                cout << ' ' << input[j];
            }
        }
        cout << endl;
    }
    return input;
}

int main()
{
    int n;
    cin >> n;
    vector<int> test(n);//构造容器
    for (int i = 0; i < n; i++) {
        cin >> test[i];
    }
    vector<int> result = test;
    result = RadixSort(result, n);
    cout << endl;
}
