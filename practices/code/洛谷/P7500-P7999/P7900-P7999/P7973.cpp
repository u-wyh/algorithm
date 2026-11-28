// https://www.luogu.com.cn/problem/P7973
// 题意：给定 N 个点的无向图，点 i 有权值 A_i 和价值 B_i。
// 两点 x, y 之间有边当
// 且仅当 (A_x xor A_y) > max(A_x, A_y)。
// 依次对 i = 1..N 求点 i 所在连通块内所有点的价值 B 之和。
// 第一行输入 N，第二行输入 N 个 A_i，第三行输入 N 个 B_i。
// 输出 N 行每行一个整数。
// 数据范围：1 <= N <= 10^5，
// 1 <= A_i <= 2^{30} - 1，1 <= B_i <= 10^9。
// 难度评分：1500（洛谷分级换算）
// 算法标签：并查集、位运算
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int a[MAXN],b[MAXN];
int fa[MAXN],val[MAXN];
int n;
vector<int>zero;
vector<int>one;

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    //cout<<x<<' '<<y<<endl;
    int fx=find(x),fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
        val[fy]+=val[fx];
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
        fa[i]=i,val[i]=b[i];
    }
    for(int i=0;i<=29;i++){
        //cout<<i<<' '<<(1<<i)<<endl;
        for(int j=1;j<=n;j++){
            if((a[j]&(1<<i))&&(a[j]<(1<<(i+1)))){
                one.push_back(j);
            }
            if((a[j]>=(1<<(i+1)))&&((a[j]&(1<<i))==0)){
                zero.push_back(j);
            }
        }
        //cout<<i<<' '<<one.size()<<' '<<zero.size()<<endl;
        if(one.size()>0&&zero.size()>0){
            for(int j=0;j<one.size()-1;j++){
                un(one[j],one[j+1]);
            }
            for(int j=0;j<zero.size()-1;j++){
                un(zero[j],zero[j+1]);
            }
            un(one[0],zero[0]);
        }
        one.clear();
        zero.clear();
    }
    for(int i=1;i<=n;i++){
        int f=find(i);
        cout<<val[f]<<endl;
    }
    return 0;
}
