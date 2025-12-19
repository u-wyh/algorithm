#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 65;
const int MOD = 1e9+7;
const int INV2 = 500000004;

int n,m,k;
int len1;
int nums1[MAXN];
int len2;
int nums2[MAXN];

int f[MAXN][2][2];

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

int gettotal(){
    return ((((n-m)%MOD)*((m+1)%MOD))%MOD+((((m+1)%MOD)*((m+2)%MOD)%MOD)*INV2%MOD))%MOD;
}

int dfs(int x,int free1,int free2){
    if(x==0){
        return 1;
    }
    if(f[x][free1][free2]!=-1){
        return f[x][free1][free2];
    }
    int ans=0;
    int upa=free1?k-1:nums1[x];
    int upb=free2?k-1:nums2[x];
    for(int a=0;a<=upa;a++){
        int bb=min(upb,a);
        for(int b=0;b<=bb;b++){
            ans=(ans+dfs(x-1,free1||a<nums1[x],free2||b<nums2[x]))%MOD;
        }
    }
    f[x][free1][free2]=ans;
    return ans;
}

int compute(){
    len1=0,len2=0;
    while(n){
        nums1[++len1]=n%k;
        n/=k;
    }
    while(m){
        nums2[++len2]=m%k;
        m/=k;
    }
    for(int i=len2+1;i<=len1;i++){
        nums2[i]=0;
    }
    memset(f,-1,sizeof(f));
    return dfs(len1,0,0);
}

signed main()
{
    int T=read();
    k=read();
    while(T--){
        n=read(),m=read();
        m=min(n,m);
        int all=gettotal();
        int res=compute();
        all=(all-res+MOD)%MOD;
        cout<<all<<endl;
    }
    return 0;
}