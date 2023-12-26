#include<iostream>
using namespace std;
void isort(int start, int end, int* a, int N){
	for (int i = 1; i <= end; i++){
		int key = a[i];
		int j = i - 1;
		while (j >= start && a[j] > key){
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}
bool isab(int* a, int* b, int n){
	for (int i = 0; i < n; i++){
		if (a[i] != b[i])
			return false;
	}
	return true;
}
bool msort(int* a, int* b, int n){
	for (int i = 2; i < n; i += i){
		for (int j = 0; j < n; j += i){
			int end = (j + i - 1 < n - 1 ? j + i - 1 : n - 1);
			isort(j, end, a, n);
		}
		if (isab(a, b, n)){
			cout << "Merge Sort" << endl;
			int k = 2 * i;
			for (int j = 0; j < n; j += k){
				int end = (j + k - 1 < n - 1 ? j + k - 1 : n - 1);
				isort(j, end, a, n);
			}
			for (int m = 0; m < n - 1; m++)
				cout << a[m] << " ";
			cout << a[n - 1];
			return true;
		}
	}
	return false;
}
int main() {
	int n;
	cin >> n;
	int* a = new int[n];
	int* c = new int[n];
	int* b = new int[n];
	for (int i = 0; i < n; i++){
		cin >> a[i];
		c[i] = a[i];//拷贝一份给c数组
	}

	for (int i = 0; i < n; i++)
		cin >> b[i];//过程中得到的序列
	if (msort(a, b, n) == true)
		return 0;
	else{
		for (int i = 1; i < n; i++){
			isort(0, i, c, n);
			if (isab(b, c, n)){
				cout << "Insertion Sort" << endl;
				isort(0, i + 1, c, n);
				for (int k = 0; k < n - 1; k++)
					cout << c[k] << " ";
				cout << c[n - 1];
				break;
			}
		}
		return 0;
	}
}