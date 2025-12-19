#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 1e6+5;

int n,m;
int stx,sty,enx,eny;
int nums[MAXN][MAXN];

int head[MAXM];
int nxt[MAXM<<2];
int to[MAXM<<2];
int weight[MAXM<<2];
int cnt=1;

inline int id(int x,int y,int op){
    return (x-1)*m+y+op*n*m;
}

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            scanf("%c",&c);
            if(c=='C'){
                stx=i,sty=j;
            }
            else if(c=='D'){
                enx=i,eny=j;
            }
            if(c!='#'){
                nums[i][j]=1;
            }
        }
    }
    for(int i=m+1;i<=n*m-m;i++){
        addedge(i,i+n*m,1);
        addedge(i+n*m,i,1);
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=n;j++){
            if(nums[i][j]==1){
                if(nums[i+1][j]==0){
                    //表示不会向下掉
                    
                }
            }
        }
    }
    return 0;
}