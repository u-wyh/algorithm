// 用途：离线查询静态数组区间内不同数的数量。
// 时间：排序 O(q log q)，移动约 O((n+q)√n)。
// 空间：O(n+q+V)。
// 注意：值域 1..1e6，n<=3e4。
// 例题：https://www.luogu.com.cn/problem/SP3267
// 题意：静态数组多次查询区间不同数个数。
// 思路：按块排序询问，移动左右端点并维护各值出现次数。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 30001;
const int MAXV = 1000001;
const int MAXQ = 200001;

struct Query {
    int l, r, id;
};

int n, q;
int arr[MAXN];
Query query[MAXQ];

int bi[MAXN];
int cnt[MAXV];
int kind = 0;

int ans[MAXQ];

bool QueryCmp1(Query &a, Query &b) {
    if (bi[a.l] != bi[b.l]) {
        return bi[a.l] < bi[b.l];
    }
    return a.r < b.r;
}

bool QueryCmp2(Query &a, Query &b) {
    if (bi[a.l] != bi[b.l]) {
        return bi[a.l] < bi[b.l];
    }
    if ((bi[a.l] & 1) == 1) {
        return a.r < b.r;
    } else {
        return a.r > b.r;
    }
}

void del(int num) {
    if (--cnt[num] == 0) {
        kind--;
    }
}

void add(int num) {
    if (++cnt[num] == 1) {
        kind++;
    }
}

void prepare() {
    int blen = (int)sqrt(n);
    for (int i = 1; i <= n; i++) {
        bi[i] = (i - 1) / blen + 1;
    }
    sort(query + 1, query + q + 1, QueryCmp2);
}

// 按排好序的查询移动左右端点，计数只在频次过零时改变。
void compute() {
    int winl = 1, winr = 0;
    for (int i = 1; i <= q; i++) {
        int jobl = query[i].l;
        int jobr = query[i].r;
        while (winl > jobl) {
            add(arr[--winl]);
        }
        while (winr < jobr) {
            add(arr[++winr]);
        }
        while (winl < jobl) {
            del(arr[winl++]);
        }
        while (winr > jobr) {
            del(arr[winr--]);
        }
        ans[query[i].id] = kind;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> query[i].l;
        cin >> query[i].r;
        query[i].id = i;
    }
    prepare();
    compute();
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}
