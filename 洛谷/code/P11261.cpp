// https://www.luogu.com.cn/problem/P11261
// 题意：给 n 格直方图和面积下限 p。统计四角坐标都是整数、底边在 x 轴上、整个矩形都在直方图内，且面积至少为 p 的矩形数，允许贴边。
// 数据范围：1 ≤ n ≤ 10^5，1 ≤ p ≤ 10^14，1 ≤ h[i] ≤ 10^9。

#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 1e6+5;

int n,p;
int pre[MAXN];
int val[MAXN];
int ls[MAXN];
int rs[MAXN];
int st[MAXN];
int ans;

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
    int top=0;
    for(int i=1;i<=n;i++){
        int pos=top;
        while(pos>0&&val[st[pos]]>val[i]){
            pos--;
        }
        if(pos>0){
            rs[st[pos]]=i;
        }
        if(pos<top){
            ls[i]=st[pos+1];
        }
        st[++pos]=i;
        top=pos;
    }
}

int calc(int l,int r,int h){
    l=max(l+1,(p+h-1)/h);
    if(l>r){
        return 0;
    }
    return (r-l+1)*(h+1)-pre[r]+pre[l-1];
}

void dfs(int cur,int l,int r){
    // cout<<cur<<' '<<l<<' '<<r<<endl;
    if(ls[cur]){
        dfs(ls[cur],l,cur-1);
    }
    if(rs[cur]){
        dfs(rs[cur],cur+1,r);
    }
    int lt=cur-l,rt=r-cur;
    if(lt>rt){
        swap(lt,rt);
    }
    for(int i=0;i<=lt;i++){
        ans+=calc(i,i+rt+1,val[cur]);
    }
}

signed main()
{
    n=read(),p=read();
    for(int i=1;i<=n;i++){
        pre[i]=pre[i-1]+(p+i-1)/i;
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    build();
    dfs(st[1],1,n);
    cout<<ans<<endl;
    return 0;
}