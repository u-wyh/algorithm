#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e7+5;

int n,m,d,x,tp;
int arr[MAXN],Seed;
int f[MAXN];
int q[MAXN],head,tail;

inline int rnd () {
	static const int MOD = 1e9;
	return Seed = ( 1LL * Seed * 0x66CCFF % MOD + 20120712 ) % MOD;
}

signed main()
{
    cin>>n>>m>>d>>x>>tp;
    if(tp==0){
        for(int i=1;i<=n;i++){
            cin>>arr[i];
        }
    }else{
        cin>>Seed;
        for(int i=1;i<=n;i++){
            arr[i]=rnd();
            //cout<<arr[i]<<' ';
        }
    }
    for(int i=1;i<=n;i++){
        f[i]=1e16;
    }
    f[1]=arr[1];
    head=1,tail=2;
    q[head]=1;
    f[1]=f[1]-2*d;
    for(int i=2;i<=n;i++){
        while(head<tail&&q[head]<i-x){
            head++;
        }
        while(head<tail&&f[q[tail-1]]>=f[i-1]){
            tail--;
        }
        q[tail++]=i-1;
        if(i==n)
            f[i]=f[q[head]]+arr[i]+m+i*d;
        else
            f[i]=f[q[head]]+arr[i]+m+i*d-(i+1)*d;
    }
    cout<<f[n]<<endl;
    return 0;
}
