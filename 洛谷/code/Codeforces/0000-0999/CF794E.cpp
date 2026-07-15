#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n;
int nums[MAXN];
int h[MAXN];
int g[MAXN];

int H[MAXN],G[MAXN];
int ans[MAXN];

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
        nums[i]=read();
        ans[n-1]=max(ans[n-1],nums[i]);
    }
    if(n==1){
        cout<<nums[1]<<endl;
        return 0;
    }
    for(int i=1;i<n;i++){
        h[i]=max(nums[i],nums[i+1]);
    }
    for(int i=2;i<n;i++){
        g[i]=max(min(nums[i],nums[i-1]),min(nums[i],nums[i+1]));
    }

    int even=(n%2==0)?n:n-1;
    if(even>=2){
        for(int m=even;m>=2;m-=2){
            int l=m/2;
            int r=n-m/2;
            H[m]=max(H[m+2],max(h[l],h[r]));
        }
    }

    int odd=(n%2==1)?n:n-1;
    if(odd>=3){
        for(int m=odd;m>=3;m-=2){
            int l=(m+1)/2;
            int r=n-(m-1)/2;
            G[m]=max(G[m+2],max(g[l],g[r]));
        }
    }

    for(int i=0;i<n;i++){
        int m=n-i;
        if(m==1){
            continue;
        }
        if(m%2==0){
            ans[i]=H[m];
        }
        else{
            ans[i]=G[m];
        }
    }

    for(int i=0;i<n;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}