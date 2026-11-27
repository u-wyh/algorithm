// https://www.luogu.com.cn/problem/P9358
// 题意：有 n 个国家排成编号 1..n，
// 每个国家是一条含 m+1 个结点 (a, 1)..(a, m+1)
// 的链（(a, b) 连向 (a, b+1)）。
// 共 q 次操作：
// 1 a b 在 (a, b) 与 (a+1, b)
// 间建一座桥（保证每个结点至多连一座桥）；
// 2 a 询问英雄从 (a, 1) 出发，若当前结点有未走过的桥则过桥，
// 否则向右走到 y+1，到达任一国家第 m+1 结点停止
// 求最终所在国家编号（各询问独立）。
// 题意：第一行输入 n, m, q，随后输入 q 个操作；
// 对每个操作 2 输出一行一个整数。
// 数据范围：1 <= n, m, q <= 10^5，
// 操作 1 满足 1 <= a < n, 1 <= b <= m
// 操作 2 满足 1 <= a <= n。
// 算法标签：分块、模拟
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXB = 320;

int n,m,q;

int blen;
int bnum;
int bl[MAXB];
int br[MAXB];
int bi[MAXN];

int to[MAXB][MAXN];

map<int,int>bridge[MAXN];

void prepare(){
    blen=max(1,(int)sqrt(m));
    bnum=(m+blen-1)/blen;
    for(int i=1;i<=m;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(m,i*blen);
    }

    for(int i=1;i<=bnum;i++){
        for(int j=1;j<=n;j++){
            to[i][j]=j;
        }
    }
}

void addbridge(int a,int b){
    int id=bi[b];
    int x=a;
    int y=a+1;
    for(int j=b-1;j>=bl[id];j--){
        auto it=bridge[x].find(j);
        if(it!=bridge[x].end()){
            x=it->second;
        }

        it=bridge[y].find(j);
        if(it!=bridge[y].end()){
            y=it->second;
        }
    }
    swap(to[id][x],to[id][y]);
    bridge[a][b]=a+1;
    bridge[a+1][b]=a;
}

int query(int x){
    for(int i=1;i<=bnum;i++){
        x=to[i][x];
    }
    return x;
}

int main()
{
    cin>>n>>m>>q;
    prepare();
    for(int i=1;i<=q;i++){
        int op,a,b;
        cin>>op>>a;
        if(op==1){
            cin>>b;
            addbridge(a,b);
        }
        else{
            cout<<query(a)<<endl;
        }
    }
    return 0;
}