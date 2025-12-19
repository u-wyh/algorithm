#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 1e6+5;

int n,m;
long long val[MAXN];

int up[MAXN];
int ls[MAXN];
int rs[MAXN];
int dist[MAXN];

int fa[MAXN];

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

void prepare(){
    dist[0]=-1;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int merge(int i,int j){
    if(i==0||j==0){
        return i+j;
    }
    if(val[i]>val[j]){
        swap(i,j);
    }
    rs[i]=merge(rs[i],j);
    up[rs[i]]=i;
    if(dist[ls[i]]<dist[rs[i]]){
        swap(ls[i],rs[i]);
    }
    dist[i]=dist[rs[i]]+1;
    fa[ls[i]]=fa[rs[i]]=i;
    return i;
}

int remove(int i){
    int h=find(i);
    fa[ls[i]]=ls[i];
    fa[rs[i]]=rs[i];
    int s=merge(ls[i],rs[i]);
    int f=up[i];
    if(s){
        fa[i]=s;
        up[s]=f;
    }
    if(h!=i){
        fa[s]=h;
        if (ls[f] == i) {
            ls[f] = s;
        } else {
            rs[f] = s;
        }
        //向上修正  逐层更新  直到到达某层之后不会继续影响上面
        for (int d = dist[s], tmp; dist[f] > d + 1; f = up[f], d++) {
            dist[f] = d + 1;
            if (dist[ls[f]] < dist[rs[f]]) {
                tmp = ls[f]; ls[f] = rs[f]; rs[f] = tmp;
            }
        }
    }
    up[i] = ls[i] = rs[i] = dist[i] = 0;//将这个节点的信息修正  消除信息
    return fa[s];
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    prepare();
    for(int i=1;i<=m;i++){
        int op,x,y,z;
        op=read(),x=read();
        if(op==0){
            y=read();
            remove(y);
        }
        else if(op==1){
            int h=find(x);
            printf("%lld\n",val[h]);
        }
        else if(op==2){
            y=read();
            fa[find(x)]=fa[find(y)]=merge(find(x),find(y));
        }
        else{
            y=read(),z=read();
            int h=remove(y);
            val[y]=z;
            fa[h]=fa[y]=merge(y,h);
        }
    }
    return 0;
}