// https://www.luogu.com.cn/problem/P2798
//其实也完全就是带权二分题
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXM = 4e4+5;

int n,k,m;
int mid;
struct node{
    int u,v,w,op;
};
int res=INT_MAX;
node nums[MAXM];

int fa[MAXN];

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

bool cmp(node a,node b){
    if((a.w+a.op*mid)!=(b.w+b.op*mid)){
        return (a.w+a.op*mid)<(b.w+b.op*mid);
    }
    return a.op>b.op;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

bool check(){
    int cnt=0;
    sort(nums+1,nums+2*m+1,cmp);
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    int now=0;
    int tmp=INT_MIN;
    for(int i=1;i<=2*m;i++){
        int x=nums[i].u;
        int y=nums[i].v;
        int fx=find(x),fy=find(y);
        if(cnt>=k&&nums[i].op==1){
            continue;
        }
        if(fx!=fy){
            fa[fx]=fy;
            tmp=max(tmp,nums[i].w);
            if(nums[i].op==1){
                cnt++;
            }
            now++;
            if(now==n-1){
                break;
            }
        }
    }
    if(cnt>=k){
        res=min(res,tmp);
    }
    return cnt>=k;
}

int main()
{
    n=read(),k=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v,t,T;
        u=read(),v=read(),T=read(),t=read();
        nums[i*2-1]={u,v,t,0};
        nums[i*2]={u,v,T,1};
    }
    int l=-5000000,r=5000000;
    while(l<=r){
        mid=(l+r)>>1;
        if(check()){
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    
    cout<<res<<endl;
    return 0;
}