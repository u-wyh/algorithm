#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1732073999;
const int MAXL = 40;

int n;
int p[MAXL];
int f[MAXL][MAXL][2];
int nums[MAXL];
int len;

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

int dfs(int x,int now,int free){
    if(x==0){
        return p[now];
    }
    if(f[x][now][free]!=-1){
        return f[x][now][free];
    }
    int ans=0;
    int up=free?2:nums[x];
    for(int d=0;d<=up;d++){
        ans=(ans+dfs(x-1,now+(d==1),free||(d<nums[x])))%MOD;
    }
    f[x][now][free]=ans;
    return ans;
}

signed main()
{
    int T;
    T=read(),n=read();
    p[0]=1;
    for(int i=1;i<MAXL;i++){
        p[i]=(p[i-1]*2)%MOD;
    }
    while(T--){
        n=read();
        len=0;
        int m=n;
        while(m){
            nums[++len]=m%3;
            m/=3;
        }
        for(int i=1;i<=len;i++){
            for(int j=0;j<=len;j++){
                f[i][j][0]=-1;
                f[i][j][1]=-1;
            }
        }
        cout<<dfs(len,0,0)<<endl;
    }
    return 0;
}