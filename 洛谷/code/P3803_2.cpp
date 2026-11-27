// https://www.luogu.com.cn/problem/P3803
// 题意：第一行输入两个多项式次数 n, m，随后两行分别从低次到高次输入 F(x) 的 n+1 个系数和 G(x) 的 m+1 个系数。
// 计算多项式乘积 F(x) * G(x)。
// 一行输出 n+m+1 个整数，从低次到高次表示乘积多项式的系数。
// 数据范围：对于 100% 的数据，0 <= n, m <= 10^6，输入系数均为 0 到 9 的整数。
#include<bits/stdc++.h>
// 算法标签：FFT
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
int rev[MAXT];

// 如果是正变换 由系数求点值  那么op=1
// 如果是逆变换 由点值求系数  那么op=-1
// 这样可以统一方便的初始w1
void FFT(Complex *A,int n,int op){
    for(int i=0;i<n;i++){
        rev[i]=(rev[i>>1]>>1)+((i&1)?(n>>1):0);
    }
    for(int i=0;i<n;i++){
        if(i<rev[i]){
            swap(A[i],A[rev[i]]);
        }
    }
    for(int m=2;m<=n;m<<=1){
        Complex w1({cos(2*PI/m),sin(2*PI/m)*op});
        for(int i=0;i<n;i+=m){
            Complex wk({1,0});
            for(int j=0;j<m/2;j++){
                Complex x=A[i+j],y=A[i+j+m/2]*wk;
                A[i+j]=x+y;
                A[i+j+m/2]=x-y;
                wk=wk*w1;
            }
        }
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<=n;i++){
        scanf("%lf",&A[i].x);
    }
    for(int i=0;i<=m;i++){
        scanf("%lf",&B[i].x);
    }
    // n的值至少要大于最高项  也就是n+m 同时必须是2的幂次
    for(m=n+m,n=1;n<=m;n<<=1);
    FFT(A,n,1);
    FFT(B,n,1);
    for(int i=0;i<n;i++){
        A[i]=A[i]*B[i];
    }
    FFT(A,n,-1);
    for(int i=0;i<=m;i++){
        printf("%d ",(int)((A[i].x/n)+0.5));
    }
    return 0;
}