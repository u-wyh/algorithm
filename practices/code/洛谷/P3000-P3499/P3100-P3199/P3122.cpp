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
// 算法标签：树状数组、凸包、二分查找
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MAXM = MAXN*20;

int n,q;

struct Point{
    int x,y;
};
Point p[MAXN];
int cntp;

struct Query{
    int op,t;
    int A,B,C;
};
Query query[MAXN];

int cnt[MAXN];
int pos[MAXN];
int used[MAXN];
int lenup[MAXN];
int lendn[MAXN];
int ord[MAXM];
int up[MAXM];
int dn[MAXM];

bool cmp(int a,int b){
    if(p[a].x!=p[b].x){
        return p[a].x<p[b].x;
    }
    return p[a].y<p[b].y;
}

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

int calc(int i,int a,int b){
    return a*p[i].x+b*p[i].y;
}

void build(){
    for(int i=1;i<=cntp;i++){
        for(int j=i;j<=cntp;j+=(j&-j)){
            cnt[j]++;
        }
    }
    for(int i=1;i<=cntp;i++){
        pos[i]=pos[i-1]+cnt[i-1];
    }
    for(int i=1;i<=cntp;i++){
        for(int j=i;j<=cntp;j+=(j&-j)){
            ord[pos[j]+(used[j]++)]=i;
        }
    }
    for(int i=1;i<=cntp;i++){
        int s=pos[i],t=pos[i]+cnt[i]-1;
        sort(ord+s,ord+t+1,cmp);
        for(int j=s;j<=t;j++){
            int x=ord[j];
            while(lenup[i]>=2 && cross(p[up[s+lenup[i]-1]]-p[up[s+lenup[i]-2]],p[x]-p[up[s+lenup[i]-2]])>=0){
                lenup[i]--;
            }
            up[s+(lenup[i]++)]=x;

            while(lendn[i]>=2 && cross(p[dn[s+lendn[i]-1]]-p[dn[s+lendn[i]-2]],p[x]-p[dn[s+lendn[i]-2]])<=0){
                lendn[i]--;
            }
            dn[s+(lendn[i]++)]=x;
        }
    }
}

int getmax(int i,int A,int B){
    int s=pos[i];
    if(B==0){
        if(A>0){
            return A*p[ord[s+cnt[i]-1]].x;
        }
        else{
            return A*p[ord[s]].x;
        }
    }
    int *h=(B>0)?up:dn;
    int l=pos[i];
    int r=pos[i]+((B>0)?lenup[i]:lendn[i])-1;
    while(l<r){
        int mid=(l+r)>>1;
        if(calc(h[mid],A,B)<calc(h[mid+1],A,B)){
            l=mid+1;
        }
        else{
            r=mid;
        }
    }
    return calc(h[l],A,B);
}

void compute(){
    for(int i=1;i<=q;i++){
        if(query[i].op==1){
            continue;
        }
        int A=query[i].A;
        int B=query[i].B;
        int C=query[i].C;
        int t=query[i].t;
        int v=calc(1,A,B);
        bool flag=(v!=C);
        if(v<C){
            for(int j=t;j&&flag;j-=(j&-j)){
                if(getmax(j,A,B)>=C){
                    flag=false;
                }
            }
        }
        else{
            for(int j=t;j&&flag;j-=(j&-j)){
                if(getmax(j,-A,-B)>=-C){
                    flag=false;
                }
            }
        }
        cout<<(flag?"YES":"NO")<<endl;
    }
}

signed main()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    cntp=n;
    for(int i=1;i<=q;i++){
        int op;
        cin>>op;
        query[i].op=op;
        if(op==1){
            cntp++;
            cin>>p[cntp].x>>p[cntp].y;
        }
        else{
            cin>>query[i].A>>query[i].B>>query[i].C;
            query[i].t=cntp;
        }
    }

    build();

    compute();

    return 0;
}