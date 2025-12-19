#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 1e6+5;

int n,m,w,d;
int cnt[MAXN];
bool vis[MAXN];
int a[MAXN],b[MAXN];
int len;
int c[MAXN];
int pos[MAXN];
int nxt[MAXN];
int fac[MAXN];
int inv[MAXN];

int ans[MAXN];
int anscnt;

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

int power(int a,int b){
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

void calcnext(){
    nxt[1]=0;
    for(int i=2,j=0;i<=m;i++){
        // 当不匹配时，通过next数组回溯
        while(j>0&&b[i]!=b[j+1]){
            j=nxt[j];
        }
        // 如果当前字符匹配，j增加
        if(b[i]==b[j+1]){
            j++;
        }
        // 设置当前位置的next值
        nxt[i]=j;
    }
}

int comb(int a,int b){
    if(b<0||a<b){
        return 0;
    }
    return fac[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void kmp(){
    for(int i=1,j=0;i<=len;i++){
        // 当不匹配时，通过next数组回溯
        while(j>0&&c[i]!=b[j+1]){
            j=nxt[j];
        }
        // 如果当前字符匹配，j增加
        //否则 说明无法匹配上当前的s1字符  只能向下移动一位
        if(c[i]==b[j+1]){
            j++;
        }
        // 完全匹配成功
        if (j == m) {
            ans[++anscnt]=i;
            j=nxt[j];
        }
    }
}

signed main()
{
    fac[0]=inv[0]=1;
    for(int i=1;i<MAXN;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[MAXN-1]=power(fac[MAXN-1],MOD-2);
    for(int i=MAXN-2;i>=1;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }
    int T;
    T=read();
    while(T--){
        memset(vis, 0, sizeof(vis));
        memset(cnt, 0, sizeof(cnt));
        n=read(),m=read(),w=read(),d=read();
        for(int i=1;i<=n;i++){
            a[i]=read();
        }
        for(int i=1;i<=m;i++){
            b[i]=read();
        }
        int all=0;
        for(int i=1;i<=m;i++){
            if(!vis[b[i]]){
                all++;
                vis[b[i]]=true;
            }
        }
        all=w-all;
        calcnext();
        len=0;
        for(int i=1;i<=n;i++){
            if(vis[a[i]]){
                ++len;
                c[len]=a[i];
                pos[len]=i;
            }
        }
        anscnt=0;
        kmp();
        if(anscnt==0){
            cout<<0<<endl;
            continue;
        }
        int res=0;
        int kind=0;
        int lt=1,rt=0;
        for(int i=1;i<=anscnt;i++){
            int l=pos[ans[i]-m+1],r=pos[ans[i]];
            while(rt<r){
                rt++;
                if(!vis[a[rt]]){
                    cnt[a[rt]]++;
                    if(cnt[a[rt]]==1){
                        kind++;
                    }
                }
            }
            while(lt<l){
                if(!vis[a[lt]]){
                    cnt[a[lt]]--;
                    if(cnt[a[lt]]==0){
                        kind--;
                    }
                }
                lt++;
            }
            res+=comb(all-kind,d-kind);
            res%=MOD;
        }
        cout<<res<<endl;
    }
    return 0;
}