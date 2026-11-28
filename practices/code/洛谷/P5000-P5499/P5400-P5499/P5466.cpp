// https://www.luogu.com.cn/problem/P5466
// 题意：给定由 '0'、'1'、'?' 组成的字符串 s，
// 把每个 '?' 替换为 '0' 或 '1'
// 判断每个长度 len 能否成为合法
// border（记 f(len) 为 1 或 0）。
// 输入字符串 s；
// 输出所有 (f(len) * len^2)（len=1..|s|）的按位异或和。
// 数据范围：|s| <= 5*10^5，字符仅含 '0'、'1'、'?'。
// 难度评分：2700（洛谷分级换算）
// 算法标签：FFT、枚举
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
bool bad[MAXN];

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

int main()
{
    string s;
    cin>>s;
    n=s.length();
    m=1;
    while(m<(2*n-1)){
        m<<=1;
    }

    for(int i=0;i<n;i++){
        if(s[i]=='0'){
            A[i].x=1;
        }
        if(s[i]=='1'){
            B[n-i-1].x=1;
        }
    }

    FFT(A,m,1);
    FFT(B,m,1);
    for(int i=0;i<m;i++){
        A[i]=A[i]*B[i];
    }
    FFT(A,m,-1);

    for(int d=1;d<n;d++){
        int x=(int)(A[n-1+d].x/m+0.5);
        int y=(int)(A[n-1-d].x/m+0.5);
        if(x||y){
            bad[d]=true;
        }
    }
    long long ans=1ll*n*n;
    for(int p=1;p<n;p++){
        bool flag=true;
        // 检查p的所有倍数
        for(int d=p;d<n;d+=p){
            if(bad[d]){
                flag=false;
                break;
            }
        }

        if(flag){
            long long len=n-p;
            ans^=len*len;
        }
    }
    cout<<ans<<endl;
    return 0;
}