#include<iostream>
using namespace std;
struct Node {
    int Val=0;
    int Col=0;
    int Row=0;
};
void SparseMatrix(Node *mat1,int row,int col,int count,Node *mat2) {//转置函数
    int i,j,currentb;
    if (count > 0){// 非零矩阵 
        currentb = 0;
        for (i = 1; i <= col; i++) {//按a的列转置
            for (j = 0; j <= count; j++) {//找出当前列的所有元素
                if (mat1[j].Col == i) {//元素是当前列的，加入b
                    mat2[currentb].Row = mat1[j].Col;
                    mat2[currentb].Col = mat1[j].Row;
                    mat2[currentb].Val = mat1[j].Val;
                    currentb++;
                }
            }
        }
    }
}
int main() {
    int row1, col1, count1,row2,col2,count2;
    
    cin >> row1 >> col1>> count1;
    Node* mat1 = new Node[count1];
    for (int i = 0; i < count1; i++)
        cin >> mat1[i].Row >> mat1[i].Col >> mat1[i].Val;

    cin >> row2 >> col2 >> count2;
    Node* mat2 = new Node[count2];
    Node* mat3 = new Node[count2];
    for(int i=0;i<count2;i++)
        cin >> mat2[i].Row >> mat2[i].Col >> mat2[i].Val;
    if (col1 != row2) {
        cout << "ERROR";
        return 0;
    }
    else {
        SparseMatrix(mat2, row2, col2, count2, mat3);//转置
        /*for (int i = 0; i < count2; i++)
            cout << mat3[i].Row<<' '<<mat3[i].Col <<' '<< mat3[i].Val<<endl;*/
        Node* res = new Node[row1*col2];
        int i=1, j=1,count=0;//指针，i指向mat1的row参数，j指向mat2的row参数,j对应结果里的列标
        int k = 0,s=0;
        while (true) {
            if (i < mat1[k].Row || j < mat3[s].Row) {//说明结果矩阵的(i,j)一定为零
                if (i < mat1[k].Row) {
                //三元组的第一个就不是第i行的，说明mat1的第i行都为0，所以怎么乘都是0
                    i++;
                    j = 1;//j重新从1开始
                    continue;
                }
                else {
                    if (j < col2) {//未超出mat3的所有行
                        j++;//先尝试一下挪动行，遍历mat3的每一行
                        continue;
                    }
                }
            }
            else {
                while (true) {
                    if (mat1[k].Col == mat3[s].Col) {
                        res[count].Val += mat1[k].Val * mat3[s].Val;//恰好行列相等
                    }
                    else if (mat1[k].Col > mat3[s].Col) {
                        s++;
                    }
                    else if (mat3[s].Col > mat1[k].Col) {
                        k++;
                    }
                    if (mat1[k].Row > i || mat3[s].Row > j) {
                        if (res[count].Val > 0) {
                            count++;
                        }
                        break;
                    }
                }
            }
            if (s > count2)
                break;
        }
        for (k = 0; k < count1; k++) {
            for (s = 0; s < count2; s++) {
                if (mat1[k].Col == mat3[s].Col) {
                    res[count].Val += mat1[k].Val * mat3[s].Val;
                }
                if (res[count].Row == 0) {//未初始化过
                    res[count].Row = mat1[k].Row;
                    res[count].Col = mat3[s].Row;
                }
                else if(res[count].Col==mat3[s].Col)
            }
        }
        for (int a = 0; a < count; a++)
            cout << res[a].Row << ' ' << res[a].Col << ' ' << res[a].Val << endl;
    }
    return 0;
}



#include<iostream>
using namespace std;
int main() {
    int row1, col1, count1;
    cin >> row1 >> col1 >> count1;
    int** m1 = new int* [row1];
    for (int i = 0; i < row1; i++) {
        m1[i] = new int[col1];
        for (int j = 0; j < col1; j++)
            m1[i][j] = 0;
    }
    for (int i = 0; i < count1; i++) {
        int c, l, v;
        cin >> c >> l >> v;
        m1[c - 1][l - 1] = v;
    }
    int row2, col2, count2;
    cin >> row2 >> col2 >> count2;
    int** m2 = new int* [row2];
    for (int i = 0; i < row2; i++) {
        m2[i] = new int[col2];
        for (int j = 0; j < col2; j++)
            m2[i][j] = 0;
    }
    for (int i = 0; i < count2; i++) {
        int c, l, v;
        cin >> c >> l >> v;
        m2[c - 1][l - 1] = v;
    }
    bool judge = true;
    if (col1 != row2) {
        cout << "ERROR";
        return 0;
    }
    else {
        int** m3 = new int* [row1];
        for (int i = 0; i < row1; i++) {
            m3[i] = new int[col2];
            for (int j = 0; j < col2; j++)
                m3[i][j] = 0;
        }
        for (int i = 0; i < row1; i++) {
            for (int j = 0; j < col2; j++) {
                for (int k = 0; k < col1;k++) {
                    m3[i][j] += m1[i][k] * m2[k][j];
                }
                if (m3[i][j] != 0) {
                    judge = false;
                    cout << i + 1 << ' ' << j + 1 <<' '<< m3[i][j] << endl;
                }
            }
        }
        if (judge) {
            cout << "The answer is a Zero Matrix";
        }
    }
    return 0;
}