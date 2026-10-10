// https://www.luogu.com.cn/problem/P2563
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;

int prime[MAXN];
int cnt;
bool vis[MAXN];

int c[MAXN<<1];
int d[MAXN<<1];

void prepare(int n){
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                break;
            }
        }
    }

    c[0]=1;
    for(int i=1;i<=cnt;i++){
        for(int j=0;j<=n;j++){
            for(int k=0;k+j<=n;k+=prime[i]){
                d[j+k]+=c[j];
            }
        }
        for(int j=0;j<=n;j++){
            c[j]=d[j];
            d[j]=0;
        }
    }
}

int main()
{
    prepare(200);
    int n;
    while(cin>>n){
        cout<<c[n]<<endl;
    }
    return 0;
}