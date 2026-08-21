#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXB = 62;

int n,d;
int ans;

int pw[MAXB];
int pwm[MAXB];

int calc(int x,int b){
    if(x<0){
        return 0;
    }
    int len=pw[b+1];
    int all=(x+1)>>(b+1);
    int rest=(x+1)&(len-1);
    return ((all%MOD)*pwm[b]+max(0ll,rest-pw[b]))%MOD;
}
 
int get(int l,int r,int b){
    if(l>r){
        return 0;
    }
    int res=calc(r,b)-calc(l-1,b);
    if(res<0){
        res+=MOD;
    }
    return res;
}
 
int compute(int p,int q){
    int len1=1ll<<(p+1);
    int len2=1ll<<(q+1);
 
    if(len1>=len2){
        int all=(n+1)>>(p+1);
        int rest=(n+1)&(len1-1);
 
        int res=(all%MOD)*get(d+pw[p],d+len1-1,q)%MOD;
 
        if(rest>pw[p]){
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
        if(n<pw[i]){
            continue;
        }
        for(int j=0;j<=60;j++){
            if((n+d)<pw[j]){
                continue;
            }
            ans+=compute(i,j);
            ans%=MOD;
        }
    }
    ans=(ans%MOD+MOD)%MOD;
}

signed main()
{
    pw[0]=1;
    pwm[0]=1;
    for(int i=1;i<MAXB;i++){
        pw[i]=pw[i-1]<<1;
        pwm[i]=(pwm[i-1]<<1)%MOD;
    }

    int T;
    cin>>T;
    while(T--){
        cin>>n>>d;
        compute();
        cout<<ans<<endl;
    }
    return 0;
}