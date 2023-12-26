#include<iostream>
#include<vector>
using namespace std;
class DSU {
private:
    vector<int> arr;
    int findHead(int n) {
        int res = arr[n];//对应的老大
        while (arr[res] != res) {//当它的老大不是自己而另有其人的时候就做循环
            res = arr[res];//指向老大
        }
        arr[n] = res;
        return res;
    }
public:
    DSU(int n) {
        arr = vector<int>(n);
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }
    }
    void merge(int a, int b) {
        int aHead = findHead(a);
        int bHead = findHead(b);
        arr[aHead] = bHead;
        arr[a] = bHead;
    }
    bool test(int a, int b) {
        return findHead(a) == findHead(b);
    }
};
int main() {
    int N, M;//N表示元素数，M表示操作数
    cin >> N >> M;
    DSU dsu(N+1);
    int x, y, z;
    for (int i = 0; i < M; i++) {
        cin >> x>>y>>z;
        if (x == 1) 
            dsu.merge(y, z);
        else if (x == 2) {
            if (dsu.test(y, z))
                cout << "Y" << endl;
            else
                cout << "N" << endl;
        }
    }
    return 0;
}

