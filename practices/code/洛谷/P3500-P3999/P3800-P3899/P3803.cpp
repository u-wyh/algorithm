// https://www.luogu.com.cn/problem/P3803
// 题意：第一行输入两个多项式次数 n, m，
// 随后两行分别从低次到高次输入 F(x) 的 n+1 个系数和 G(x) 的
// m+1 个系数。
// 计算多项式乘积 F(x) * G(x)。
// 一行输出 n+m+1 个整数，从低次到高次表示乘积多项式的系数。
// 数据范围：对于 100% 的数据，0 <= n, m <= 10^6，
// 输入系数均为 0 到 9 的整数。
// 难度评分：2700（洛谷分级换算）
// 算法标签：FFT
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MAXT = 4e6+5;
const double PI = acos(-1);
#define complex complex<double>

int n,m;
complex A[MAXT],B[MAXT];

// 如果是正变换 由系数求点值  那么op=1
// 如果是逆变换 由点值求系数  那么op=-1
// 这样可以统一方便的初始w1
void FFT(complex *A,int n,int op){
    if(n==1){
        return ;
    }
    complex A1[n/2],A2[n/2];
    for(int i=0;i<n/2;i++){
        A1[i]=A[2*i];
        A2[i]=A[2*i+1];
    }
    FFT(A1,n/2,op);
    FFT(A2,n/2,op);
    complex w1({cos(2*PI/n),sin(2*PI/n)*op});
    complex wk({1,0});
    for(int i=0;i<n/2;i++){
        A[i]=A1[i]+A2[i]*wk;
        A[i+n/2]=A1[i]-A2[i]*wk;
        wk=wk*w1;
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<=n;i++){
        scanf("%lf",&A[i]);
    }
    for(int i=0;i<=m;i++){
        scanf("%lf",&B[i]);
    }
    // n的值至少要大于最高项  也就是n+m 同时必须是2的幂次
    for(m=n+m,n=1;n<=m;n<<=1);
    cout<<n<<endl;
    FFT(A,n,1);
    FFT(B,n,1);
    for(int i=0;i<n;i++){
        A[i]=A[i]*B[i];
    }
    FFT(A,n,-1);
    for(int i=0;i<=m;i++){
        printf("%d ",(int)((A[i].real()/n)+0.5));
    }
    return 0;
}