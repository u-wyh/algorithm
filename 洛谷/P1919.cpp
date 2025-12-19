#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MAXT = 8e6+5;
const double PI = acos(-1);

int n,m;
char s1[MAXN];
char s2[MAXN];

struct Complex{
    double x,y;
        
    Complex operator+(const Complex& t)const{
        return {x+t.x, y+t.y};
    }
    Complex operator-(const Complex& t)const{
        return {x-t.x, y-t.y};
    }
    Complex operator*(const Complex& t)const{
        return {x*t.x-y*t.y, x*t.y+y*t.x};
    }
};
Complex A[MAXT],B[MAXT];
int ans[MAXT];

// 如果是正变换 由系数求点值  那么op=1
// 如果是逆变换 由点值求系数  那么op=-1
// 这样可以统一方便的初始w1
void FFT(Complex *A,int n,int op){
    if(n==1){
        return ;
    }
    Complex A1[n/2],A2[n/2];
    for(int i=0;i<n/2;i++){
        A1[i]=A[2*i];
        A2[i]=A[2*i+1];
    }
    FFT(A1,n/2,op);
    FFT(A2,n/2,op);
    Complex w1({cos(2*PI/n),sin(2*PI/n)*op});
    Complex wk({1,0});
    for(int i=0;i<n/2;i++){
        A[i]=A1[i]+A2[i]*wk;
        A[i+n/2]=A1[i]-A2[i]*wk;
        wk=wk*w1;
    }
}

int main()
{
    scanf("%s %s",s1,s2);
    n=strlen(s1)-1,m=strlen(s2)-1;
    for(int i=0;i<=n;i++){
        A[i].x=s1[n-i]-'0';
    }
    for(int i=0;i<=m;i++){
        B[i].x=s2[m-i]-'0';
    }
    // n的值至少要大于最高项  也就是n+m 同时必须是2的幂次
    for(m=n+m,n=1;n<=m;n<<=1);
    FFT(A,n,1);
    FFT(B,n,1);
    for(int i=0;i<n;i++){
        A[i]=A[i]*B[i];
    }
    FFT(A,n,-1);
    int k=0;
    for(int i=0,t=0;i<n||t;i++){
        t+=A[i].x/n+0.5;
        ans[k++]=t%10;
        t/=10;
    }
    while(k>1&&!ans[k-1]){
        k--;
    }
    for(int i=k-1;i>=0;i--){
        cout<<ans[i];
    }
    return 0;
}