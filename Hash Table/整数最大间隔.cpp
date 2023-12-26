#include<iostream>
using namespace std;
int  n,seed;
int rand() { 
    return(((seed = seed * 214013L + 2531011L) >> 16) & 0x7fff);
}
int rand32() {
    return ((rand() << 16) + (rand() << 1) + rand() % 2);
}
int maxgap(int a[]) {
    int maxgap=0;
    int left=a[0], right=a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] < left)
            left = a[i];
        if (a[i] > right)
            right = a[i];
    }
    /*traverse through all breakpoints to find the position of the leftmost point and the position of the rightmost point.*/
    if (left == right)
        return 0;
    /*special situation*/
    double average_gap = double(right - left) / (n - 1); 
    bool* bucket = new bool[n];//judge whether the bucket is empty
    for (int i = 0; i < n; i++) {
        bucket[i] = 0;
    }
    //use bool to adjust two parameters dynamicly
    int* tmp_max = new int[n];
    int* tmp_min = new int[n];
    for (int i = 0; i < n; i++) {/*put the point into different bucket*/
        int index = ((a[i] - left) / average_gap);//calculate the key
        if (bucket[index] == 0) {
            tmp_min[index] = a[i];
            tmp_max[index] = a[i];
            bucket[index] = 1;
        }
        else {
            if (tmp_min[index] > a[i])
                tmp_min[index] = a[i];
            else if (tmp_max[index] < a[i])
                tmp_max[index] = a[i];
        }
    }
    int lastmax;
    /*find the last tmp_max*/
    for (int i = 0; i < n; i++)
        if (bucket[i] != 0)
            lastmax = tmp_max[i];
    for (int i = 1; i < n; i++){
        if (bucket[i] != 0)
        {
            int tem = max(tmp_min[i] - lastmax, tmp_max[i] - tmp_min[i]);
            maxgap = max(maxgap, tem);
            lastmax = tmp_max[i];
        }
    }
    /*calculate distanceand keep the maximum*/
    return maxgap;
}
int main() {
    cin >> n >> seed;
    int* np = new int[n];
    for (int i = 0; i < n; i++)
        np[i] = rand32();
    cout << maxgap(np);
    return 0;
}