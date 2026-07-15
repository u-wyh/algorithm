#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MAXM = 5e5+5;

int n,m,k;
int kind[MAXN];
int val[MAXN];
int t[MAXN];//表示这个种类的出现了多少次
int nxt[MAXN];//表示下一个相同种类的在什么位置
int st[MAXN];//表示这个种类第一次出现的位置
int en[MAXN];//表示这个种类上一次出现的位置
int ans[MAXN];
struct node{
    int l,r,sub;
}nums[MAXN];
int tree[MAXN];

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
    return a.r<b.r;
}

int lowbit(int x){
    return x&(-x);
}

int sum(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void add(int x,int val){
    while(x<=n){
        tree[x]+=val;
        x+=lowbit(x);
    }
}

int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++){
        kind[i]=read();
        if(st[kind[i]]==0){
            st[kind[i]]=i;
        }
        else{
            nxt[en[kind[i]]]=i;
        }
        en[kind[i]]=i;
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=m;i++){
        nums[i].l=read(),nums[i].r=read();
        nums[i].sub=i;
    }
    sort(nums+1,nums+m+1,cmp);
    int r=0;
    for(int i=1;i<=n;i++){
        en[kind[i]]=st[kind[i]];
    }
    for(int i=1;i<=m;i++){
        while(nums[i].r>r){
            r++;
            t[kind[r]]++;
            add(r,val[r]);
            if(t[kind[r]]>=k){
                t[kind[r]]--;
                add(en[kind[r]],-val[en[kind[r]]]);
                en[kind[r]]=nxt[en[kind[r]]];
            }
        }
        ans[nums[i].sub]=sum(nums[i].r)-sum(nums[i].l-1);
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
