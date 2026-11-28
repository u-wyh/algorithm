// https://www.luogu.com.cn/problem/P4290
// 题意：初始从 W, I, N, G 中选一个字母，
// 按给出的双字母替换规则不断将任意单个字母替换成两个字母，
// 给定长度为 L 的最终字符串
// 按 W, I, N, G
// 顺序输出所有可能作为初始字母的字符
// （都不可行输出 The name is wrong!）。
// 数据范围：L <= 200，W, I, N, G <= 16。
// 难度评分：1500（洛谷分级换算）
// 算法标签：区间动态规划
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;

int a[5];
bool change[5][5][5];
bool f[MAXN][MAXN][5];
char s[MAXN];

inline int val(char c){
    if(c=='W') return 1;
    if(c=='I') return 2;
    if(c=='N') return 3;
    if(c=='G') return 4;
}

int main()
{
    for(int i=1;i<=4;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=4;i++){
        for(int j=1;j<=a[i];j++){
            char c[2];
            scanf("%s",c);
            change[i][val(c[0])][val(c[1])]=true;
        }
    }
    scanf("%s",s+1);
    int n=strlen(s+1);
    for(int i=1;i<=n;i++){
        f[i][i][val(s[i])]=1;
    }
    for(int len=2;len<=n;len++){
        for(int i=1;i<=(n+1-len);i++){
            int j=i+len-1;
            for(int k=i;k<j;k++){
                for(int a=1;a<=4;a++){
                    for(int b=1;b<=4;b++){
                        for(int c=1;c<=4;c++){
                            if(change[a][b][c]&&f[i][k][b]&&f[k+1][j][c]){
                                f[i][j][a]=true;
                            }
                        }
                    }
                }
            }
        }
    }
    bool flag=false;
    if(f[1][n][1]){
        flag=true;
        cout<<"W";
    }
    if(f[1][n][2]){
        flag=true;
        cout<<"I";
    }
    if(f[1][n][3]){
        flag=true;
        cout<<"N";
    }
    if(f[1][n][4]){
        flag=true;
        cout<<"G";
    }
    if(!flag){
        cout<<"The name is wrong!";
    }
    return 0;
}