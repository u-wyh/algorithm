#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 2e6+5;

int n,m;
int sta[MAXN],top;

int val[MAXN];
int pos[MAXN];
int nxt[MAXN];
int ans[MAXM];

int head[MAXN];
int nxtq[MAXM];
int qid[MAXM];
int qpos[MAXM];
int cnt=1;

int tree[MAXN];

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

inline void addedge(int u,int v,int id){
    nxtq[cnt]=head[u];
    qid[cnt]=id;
    qpos[cnt]=v;
    head[u]=cnt++;
}

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

pair<int,int>find(int x){
    int pos=0,sum=0;
    for(int i=17;i>=0;i--){
        int nxt=pos+(1<<i);
        if(nxt<=n&&sum+tree[nxt]<x){
            pos=nxt;
            sum+=tree[nxt];
        }
    }
    return {pos+1,x-sum};
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
        pos[val[i]]=i;
    }

    sta[0]=n+1;
    for(int i=n;i>=1;i--){
        while(top&&val[i]>val[sta[top]]){
            top--;
        }
        nxt[i]=sta[top];
        sta[++top]=i;
    }

    for(int i=1;i<=n;i=nxt[i]){
        add(val[i],nxt[i]-i);
    }

    for(int i=1;i<=m;i++){
        int t,k;
        t=read(),k=read();
        t=min(t,n);
        addedge(t,k,i);
    }

    for(int u=0;u<=n;u++){
        for(int i=head[u];i;i=nxtq[i]){
            int id=qid[i];
            int q=qpos[id];
            pair<int,int>tmp=find(q);
            ans[id]=val[pos[tmp.first]+tmp.second-1];
        }
        int mid=n/2+1;
        pair<int,int>tmp=find(mid);
        if(tmp.second==1){
            continue;
        }

        int len=query(tmp.first)-query(tmp.first-1);
        add(tmp.first,tmp.second-1-len);

        for(int i=pos[tmp.first]+tmp.second-1;i<pos[tmp.first]+len;i=nxt[i]){
            add(val[i],min(pos[tmp.first]+len,nxt[i])-i);
        }
    }

    for(int i=1;i<=m;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}