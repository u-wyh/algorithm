// https://www.luogu.com.cn/problem/P15005
// 题意：动态删边与减少点权，求两点所在连通块点权和之和 >= z 的最晚时刻。
// 输入：首行 n, m, d, s，次行点权 a_i，后 m 行边，d 行事件，
// s 行询问。
// 规则：事件 1 删边；事件 2 点 w 权减 k；点幸福值为所在连通块点权之和。
// 输出：对每个询问 (x, y, z)，
// 输出幸福值和 >= z 的最后天数（0..d 或 -1）。
// 数据范围：1 <= n, m, d, s <= 2*10^5，
// 1 <= a_i, k_i, z_i <= 10^9。
// 数据范围：无重边，任意时刻各点点权至少为 1。
// 难度评分：2700（洛谷分级换算）
// 算法标签：整体二分、可撤销并查集
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,m,d,s;

int val[MAXN];

int u[MAXN];
int v[MAXN];
int ok[MAXN];
map<pair<int,int>,int>mp;

int op[MAXN];
int x[MAXN];
int y[MAXN];

int qx[MAXN];
int qy[MAXN];
int qz[MAXN];

int ans[MAXN];

int qid[MAXN];
int lset[MAXN];
int rset[MAXN];

int fa[MAXN];
int sz[MAXN];
int sum[MAXN];

struct node{
    int op;
    int x,y,z;
    int all;
};
node rollback[MAXN*4];
int opsize;

int find(int x){
    while(x!=fa[x]){
        x=fa[x];
    }
    return x;
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        if(sz[fx]>sz[fy]){
            swap(fx,fy);
        }
        rollback[++opsize]={1,fx,fy,sz[fy],sum[fy]};
        fa[fx]=fy;
        sz[fy]+=sz[fx];
        sum[fy]+=sum[fx];
    }
}

void add(int x,int val){
    int fx=find(x);
    rollback[++opsize]={2,fx,0,0,sum[fx]};
    sum[fx]+=val;
}

void undo(){
    if(rollback[opsize].op==1){
        fa[rollback[opsize].x]=rollback[opsize].x;
        sz[rollback[opsize].y]=rollback[opsize].z;
        sum[rollback[opsize].y]=rollback[opsize].all;
    }
    else{
        sum[rollback[opsize].x]=rollback[opsize].all;
    }
    opsize--;
}

void event(int day){
    if(op[day]==1){
        un(x[day],y[day]);
    }
    else{
        add(x[day],y[day]);
    }
}

bool check(int id){
    return sum[find(qx[id])]+sum[find(qy[id])]>=qz[id];
}

void compute(int ql,int qr,int vl,int vr){
    if(ql>qr){
        return ;
    }
    if(vl==vr){
        for(int i=ql;i<=qr;i++){
            ans[qid[i]]=vl;
        }
        return ;
    }

    int mid=(vl+vr+1)/2;
    int snapshot=opsize;

    for(int day=vr;day>mid;day--){
        event(day);
    }

    int lsz=0,rsz=0;
    for(int i=ql;i<=qr;i++){
        int id=qid[i];

        if(check(id)){
            rset[++rsz]=id;
        }
        else{
            lset[++lsz]=id;
        }
    }
    
    for (int i = 1; i <= lsz; i++) {
        qid[ql + i - 1] = lset[i];
    }

    for (int i = 1; i <= rsz; i++) {
        qid[ql + lsz + i - 1] = rset[i];
    }

    int snapshot2=opsize;
    if(lsz){
        if(mid>0){
            event(mid);
        }
        compute(ql,ql+lsz-1,vl,mid-1);
        while(opsize!=snapshot2){
            undo();
        }
    }
    while(opsize!=snapshot){
        undo();
    }
    if(rsz){
        compute(ql+lsz,qr,mid,vr);
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>d>>s;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i];
        if(u[i]>v[i]){
            swap(u[i],v[i]);
        }
        mp[{u[i],v[i]}]=i;
        ok[i]=true;
    }

    for(int i=1;i<=d;i++){
        cin>>op[i]>>x[i]>>y[i];
        if(op[i]==1){
            if(x[i]>y[i]){
                swap(x[i],y[i]);
            }
            ok[mp[{x[i],y[i]}]]=false;
        }
        else{
            val[x[i]]-=y[i];
        }
    }

    for(int i=1;i<=s;i++){
        cin>>qx[i]>>qy[i]>>qz[i];
        qid[i]=i;
    }

    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
        sum[i]=val[i];
    }
    for(int i=1;i<=m;i++){
        if(ok[i]){
            un(u[i],v[i]);
        }
    }

    compute(1,s,-1,d);

    for(int i=1;i<=s;i++){
        cout<<ans[i]<<endl;
    }

    return 0;
}