#include<bits/stdc++.h>
using namespace std;
#define int long long

int d,x,y,tx,ty;

int m[50];
int r[]={0,1,2,1,4,5,4,1,2,9,0,5,10,11,14,9,0,11,18,9,11,11,15,17,9,23,20,25,
        16,29,27,25,11,17,4,29,22,37,23,9,1,11,11,33,29,15,5,41,46};

void exgcd(int a,int b){
    if(b==0){
        d=a;
        x=1;
        y=0;
    }
    else{
        exgcd(b,a%b);
        tx=x;
        ty=y;
        x=ty;
        y=tx-a/b*ty;
    }
}

int mul(int a,int b,int mod){
    int ans=0;
    a=(a%mod+mod)%mod;
    b=(b%mod+mod)%mod;
    while(b){
        if(b&1){
            ans=(ans+a)%mod;
        }
        a=(a+a)%mod;
        b>>=1;
    }
    return ans;
}

int excrt(int n){
    int tail=0,lcm=1,tmp,b,c,x0;
    //ans=lcm*x+tail
    for(int i=1;i<=n;i++){
        //ans=y*mi+ri
        //tail-ri=lcm*x+mi*y
        //a=lcm  b=mi
        b=m[i];
        c=((r[i]-tail)%b+b)%b;
        exgcd(lcm,b);
        if(c%d){
            return -1;
        }
        //x0=c*x
        x0=mul(x,c/d,b/d);
        //ans=lcm*x+tail=lcm*(x0+b/d*n)+tail
        //ans=lcm*x0+tail   +   lcm*b/d*n
        tmp=lcm*(b/d);
        tail=(tail+mul(x0,lcm,tmp))%tmp;
        lcm=tmp;
        cout<<i<<' '<<tail<<endl;
    }
    return tail;
}

signed main()
{
    for(int i=1;i<=48;i++){
        m[i]=i+1;
    }
    // for(int i=1;i<49;i++){
    //     cout<<m[i]<<' '<<r[i]<<endl;
    // }
    cout<<excrt(40);
    return 0;
}