// https://www.luogu.com.cn/problem/P9862
// 题意：多组数据（共 n 组）。
// 有 A, B, C, D 四种粒子，
// Patrick 先手、Roland 后手轮流操作
// 每次需按五种固定配方之一消耗粒子：AABDD、ABCD、CCD、BBB、AD。
// 无法操作者输。
// 给定各粒子初始数量，判断谁有必胜策略。
// 题意：第一行输入 n，
// 接下来 n 行每行 4 个整数表示 A, B, C, D 数量；
// 每组输出 Roland 或 Patrick。
// 数据范围：1 <= n < 100，0 <= A, B, C, D <= 30。
// 算法标签：博弈、记忆化搜索
#include<bits/stdc++.h>
using namespace std;

int n;
bool win[31][31][31][31];
bool vis[31][31][31][31];

int s[5][4]={{2,1,0,2},{1,1,1,1},{0,0,2,1},{0,3,0,0},{1,0,0,1}};

bool dfs(int a,int b,int c,int d){
    if(a<0||b<0||c<0||d<0){
        return true;
    }
    if(vis[a][b][c][d]){
        return win[a][b][c][d];
    }
    vis[a][b][c][d]=true;
    bool flag=false;
    for(int i=0;i<5;i++){
        if(!dfs(a-s[i][0],b-s[i][1],c-s[i][2],d-s[i][3])){
            flag=true;
            break;
        }
    }
    win[a][b][c][d]=flag;
    return flag;
}

int main()
{
    cin>>n;
    while(n--){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        if(!dfs(a,b,c,d)){
            cout<<"Roland"<<endl;
        }
        else{
            cout<<"Patrick"<<endl;
        }
    }
    return 0;
}