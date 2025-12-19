#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,k;
int val[MAXN];
int cnt[MAXN];

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

bool check(int limit){
    int now=0;
    for(int i=1;i<=limit;i++){
        int b=(val[i]-1)/m+1;
        cnt[b]++;
        now=max(now,cnt[b]);
    }
    for(int i=1;i<=limit;i++){
        int b=(val[i]-1)/m+1;
        cnt[b]--;
    }
    // cout<<limit<<":  "<<now<<endl;
    return (m-now)<=k;
}

int main()
{
    int T=read();
    while(T--){
        n=read(),m=read(),k=read();
        for(int i=1;i<=n*m;i++){
            val[i]=read();
        }
        // for(int i=1;i<=n*m;i++){
        //     cout<<(((val[i]-1)%m)+1)<<' ';
        // }
        // cout<<endl;
        int l=m,r=n*m,ans=n*m;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid)){
                ans=mid;
                r=mid-1;
            }
            else{
                l=mid+1;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}