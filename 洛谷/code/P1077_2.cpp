// https://www.luogu.com.cn/problem/P1077
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e6+7;
const int MAXN = 105;

int n,m;
int a[MAXN];
int c[MAXN<<1];
int d[MAXN<<1];

void compute(){
    for(int i=0;i<=a[1];i++){
        c[i]=1;
    }
    for(int i=2;i<=n;i++){
        for(int j=0;j<=m;j++){
            for(int k=0;k<=a[i];k++){
                d[j+k]+=c[j];
                d[j+k]%=MOD;
            }
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