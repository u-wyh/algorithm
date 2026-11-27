// https://www.luogu.com.cn/problem/P4054
// 题意：第一行输入网格大小 n, m，
// 接下来 n * m 矩阵给出格子初始整数权值；
// 再输入操作数 Q
// 接下来 Q 行每行执行修改操作 1 x y c（将 (x, y) 权值改为 c）
// 或查询操作 2 x_1 x_2 y_1 y_2
// c（查询子矩形 [x_1, x_2]*[y_1, y_2]
// 内权值为 c 的格子数）。
// 对每个查询操作输出一行答案。
// 数据范围：对于 100% 的数据，1 <= n, m <= 300，
// 1 <= Q <= 2 * 10^5，1 <= x <= n，
// 1 <= y <= m
// 1 <= x_1 <= x_2 <= n，
// 1 <= y_1 <= y_2 <= m，1 <= c <= 100。
//P4054
//这道题特殊的地方就在于他不是普通的树状数组
//他是一个二维树状数组  其实没什么难度 只是比较新奇
// 算法标签：二维树状数组
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 305;
const int MAXC = 105;

int arr[MAXN][MAXN];
int tree[MAXN][MAXN][MAXC];
int n,m,k;

int lowbit(int i){
    return i&-i;
}

//在(x,y)上给color加上v
void add(int x,int y,int color,int v){
    for(int i=x;i<=n;i+=lowbit(i)){
        for(int j=y;j<=m;j+=lowbit(j)){
            tree[i][j][color]+=v;
        }
    }
}

//查询从(1,1)到(x,y)上  颜色color出现了多少次
int sum(int x,int y,int color){
    int ans=0;
    for(int i=x;i;i-=lowbit(i)){
        for(int j=y;j;j-=lowbit(j)){
            ans+=tree[i][j][color];
        }
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>arr[i][j];
            add(i,j,arr[i][j],1);
        }
    }
    cin>>k;
    for(int i=1;i<=k;i++){
        int op;
        cin>>op;
        if(op==2){
            int x1,x2,y1,y2,c;
            cin>>x1>>x2>>y1>>y2>>c;
            int ans=sum(x2,y2,c)+sum(x1-1,y1-1,c)-sum(x2,y1-1,c)-sum(x1-1,y2,c);
            cout<<ans<<endl;
        }
        else{
            int x,y,c;
            cin>>x>>y>>c;
            add(x,y,arr[x][y],-1);
            arr[x][y]=c;
            add(x,y,arr[x][y],1);
        }
    }
    return 0;
}
