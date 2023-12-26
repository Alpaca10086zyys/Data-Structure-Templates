#include<iostream>
using namespace std;
int n;
bool is_Max(int* arr) {//返回值即为是否为大顶堆
    for (int i = 2; i <= n; i++) {
        if (arr[i] > arr[i / 2])
            return false;
    }
    return true;
}
bool is_Min(int* arr) {//返回值即为是否为小顶堆
    for (int i = 2; i <= n; i++) {
        if (arr[i] < arr[i / 2])
            return false;
    }
    return true;
}

void buildMax(int* arr,int p) {
    int Parent, Child;
    int X;
    X = arr[p];//取出根结点存放的值
    for (Parent = p; Parent * 2 <= n; Parent = Child) {
        Child = Parent * 2;
        if ((Child != n) && (arr[Child] <= arr[Child + 1]))
            Child++;
        if (X >= arr[Child])
            break;
        else
            arr[Parent] = arr[Child];
    }
    arr[Parent] = X;
}
void buildMin(int* arr, int p) {
    int Parent, Child;
    int X;
    X = arr[p];//取出根结点存放的值
    for (Parent = p; Parent * 2 <= n; Parent = Child) {
        Child = Parent * 2;
        if ((Child != n) && (arr[Child] >= arr[Child + 1]))
            Child++;
        if (X <= arr[Child])
            break;
        else
            arr[Parent] = arr[Child];
    }
    arr[Parent] = X;
}
void operation(bool max,bool min,int *arr) {
    if (max&&min) {
        cout << "max min";
        return;
    }
    if (max&&!min) {//改成小顶堆
        cout << "max ";
        for (int i = n / 2; i > 0; i--)
            buildMin(arr, i);
    }
    else if (!max && min) { //改成大顶堆
        cout << "min ";
        for (int i = n / 2; i > 0; i--)
            buildMax(arr, i);
    }
    else 
        for (int i = n / 2; i > 0; i--)
            buildMax(arr, i);
}
int main() {
    cin >> n;
    int* arr = new int[n+1];
    for (int i = 1; i < n + 1; i++) 
        cin >> arr[i];
    bool max, min;

    max = is_Max(arr);
    min = is_Min(arr);
    operation(max, min, arr);
    if (max && min);
    else
        for (int i = 1; i <= n; i++)
            cout<< arr[i]<<' ';
    
    return 0;
}

