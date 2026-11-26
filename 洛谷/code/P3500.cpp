// https://www.luogu.com.cn/problem/P3500
// 题意：输入母串长度 n 和母串序列 a_1..a_n，再输入询问数 q，每次询问给出长度 m 和序列 b_1..b_m。
// 判断每次询问的序列 b 是否是母串 a 的子序列（可不连续但须保持相对顺序）。
// 输出 q 行，是子序列输出 TAK，否则输出 NIE。
// 数据范围：1 <= n, m, a_i, b_i <= 1000000，sum(m) <= 1000000。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
vector<int>vec[MAXN];

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

int find(int st,int v){
    int l=0,r=vec[v].size()-1,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(vec[v][mid]>st){
            ans=vec[v][mid];
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        int u=read();
        vec[u].push_back(i);
    }
    int q=read();
    while(q--){
        int m=read();
        int u=0;
        for(int i=1;i<=m;i++){
            int v=read();
            if(u==-1){
                continue;
            }
            u=find(u,v);
        }
        if(u==-1){
            printf("NIE\n");
        }
        else{
            printf("TAK\n");
        }
    }
    return 0;
}