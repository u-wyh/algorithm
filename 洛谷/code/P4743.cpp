#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;
const int MAXM = 205;

int n,m,q;
int all;

int head=0;
int cnt=0;
int val[MAXN][MAXM];
int sum[MAXN][MAXM];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
double priority[MAXN];

int key[MAXM];

void up(int i){
    sz[i]=sz[ls[i]]+sz[rs[i]]+1;
    for(int k=1;k<=m;k++){
        sum[i][k]=sum[ls[i]][k]+sum[rs[i]][k]+val[i][k];
    }
}

int newnode(){
    ++cnt;
    sz[cnt]=1;
    priority[cnt]=(double)rand()/RAND_MAX;
    for(int i=1;i<=m;i++){
        val[cnt][i]=key[i];
        sum[cnt][i]=key[i];
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

int main()
{
    scanf("%d %d",&n,&m);
    all=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            key[j]=0;
        }
        int k;
        scanf("%d",&k);
        for(int j=1;j<=k;j++){
            int x,y;
            scanf("%d %d",&x,&y);
            x++;
            key[x]=y;
        }
        head=merge(head,newnode());
    }
    scanf("%d",&q);
    while(q--){
        char op[3];
        scanf("%s",op+1);
        if(op[1]=='Q'){
            if(op[2]=='A'){
                printf("%d\n",all);
            }
            else{
                int lt,rt;
                scanf("%d %d",&lt,&rt);

                split(0,0,head,rt);
                int lm=rs[0];
                int r=ls[0];
                split(0,0,lm,lt-1);
                int l=rs[0];
                int mid=ls[0];
                for(int i=1;i<=m;i++){
                    printf("%d ",sum[mid][i]);
                }
                printf("\n");
                head=merge(merge(l,mid),r);
            }
        }
        else if(op[1]=='I'){
            int x;
            scanf("%d",&x);
            split(0,0,head,x);
            int lm=rs[0];
            int r=ls[0];
            for(int j=1;j<=m;j++){
                key[j]=0;
            }
            int k;
            scanf("%d",&k);
            for(int j=1;j<=k;j++){
                int x,y;
                scanf("%d %d",&x,&y);
                x++;
                key[x]=y;
            }
            head=merge(merge(lm,newnode()),r);
            all++;
        }
        else{
            int x;
            scanf("%d",&x);
            all--;
            split(0,0,head,x);
            int lm=rs[0];
            int r=ls[0];
            split(0,0,lm,x-1);
            head=merge(rs[0],r);
        }
    }
    printf("end\n");
    return 0;
}