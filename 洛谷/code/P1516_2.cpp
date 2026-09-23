// https://www.luogu.com.cn/problem/P1516
#include<bits/stdc++.h>
using namespace std;
#define int long long

int a,b,n,m,len;
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

signed main()
{
    cin>>a>>b>>n>>m>>len;
    if(n<m){
        swap(n,m);
        swap(a,b);
    }
    exgcd(n-m,len);
    int c=b-a;

    if(c%d!=0){
        cout<<"Impossible"<<endl;
        return 0;
    }

    int dx=len/d;
    int dy=(n-m)/d;
    x=c/d*x;
    if(x<0){
        int delta=(1-x+dx-1)/dx;
        x+=dx*delta;
    }
    else{
        int delta=(x-1)/dx;
        x-=dx*delta;
    }
    cout<<x<<endl;
    return 0;
}