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
        A[i]={((s0[i]==c)||(s0[i]=='*'))?1:0,0};
    }
    for(int i=0;i<m;i++){
        B[i]={(s1[i]==c)?1:0,0};
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

int res[MAXN];

void solve(){
    cin>>m>>n>>s1>>s0;
    for(int i=0,j=m-1;i<=j;i++,j--){
        swap(s1[i],s1[j]);
    }
    int cnt=0;
    for(int i=0;i<m;i++){
        if(s1[i]=='*'){
            cnt++;
        }
    }
    for(int i=0;i<n;i++){
        ans[i]=0;
    }

    for(char c='a';c<='z';c++){
        compute(c);
    }

    int len=0;
    for(int i=0;i<=n-m;i++){
        if(ans[i]==m-cnt){
            res[++len]=i+1;
        }
    }
    cout<<len<<endl;
    for(int i=1;i<=len;i++){
        cout<<res[i]<<' ';
    }
}

int main()
{
    solve();
    return 0;
}