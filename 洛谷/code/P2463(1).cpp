// 使用哈希实现
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e3+5;
const int BASE = 499;
const int MOD = 998244353;

int n;
int len[MAXN];
int val[MAXN][MAXN];
int diff[MAXN][MAXN];

int p[MAXN];

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

bool check(int length){
    unordered_set<int>hs1;
    int val=0;
    for(int i=1;i<=length;i++){
        val=(val*BASE+diff[1][i])%MOD;
    }
    hs1.insert(val);
    for(int i=length+1;i<len[1];i++){
        val=((val-diff[1][i-length]*p[length-1])%MOD+MOD)%MOD;
        val=(val*BASE+diff[1][i])%MOD;
        hs1.insert(val);
    }

    for(int i=2;i<=n;i++){
        unordered_set<int>hs2;
        int val=0;
        for(int j=1;j<=length;j++){
            val=(val*BASE+diff[i][j])%MOD;
        }
        if(hs1.count(val)){
            hs2.insert(val);
        }
        for(int j=length+1;j<len[i];j++){
            val=((val-diff[i][j-length]*p[length-1])%MOD+MOD)%MOD;
            val=(val*BASE+diff[i][j])%MOD;
            
            if(hs1.count(val)){
                hs2.insert(val);
            }
        }
        if(hs2.empty()){
            return false;
        }
        hs1=hs2;
    }
    return true;
}

signed main()
{
    p[0]=1;
    for(int i=1;i<=1000;i++){
        p[i]=(p[i-1]*BASE)%MOD;
    }
    n=read();
    for(int i=1;i<=n;i++){
        len[i]=read();
        for(int j=1;j<=len[i];j++){
            val[i][j]=read();
        }
        for(int j=1;j<len[i];j++){
            diff[i][j]=val[i][j+1]-val[i][j];
        }
    }
    int l=1,r=1000,ans=0;
    for(int i=1;i<=n;i++){
        r=min(r,len[i]-1);
    }
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    cout<<(ans+1)<<endl;
    return 0;
}