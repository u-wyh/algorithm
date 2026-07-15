#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e6+5;

int n,m,d;
int arr[MAXN];
int sum[MAXN];
int q[MAXN],head,tail;

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

signed main()
{
    n=read(),m=read(),d=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
        sum[i]=sum[i-1]+arr[i];
    }
    int ans=d;
    int l=1;
    head=0,tail=1;
    q[head]=d;
    for(int r=d+1;r<=n;r++){
        while(head<tail&&sum[r]-sum[r-d]>sum[q[tail-1]]-sum[q[tail-1]-d]){
            tail--;
        }
        q[tail++]=r;
        while(head<tail&&sum[r]-sum[l-1]-sum[q[head]]+sum[q[head]-d]>m){
            l++;
            while(head<tail&&q[head]-d+1<l){
                head++;
            }
        }
        ans=max(ans,r-l+1);
    }
    cout<<ans<<endl;
    return 0;
}
