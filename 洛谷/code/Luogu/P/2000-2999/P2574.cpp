#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200005;

int arr[MAXN];
int sum0[MAXN<<2],sum1[MAXN<<2];
bool Reverse[MAXN<<2];
int n,m;

void up(int i){
    sum0[i]=sum0[i<<1]+sum0[i<<1|1];
    sum1[i]=sum1[i<<1]+sum1[i<<1|1];
}

void lazy(int i,int n){
    sum0[i]=n-sum0[i];
    sum1[i]=n-sum1[i];
    Reverse[i]=!Reverse[i];
}

void down(int i,int ln,int rn){
    if(Reverse[i]){
        lazy(i<<1,ln);
        lazy(i<<1|1,rn);
        Reverse[i]=false;
    }
}

void build(int l,int r,int i){
    if(l==r){
        sum0[i]= (arr[l]==1)?0:1;
        sum1[i]= (arr[l]==1)?1:0;
    }else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
    Reverse[i]=false;
}

void reversE(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,r-l+1);
    }else{
        int mid=(l+r)/2;
        down(i,mid-l+1,r-mid);
        if(jobl<=mid){
            reversE(jobl,jobr, l, mid,i<<1);
        }
        if(jobr>mid){
            reversE(jobl,jobr,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return sum1[i];
    }else{
        int mid=(l+r)/2;
        down(i,mid-l+1,r-mid);
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

int main()
{
    cin>>n>>m;
    char c;
    for(int i=1;i<=n;i++){
        cin>>c;
        arr[i]=c-'0';
        //printf("%3d",arr[i]);
    }
    //cout<<endl;
    build(1,n,1);
    for(int i=1,op,jobl,jobr;i<=m;i++){
        cin>>op>>jobl>>jobr;
        if(op==0){
            reversE(jobl,jobr,1,n,1);
        }else{
            cout<<query(jobl,jobr,1,n,1)<<endl;
        }
    }
    return 0;
}
