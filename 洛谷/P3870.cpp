#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int sum[MAXN << 2];
bool update[MAXN << 2];
int n,m;

// 累加和信息的汇总
void up(int i) {
    // 父范围的累加和 = 左范围累加和 + 右范围累加和
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
}

void lazy(int i,  int n) {
    sum[i] = n - sum[i];
    update[i] = !update[i];
}

// 懒信息的下发
void down(int i, int ln, int rn) {
    if (update[i]) {
        lazy(i << 1, ln);
        lazy(i << 1 | 1, rn);
        update[i] = false;
    }
}

void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = 0;
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    update[i] = false;
}

void Update(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, r - l + 1);
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) {
            Update(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
            Update(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

long query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    long ans = 0;
    if (jobl <= mid) {
        ans += query(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans += query(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    build(1,n,1);
    for (int i = 1, op, jobl, jobr; i <= m; i++) {
        cin>>op;
        if (op == 0) {
            cin>>jobl;
            cin>>jobr;
            Update(jobl, jobr, 1, n, 1);
        } else {
            cin>>jobl;
            cin>>jobr;
            cout<<query(jobl, jobr, 1, n, 1)<<endl;
        }
    }
    return 0;
}
