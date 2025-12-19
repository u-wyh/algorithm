#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXE = 4e5+5;
const int INF = 1e9+5;

int n,m;

int arr[MAXN];

// 事件编号组成的数组
int eid[MAXE];
// op == 1，代表修改事件，x处，值y，效果v
// op == 2，代表查询事件，[x..y]范围上查询第v小，q表示问题的编号
int op[MAXE];
int x[MAXE];
int y[MAXE];
int v[MAXE];
int q[MAXE];
int cnte = 0;
int cntq = 0;//辅助填写ans数组

// 树状数组
int tree[MAXN];

// 整体二分
int lset[MAXE];
int rset[MAXE];

// 查询的答案
int ans[MAXN];

inline int lowbit(int x){
    return x&(-x);
}

void add(int i,int v){
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
    }
}

int sum(int i){
    int ans=0;
    while(i){
        ans+=tree[i];
        i-=lowbit(i);
    }
    return ans;
}

int query(int l,int r){
    return sum(r)-sum(l-1);
}

void compute(int el,int er,int vl,int vr){
    if(el>er){
        return ;
    }
    if(vl==vr){
        for(int i=el;i<=er;i++){
            int id=eid[i];
            if(op[id]==2){
                ans[q[id]]=vl;
            }
        }
    }
    else{
        int mid=(vl+vr)>>1;
        int lsz=0,rsz=0;
        for(int i=el;i<=er;i++){
            int id=eid[i];
            if(op[id]==1){
                if(y[id]<=mid){
                    add(x[id],v[id]);
                    lset[++lsz]=id;
                }
                else{
                    rset[++rsz]=id;
                }
            }
            else{
                int tmp=query(x[id],y[id]);
                if(v[id]<=tmp){
                    lset[++lsz]=id;
                }
                else{
                    v[id]-=tmp;
                    rset[++rsz]=id;
                }
            }
        }
        for (int i = 1; i <= lsz; i++) {
            eid[el + i - 1] = lset[i];
        }
        for (int i = 1; i <= rsz; i++) {
            eid[el + lsz + i - 1] = rset[i];
        }
        //还原操作
        for (int i = 1; i <= lsz; i++) {
            int id = lset[i];
            if (op[id] == 1 && y[id] <= mid) {
                add(x[id], -v[id]);
            }
        }
        compute(el, el + lsz - 1, vl, mid);
        compute(el + lsz, er, mid + 1, vr);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        op[++cnte]=1;
        x[cnte]=i;
        y[cnte]=arr[i];
        v[cnte]=1;
    }
    for(int i=1;i<=m;i++){
        char c;
        cin>>c;
        if(c=='C'){
            int v1,v2;
            cin>>v1>>v2;

            op[++cnte]=1;
            x[cnte]=v1;
            y[cnte]=arr[v1];
            v[cnte]=-1;

            op[++cnte]=1;
            x[cnte]=v1;
            y[cnte]=v2;
            v[cnte]=1;
            arr[v1]=v2;
        }
        else{
            op[++cnte]=2;
            cin>>x[cnte]>>y[cnte]>>v[cnte];
            q[cnte]=++cntq;
        }
    }
    for(int i=1;i<=cnte;i++){
        eid[i]=i;
    }
    compute(1,cnte,0,INF);
    for(int i=1;i<=cntq;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}