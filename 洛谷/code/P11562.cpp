// https://www.luogu.com.cn/problem/P11562
// 题意：
// n 个寄存器由 n-1 条带开关电线连成树，初始值全为 0，目标值 a_i ∈ {0, 1}。
// 每次可独立设定所有电线开关状态，并选一个寄存器通电。
// 与通电寄存器有开启电线相连的连通块全部通电，所有通电寄存器值 0/1 翻转。
// 输出使所有寄存器达到目标状态的最少通电次数。
// 数据范围：
// 1 <= n <= 10^6
// 1 <= u, v <= n
// 0 <= a_i <= 1
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
int arr[MAXN];
int deep[MAXN];
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int st;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void dfs(int u,int f){
    if(arr[u]!=arr[f]){
        deep[u]=deep[f]+1;
    }
    else{
        deep[u]=deep[f];
    }
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f)
            dfs(v,u);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    n=read();
    int sum=0;
    arr[0]=-1;
    for(int i=1;i<=n;i++){
        arr[i]=read();
        sum+=arr[i];
    }
    if(sum==0){
        cout<<0<<endl;
        return 0;
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
    }
    dfs(1,0);
    int ans=0;
    for(int i=1;i<=n;i++){
        if(deep[i]>ans&&arr[i]){
            ans=deep[i];
            st=i;
        }
    }
    dfs(st,0);
    for(int i=1;i<=n;i++){
        if(deep[i]>ans&&arr[i]){
            ans=deep[i];
            st=i;
        }
    }
    cout<<(ans+1)/2<<endl;
    return 0;
}
