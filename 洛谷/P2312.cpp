#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;

int n,m;
queue<int>q;
int arr[105];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',x%=MOD,ch=getchar();
    return x*f;
}

inline bool check(int x){
    int sum=0;
    for(int i=n;i>=1;i--){
        sum=((arr[i]+sum)*x)%MOD;
    }
    sum=(sum+arr[0])%MOD;
    return sum==0;
}

signed main()
{
    n=read(),m=read();
    for(int i=0;i<=n;i++){
        arr[i]=read();
    }
    for(int i=1;i<=m;i++){
        if(check(i)){
            q.push(i);
        }
    }
    printf("%lld\n",(int)q.size());
    while(!q.empty()){
        printf("%lld\n",q.front());
        q.pop();
    }
    return 0;
}