#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;
int minl[MAXN];
int maxl[MAXN];
int f[MAXN];
int q[MAXN];
int head,tail;

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
    n=read(),m=read();
    for(int i=1;i<=n+1;i++){
        minl[i]=i;
    }
    for(int i=1;i<=m;i++){
        int l,r;
        l=read(),r=read();
        minl[r]=min(minl[r],l);
        maxl[r+1]=max(maxl[r+1],l);
    }
    for(int i=n;i>=1;i--){
        minl[i]=min(minl[i],minl[i+1]);
    }
    for(int i=1;i<=n+1;i++){
        maxl[i]=max(maxl[i],maxl[i-1]);
    }
    f[0]=1;
    head=1,tail=0;
    q[++tail]=0;
    int j=1;
    for(int i=1;i<=n+1;i++){
        while(j<minl[i]){
            if(f[j]==0){
                j++;
                continue;
            }
            while(head<=tail&&f[q[tail]]<f[j]){
                tail--;
            }
            q[++tail]=j;
            j++;
        }
        while(head<=tail&&q[head]<maxl[i]){
            head++;
        }

        if(head<=tail){
            f[i]=f[q[head]]+(i!=(n+1));
        }
    }
    printf("%d\n",f[n+1]-1);
    return 0;
}