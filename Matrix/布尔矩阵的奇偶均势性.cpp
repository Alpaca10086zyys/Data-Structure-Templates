#include<iostream>
using namespace std;
int main() {
	int N;
	cin >> N;
	int** matrix = new int* [N + 1];
	for (int i = 0; i <= N; i++) {
		matrix[i] = new int[N + 1];
	}//动态数组
	int bad_row = 0, bad_col = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N;j++)
			cin>> matrix[i][j];
	for (int i = 1; i <= N; i++) {
		int sum_row = 0,sum_col=0;
		for (int j = 1; j <= N; j++) {
			sum_row += matrix[i][j];
			sum_col += matrix[j][i];
		}
		if (sum_row % 2 == 1) {
			if (bad_row == 0)
				bad_row = i;
			else
				bad_row = -1;
		}
		if (sum_col % 2 == 1) {
			if (bad_col == 0)
				bad_col = i;
			else
				bad_col = -1;
		}
	}
	if (bad_row == 0 && bad_col == 0)
		cout << "OK";
	else if (bad_row != 0 && bad_col != 0) {
		if (bad_row != -1 && bad_col != -1)
			cout << "Change bit (" << bad_row << ',' << bad_col << ")";
		else
			cout << "Corrupt";
	}
	else
	    cout << "Corrupt";
	return 0;
}



