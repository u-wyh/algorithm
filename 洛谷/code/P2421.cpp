// https://www.luogu.com.cn/problem/P2421
#include<bits/stdc++.h>
using namespace std;

int n;
int c[16];
int p[16];
int l[16];

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

bool check(int i,int j,int m){
    if(p[i]<p[j]){
        swap(i,j);
    }

    int a=p[i]-p[j];
    int k=c[j]-c[i];
    exgcd(a,m);
    if(k%d!=0){
        return true;
    }
    int dx=m/d;
    x=k/d*x;
    if(x<=0){
        int delta=(dx-x)/dx;
        x+=delta*dx;
    }
    else{
        int delta=(x-1)/dx;
        x-=delta*dx;
    }
    return x>min(l[i],l[j]);
}

int main()
{
    cin>>n;
    int maxv=0;
    for(int i=1;i<=n;i++){
        cin>>c[i]>>p[i]>>l[i];
        maxv=max(maxv,c[i]);
    }

    for(int m=maxv;m<=1000000;m++){
        bool flag=true;
        for(int i=1;i<=n;i++){
            for(int j=1+i;j<=n;j++){
                if(!check(i,j,m)){
                    flag=false;
                    break;
                }
            }
            if(!flag){
                break;
            }
        }
        if(flag){
            cout<<m<<endl;
            return 0;
        }
    }
    return 0;
}