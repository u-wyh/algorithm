// https://www.luogu.com.cn/problem/CF710D
#include<bits/stdc++.h>
using namespace std;
#define int long long

int a1,b1,a2,b2,lt,rt;
__int128 x,y,d,px,py;

void exgcd(__int128 a,__int128 b){
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

signed main()
{
    cin>>a1>>b1>>a2>>b2>>lt>>rt;
    lt=max(lt,max(b1,b2));
    if(lt>rt){
        cout<<0<<endl;
        return 0;
    }

    int c=b2-b1;
    exgcd(a1,a2);
    if(c%d!=0){
        cout<<0<<endl;
        return 0;
    }

    int dx=a2/d;
    int dy=a1/d;
    x=c/d*x;
    y=c/d*y;
    x=(x%dx+dx)%dx;
    __int128 step=(__int128)a1/d*a2;
    __int128 xx=(__int128)b1+(__int128)a1*x;
    if(xx<lt){
        __int128 delta=(lt-xx+step-1)/step;
        xx+=delta*step;
    }
    if(xx>rt){
        cout<<0<<endl;
        return 0;
    }
    int ans=(rt-xx)/step+1;
    cout<<ans<<endl;
    return 0;
}