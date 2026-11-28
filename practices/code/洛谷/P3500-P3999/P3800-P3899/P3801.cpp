// https://www.luogu.com.cn/problem/P3801
// 题意：第一行输入矩阵大小 n, m 和操作数 q，初始 n*m 网格全无红雾。
// 接下来 q 行操作：
// 1 x y 表示在 (x, y)
// 向四个方向释放无限长红雾
// （影响整行与整列但不影响 (x, y) 本身，两阵红雾碰撞则消失
// 即对应格状态翻转）；
// 2 x1 y1 x2 y2 查询左上角 (x1, y1) 到右下角
// (x2, y2) 的矩形内被红雾遮盖的格子数。
// 对每个操作 2 输出一行一个整数。
// 数据范围：对于 100% 的数据，1 <= n, m, q <= 10^5，
// 1 <= x1 <= x2 <= n，1 <= y1 <= y2 <= m
// 1 <= x <= n，1 <= y <= m。
// 难度评分：1700（洛谷分级换算）
// 算法标签：线段树、容斥原理
#include<bits/stdc++.h>
using namespace std;

int n,m,q;
int xsum[100005],ysum[100005];

void xup(int i) {
    xsum[i] = xsum[i << 1] + xsum[i << 1 | 1];
}

void xUpdate(int jobl, int l, int r, int i) {
    if (l==r) {
        xsum[i]^=1;
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            xUpdate(jobl, l, mid, i << 1);
        }else {
            xUpdate(jobl, mid + 1, r, i << 1 | 1);
        }
        xup(i);
    }
}

int xquery(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return xsum[i];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if (jobl <= mid) {
        ans += xquery(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans += xquery(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

void yup(int i) {
    ysum[i] = ysum[i << 1] + ysum[i << 1 | 1];
}

void yUpdate(int jobl, int l, int r, int i) {
    if (l==r) {
        ysum[i]^=1;
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            yUpdate(jobl, l, mid, i << 1);
        }else {
            yUpdate(jobl, mid + 1, r, i << 1 | 1);
        }
        yup(i);
    }
}

int yquery(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return ysum[i];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if (jobl <= mid) {
        ans += yquery(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans += yquery(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

int main()
{
    cin>>n>>m>>q;
    for(int i=1;i<=q;i++){
        int op,x,y,x1,y1;
        cin>>op;
        if(op==1){
            cin>>x>>y;
            xUpdate(x,1,n,1);
            yUpdate(y,1,n,1);
        }else{
            cin>>x>>y>>x1>>y1;
            cout<<xquery(x,x1,1,n,1)*(y1-y+1)+yquery(y,y1,1,n,1)*(x1-x+1)-2*xquery(x,x1,1,n,1)*yquery(y,y1,1,n,1)<<endl;
        }
    }
    return 0;
}
