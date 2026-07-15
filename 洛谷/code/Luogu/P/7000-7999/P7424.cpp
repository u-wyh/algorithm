#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;

int qid[MAXN];
int l[MAXN];
int r[MAXN];
int k[MAXN];
int ans[MAXN];//记录每块砖是被谁打破的
int used=0;

int maxp;
int pos[MAXN];

int res[MAXN];

int tree[MAXN];

int lset[MAXN];
int rset[MAXN];

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

inline int lowbit(int x){
    return x&(-x);
}

void add(int x,int v){
    if(x==0){
        return ;
    }
    while(x<=maxp){
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

int sum(int l,int r){
    return query(r)-query(l-1);
}

void compute(int ql,int qr,int vl,int vr){
    if(ql>qr){
        return ;
    }
    if(vl==vr){
        for(int i=ql;i<=qr;i++){
            int id=qid[i];
            ans[id]=vl;
        }
    }
    else{
        int mid=(vl+vr)/2;
        while(used<mid){
            used++;
            add(pos[used],1);
        }
        while(used>mid){
            add(pos[used],-1);
            used--;
        }
        int lsz=0,rsz=0;
        for(int i=ql;i<=qr;i++){
            int id=qid[i];
            int all=sum(l[id],min(r[id],maxp));
            if(all>=k[id]){
                lset[++lsz]=id;
            }
            else{
                rset[++rsz]=id;
            }
        }
        for(int i=ql;i<=ql+lsz-1;i++){
            qid[i]=lset[i-ql+1];
        }
        for(int i=ql+lsz;i<=qr;i++){
            qid[i]=rset[i-ql-lsz+1];
        }
        compute(ql,ql+lsz-1,vl,mid);
        compute(ql+lsz,qr,mid+1,vr);
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        l[i]=read();
        r[i]=read();
        k[i]=read();
        qid[i]=i;
    }
    for(int i=1;i<=m;i++){
        pos[i]=read();
        maxp=max(maxp,pos[i]);
    }
    compute(1,n,1,m+1);
    for(int i=1;i<=n;i++){
        res[ans[i]]++;
    }
    for(int i=1;i<=m;i++){
        printf("%d\n",res[i]);
    }
    return 0;
}