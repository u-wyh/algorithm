// 用途：实数 FFT 求两个整数系数多项式的卷积。
// 时间：O(L log L)，L 为补齐后的长度。
// 空间：O(L)。
// 注意：浮点结果四舍五入；大系数需评估精度。
// 例题：https://www.luogu.com.cn/problem/P3803
// 题意：给定两个整数系数多项式，求乘积各项系数。
// 思路：FFT 把系数变到点值形式，相乘后逆变换并四舍五入。
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
int rev[MAXT];

// 位逆序置换后，按长度倍增执行蝶形运算。
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
    for(m=n+m,n=1;n<=m;n<<=1);
    // 补到严格大于结果最高次数的 2 的幂，避免循环卷积覆盖有效系数。
    FFT(A,n,1);
    FFT(B,n,1);
    for(int i=0;i<n;i++){
        A[i]=A[i]*B[i];
    }
    FFT(A,n,-1);
    // 逆变换需除以 n，再把浮点误差四舍五入。
    for(int i=0;i<=m;i++){
        printf("%lld ",llround(A[i].x/n));
    }
    return 0;
}
