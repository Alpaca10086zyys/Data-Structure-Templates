#include<iostream>
#include<cstring>
#include<time.h>
#include<fstream>
using namespace std;
ifstream ifs;
ofstream ofs;
int CompareNum=0;
const int SIZE = 256;
void MakeHash(long long* hash, string P) {
    for (int i = 0; i < SIZE; i++) {
        hash[i] = -1;
    }
    for (int i = 0; i < P.size(); i++) {
        int ascii = (int)P[i];//计算b[i]的ASCII值
        hash[ascii] = i;//找出每一个字母最后出现的位置
    }
}
int moveByGs(int j, int m, int suffix[], bool prefix[]) {
    int k = m - 1 - j;//好后缀的长度
    if (suffix[k] != -1) return j - suffix[k] + 1;
    for (int r = j + 2; r <= m - 1; ++r) {
        if (prefix[m - r] == true) {
            return r;
        }
    }
    return m;
}
void generateGS(string P, int* suffix, bool* prefix) {
    int m = P.size();
    for (int i = 0; i < m; ++i) {
        //初始化suffix,prefix数组
        suffix[i] = -1;
        prefix[i] = false;
    }
    for (int i = 0; i < m - 1; ++i) {
        //循环处理b[0,i]
        int j = i;
        int k = 0;//公共后缀子串的长度
        while (j >= 0 && P[j] == P[m - 1 - k]) {
            //与b[0,m-1]求公共后缀子串
            --j;
            ++k;
            suffix[k] = j + 1;//j+1表示公共后缀子串在b[0,i]中的起始下标
            CompareNum++;
        }
        if (j == -1) prefix[k] = true;   //公共后缀子串也是模式串的前缀子串
    }
}
int BM(string P, string T) {
    int m = P.size();
    int n = T.size();
    long long bc[SIZE];//记录模式串中每个字符最后出现的位置
    MakeHash(bc, P);//构建坏字符哈希表
    int* suffix = new int[m];
    bool* prefix = new bool[m];
    generateGS(P, suffix, prefix);
    int i = 0;//表示主串与模式串匹配的第一个字符
    while (i <= n - m) {
        int j;
        for (j = m - 1; j >= 0; --j) {
            //模式串从后往前匹配
            if (T[i + j] != P[j]&&++CompareNum) {
                break; //坏字符对应模式串中的下标是j
            }
        }
        if (j < 0) {
            return i;   //匹配成功，返回主串与模式串第一个匹配的字符的位置
        }
        int x = j - bc[(int)T[i + j]];
        int y = 0;
        if (j < m - 1) {
            y = moveByGs(j, m, suffix, prefix);
        }
        i = i + max(x, y);
    }
    return -1;
}
int main() {
    string T, P;
    ifs.open("C:\\Users\\20991\\Desktop\\01_data(long target).txt",ios::in);
    if (!ifs.is_open())
        cout << "ERROR!"<<endl;
    else {
        /*while (ifs >> T >> P) {
            start = clock();
            long long hash[256];
            for (int i = 0; i < SIZE; i++) {
                hash[i] = -1;
            }
            MakeHash(hash, P);
            long place = BM(P, T);
            stop = clock();
            duration = ((double)(stop - start)) * 1000 * 1000 / CLOCKS_PER_SEC;
            cout << "RunTime is:" << duration << 's' << endl;
            cout << "RunCount is" << endl;
            if (place == -1)
                cout << "not found" << endl;
            else
                cout << "Position is " << place << endl;
        }
        */
        ofs.open("C:\\Users\\20991\\Desktop\\01_long_result.txt", ios::out);
        if (!ofs.is_open()) 
            cout << "Fail to open result!"<<endl;
        else {
            cout << "Success to open result.txt!"<<endl;
            while (ifs >> T >> P) {
                cout << "Begin to operate!" << endl;
                long long hash[256];
                for (int i = 0; i < SIZE; i++) {
                    hash[i] = -1;
                }
                MakeHash(hash, P);
                long place = BM(P, T);
                //cout << "RunTime is:" << duration << 's' << endl;
                ofs<< "RunCount is " <<CompareNum<< endl;
                //cout << "RunCount is" << endl;
                if (place == -1)
                    ofs<< "not found" << endl;
                    //cout << "not found" << endl;
                else
                    ofs<< "Position is " << place << endl;
                    //cout << "Position is " << place << endl;
                ofs << endl;
            }
            ifs.close();
            ofs.close();
            cout << "Success!";
        }
    }
    return 0;
}


