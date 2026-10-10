// https://www.luogu.com.cn/problem/P1474
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e4+5;

int n,m;
int a[26];
int c[MAXN];
int d[MAXN];

void compute(){
    c[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            for(int k=0;k<=j;k+=a[i]){
                d[j]+=c[j-k];
            }
        }
        for(int j=0;j<=m;j++){
            c[j]=d[j];
            d[j]=0;
        }
    }

    cout<<c[m]<<endl;
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }

    compute();

    return 0;
}