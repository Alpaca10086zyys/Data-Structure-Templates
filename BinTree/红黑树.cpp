#include <iostream>
#include <vector>
#include <time.h>
#include "RBTree.h"
using namespace std;

clock_t start_Insert, stop_Insert;
clock_t start_Find, stop_Find;
clock_t start_Delete, stop_Delete;
double duration_Insert, duration_Find, duration_Delete;//函数经过的时间

int main()
{

    int a[] = { 10, 40, 30, 60, 90, 70, 20, 50, 80 };
    

    int check_insert = 0;    // "插入"动作的检测开关(0，关闭；1，打开)
    int check_remove = 0;    // "删除"动作的检测开关(0，关闭；1，打开)
    int i;
    int ilen = (sizeof(a)) / (sizeof(a[0]));
    RBTree<int>* tree = new RBTree<int>();

    
    /*
    cout << "== 原始数据: ";
    for (i = 0; i < ilen; i++)
        cout << a[i] << " ";
    cout << endl;
    */

    vector <long long> v;
    long long count = 10000;
    for (int i = 0; i < 20; i++) {

        start_Insert = clock();
        for (long long j = 1; j <= count; j++) {
            tree->insert((rand() % (count - 1)));
        }
        stop_Insert = clock();
        duration_Insert = (((double)(stop_Insert - start_Insert)) / CLK_TCK )*1000;
        cout << "N=" << count << " Insert_time:" << duration_Insert << endl;

        start_Find = clock();
        for (int j = 0; j < 1000; j++) {
            tree->search((rand() % (count - 1)) + 1);
        }
        stop_Find = clock();
        duration_Find = (((double)(stop_Find - start_Find)) / CLK_TCK) * 1000;
        cout << "N=" << count << " Find_time:" << duration_Find << endl;

        start_Delete = clock();
        for (long long j = count; j >=1 ; j--) {
            tree->remove((rand() % (count - 1)));
        }
        stop_Delete = clock();
        duration_Delete = (((double)(stop_Delete - start_Delete)) / CLK_TCK)*1000;
        cout << "N=" << count << " Delete_time:" << duration_Delete << endl<<endl;

        count += 20000;
    }

    // 销毁红黑树
    tree->destroy();

    return 0;
}