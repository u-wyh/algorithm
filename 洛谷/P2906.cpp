#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int INF = 1e10;

int n,c;
int fa[MAXN];
int sz[MAXN];

struct node{
    int x,y,id;
    bool operator<(const node&other)const{
        return y<other.y;
    }
};
node nums[MAXN];
multiset<node>s;

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

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        sz[fx]+=sz[fy];
        fa[fy]=fx;
    }
}

bool cmp(node a,node b){
    return a.x<b.x;
}

void compute(){
    sort(nums+1,nums+n+1,cmp);

    s.insert(nums[1]);

    node tmp={0,INF,0};
    s.insert(tmp);
    tmp.y=-INF;
    s.insert(tmp);

    int head=1;
    for(int i=2;i<=n;i++){
        while(nums[i].x-nums[head].x>c){
            s.erase(s.find(nums[head]));
            head++;
        }
        auto it=s.lower_bound(nums[i]);
        tmp=*it;
        if(tmp.y-nums[i].y<=c){
            un(tmp.id,nums[i].id);
        }
        tmp=*(--it);
        if(nums[i].y-tmp.y<=c){
            un(tmp.id,nums[i].id);
        }
        s.insert(nums[i]);
    }
}

signed main()
{
    n=read(),c=read();
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }
    for(int i=1;i<=n;i++){
        int x,y;
        x=read(),y=read();
        nums[i]={x+y,x-y,i};
    }
    compute();
    int ans=0,maxx=0;
    for(int i=1;i<=n;i++){
        if(i==find(i)){
            ans++;
            maxx=max(maxx,sz[i]);
        }
    }
    cout<<ans<<' '<<maxx<<endl;
    return 0;
}