#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000001;
const int MAXM = MAXN * 30;

int cnt = 0;
int head[MAXN];
int key[MAXM];
int ls[MAXM];
int rs[MAXM];
int size[MAXM];
double priority[MAXM];

int copy(int i) {
    key[++cnt] = key[i];
    ls[cnt] = ls[i];
    rs[cnt] = rs[i];
    size[cnt] = size[i];
    priority[cnt] = priority[i];
    return cnt;
}

void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + 1;
}

//根据排名分裂树
void split(int l, int r, int i, int rank) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        i = copy(i);
        if (size[ls[i]] + 1 <= rank) {
            rs[l] = i;
            split(i, r, rs[i], rank - size[ls[i]] - 1);
        } else {
            ls[r] = i;
            split(l, i, ls[i], rank);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        l = copy(l);
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        r = copy(r);
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    int n,num;
    cin >> n>>num;
    for(int i=1;i<=n;i++){
        int x,l,r;
        cin>>x;
        split(0, 0, head[0], i-1);
        l = rs[0];
        r = ls[0];
        ls[0] = rs[0] = 0;
        key[++cnt] = x;
        size[cnt] = 1;
        priority[cnt] = (double)rand() / RAND_MAX;//新增节点
        head[0] = merge(merge(l, cnt), r);
    }
    for(int i=1;i<=num;i++){
        int vision,op,x;
        cin>>vision>>op>>x;
        if(op==1){
            int y,lm,l,m,r;
            cin>>y;
            split(0,0,head[vision],x);
            lm=rs[0];
            r=ls[0];
            split(0, 0, lm, x - 1);
            l = rs[0];
            m = ls[0];
            key[m]=y;
            ls[0] = rs[0] = 0;
            head[i] = merge(merge(l, m),r);
        }
        else{
            int lm,l,r,m;
            split(0,0,head[vision],x);
            lm=rs[0];
            r=ls[0];
            split(0, 0, lm, x - 1);
            l = rs[0];
            m = ls[0];
            cout<<key[m]<<endl;
            ls[0] = rs[0] = 0;
            head[i] = merge(merge(l, m),r);
        }
    }
    return 0;
}

