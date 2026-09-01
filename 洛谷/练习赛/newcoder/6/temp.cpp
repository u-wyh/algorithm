#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD=998244353;
const int MAXB=62;

int n,d;
int ans;

int pw[MAXB];
int pwm[MAXB];

inline int calc(int x,int b){
    if(x<0)
        return 0;

    int y=x+1;
    int half=pw[b];
    int len=pw[b+1];

    int all=y>>(b+1);
    int rest=y&(len-1);

    return ((all%MOD)*pwm[b]+max(0ll,rest-half))%MOD;
}

inline int get(int l,int r,int b){
    if(l>r)
        return 0;

    int res=calc(r,b)-calc(l-1,b);
    if(res<0)
        res+=MOD;
    return res;
}

inline int compute(int p,int q){
    int len1=pw[p+1];
    int len2=pw[q+1];

    int res=0;

    if(len1>=len2){
        int all=(n+1)>>(p+1);
        int rest=(n+1)&(len1-1);

        int allone;

        // p>q 时，长度为 2^p 的区间包含完整的第 q 位周期
        if(p>q)
            allone=(all%MOD)*pwm[p-1]%MOD;
        else
            allone=(all%MOD)*get(d+pw[p],d+len1-1,q)%MOD;

        int restone=0;
        if(rest>pw[p]){
            int len=rest-pw[p];
            restone=get(n+d-len+1,n+d,q);
        }

        res=allone+restone;
        if(res>=MOD)
            res-=MOD;
    }
    else{
        int all=(n+1)>>(q+1);
        int rest=(n+1)&(len2-1);

        int t=d&(len2-1);
        int l=(pw[q]-t+len2)&(len2-1);
        int r=(l+pw[q]-1)&(len2-1);

        // p<q 时，长度为 2^q 的区间中第 p 位恰有一半为 1
        int allone=(all%MOD)*pwm[q-1]%MOD;
        int restone=0;

        if(l<=r){
            if(rest>l)
                restone=get(l,min(rest-1,r),p);
        }
        else{
            if(rest>0)
                restone=get(0,min(r,rest-1),p);

            if(rest>l){
                restone+=get(l,rest-1,p);
                if(restone>=MOD)
                    restone-=MOD;
            }
        }

        res=allone+restone;
        if(res>=MOD)
            res-=MOD;
    }

    return res;
}

void compute(){
    ans=0;

    for(int i=0;i<60;i++){
        for(int j=0;j<=60;j++){
            ans+=compute(i,j);
            if(ans>=MOD)
                ans-=MOD;
        }
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    pw[0]=1;
    pwm[0]=1;

    for(int i=1;i<MAXB;i++){
        pw[i]=pw[i-1]<<1;
        pwm[i]=pwm[i-1]*2%MOD;
    }

    int T;
    cin>>T;

    while(T--){
        cin>>n>>d;
        compute();
        cout<<ans<<"\n";
    }

    return 0;
}