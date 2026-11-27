// https://www.luogu.com.cn/problem/P8856
// 题意：输入站点数 C（1 号开往 C 号）、列车总座位数 S 和依次处理的订票请
// 求数 R
// 每个请求 (O, D, N) 要求在区间 [O, D) 的每一站都留有
// 至少 N 个空座；
// 按顺序若可满足则占用座位并输出 T，否则不修改并输出 N。
// 数据范围：
// 1 <= C, S,
// R <= 60000（未单独标注 O, D, N 的范围）。
// 算法标签：线段树
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 60005;

int Max[MAXN << 2];
int add[MAXN << 2];
int n,m,s;

void up(int i) {
    Max[i] = max(Max[i << 1] ,Max[i << 1 | 1]);
}

void lazy(int i, long v) {
    Max[i] += v;
    add[i] += v;
}

void down(int i) {
    if (add[i] != 0) {
        // 发左
        lazy(i << 1, add[i]);
        // 发右
        lazy(i << 1 | 1, add[i]);
        // 父范围懒信息清空
        add[i] = 0;
    }
}

void build(int l, int r, int i) {
    if (l == r) {
        Max[i] = 0;
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    add[i]=0;
}

void Add(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv);
    } else {
        int mid = (l + r) >> 1;
        down(i);
        if (jobl <= mid) {
            Add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            Add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

int query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return Max[i];
    }
    int mid = (l + r) >> 1;
    down(i);
    int ans = 0;
    if (jobl <= mid) {
        ans =max(ans, query(jobl, jobr, l, mid, i << 1));
    }
    if (jobr > mid) {
        ans =max(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
    }
    return ans;
}

int main()
{
    cin>>n>>s>>m;
    build(1,n,1);
    for (int i = 1, jobv, jobl, jobr; i <= m; i++) {
        cin>>jobl>>jobr>>jobv;
        jobr--;
        if(query(jobl,jobr,1,n,1)+jobv>s){
            cout<<'N'<<endl;
        }else{
            cout<<'T'<<endl;
            Add(jobl,jobr,jobv,1,n,1);
        }
    }
    return 0;
}

