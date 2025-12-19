#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXB = 405;

int n,q,blen;
int nums[MAXN];
int f[MAXN][MAXB];

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

void prepare(){
    blen=sqrt(n);
    for(int i=n;i>=1;i--){
        for(int d=1;d<=blen;d++){
            f[i][d]=1+(i+nums[i]+d>n?0:f[i+nums[i]+d][d]);
        }
    }
}

int query(int p,int k){
    if(k<=blen){
        return f[p][k];
    }
    else{
        int ans=0;
        while(p<=n){
            ans++;
            p=p+k+nums[p];
        }
        return ans;
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    prepare();
    q=read();
    while(q--){
        int p,k;
        p=read(),k=read();
        cout<<query(p,k)<<endl;
    }
    return 0;
}