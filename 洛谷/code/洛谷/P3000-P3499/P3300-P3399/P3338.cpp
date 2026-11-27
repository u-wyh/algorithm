// https://www.luogu.com.cn/problem/P3338
// 题意：输入正整数 n 和 n 个实数 q_1..q_n。
// 定义 F_j = sum_{i=1..j-1}
// (q_i * q_j) / (i - j)^2 - sum_{i=j+1..n}
// (q_i * q_j)
// / (i - j)^2
// 以及 E_i = F_i / q_i。
// 输出 n 行，
// 第 i 行输出实数 E_i（与标准答案相差不超过 10^-2 即可）。
// 数据范围：1 <= n <= 10^5，0 < q_i < 10^9。
// 算法标签：FFT
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MAXT = 4e6+5;
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

double q[MAXN];
double L[MAXN];

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

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>q[i];
        A[i].x=q[i];
    }
    for(int i=1;i<n;i++){
        B[i].x=1.0/i/i;
    }

    m=1;
    while(m<(2*n-1)){
        m<<=1;
    }

    FFT(A,m,1);
    FFT(B,m,1);
    for(int i=0;i<m;i++){
        A[i]=A[i]*B[i];
    }
    FFT(A,m,-1);

    for(int i=0;i<m;i++){
        L[i]=A[i].x/m;
    }
    for(int i=0;i<m;i++){
        A[i]={q[n-i-1],0};
    }

    FFT(A,m,1);
    for(int i=0;i<m;i++){
        A[i]=A[i]*B[i];
    }
    FFT(A,m,-1);
    
    for(int i=0;i<n;i++){
        double ans=L[i]-A[n-i-1].x/m;
        printf("%.6lf\n",ans);
    }
    return 0;
}