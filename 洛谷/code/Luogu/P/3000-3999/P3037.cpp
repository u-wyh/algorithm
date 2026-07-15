#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e4+5;
const int MAXM = 1e5+5;
const int MAXW = 1e6+5;
const int MOD = 1e9+7;

int n,m;
int fa[MAXN];
int sz[MAXN];
int uncnt[MAXW];
long long ans1,ans2=1;

int rollback[MAXN][2];
int rollsz;

struct Edge{
    int u,v,w;
};
Edge edge[MAXM];

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

bool cmp(Edge a,Edge b){
    return a.w<b.w;
}

int find(int i){
    while(i!=fa[i]){
        i=fa[i];
    }
    return i;
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(sz[fx]<sz[fy]){
        swap(fx,fy);
    }
    fa[fy]=fx;
    sz[fx]+=sz[fy];
    rollback[++rollsz][0]=fx;
    rollback[rollsz][1]=fy;
}

void undo(){
    int fx=rollback[rollsz][0];
    int fy=rollback[rollsz--][1];
    fa[fy]=fy;
    sz[fx]-=sz[fy];
}

void compute1(){
    for(int i=1;i<=m;){
        int j=i;
        while(j+1<=m&&edge[j+1].w==edge[i].w){
            j++;
        }
        for(int k=i;k<=j;k++){
            int x=find(edge[k].u);
            int y=find(edge[k].v);
            int w=edge[k].w;
            if(x!=y){
                un(x,y);
                uncnt[w]++;
                ans1=(ans1+w)%MOD;
            }
        }
        i=j+1;
    }
}

int compute(int e,int s,int len){
    // cout<<' '<<e<<' '<<s<<' '<<len<<endl;
    int one=0;
    for(int i=0;i<len;i++){
        if(s&(1<<i)){
            one++;
        }
    }
    if(one!=uncnt[edge[e].w]){
        return 0;
    }
    int ans=0;
    for(int i=0;i<len;i++){
        if(s&(1<<i)){
            int id=e+i;
            // cout<<s<<"    "<<id<<endl;
            int x=find(edge[id].u);
            int y=find(edge[id].v);
            if(x!=y){
                un(x,y);
                ans++;
            }
        }
    }
    int tmp=ans;
    while(tmp--){
        undo();
    }
    return ans;
}

void compute2(){
    rollsz=0;
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }

    for(int i=1;i<=m;){
        int j=i;
        while(j+1<=m&&edge[j+1].w==edge[i].w){
            j++;
        }
        if(uncnt[edge[i].w]==0||uncnt[edge[i].w]==(j-i+1)){
            for(int k=i;k<=j;k++){
                int x=find(edge[k].u);
                int y=find(edge[k].v);
                if(x!=y){
                    un(x,y);
                }
            }
            i=j+1;
            continue;
        }
        int tmp=0;
        for(int k=1;k<=(1<<(j-i+1))-2;k++){
            if(compute(i,k,(j-i+1))==uncnt[edge[i].w]){
                tmp++;
                // cout<<' '<<k<<endl;
            }
        }
        ans2=(ans2*tmp)%MOD;

        for(int k=i;k<=j;k++){
            int x=find(edge[k].u);
            int y=find(edge[k].v);
            if(x!=y){
                un(x,y);
            }
        }
        i=j+1;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        edge[i].u=read();
        edge[i].v=read();
        edge[i].w=read();
    }
    sort(edge+1,edge+m+1,cmp);

    for(int i=1;i<=n;i++){
        fa[i]=i,sz[i]=1;
    }
    compute1();
    // cout<<' '<<uncnt[1]<<endl;
    // cout<<' '<<uncnt[2]<<endl;
    compute2();
    cout<<ans1<<' '<<ans2<<endl;
    return 0;
}