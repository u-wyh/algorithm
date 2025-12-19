// https://www.luogu.com.cn/problem/P5633
// 这道题要求的是必须是k个  我们判断的时候  要处理优先选和优先不选的情况  这是两个极值
// 可能会有多个数字都满足条件 但是这些数字最终的答案都是一样的
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXM = 5e5+5;

int n,m,s,k;
int all=0;

struct node{
    int u,v,w,op;
};
node nums[MAXM];

int fa[MAXN];

int pritority;//1的话  s靠前
int x;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

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

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

bool cmp(node a,node b){
    return ((a.w+a.op*x)==(b.w+b.op*x))?(pritority?(a.op>b.op):(a.op<b.op)):((a.w+a.op*x)<(b.w+b.op*x));
}

int query(int limit,int op){
    all=0;
    x=limit,pritority=op;
    sort(nums+1,nums+m+1,cmp);
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    int cnt=0;
    for(int i=1;i<=m;i++){
        int fx=find(nums[i].u);
        int fy=find(nums[i].v);
        if(fx!=fy){
            all+=nums[i].w+nums[i].op*limit;
            fa[fx]=fy;
            if(nums[i].op){
                cnt++;
            }
        }
    }
    return cnt;
}

bool check(){
    int cnt=0;
    sort(nums+1,nums+m+1,cmp);
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int fx=find(nums[i].u);
        int fy=find(nums[i].v);
        if(fx!=fy){
            fa[fx]=fy;
            cnt++;
        }
    }
    return cnt==n-1;
}

int main()
{
    n=read(),m=read(),s=read(),k=read();
    all=0;
    for(int i=1;i<=m;i++){
        nums[i].u=read(),nums[i].v=read(),nums[i].w=read();
        if(nums[i].u==s||nums[i].v==s){
            nums[i].op=1;
            all++;
        }
    }

    if(all<k||!check()){
        cout<<"Impossible"<<endl;
        return 0;
    }

    int l=-30005,r=30005,ans=0;
    bool flag=false;
    while(l<=r){
        int mid=(l+r)>>1;
        int cntmin=query(mid,0);
        int cntmax=query(mid,1);
        if(cntmin<=k&&cntmax>=k){
            flag=true;
            ans=all-k*mid;
            break;
        }
        else if(cntmin>k){
            l=mid+1;
        }
        else if(cntmax<k){
            r=mid-1;
        }
    }
    if(flag){
        cout<<ans<<endl;
    }
    else{
        cout<<"Impossible"<<endl;
    }
    return 0;
}