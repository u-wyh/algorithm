#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 5e5+5;
const int INV = 748683265;
const int INV2 = 499122177;

int n;
int fa[MAXN];
int sz[MAXN];
int ans[MAXN];
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

void prepare(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }
}

long long power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
        sz[fy]+=sz[fx];
    }
}

signed main()
{
    // cout<<power(4,MOD-2)<<endl;
    int T;
    T=read();
    while(T--){
        n=read();
        prepare();
        for(int i=1;i<=n;i++){
            int u=read();
            un(i,u);
        }
        len=0;
        int cnt=0;
        int jishu=1;
        for(int i=1;i<=n;i++){
            if(find(i)==i){
                if(sz[i]%2==1){
                    cnt++;
                    jishu*=sz[i];
                    jishu%=MOD;
                }
                else{
                    ans[++len]=sz[i];
                }
            }
        }
        int res=0;
        if(cnt>=3){
            res=0;
        }
        else if(cnt==0){
            int tmp=1;
            for(int i=1;i<=len;i++){
                if(ans[i]>2){
                    tmp*=2;
                    tmp%=MOD;
                }
            }
            
            for(int i=1;i<=len;i++){
                int temp=tmp;
                if(ans[i]>2){
                    temp*=INV2;
                    temp%=MOD;
                }
                res=(res+temp*(ans[i]*ans[i]%MOD)%MOD*INV%MOD)%MOD;
            }
        }
        else{
            res=jishu;
            for(int i=1;i<=len;i++){
                if(ans[i]>2){
                    res*=2;
                    res%=MOD;
                }
            }
        }
        // cout<<cnt<<":    ";
        cout<<res<<endl;
    }
    return 0;
}