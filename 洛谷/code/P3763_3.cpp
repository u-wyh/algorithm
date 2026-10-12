// https://www.luogu.com.cn/problem/P3763
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = 8e5+5;
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

string s0,s1;
int ans[MAXN];

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

void compute(char c){
    int len=1;
    while(len<(n+m-1)){
        len<<=1;
    }
    for(int i=0;i<len;i++){
        A[i]=B[i]={0,0};
    }
    for(int i=0;i<n;i++){
        A[i]={s0[i]==c?1:0,0};
    }
    for(int i=0;i<m;i++){
        B[i]={s1[i]==c?1:0,0};
    }
    FFT(A,len,1);
    FFT(B,len,1);
    for(int i=0;i<len;i++){
        A[i]=A[i]*B[i];
    }
    FFT(A,len,-1);

    for(int i=0;i<n;i++){
        ans[i]+=(int)(A[i+m-1].x/len+0.5);
    }
}

void solve(){
    cin>>s0>>s1;
    n=s0.length();
    m=s1.length();
    if(n<m){
        cout<<0<<endl;
        return ;
    }
    for(int i=0,j=m-1;i<=j;i++,j--){
        swap(s1[i],s1[j]);
    }
    for(int i=0;i<n;i++){
        ans[i]=0;
    }

    compute('A');
    compute('T');
    compute('G');
    compute('C');

    int res=0;
    for(int i=0;i<=n-m;i++){
        if(ans[i]>=m-3){
            res++;
        }
    }
    cout<<res<<endl;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}