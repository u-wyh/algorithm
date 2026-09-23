// https://www.luogu.com.cn/problem/P3986
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;

int f[50];
int k;

int x,y,d,px,py;

void exgcd(int a,int b){
    if(b==0){
        d=a;
        x=1;
        y=0;
    }
    else{
        exgcd(b,a%b);
        px=x;
        py=y;
        x=py;
        y=px-py*(a/b);
    }
}

int compute(int a,int b){
    exgcd(a,b);
    int dx=b;
    int dy=a;
    x=k*x;
    y=k*y;
    if(x<=0){
        int delta=(dx-x)/dx;
        x+=delta*dx;
        y-=delta*dy;
    }
    else{
        int delta=(x-1)/dx;
        x-=delta*dx;
        y+=delta*dy;
    }

    if(y<=0){
        return 0;
    }
    else{
        return ((y-1)/dy+1)%MOD;
    }
}

signed main()
{
    cin>>k;
    f[0]=0;
    f[1]=1;
    f[2]=1;
    int ans=0;
    for(int i=2;i<=49;i++){
        f[i]=f[i-1]+f[i-2];
        if(f[i]+f[i-1]>k){
            break;
        }
        ans+=compute(f[i-1],f[i]);
        ans%=MOD;
    }
    cout<<ans<<endl;
    return 0;
}