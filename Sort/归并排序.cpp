#include<iostream>
#include<vector>
using namespace std;
void Merge(int* a, int begin, int mid, int end) {
	vector<int> temp;
	int i = begin;
	int j = mid + 1;
	while (i <= mid && j <= end) {
		if (a[j] < a[i]) {
			temp.push_back(a[j]);
			j++;
		}
		else {
			temp.push_back(a[i]);
			i++;
		}
	}
	while (i <= mid) {
		temp.push_back(a[i++]);
	}
	while (j <= end) {
		temp.push_back(a[j++]);
	}
	for (int k = 0; k < temp.size();k++) {
		a[begin + k] = temp[k];
	}
}
void MergeSort(int* a, int left, int right) {
	if (right - left ==0)
		return;
	int mid = (left + right) / 2;
	MergeSort(a, left, mid);
	MergeSort(a, mid + 1, right);
	Merge(a, left, mid, right);
}

int main() {
	int n;
	cin >> n;
	int* p = new int[n];
	for (int i = 0; i < n; i++)
		cin >> p[i];
    MergeSort(p, 0, n-1);
	for (int i = 0; i < n; i++)
		cout<<p[i]<<' ';
	return 0;
}