// https://www.luogu.com.cn/problem/P3273
// 题意：N 个点初始互不连通，各自有权值 a_i，支持 Q 次以下 7 种操作：
// U x y（合并 x,y 连通块）、A1 x v（单点加 v）、A2 x
// v（连通块加 v）、A3 v（全局加 v）。
// F1 x（查单点值）、F2 x（查连通块最大值）、F3（查全局最大值）。
// 逐行输出所有查询操作的结果。
// 数据范围：
// 1 <= N <= 3*10^5（点数）
// 1 <= Q <= 3*10^5（操作数）
// -1000 <= v,
// a_1..a_N <= 1000（初始权值与增量，保证输入合法）
// 难度评分：2600（洛谷分级换算）
// 算法标签：左偏树、并查集、启发式合并
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n,m;

int val[MAXN];
int up[MAXN];
int ls[MAXN];
int rs[MAXN];
int dis[MAXN];

int fa[MAXN];
int sz[MAXN];
int add[MAXN];
int sta[MAXN];

multiset<int>head;
int addall;

void minushead(int h){
    if(h){
        head.erase(head.find(val[h]+add[h]));
    }
}

void addhead(int h){
    if(h){
        head.insert(val[h]+add[h]);
    }
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void prepare() {
    dis[0] = -1;
    for (int i = 1; i <= n; i++) {
        up[i] = ls[i] = rs[i] = dis[i] = 0;
        fa[i] = i;
        sz[i] = 1;
        add[i] = 0;
        addhead(i);//自己一个节点是一个集合  直接加到有序表中
    }
    addall = 0;
}

int merge(int i,int j){
    if (i == 0 || j == 0) return i + j;
    if (val[i] < val[j]) {
        swap(i, j);
    }
    rs[i] = merge(rs[i], j);
    up[rs[i]] = i;
    if (dis[ls[i]] < dis[rs[i]]) {
        swap(ls[i], rs[i]);
    }
    dis[i] = dis[rs[i]] + 1;
    fa[ls[i]] = i;
    fa[rs[i]] = i;
    return i;
}

int remove(int i) {
    int h = find(i);
    fa[ls[i]] = ls[i];
    fa[rs[i]] = rs[i];
    int s = merge(ls[i], rs[i]);
    int f = up[i];
    fa[i] = s;
    up[s] = f;
    if (h != i) {
        fa[s] = h;
        if (ls[f] == i) {
            ls[f] = s;
        } else {
            rs[f] = s;
        }
        for (int d = dis[s]; dis[f] > d + 1; f = up[f], d++) {
            dis[f] = d + 1;
            if (dis[ls[f]] < dis[rs[f]]) {
                swap(ls[f], rs[f]);
            }
        }
    }
    up[i] = ls[i] = rs[i] = dis[i] = 0;
    return fa[s];
}

void down(int i,int v){
    if(i){
        // add[i]=0;
        int size=0;
        sta[++size]=i;
        while(size){
            i=sta[size--];
            val[i]+=v;
            if(rs[i]){
                sta[++size]=rs[i];
            }
            if(ls[i]){
                sta[++size]=ls[i];
            }
        }
    }
}

void un(int i,int j){
    int l=find(i);
    int r=find(j);
    if(l==r){
        return ;
    }
    int lsz=sz[l];
    int rsz=sz[r];
    minushead(l);
    minushead(r);
    int addtag;
    if(lsz<=rsz){
        down(l,add[l]-add[r]);
        addtag=add[r];
    }
    else{
        down(r,add[r]-add[l]);
        addtag=add[l];
    }
    int h=merge(l,r);
    sz[h]=rsz+lsz;
    add[h]=addtag;
    addhead(h);    
}

void a1(int x,int v){
    int h=find(x);
    minushead(h);
    int l=remove(x);
    if(l){
        sz[l]=sz[h]-1;
        add[l]=add[h];
        addhead(l);
    }
    val[x]=val[x]+add[h]+v;
    fa[x]=x;
    sz[x]=1;
    add[x]=0;
    addhead(x);
    un(l,x);
}

void a2(int x,int v){
    int h=find(x);
    minushead(h);
    add[h]+=v;
    addhead(h);
}

void a3(int v){
    addall+=v;
}

int f1(int x){
    return val[x]+add[find(x)]+addall;
}

int f2(int x){
    int h=find(x);
    return val[h]+add[h]+addall;
}

int f3(){
    return (*head.rbegin())+addall;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    prepare();
    cin>>m;
    for(int i=1;i<=m;i++){
        string op;
        cin>>op;
        if(op=="F3"){
            cout<<f3()<<endl;
        }
        else{
            int x;
            cin>>x;
            if(op=="U"){
                int y;
                cin>>y;
                un(x,y);
            }
            else if(op=="A1"){
                int y;
                cin>>y;
                a1(x,y);
            }
            else if(op=="A2"){
                int y;
                cin>>y;
                a2(x,y);
            }
            else if(op=="A3"){
                a3(x);
            }
            else if(op=="F1"){
                cout<<f1(x)<<endl;
            }
            else{
                cout<<f2(x)<<endl;
            }
        }
    }
    return 0;
}