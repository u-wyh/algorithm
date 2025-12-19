#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e9;
const int MAXN = 1e5+5;
const int MAXK = 55;

int n,k,m;
int fullstate;
int val[MAXN];

int state[MAXN<<2];
int tree[MAXN<<2];
int len[MAXN<<2];
int precnt[MAXN<<2];
int sufcnt[MAXN<<2];
pair<int,int>pre[MAXN<<2][MAXK];
pair<int,int>suf[MAXN<<2][MAXK];

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

void up(int i){
    state[i]=state[i<<1]|state[i<<1|1];

    for(int k=1;k<=precnt[i<<1];k++){
        pre[i][k]=pre[i<<1][k];
    }
    precnt[i]=precnt[i<<1];
    for(int j=1;j<=precnt[i<<1|1];j++){
        if((pre[i][precnt[i]].first&pre[i<<1|1][j].first)!=pre[i<<1|1][j].first){
            pre[i][1+precnt[i]]={pre[i][precnt[i]].first|pre[i<<1|1][j].first,len[i<<1]+pre[i<<1|1][j].second};
            precnt[i]++;
        }
        if(precnt[i]>=k){
            break;
        }
    }

    for(int k=1;k<=sufcnt[i<<1|1];k++){
        suf[i][k]=suf[i<<1|1][k];
    }
    sufcnt[i]=sufcnt[i<<1|1];
    for(int j=1;j<=sufcnt[i<<1];j++){
        if((suf[i][sufcnt[i]].first&suf[i<<1][j].first)!=suf[i<<1][j].first){
            suf[i][1+sufcnt[i]]={suf[i][sufcnt[i]].first|suf[i<<1][j].first,len[i<<1|1]+suf[i<<1][j].second};
            sufcnt[i]++;
        }
        if(sufcnt[i]>=k){
            break;
        }
    }

    tree[i]=min(tree[i<<1],tree[i<<1|1]);
    if((state[i<<1]|state[i<<1|1])==fullstate){
        for(int s=1;s<=sufcnt[i<<1];s++){
            int s1=suf[i<<1][s].first;
            int len1=suf[i<<1][s].second;
            for(int p=1;p<=precnt[i<<1|1];p++){
                int s2=pre[i<<1|1][p].first;
                int len2=pre[i<<1|1][p].second;
                if((s1|s2)==fullstate){
                    tree[i]=min(tree[i],len1+len2);
                }
            }
        }
    }
}

void build(int l,int r,int i){
    len[i]=r-l+1;
    if(l==r){
        if(val[l]<=k){
            state[i]=(1ll<<(val[l]-1));
        }
        pre[i][++precnt[i]]={state[i],1};
        suf[i][++sufcnt[i]]={state[i],1};
        tree[i]=(state[i]==fullstate)?1:INF;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void update(int pos,int val,int l,int r,int i){
    if(l==r){
        precnt[i]=0;
        sufcnt[i]=0;
        if(val<=k){
            state[i]=(1ll<<(val-1));
        }
        pre[i][++precnt[i]]={state[i],1};
        suf[i][++sufcnt[i]]={state[i],1};
        tree[i]=(state[i]==fullstate)?1:INF;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(pos,val,l,mid,i<<1);
        }
        else{
            update(pos,val,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

signed main()
{
    n=read(),k=read(),m=read();
    fullstate=(1ll<<k)-1;
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op=read();
        if(op==2){
            if(tree[1]>=INF){
                printf("-1\n");
            }
            else{
                printf("%lld\n",tree[1]);
            }
        }
        else{
            int pos,val;
            pos=read(),val=read();
            update(pos,val,1,n,1);
        }
    }
    return 0;
}