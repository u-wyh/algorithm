#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n,m;
int fa[MAXN];
int cnt[MAXN];
int father[MAXN];
int ans[MAXN];

struct node{
    int x,y,t;
};
node pos[MAXN<<1];

set<pair<int,int>>s;

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

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

bool cmp(node a,node b){
    if(a.y!=b.y){
        return a.y>b.y;
    }
    return a.t>b.t;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        pos[i].x=read();
        pos[i].y=read();
        pos[i].t=0;
    }
    m=read();
    for(int i=1;i<=m;i++){
        pos[i+n].x=read();
        pos[i+n].y=read();
        pos[i+n].t=i;
    }
    sort(pos+1,pos+n+m+1,cmp);
    for(int i=1;i<=n+m;i++){
        if(pos[i].t==0){
            auto it=s.lower_bound({pos[i].x,0});
            if(it!=s.end()){
                cnt[it->second]++;
            }
        }
        else{
            int t=pos[i].t;
            auto it=s.lower_bound({pos[i].x,t});
            if(it!=s.end()){
                father[t]=it->second;
            }
            else{
                father[t]=0;
            }
            s.insert({pos[i].x,t});
            it=s.find({pos[i].x,t});
            if(it!=s.begin()){
                it--;
                while(true){
                    if(it->second>t){
                        it=s.erase(it);
                        if(it==s.begin()){
                            break;
                        }
                        it--;
                    }
                    else{
                        break;
                    }
                }
            }
        }
    }

    for(int i=1;i<=m;i++){
        fa[i]=i;
    }

    for(int i=m;i>=1;i--){
        ans[i]=cnt[i];
        if(father[i]){
            int x=find(i);
            int y=find(father[i]);
            fa[x]=y;
            cnt[y]+=cnt[x];
        }
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}