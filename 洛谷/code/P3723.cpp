// https://www.luogu.com.cn/problem/P3723
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e4+5;
const int MAXT = 2e5+5;
const double PI = acos(-1);

int n,m;
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

// 递归分治
void FFT(Complex A[],int n,int op){
    if(n==1){
        return;
    }

    Complex A1[n/2],A2[n/2];

    for(int i=0;i<n/2;i++){
        A1[i]=A[i*2];
        A2[i]=A[i*2+1];
    }

    FFT(A1,n/2,op);
    FFT(A2,n/2,op);

    Complex w1={cos(2*PI/n),sin(2*PI/n)*op};
    Complex wk={1,0};

    for(int i=0;i<n/2;i++){
        A[i]=A1[i]+A2[i]*wk;
        A[i+n/2]=A1[i]-A2[i]*wk;
        wk=wk*w1;
    }
}

signed main()
{
    cin>>n>>m;
    m=1;
    while(m<(2*n-1)){
        m<<=1;
    }
    int x;
    int ans=0;
    int sum=0;
    for(int i=0;i<n;i++){
        cin>>x;
        ans+=x*x;
        sum+=x;
        A[i].x=x;
    }
    for(int i=0;i<n;i++){
        cin>>x;
        ans+=x*x;
        sum-=x;
        B[n-i-1].x=x;
    }

    FFT(A,m,1);
    FFT(B,m,1);
    for(int i=0;i<m;i++){
        A[i]=A[i]*B[i];
    }
    FFT(A,m,-1);

    int best=0;
    for(int k=0;k<n;k++){
        int p=(int)(A[n-1+k].x/m+0.5);
        if(k){
            p+=(int)(A[k-1].x/m+0.5);
        }
        best=max(best,p);
    }
    ans-=2*best;

    sum=abs(sum);
    int c=sum/n;
    ans+=min(n*c*c-2*sum*c,n*(c+1)*(c+1)-2*sum*(1+c));
    cout<<ans<<endl;
    return 0;
}