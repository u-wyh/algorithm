// https://www.luogu.com.cn/problem/P5859
// 题意：人在 (0,0)，动态支持生成线段平面镜（端坐标与不透明度 v）、摧毁第 d 个镜子、查询射线 (0,0)->(x,y) 穿过所有镜子的 v 之和
// 以及查询经过第 d 个镜子的射线能达到的最大不透明度之和。
// 输入操作数 n 及各操作；对每个 3、4 类询问输出答案（镜子已摧毁输出 oops!）。
// 数据范围：1 <= n <= 2*10^5，1 <= v <= 10^3，0 <= |x|, |y| <= 10^5，镜子总数 <= 10^5。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int INF = 1e18;

int q;
struct Query{
    int op;
    int x1,y1,x2,y2,v;
    int x,y;
    int id;
};
Query query[MAXN];

struct Point{
    int x,y;
};
Point p[MAXN<<2];
int cntp;
int m;

struct Mirror{
    Point a,b;
    int v,s,t;
    bool alive;
};
Mirror mirror[MAXN];
int cntm;

int maxx[MAXN<<3];
int tag[MAXN<<3];

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

int half(Point a){
    return (a.y>0 || (a.y==0 && a.x>0))?0:1;
}

bool cmp(Point a,Point b){
    if(half(a)!=half(b)) {
        return half(a)<half(b);
    }
    return cross(a,b)>0;
}

bool same(Point a,Point b){
    return a.x==b.x && a.y==b.y;
}

Point getPoint(int x,int y){
    int g=gcd(abs(x),abs(y));
    x/=g;
    y/=g;
    return {x,y};
}

void up(int x){
    maxx[x]=max(maxx[x<<1],maxx[x<<1|1]);
}

void lazy(int x,int v){
    maxx[x]+=v;
    tag[x]+=v;
}

void down(int x){
    if(tag[x]){
        lazy(x<<1,tag[x]);
        lazy(x<<1|1,tag[x]);
        tag[x]=0;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int ask(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return maxx[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        int ans=-INF;
        if(jobl<=mid){
            ans=max(ans,ask(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,ask(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

// 查询方向对应的离散编号
int getPos(Point a){
    return lower_bound(p+1,p+m+1,a,cmp)-p;
}

void initMirror(int id){
    Point a=mirror[id].a;
    Point b=mirror[id].b;

    int x=getPos(a);
    int y=getPos(b);

    if(cross(a,b)>0){
        mirror[id].s=x;
        mirror[id].t=y;
    }else if(cross(a,b)<0){
        mirror[id].s=y;
        mirror[id].t=x;
    }else{
        // 线段不经过原点，因此两个端点方向相同
        mirror[id].s=x;
        mirror[id].t=x;
    }
}

void compute(){
    sort(p+1,p+cntp+1,cmp);
    m=0;
    for(int i=1;i<=cntp;i++){
        if(!m || !same(p[m],p[i])){
            p[++m]=p[i];
        }
    }
    for(int i=1;i<=cntm;i++){
        initMirror(i);
    }
}

// 区间加，处理跨越极角起点的情况
void add(int s,int t,int v){
    if(s<=t){
        add(s,t,v,1,m,1);
    }else{
        add(s,m,v,1,m,1);
        add(1,t,v,1,m,1);
    }
}

// 查询镜子覆盖范围内的最大值
int ask(int s,int t){
    if(s<=t){
        return ask(s,t,1,m,1);
    }
    return max(ask(s,m,1,m,1),
               ask(1,t,1,m,1));
}

signed main()
{
    cin>>q;
    for(int i=1;i<=q;i++){
        int op;
        cin>>op;
        if(op==1){
            int x1,y1,x2,y2,v;
            cin>>x1>>y1>>x2>>y2>>v;
            query[i]={op,x1,y1,x2,y2,v};
            ++cntm;
            mirror[cntm].a=getPoint(x1,y1);
            mirror[cntm].b=getPoint(x2,y2);
            mirror[cntm].v=v;
            p[++cntp]=mirror[cntm].a;
            p[++cntp]=mirror[cntm].b;
            query[i].id=cntm;
        }
        else if(op==3){
            int x,y;
            cin>>x>>y;
            query[i].op=op;
            query[i].x=x;
            query[i].y=y;
            p[++cntp]=getPoint(x,y);
        }
        else{
            int id;
            cin>>id;
            query[i].op=op;
            query[i].id=id;
        }
    }

    compute();

    for(int i=1;i<=q;i++){
        int op=query[i].op;
        if(op==1){
            int id=query[i].id;
            mirror[id].alive=true;
            add(mirror[id].s,mirror[id].t,mirror[id].v);
        }
        else if(op==2){
            int id=query[i].id;
            mirror[id].alive=false;
            add(mirror[id].s,mirror[id].t,-mirror[id].v);
        }
        else if(op==3){
            int pos=getPos(getPoint(query[i].x,query[i].y));
            cout<<ask(pos,pos,1,m,1)<<endl;
        }
        else{
            int id=query[i].id;
            if(!mirror[id].alive){
                cout<<"oops!"<<endl;
            }
            else{
                cout<<ask(mirror[id].s,mirror[id].t)<<endl;
            }
        }
    }
    return 0;
}