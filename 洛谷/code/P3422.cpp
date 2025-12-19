#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
int p[MAXN];
int d[MAXN];

int sum[MAXN<<1];

bool ans[MAXN];

int q[MAXN];

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
        p[i]=read(),d[i]=read();
    }

    for(int i=1;i<=n;i++){
        sum[i]=sum[i+n]=p[i]-d[i];
    }
    for(int i=1;i<=2*n;i++){
        sum[i]+=sum[i-1];
    }
    
    int head=0,tail=0;
    for(int i=2*n;i>=1;i--){
        while(head<tail&&q[head]>=i+n){
            head++;
        }
        while(head<tail&&sum[q[tail-1]]>=sum[i]){
            tail--;
        }
        q[tail++]=i;
        if(i<=n){
            if(sum[q[head]]-sum[i-1]>=0){
                ans[i]=true;
            }
        }
    }

    d[0]=d[n];
    for(int i=1;i<=n;i++){
        sum[i]=sum[i+n]=p[i]-d[i-1];
    }
    for(int i=1;i<=2*n;i++){
        sum[i]+=sum[i-1];
    }
    head=tail=0;
    for(int i=1;i<=2*n;i++){
        while(head<tail&&q[head]<=i-n-1){
            head++;
        }
        if(i>n){
            if(sum[i]-sum[q[head]]>=0){
                ans[i-n]=true;
            }
        }
        while(head<tail&&sum[q[tail-1]]<=sum[i]){
            tail--;
        }
        q[tail++]=i;
    }
    for(int i=1;i<=n;i++){
        if(ans[i]){
            printf("TAK\n");
        }
        else{
            printf("NIE\n");
        }
    }
    return 0;
}