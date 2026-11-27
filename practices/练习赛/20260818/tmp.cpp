#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e6+5;
const int MOD = 1e9+7;

int n,q,k;
int a[MAXN];
int c[MAXN];

int tree[MAXN<<2];

mt19937_64 rng(time(0));
map<pair<int,int>,int>mp1;
map<int,int>mp2;
map<int,int>mp3;

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

void up(int x){
    tree[x]=(tree[x<<1]+tree[x<<1|1])%MOD;
}

void calc(int a,int c,int i){
    int v=mp1[{a,c}];
    if(v==0&&mp2[a]!=k){
        v=rng()%MOD;
        if(v==0){
            v++;
        }

        int t=++mp2[a];
        if(t==k){
            v=-mp3[a];
            mp3[a]=0;
        }
        else{
            mp3[a]+=v;
            mp3[a]%=MOD;
        }
        mp1[{a,c}]=v;
    }
    tree[i]=v;
}

void build(int l,int r,int i){
    if(l==r){
        calc(a[l],c[l],i);
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void update(int pos,int joba,int jobc,int l,int r,int i){
    if(l==r){
        calc(joba,jobc,i);
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(pos,joba,jobc,l,mid,i<<1);
        }
        else{
            update(pos,joba,jobc,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int all;

void query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        all+=tree[i];
        all%=MOD;
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            query(jobl,jobr,mid+1,r,i<<1|1);
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    T=read();
    while(T--){
        n=read(),q=read(),k=read();
        mp1.clear();
        mp2.clear();
        mp3.clear();
        for(int i=1;i<=n;i++){
            a[i]=read();
        }
        for(int i=1;i<=n;i++){
            c[i]=read();
        }

        build(1,n,1);

        for(int i=1;i<=q;i++){
            int op=read();
            if(op==1){
                int pos,x,y;
                pos=read(),x=read(),y=read();
                update(pos,x,y,1,n,1);
            }
            else{
                all=0;
                int l=read(),r=read();
                query(l,r,1,n,1);
                if(all==0){
                    cout<<"YES"<<endl;
                }
                else{
                    cout<<"NO"<<endl;
                }
            }

        }
    }
    return 0;
}