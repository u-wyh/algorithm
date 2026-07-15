#include<bits/stdc++.h>
using namespace std;

long long mod;
long long sum[400005];
long long d[100005];

void up(int i){
    sum[i]=(sum[i<<1]*sum[i<<1|1])%mod;
}

void build(int l,int r,int i){
    if(l==r){
        sum[i]=1;
    }else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void update(int jobi,double jobv,int l,int r,int i){
    if(l==r){
        sum[i]=(long long )(sum[i]*jobv)%mod;
    }else{
        int mid=(l+r)/2;
        if(jobi<=mid){
            update(jobi,jobv,l,mid,i<<1);
        }else{
            update(jobi,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int main()
{
    int t;
    cin>>t;
    while(t--){
        int q,op,m;
        cin>>q>>mod;
        build(1,q,1);
        for(int i=1;i<=q;i++){
            cin>>op>>d[i];
            if(op==1){
                update(i,d[i],1,q,1);
            }else{
                update(d[d[i]],1.0/d[i],1,q,1);
            }
            cout<<sum[1]<<endl;
        }
    }
    return 0;
}
