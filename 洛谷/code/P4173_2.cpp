// https://www.luogu.com.cn/problem/P4173
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int MAXT = 2e6+5;
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
Complex A[MAXT],B[MAXT],C[MAXT];
int val1[MAXN];
int val0[MAXN];
string s1,s0;

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

void compute(int op,int len){
    for(int i=0;i<len;i++){
        A[i]=B[i]={0,0};
    }
    for(int i=0;i<m;i++){
        int x=val1[i];
        if(op==0){
            A[m-1-i].x=x*x*x;
        }
        else if(op==1){
            A[m-1-i].x=x*x;
        }
        else{
            A[m-1-i].x=x;
        }
    }
    for(int i=0;i<n;i++){
        int x=val0[i];
        if(op==0){
            B[i].x=x;
        }
        else if(op==1){
            B[i].x=x*x;
        }
        else{
            B[i].x=x*x*x;
        }
    }

    FFT(A,len,1);
    FFT(B,len,1);
    for(int i=0;i<len;i++){
        Complex t=A[i]*B[i];

        if(op==1){
            C[i].x-=2*t.x;
            C[i].y-=2*t.y;
        }
        else{
            C[i]=C[i]+t;
        }
    }
}


int ans[MAXN];

int main()
{
    cin>>m>>n>>s1>>s0;
    int len=1;
    while(len<(m+n-1)){
        len<<=1;
    }

    for(int i=0;i<n;i++){
        if(s0[i]=='*'){
            val0[i]=0;
        }
        else{
            val0[i]=s0[i]-'a'+1;
        }
    }
    for(int i=0;i<m;i++){
        if(s1[i]=='*'){
            val1[i]=0;
        }
        else{
            val1[i]=s1[i]-'a'+1;
        }
    }

    compute(0,len);
    compute(1,len);
    compute(2,len);

    FFT(C,len,-1);

    int cnt=0;
    for(int i=0;i<=n-m;i++){
        int x=(C[i+m-1].x/len+0.5);
        if(x==0){
            ans[++cnt]=i+1;
        }
    }
    cout<<cnt<<endl;
    for(int i=1;i<=cnt;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}