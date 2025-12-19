#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int BASE = 2;
const int BAS = 499;

int n,m;

int power[MAXN];
int p[MAXN];
int arr[MAXN];

int tree[MAXN<<2];
int minn[MAXN<<2];
int sum[MAXN<<2];

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

inline void prepare(){
    power[0]=1;
    p[0]=1;
    for(int i=1;i<=1e6;i++){
        power[i]=power[i-1]*BASE;
        p[i]=p[i-1]*BAS;
    }
}

inline void up(int i){
    minn[i]=min(minn[i<<1],minn[i<<1|1]);
    tree[i]=tree[i<<1]+tree[i<<1|1];
    sum[i]=sum[i<<1]+sum[i<<1|1];
}

void build(int l,int r,int i){
    if(l==r){
        minn[i]=arr[l];
        tree[i]=power[arr[l]];
        sum[i]=p[arr[l]];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
    //cout<<minn[i]<<' '<<tree[i]<<endl;
}

void update(int pos,int val,int l,int r,int i){
    if(l==r){
        minn[i]=val;
        tree[i]=power[val];
        sum[i]=p[val];
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            update(pos,val,l,mid,i<<1);
        }
        else{
            update(pos,val,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

pair<int,pair<int,int>> query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return {minn[i],{tree[i],sum[i]}};
    }
    else{
        pair<int,pair<int,int>> ans={1e9,{0,0}};
        int mid=(l+r)/2;
        if(jobl<=mid){
            pair<int,pair<int,int>>tmp=query(jobl,jobr,l,mid,i<<1);
            ans.first=min(ans.first,tmp.first);
            ans.second.first+=tmp.second.first;
            ans.second.second+=tmp.second.second;
        }
        if(jobr>mid){
            pair<int,pair<int,int>>tmp=query(jobl,jobr,mid+1,r,i<<1|1);
            ans.first=min(ans.first,tmp.first);
            ans.second.first+=tmp.second.first;
            ans.second.second+=tmp.second.second;
        }
        return ans;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    n=read(),m=read();
    prepare();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op,u,v,x,y;
        op=read(),u=read(),v=read();
        if(op==0){
            update(u,v,1,n,1);
        }
        else{
            x=read(),y=read();
            pair<int,pair<int,int>>tmp1=query(u,v,1,n,1);
            pair<int,pair<int,int>>tmp2=query(x,y,1,n,1);
            //cout<<tmp1.first<<' '<<tmp1.second<<' '<<tmp2.first<<' '<<tmp2.second<<endl;
            if(tmp1.first>tmp2.first){
                swap(tmp1,tmp2);
            }
            if((tmp1.second.first*power[tmp2.first-tmp1.first]==tmp2.second.first)&&
               (tmp1.second.second*p[tmp2.first-tmp1.first]==tmp2.second.second)){
                cout<<"YES"<<endl;
            }
            else{
                cout<<"NO"<<endl;
            }
        }
    }
    return 0;
}
