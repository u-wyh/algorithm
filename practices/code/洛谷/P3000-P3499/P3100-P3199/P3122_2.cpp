// https://www.luogu.com.cn/problem/P3122
// 题意：输入初始牛群数 n、操作数 q，以及初始 n 个点的坐标 (x, y)。
// 操作 1 x y 新加入一个位于 (x, y) 的牛群；
// 操作 2 A B C 询问当前所有牛群是否都严格位于直线 Ax+By=C
// 的同一侧（不能有牛在直线上）。
// 对每个操作 2 输出 YES 或 NO。
// 每个 2 类询问输出一行 YES 或 NO。
// 数据范围：1 <= n, q <= 10^5，
// -10^9 <= x, y, A, B <= 10^9，
// -10^18 <= C <= 10^18，点互不相同
// A 与 B 不同时为 0。
// 难度评分：2500（洛谷分级换算）
// 算法标签：线段树、凸包、二分查找
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MAXV = MAXN<<2;
const int MAXM = MAXN*20;
const int INF = 4e18;

int n,q,m;

struct Point{
    int x,y;
};
Point p[MAXN];

struct Query{
    int op,t;
    int A,B,C;
};
Query query[MAXN];

Point up[MAXM];
Point dn[MAXM];
int uplen;
int dnlen;
int stup[MAXV],enup[MAXV];
int stdn[MAXV],endn[MAXV];

Point temp[MAXN];

int calc(Point p,int a,int b){
    return a*p.x+b*p.y;
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

bool cmp(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

void build(int l,int r,int i){
    for(int i=l;i<=r;i++){
        temp[i-l+1]=p[i];
    }
    int len=r-l+1;
    sort(temp+1,temp+len+1,cmp);

    stup[i]=uplen+1,stdn[i]=dnlen+1;
    int upnow=uplen,dnnow=dnlen;
    for(int i=1;i<=len;i++){
        while(uplen>=upnow+2 && cross(up[uplen]-up[uplen-1],temp[i]-up[uplen-1])>=0){
            uplen--;
        }
        up[++uplen]=temp[i];
        while(dnlen>=dnnow+2 && cross(dn[dnlen]-dn[dnlen-1],temp[i]-dn[dnlen-1])<=0){
            dnlen--;
        }
        dn[++dnlen]=temp[i];
    }
    enup[i]=uplen,endn[i]=dnlen;

    if(l!=r){
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

int compute(int x,int l,int r,int a,int b){
    if(b==0){
        if(a>0){
            return a*up[enup[x]].x;
        }
        else{
            return a*up[stup[x]].x;
        }
    }
    Point *h=(b>0)?up:dn;
    int lt=(b>0)?stup[x]:stdn[x];
    int rt=(b>0)?enup[x]:endn[x];
    while(lt<rt){
        int mid=(lt+rt)>>1;
        if(calc(h[mid],a,b)<calc(h[mid+1],a,b)){
            lt=mid+1;
        }
        else{
            rt=mid;
        }
    }
    return calc(h[lt],a,b);
}

int ask(int jobl,int jobr,int a,int b,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return compute(i,l,r,a,b);
    }
    else{
        int mid=(l+r)>>1;
        int ans=-INF;
        if(jobl<=mid){
            ans=max(ans,ask(jobl,jobr,a,b,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,ask(jobl,jobr,a,b,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

signed main()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    m=n;
    for(int i=1;i<=q;i++){
        int op;
        cin>>op;
        if(op==1){
            ++m;
            cin>>p[m].x>>p[m].y;
        }
        else{
            cin>>query[i].A>>query[i].B>>query[i].C;
            query[i].t=m;
        }
        query[i].op=op;
    }

    build(1,m,1);

    for(int i=1;i<=q;i++){
        if(query[i].op==1){
            continue;
        }
        int A=query[i].A;
        int B=query[i].B;
        int C=query[i].C;
        int t=query[i].t;
        int v=calc(p[1],A,B);
        bool flag=(v!=C);
        if(!flag){
            cout<<"NO"<<endl;
            continue;
        }
        if(v<C){
            int v=ask(1,t,A,B,1,m,1);
            flag=(v<C);
        }
        else{
            int v=ask(1,t,-A,-B,1,m,1);
            flag=(v<-C);
        }
        cout<<(flag?"YES":"NO")<<endl;
    }
    return 0;
}