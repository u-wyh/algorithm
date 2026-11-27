#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int phi[MAXN];
int prime[MAXN];
int cnt=0;
bool vis[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void euler(int n){
    phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
            phi[i]=i-1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0){
                phi[i*prime[j]]=prime[j]*phi[i];
                break;
            }
            else{
                phi[i*prime[j]]=(prime[j]-1)*phi[i];
            }
        }
    }
}

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        int n,m;
        n=read(),m=read();
        int k=phi[n];
        int t=0;
        for(int i=1;i<=m;i++){
            int v=read();
            if(gcd(v,n)==1){
                t++;
            }
        }
        if((k-t)%2){
            cout<<"Alice"<<endl;
        }
        else{
            cout<<"Bob"<<endl;
        }
    }
    return 0;
}