// https://www.luogu.com.cn/problem/CF906D
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,m;
int w[MAXN];
int mod[31];
int len;

int phi(int n){
    int ans=n;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            ans=ans/i*(i-1);
            while(n%i==0){
                n/=i;
            }
        }
    }
    if(n>1){
        ans=ans/n*(n-1);
    }
    return ans;
}

void prepare(){
    mod[0]=m;
    while(mod[len]!=1){
        ++len;
        mod[len]=phi(mod[len-1]);
    }
    mod[len+1]=1;
}

bool flag1=false;
bool flag2=false;

int power(int a,int b,int mod){
    int ans=1;
    while(b){
        if(b&1){
            ans=ans*a;
            if(ans>=mod){
                flag2=true;
            }
            else if(flag1){
                flag2=true;
            }
            ans%=mod;
        }
        b>>=1;
        a=(a*a);
        if(a>=mod){
            flag1=true;
        }
        a%=mod;
    }
    return ans;
}

int calc(int id,int limit,int d){
    if(id==limit){
        flag2=false;
        if(w[id]>=mod[d]){
            flag2=true;
        }
        return w[id]%mod[d];
    }
    if(d==len){
        flag2=true;
        return 0;
    }
    int x=calc(id+1,limit,d+1);
    if(flag2){
        x+=mod[d+1];
    }
    flag1=flag2=false;
    return power(w[id],x,mod[d]);
}

int query(int l,int r){
    return calc(l,r,0);
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>w[i];
    }
    prepare();
    int q;
    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<query(l,r)<<endl;
    }
    return 0;
}