#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int INF = 8e18;

int n,m,t;
int a[MAXN];
int b[MAXN];

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

bool cmp(int a,int b){
    return a>b;
}

int compute(int i){
    if(b[i]==0){
        return a[i];
    }
    if(a[i]/b[i]<t){
        return 0;
    }
    return a[i]-t*b[i];
}

signed main()
{
    int T;
    T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            a[i]=read();
        }
        for(int i=1;i<=n;i++){
            b[i]=read();
        }
        sort(a+1,a+n+1,cmp);
        sort(b+1,b+n+1);
        for(int i=1;i<=n;i++){
            a[i]+=a[i-1];
            b[i]+=b[i-1];
        }
        m=read();
        while(m--){
            t=read();
            int l=0,r=n,ans=0;
            while(r-l>=3){
                int vl=l+(r-l)/3;
                int vr=l+(r-l)/3*2;
                int vall=compute(vl);
                int valr=compute(vr);
                ans=max(ans,max(vall,valr));
                if(vall>=valr){
                    r=vr;
                }
                else{
                    l=vl;
                }
            }
            for(int i=l;i<=r;i++){
                ans=max(ans,compute(i));
            }
            cout<<ans<<' ';
        }
        cout<<endl;
    }
    return 0;
}
/*
2
 4
 5 4 7 6
 2 1 3 2
 3
 3 1 2
 4
 19 47 21 13
 5 14 2 3
 5
 5 2 6 1 4
*/