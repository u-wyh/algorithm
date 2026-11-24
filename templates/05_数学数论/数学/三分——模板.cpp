//https://www.luogu.com.cn/problem/P1883
//这道题是三分函数最基础的应用
//二分无法解决  所以只能使用三分函数
//这道题目实际要求的是每个函数的最大值的最小值
//还有例题比如 P
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-9;
const int MAXN = 1e4+5;

int n;
int a[MAXN],b[MAXN],c[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

double compute(double x){
    double ans=INT_MIN;
    for(int i=1;i<=n;i++){
        ans=max(ans,x*x*a[i]+x*b[i]+c[i]);
    }
    return ans;
}

int main()
{
    int T;
    T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            a[i]=read(),b[i]=read(),c[i]=read();
        }
        double l=0,r=1000,ans=0;
        while(r-l>=eps){
            double midl=(r-l)/3+l;
            double midr=(r-l)/3*2+l;
            double k1=compute(midl);
            double k2=compute(midr);
            if(k1<=k2){
                r=midr;
                ans=midl;
            }
            else{
                l=midl;
                ans=midr;
            }
        }
        printf("%.4lf\n",compute(ans));
    }
    return 0;
}