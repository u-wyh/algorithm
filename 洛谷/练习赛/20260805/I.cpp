#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;

int n,d;
int ans;

int calc(int x,int b){
    if(x<0){
        return 0;
    }
    int len=1ll<<(b+1);
    int all=(x+1)/len;
    int rest=(x+1)%len;
    return (all*len/2+max(0ll,rest-len/2))%MOD;
}

int get(int l,int r,int b){
    if(l>r){
        return 0;
    }
    return ((calc(r,b)-calc(l-1,b))%MOD+MOD)%MOD;
}

int compute(int p,int q){
    int len1=1ll<<(p+1);
    int len2=1ll<<(q+1);

    int ans=0;
    if(len1>=len2){
        int all=(n+1)/len1;
        int rest=(n+1)%len1;
        int allone=(all%MOD)*get(d+(1ll<<p),d+len1-1,q)%MOD;

        int restone=0;
        if(rest>(1ll<<p)){
            int len=rest-(1ll<<p);
            restone=get(n+d-len+1,n+d,q);
        }
        ans=allone+restone;
    }
    else{
        int all=(n+1)/len2;
        int rest=(n+1)%len2;
        int t=d%len2;
        int l=(1ll<<q);
        int r=len2-1;
        l=(l-t+len2)%len2;
        r=(l+(1ll<<q)-1)%len2;
        if(l<=r){
            int allone=all*get(l,r,p);
            int restone=0;
            if(rest>l){
                int len=rest-l;
                restone=get(l,min(rest-1,r),p);
                // restone=get(n-len+1,n,p);
            }
            ans=allone+restone;
        }
        else{
            int allone=(get(0,r,p)+get(l,len2-1,p))*all;
            // int restone=get(n-rest+1,n-rest+1+min(r,rest-1),p);
            int restone=get(0,min(r,rest-1),p);
            if(rest>l){
                int len=rest-l;
                // restone+=get(n-len+1,n,p);
                restone+=get(l,rest-1,p);
            }
            ans=allone+restone;
        }
    }
    return ans;
}

void compute(){
    ans=0;
    for(int i=0;i<60;i++){
        for(int j=0;j<=60;j++){
            ans+=compute(i,j);
            ans%=MOD;
        }
    }
    ans=(ans%MOD+MOD)%MOD;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n>>d;
        compute();
        cout<<ans<<endl;
    }
    return 0;
}