// https://www.luogu.com.cn/problem/P8654
// 题意：输入 m,
// n（m 行 n 列网格从上到下、从左到右编号 1..m*n）、整数 k 和 k
// 对相连通的格子编号 (a, b)，输出连通块总数。
// 数据范围：1 < m, n < 1000，0 < k < 10^5。
// 难度评分：1300（洛谷分级换算）
// 算法标签：并查集
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int father[MAXN];
int n,m,k;

void build(){
    for(int i=0;i<=n*m;i++){
        father[i]=i;
    }
}

int find(int i){
    if (i != father[i]){
        father[i] = find(father[i]);
    }
    return father[i];
}

void un(int x,int y){
    father[find(x)] = find(y);
}

int main()
{
    cin>>n>>m>>k;
    build();
    for(int i=1;i<=k;i++){
        int u,v;
        cin>>u>>v;
        un(u,v);
    }
    int ans=0;
    for(int i=1;i<=m*n;i++){
        if(find(i)==i){
            ans++;
        }
    }
    cout<<ans;
    return 0;
}
