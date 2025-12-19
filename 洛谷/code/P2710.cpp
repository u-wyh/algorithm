#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int INF = 1e9;

int n,m;

int top;
int sta[MAXN];

int head;
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
int sum[MAXN];
int key[MAXN];
double priority[MAXN];
int all[MAXN];
int premax[MAXN];
int sufmax[MAXN];
bool change[MAXN];
int tag[MAXN];
bool rev[MAXN];

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
    sz[i]=1+sz[ls[i]]+sz[rs[i]];
    sum[i]=sum[ls[i]]+sum[rs[i]]+key[i];
    premax[i]=max(premax[ls[i]],sum[ls[i]]+key[i]+premax[rs[i]]);
    sufmax[i]=max(sufmax[rs[i]],sum[rs[i]]+key[i]+sufmax[ls[i]]);
    all[i]=max(max(all[ls[i]],all[rs[i]]),key[i]+sufmax[ls[i]]+premax[rs[i]]);
}

int newnode(int val){
    int cnt=sta[top--];
    sz[cnt]=1;
    key[cnt]=val,sum[cnt]=val;
    all[cnt]=val,premax[cnt]=max(0,val),sufmax[cnt]=max(0,val);
    ls[cnt]=rs[cnt]=0;
    change[cnt]=0,rev[cnt]=0;
    priority[cnt]=(double)rand()/RAND_MAX;
    return cnt;
}

void lazyreverse(int i){
    if(i==0){
        return ;
    }
    rev[i]^=1;
    swap(premax[i],sufmax[i]);
    swap(ls[i],rs[i]);
}

void lazyreplace(int i,int v){
    if(i==0){
        return ;
    }
    key[i]=v;
    sum[i]=v*sz[i];
    rev[i]=false;
    premax[i]=max(0,sum[i]);
    sufmax[i]=max(0,sum[i]);
    all[i]=max(v,sum[i]);
    change[i]=true;
    tag[i]=v;
}

void down(int i){
    if(i==0){
        return ;
    }
    if(rev[i]){
        if(ls[i]){
            lazyreverse(ls[i]);
        }
        if(rs[i]){
            lazyreverse(rs[i]);
        }
        rev[i]=false;
    }
    if(change[i]){
        if(ls[i]){
            lazyreplace(ls[i],tag[i]);
        }
        if(rs[i]){
            lazyreplace(rs[i],tag[i]);
        }
        change[i]=false;
    }
}

void split(int l,int r,int i,int rk){
    if(i==0){
        rs[l]=ls[r]=0;
    }
    else{
        down(i);
        if(sz[ls[i]]+1<=rk){
            rs[l]=i;
            split(i,r,rs[i],rk-sz[ls[i]]-1);
        }
        else{
            ls[r]=i;
            split(l,i,ls[i],rk);
        }
        up(i);
    }
}

int merge(int l,int r){
    if(l==0||r==0){
        return l+r;
    }
    if (priority[l] >= priority[r]) {
        down(l);//下发懒信息
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        down(r);
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

void freenode(int u){
    if(u==0){
        return ;
    }
    sta[++top]=u;
    if(ls[u]){
        freenode(ls[u]);
    }
    if(rs[u]){
        freenode(rs[u]);
    }
}

void get(int rk){
    int u=head;
    while(rk){
        down(u);
        if(sz[ls[u]]+1==rk){
            cout<<key[u]<<endl;
            break;
        }
        else if(sz[ls[u]]+1<rk){
            rk-=sz[ls[u]]+1;
            u=rs[u];
        }
        else{
            u=ls[u];
        }
    }
}

int main()
{
    all[0]=-INF;
    for(int i=1;i<MAXN;i++){
        sta[i]=i;
    }
    top=MAXN-1;

    n=read(),m=read();
    for(int i=1;i<=n;i++){
        int val=read();
        head=merge(head,newnode(val));
    }

    while(m--){
        string s;
        int x;
        cin>>s>>x;
        if(s[0]=='I'){
            int t=read();
            split(0,0,head,x);
            int l=rs[0];
            int r=ls[0];
            for(int i=1;i<=t;i++){
                int val=read();
                l=merge(l,newnode(val));
            }
            head=merge(l,r);
        }
        else if(s[0]=='D'){
            int t=read();
            split(0,0,head,x+t-1);
            int lm=rs[0];
            int r=ls[0];
            split(0,0,lm,x-1);
            freenode(ls[0]);
            head=merge(rs[0],r);
        }
        else if(s[0]=='R'){
            int t=read();
            split(0,0,head,x+t-1);
            int lm=rs[0];
            int r=ls[0];
            split(0,0,lm,x-1);
            lazyreverse(ls[0]);
            head=merge(merge(rs[0],ls[0]),r);
        }
        else if(s[0]=='M'){
            int t=read();
            split(0,0,head,x+t-1);
            int lm=rs[0];
            int r=ls[0];
            split(0,0,lm,x-1);
            if((int)s.length()==7){
                cout<<all[ls[0]]<<endl;
            }
            else{
                int v=read();
                lazyreplace(ls[0],v);
            }
            head=merge(merge(rs[0],ls[0]),r);
        }
        else if(s[0]=='G'){
            if((int)s.length()==3){
                get(x);
            }
            else{
                int t=read();
                split(0,0,head,x+t-1);
                int lm=rs[0];
                int r=ls[0];
                split(0,0,lm,x-1);
                cout<<sum[ls[0]]<<endl;
                head=merge(merge(rs[0],ls[0]),r);
            }
        }
    }
    return 0;
}