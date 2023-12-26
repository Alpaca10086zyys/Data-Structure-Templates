#include<iostream>
using namespace std;
int main() {
    int n;//碎块个数
    cin >> n;
    long* energy = new long[n];
    long sum = 0;
    for (int i = 0; i < n; i++) 
        cin >> energy[i];
        for (int i = 0; i < n-1; i++) {
            for (int j = 0; j < n - i-1 ; j++) {
                if (energy[j] < energy[j + 1]) {
                    long tmp = energy[j];
                    energy[j] = energy[j + 1];
                    energy[j + 1] = tmp;
                }
            }
            for (int j = 0; j < n - i -2; j++) {
                if(energy[j]< energy[j + 1]) {
                    long tmp = energy[j];
                    energy[j] = energy[j + 1];
                    energy[j + 1] = tmp;
                }
            }
            energy[n - 2 - i] += energy[n  -1- i];
            sum += energy[n - 2 - i];
        }//冒泡排序调整为从大到小
        cout << sum;
    return 0;
}