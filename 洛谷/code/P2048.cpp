// https://www.luogu.com.cn/problem/P2048
// 题意：输入长为 n 的整数序列 A（可正可负）和整数 k, L, R。
// 长度在 [L, R] 之间的连续子段称为超级和弦，美妙度为其元素和。
// 选 k 个位置不完全相同的超级和弦组成乐曲，输出美妙度之和的最大值。
// 数据范围（含图表中测试点 9~10 的 100% 范围）：
// 1 <= n <= 500,000（音符数 N）
// 1 <= k <= 500,000（和弦数 k）
// -1000 <= A_i <= 1000（音符美妙度）
// 1 <= L <= R <= n（和弦长度上下限，保证有解）
#include<bits/stdc++.h>
// 算法标签：ST表、优先队列、前缀和
using namespace std;
#define int long long
const int MAXN = 5e5+5;
const int MAXH = 20;

int n,k,l,r;
int one[MAXN];
int sum[MAXN];
int val[MAXN];

int st[MAXN][MAXH];
int pos[MAXN][MAXH];

struct node{
    int val,l,r,pos,st;
};
struct cmp{
    bool operator()(node a,node b){
        return a.val<b.val;
    }
};
priority_queue<node,vector<node>,cmp>heap;

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

void build(){
    for(int i=1;i<=n;i++){
        st[i][0]=sum[i];
        pos[i][0]=i;
    }
    for(int k=1;k<=one[n];k++){
        for(int i=1;i+(1<<k)-1<=n;i++){
            if(st[i][k-1]>=st[i+(1<<(k-1))][k-1]){
                st[i][k]=st[i][k-1];
                pos[i][k]=pos[i][k-1];
            }
            else{
                st[i][k]=st[i+(1<<(k-1))][k-1];
                pos[i][k]=pos[i+(1<<(k-1))][k-1];
            }
        }
    }
}

pair<int,int> query(int l,int r,int i){
    int p=one[r-l+1];
    if(st[l][p]>=st[r-(1<<p)+1][p]){
        return {st[l][p]-sum[i-1],pos[l][p]};
    }
    else{
        return {st[r-(1<<p)+1][p]-sum[i-1],pos[r-(1<<p)+1][p]};
    }
}

signed main()
{
    n=read(),k=read(),l=read(),r=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
        sum[i]=sum[i-1]+val[i];
    }
    one[0]=-1;
    for(int i=1;i<=n;i++){
        one[i]=one[i>>1]+1;
    }
    build();
    for(int i=1;i+l<=n+1;i++){
        pair<int,int>tmp=query(i+l-1,min(n,i+r-1),i);
        heap.push({tmp.first,i+l-1,min(n,i+r-1),tmp.second,i});
    }
    int ans=0;
    while(k--){
        node tmp=heap.top();
        heap.pop();
        ans+=tmp.val;
        if(tmp.l<tmp.pos){
            pair<int,int>res=query(tmp.l,tmp.pos-1,tmp.st);
            heap.push({res.first,tmp.l,tmp.pos-1,res.second,tmp.st});
        }
        if(tmp.r>tmp.pos){
            pair<int,int>res=query(tmp.pos+1,tmp.r,tmp.st);
            heap.push({res.first,tmp.pos+1,tmp.r,res.second,tmp.st});
        }
    }
    cout<<ans<<endl;
    return 0;
}