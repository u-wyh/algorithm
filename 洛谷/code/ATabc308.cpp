#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e7+5;
const int BIT = 29;
const int INF = 1<<30;

int q;
int tree[MAXN][2];
int pass[MAXN];
int cnt=1;
int fa[MAXN];

int mineor[MAXN];
int only[MAXN];

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

int change(int x,int v){
    int cur=1;
    pass[cur]+=v;
    for(int b=BIT;b>=0;b--){
        int path=(x>>b)&1;
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
            fa[cnt]=cur;
        }
        cur=tree[cur][path];
        pass[cur]+=v;
    }
    return cur;
}

void compute(int x,int v){
    int bottom=change(x,v);
    mineor[bottom]=pass[bottom]>=2?0:INF;
    only[bottom]=pass[bottom]==1?x:0;
    for(int i=fa[bottom];i>0;i=fa[i]){
        int l=tree[i][0];
        int r=tree[i][1];
        if(pass[i]<2){
            mineor[i]=INF;
        }
        else if(pass[l]==1&&pass[r]==1){
            mineor[i]=only[l]^only[r];
        }
        else if(pass[l]==0||pass[r]==0){
            mineor[i]=(pass[l]==0)?mineor[r]:mineor[l];
        }
        else{
            mineor[i]=min(mineor[l],mineor[r]);
        }

        if(pass[i]==1){
            only[i]=only[l]+only[r];
        }
        else{
            only[i]=0;
        }
    }
}

int main()
{
    q=read();
    for(int i=1;i<=q;i++){
        int op,x;
        op=read();
        if(op==3){
            printf("%d\n",mineor[1]);
        }
        else{
            x=read();
            if(op==1){
                compute(x,1);
            }
            else{
                compute(x,-1);
            }
        }
    }
    return 0;
}