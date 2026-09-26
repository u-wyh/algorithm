// https://www.luogu.com.cn/problem/P8178
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e3+5;

int n;
int a[MAXN];
int b[MAXN];
int p[MAXN];

int m[MAXN];
int r[MAXN];

int x,y,d,px,py;

void exgcd(int a,int b){
    if(b==0){
        d=a;
        x=1;
        y=0;
    }
    else{
        exgcd(b,a%b);
        px=x;
        py=y;
        x=py;
        y=px-py*(a/b);
    }
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    m[0]=1;
    r[0]=0;
    p[0]=1;

    map<int,int>mp;
    for(int i=1;i<=n;i++){
        int A=1,B=0;
        for(int j=1;j<=i;j++){
            A=A*a[j]%p[i];
            B=(B*a[j]+b[j])%p[i];
        }
        if(A==0){
            if(B!=0){
                cout<<"No"<<endl;
                return ;
            }
            continue;
        }
        exgcd(A,p[i]);

        int inv=(x%p[i]+p[i])%p[i];
        int r=(p[i]-B)*inv%p[i];
        if(mp.count(p[i])){
            if(mp[p[i]]!=r){
                cout<<"No"<<endl;
                return ;
            }
        }
        else{
            mp[p[i]]=r;
        }
    }

    cout<<"Yes"<<endl;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}