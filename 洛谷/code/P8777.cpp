// https://www.luogu.com.cn/problem/P8777
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int INF = 4000000000000000000LL+1;
const int INF2 = 2e9;

int n,len;

struct Point{
    int x,y,z;
    int d;
    int id;
};
Point p[MAXN];
int cntp;

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;
int cur[MAXN];

int ans[MAXN];
int cnt;
int lst;

int tree[MAXN<<2];

int quadrant(Point a){
    if(a.x>=0&&a.y>0){
        return 1;
    }
    else if(a.x>0&&a.y<=0){
        return 2;
    }
    else if(a.x<=0&&a.y<0){
        return 3;
    }
    else{
        return 4;
    }
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

bool cmp(Point a,Point b){
    int qa=quadrant(a);
    int qb=quadrant(b);
    if(qa!=qb){
        return qa<qb;
    }
    int v=cross(a,b);
    if(v==0){
        // 链式前向星建图  所以距离大的放在前面
        return (a.x*a.x+a.y*a.y)>(b.x*b.x+b.y*b.y);
    }
    return v<0;
}

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void up(int x){
    tree[x]=min(tree[x<<1],tree[x<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=p[to[head[l]]].d;
        cur[l]=head[l];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(tree[i]>len*len){
        return -1;
    }
    if(l==r){
        int now=cnt+1;
        for(int e=cur[l];e!=-1;e=nxt[e]){
            cur[l]=e;
            if(e==0){
                break;
            }
            int v=to[e];
            if(p[v].d<=len*len){
                cnt++;
                ans[p[v].id]=now;
                len=min(INF2,len+p[v].z);
            }
            else{
                break;
            }
        }
        if(cur[l]==0){
            tree[i]=INF;
        }else{
            tree[i]=p[to[cur[l]]].d;
        }
        return l;
    }
    else{
        int mid=(l+r)>>1;
        int ans=-1;
        if(jobl<=mid){
            ans=query(jobl,jobr,l,mid,i<<1);
        }
        if(ans==-1 &&jobr>mid){
            ans=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        up(i);
        return ans;
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>len;
    for(int i=1;i<=n;i++){
        ans[i]=-1;
        int x,y,z;
        cin>>x>>y>>z;
        if(x==0&&y==0){
            y=1;
        }
        p[++cntp]={x,y,z,x*x+y*y,i};
    }
    sort(p+1,p+cntp+1,cmp);
    int cntm=0;
    for(int i=1;i<=cntp;i++){
        if(i==1|| quadrant(p[i])!=quadrant(p[i-1]) || cross(p[i],p[i-1])!=0){
            ++cntm;
        }
        addedge(cntm,i);
    }
    build(1,cntm,1);
    lst=1;
    while(true){
        int now=query(lst,cntm,1,cntm,1);
        if(now==-1 &&lst>1){
            now=query(1,lst-1,1,cntm,1);
        }
        if(now==-1){
            break;
        }
        lst=now;
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}