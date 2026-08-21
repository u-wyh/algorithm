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
    return (all*(len/2)+max(0ll,rest-len/2))%MOD;
}

int get(int l,int r,int b){
    if(l>r){
        return 0;
    }
    return (calc(r,b)-calc(l-1,b)+MOD)%MOD;
}

int compute(int p,int q){
    int len1=1ll<<(p+1);
    int len2=1ll<<(q+1);

    if(len1>=len2){
        int all=(n+1)/len1;
        int rest=(n+1)%len1;

        int res=(all%MOD)*get(d+(1ll<<p),d+len1-1,q)%MOD;

        if(rest>(1ll<<p)){
            int l=all*len1+(1ll<<p);
            int r=all*len1+rest-1;
            res=(res+get(l+d,r+d,q))%MOD;
        }

        return res;
    }

    int all=(n+1)/len2;
    int rest=(n+1)%len2;

    int t=d%len2;
    int l=((1ll<<q)-t+len2)%len2;
    int r=(l+(1ll<<q)-1)%len2;

    int full=0;
    int part=0;

    if(l<=r){
        full=get(l,r,p);

        if(rest>l){
            part=get(l,min(r,rest-1),p);
        }
    }
    else{
        full=(get(0,r,p)+get(l,len2-1,p))%MOD;

        part=get(0,min(r,rest-1),p);

        if(rest>l){
            part=(part+get(l,rest-1,p))%MOD;
        }
    }

    return ((all%MOD)*full+part)%MOD;
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