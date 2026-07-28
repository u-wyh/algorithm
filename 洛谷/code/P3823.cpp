#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXS = 1e7+5;
const int HASH_SIZE = 16000057;
const int MOD = 998244353;
const int MOD1 = 1e9+7;
const int MOD2 = 1e9+9;
const int BASE = 499;

int n,m;

int val[MAXN];
int pre[MAXN];
int nxt[MAXN];
int digitalcnt[7];

int p1[51];
int p2[51];

int key1[HASH_SIZE];
int key2[HASH_SIZE];
int cnt[HASH_SIZE];

int ltval[51];
int rtval[51];

char s[MAXS];

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

void write(int x){
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

int getpos(int h1, int h2){
    return (1LL * h1 * 1000003 + h2) % HASH_SIZE;
}

int findpos(int h1,int h2){
    int p=getpos(h1,h2);
    while(key1[p]!=-1&&(key1[p]!=h1||key2[p]!=h2)){
        p++;
        if(p==HASH_SIZE){
            p=0;
        }
    }
    return p;
}

void addhash(int h1,int h2,int v){
    int p=findpos(h1,h2);
    if(key1[p]==-1){
        key1[p]=h1;
        key2[p]=h2;
    }
    cnt[p]+=v;
}

int gethash(int h1,int h2){
    int p=findpos(h1,h2);
    if(key1[p]==-1){
        return 0;
    }
    return cnt[p];
}

void change(int x,int y,int v){
    int lc=0,rc=0;
    for(int u=x;u&&lc<=49;u=pre[u]){
        ltval[++lc]=val[u];
    }
    for(int u=y;u&&rc<=49;u=nxt[u]){
        rtval[++rc]=val[u];
    }

    int h1=0,h2=0;
    for(int i=1;i<=lc;i++){
        h1=(1ll*ltval[i]*p1[i-1]+h1)%MOD1;
        h2=(1ll*ltval[i]*p2[i-1]+h2)%MOD2;

        int cur1=h1;
        int cur2=h2;

        int limit=min(rc,50-i);

        for(int j=1;j<=limit;j++){
            cur1=(1ll*cur1*BASE+rtval[j])%MOD1;
            cur2=(1ll*cur2*BASE+rtval[j])%MOD2;

            addhash(cur1,cur2,v);
        }
    }
}

int query(int len,int k){
    long long ans=1;
    if(k==1){
        for(int i=0;i<len;i++){
            ans=ans*digitalcnt[s[i]-'0']%MOD;
        }
        return ans;
    }

    int h1=0,h2=0;
    for(int i=0;i<k;i++){
        int x=s[i]-'0';
        h1=(1ll*h1*BASE+x)%MOD1;
        h2=(1ll*h2*BASE+x)%MOD2;
    }

    for(int l=0,r=k;r<=len;l++,r++){
        int now=gethash(h1,h2);
        if(now==0){
            return 0;
        }

        ans=ans*now%MOD;
        if(r==len){
            return ans;
        }

        int out=s[l]-'0';
        int in=s[r]-'0';

        h1=(h1-1ll*out*p1[k-1])%MOD1;
        h2=(h2-1ll*out*p2[k-1])%MOD2;

        if(h1<0){
            h1+=MOD1;
        }
        if(h2<0){
            h2+=MOD2;
        }

        h1=(1ll*h1*BASE+in)%MOD1;
        h2=(1ll*h2*BASE+in)%MOD2;
    }
    return ans;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
        digitalcnt[val[i]]++;
    }

    p1[0]=p2[0]=1;
    for(int i=1;i<=50;i++){
        p1[i]=(1ll*p1[i-1]*BASE)%MOD1;
        p2[i]=(1ll*p2[i-1]*BASE)%MOD2;
    }
    for(int i=0;i<HASH_SIZE;i++){
        key1[i]=-1;
    }

    for(int i=1;i<=m;i++){
        int op=read();
        if(op==1){
            int x,y;
            x=read(),y=read();

            change(x,y,1);

            nxt[x]=y;
            pre[y]=x;
        }
        else if(op==2){
            int x,y;
            x=read();
            y=nxt[x];

            change(x,y,-1);

            nxt[x]=0;
            pre[y]=0;
        }
        else{
            scanf("%s",s);
            int k=read();
            int len=strlen(s);
            write(query(len,k));
            putchar('\n');
        }
    }
    return 0;
}