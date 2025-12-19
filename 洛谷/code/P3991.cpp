#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 3e5+5;

int n;

int head=0;
int cnt=0;
int f[MAXM][4][4];
int val[MAXM][4];
double priority[MAXM];
int len[MAXM];
int sz[MAXM];
int all[MAXM];
int ls[MAXM];
int rs[MAXM];

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
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            f[x][i][j]=0;
        }
    }

    for(int i=0;i<4;i++){
        for(int j=i;j<4;j++){
            for(int k=j;k<4;k++){
                f[x][i][k]=max(f[x][i][k],f[ls[x]][i][j]+val[x][j]*len[x]+f[rs[x]][j][k]);
            }
        }
    }
    all[x]=all[ls[x]]+all[rs[x]]+len[x];
    sz[x]=sz[ls[x]]+sz[rs[x]]+1;
}

int newnode(int a,int b,int c,int d){
    ++cnt;
    len[cnt]=d;
    sz[cnt]=1;
    all[cnt]=d;
    priority[cnt]=(double)rand()/RAND_MAX;
    val[cnt][0]=a;
    val[cnt][1]=b;
    val[cnt][2]=c;
    val[cnt][3]=a;
    for(int i=0;i<=3;i++){
        for(int j=i;j<=3;j++){
            long long maxval=0;
            for(int k=i;k<=j;k++){
                maxval=max(maxval,val[cnt][k]*d);
            }
            f[cnt][i][j]=maxval;
        }
    }
    return cnt;
}

void split(int l, int r, int i, int rank) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        if (sz[ls[i]] + 1 <= rank) {
            rs[l] = i;
            split(i, r, rs[i], rank - sz[ls[i]] - 1);
        } else {
            ls[r] = i;
            split(l, i, ls[i], rank);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

// 查询>=rk的块的排名
pair<int,int> querypos(int rk){
    int u=head;
    int ans=0;
    while(u){
        if(all[ls[u]]>=rk){
            u=ls[u];
        }
        else if(all[ls[u]]+len[u]>=rk){
            return {ans+sz[ls[u]]+1,u};
        }
        else{
            rk-=all[ls[u]]+len[u];
            ans+=sz[ls[u]]+1;
            u=rs[u];
        }
    }
    return {ans+1,0};
}

int querysum(int k){
    int u=head;
    int ans=0;
    while(k){
        if(sz[ls[u]]+1<=k){
            k-=(sz[ls[u]]+1);
            ans+=all[ls[u]]+len[u];
            u=rs[u];
        }
        else{
            u=ls[u];
        }
    }
    return ans;
}

signed main()
{
    n=read();
    int now=0;
    for(int i=1;i<=n;i++){
        int before=f[head][0][3];
        int pos,a,b,c,d;
        pos=read(),a=read(),b=read(),c=read(),d=read();
        if(pos==0){
            head=merge(newnode(a,b,c,d),head);
        }
        else if(pos==now){
            head=merge(head,newnode(a,b,c,d));
        }
        else{
            pair<int,int>tmp=querypos(pos);
            int rk=tmp.first;
            int p=tmp.second;

            int length=len[p];
            int delta=querysum(rk)-pos;
            if(delta==0){
                split(0,0,head,rk);
                int lm=rs[0];
                int r=ls[0];
                head=merge(merge(lm,newnode(a,b,c,d)),r);
            }
            else{
                split(0,0,head,rk);
                int lm=rs[0];
                int r=ls[0];
                split(0,0,lm,rk-1);
                int l=rs[0];
                // int m=ls[0];
                head=merge(merge(merge(l,newnode(val[p][0],val[p][1],val[p][2],length-delta)),newnode(a,b,c,d)),merge(newnode(val[p][0],val[p][1],val[p][2],delta),r));
            }
        }
        now+=d;
        int after=f[head][0][3];
        printf("%lld\n",after-before);
    }
    return 0;
}
/*
5
0 25 37 46 2
1 32 14 16 3
3 99 77 88 4
2 43 68 57 5
14 72 36 18 6
*/