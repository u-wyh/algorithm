#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int val[MAXN];
long long sum[MAXN];

int f[MAXN];
long long g[MAXN];

int head,tail;
int que[MAXN];

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

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+val[i];
    }
    head=1,tail=0;
    que[++tail]=0;
    for(int i=1;i<=n;i++){
        while(head+1<=tail&&sum[i]>=sum[que[head+1]]+g[que[head+1]]){
            head++;
        }
        f[i]=f[que[head]]+i-que[head]-1;
        g[i]=sum[i]-sum[que[head]];
        while(head<=tail&&((sum[que[tail]]+g[que[tail]])>=(sum[i]+g[i]))){
            tail--;
        }
        que[++tail]=i;
    }
    cout<<f[n]<<endl;
    return 0;
}