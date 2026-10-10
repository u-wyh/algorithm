// https://www.luogu.com.cn/problem/P1164
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;
const int MAXM = 1e4+5;

int n,m;
int a[MAXN];
int c[MAXN+MAXM];
int d[MAXN+MAXM];

void compute(){
    c[0]=1;
    c[a[1]]=1;
    for(int i=2;i<=n;i++){
        for(int j=0;j<=m;j++){
            d[j]=c[j];
        }
        for(int j=0;j<=m;j++){
            d[j+a[i]]+=c[j];
        }
        for(int j=0;j<=m;j++){
            c[j]=d[j];
            d[j]=0;
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    compute();
    cout<<c[m]<<endl;
    return 0;
}