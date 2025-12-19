#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;

int n;
int arr[MAXN];
int f[MAXN][MAXN];

int tree[MAXN];

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

inline int lowbit(int x){
    return x&(-x);
}

void update(int x,int val){
    while(x<=n){
        tree[x]=max(tree[x],val);
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans=max(ans,tree[x]);
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    int T;
    T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            arr[i]=read();
        }
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                f[i][j]=0;
            }
        }
        for(int j=1;j<=n;j++){
            if(arr[j]>arr[j-1]){
                f[0][j]=j;
            }
            else{
                break;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(arr[j]>arr[j-1]){
                    f[i][j]=f[i][j-1]+1;
                }
                f[i][j]=max(f[i][j],query(arr[j])+1);
                update(arr[j],f[i-1][j]);
            }
            int res=n-f[i][n];
            for(int j=1;j<n;j++){
                res=min(res,j-f[i-1][j]+n-j);
            }
            printf("%d ",res);
            for(int i=1;i<=n;i++){
                tree[i]=0;
            }
        }
        printf("\n");
    }
    return 0;
}