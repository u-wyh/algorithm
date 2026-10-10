// https://www.luogu.com.cn/problem/P1450
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int a[5];
int b[5];
int c[MAXN];
int d[MAXN];

void prepare(int n){
    c[0]=1;
    for(int i=1;i<=4;i++){
        for(int j=0;j<=n;j++){
            d[j]=c[j];
            if(j>=a[i]){
                d[j]+=d[j-a[i]];
            }
        }
        for(int j=0;j<=n;j++){
            c[j]=d[j];
            d[j]=0;
        }
    }
}

void compute(int s){
    int ans=0;

    for(int mask=0;mask<16;mask++){
        int cost=0;
        int cnt=0;

        for(int i=1;i<=4;i++){
            if(mask>>(i-1)&1){
                cost+=(b[i]+1)*a[i];
                cnt++;
            }
        }

        if(cost>s) continue;

        if(cnt&1){
            ans-=c[s-cost];
        }
        else{
            ans+=c[s-cost];
        }
    }

    cout<<ans<<"\n";
}

signed main()
{
    for(int i=1;i<=4;i++){
        cin>>a[i];
    }
    prepare(100000);
    int T;
    cin>>T;
    while(T--){
        int m;
        for(int i=1;i<=4;i++){
            cin>>b[i];
        }
        cin>>m;
        compute(m);
    }
    return 0;
}