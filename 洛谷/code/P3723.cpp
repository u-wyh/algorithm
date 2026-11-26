// https://www.luogu.com.cn/problem/P3723
// 题意：输入装饰物数 n 和亮度上限 m，以及两条环形手环上按逆时针顺序排列的亮度序列 x_1..x_n 和 y_1..y_n。
// 允许将其中一个手环的所有亮度同时加上同一个非负整数 c，并任意循环旋转其中一条手环使位置对齐（不可翻转）。
// 求对齐后差异值 sum_{i=1..n} (x_i - y_i)^2 的最小值，输出一个整数。
// 数据范围：1 <= n <= 50000，1 <= x_i, y_i <= m <= 100（改造后亮度可超过 m）。
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