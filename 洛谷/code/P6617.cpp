#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n, m, w;
int val[MAXN];
set<int> pos[MAXN];
int tree[MAXN<<2];

inline int read() {
    int x=0, f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

void up(int i) {
    tree[i] = max(tree[i<<1], tree[i<<1|1]);
}

void build(int l, int r, int i) {
    if(l == r) {
        tree[i] = 0;
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i<<1);
        build(mid+1, r, i<<1|1);
        up(i);
    }
}

void update(int pos, int jobv, int l, int r, int i) {
    if(l == r) {
        tree[i] = jobv;
    } else {
        int mid = (l + r) >> 1;
        if(pos <= mid) {
            update(pos, jobv, l, mid, i<<1);
        } else {
            update(pos, jobv, mid+1, r, i<<1|1);
        }
        up(i);
    }
}

int query(int jobl, int jobr, int l, int r, int i) {
    if(jobl <= l && r <= jobr) {
        return tree[i];
    } else {
        int mid = (l + r) >> 1;
        int ans = 0;
        if(jobl <= mid) {
            ans = max(ans, query(jobl, jobr, l, mid, i<<1));
        }
        if(jobr > mid) {
            ans = max(ans, query(jobl, jobr, mid+1, r, i<<1|1));
        }
        return ans;
    }
}

int get_pre(int i) {
    int v = val[i];
    int need = w - v;
    if (need < 0 || need > w) return 0;
    
    int k = 0;
    auto it_v = pos[v].lower_bound(i);
    if (it_v != pos[v].begin()) {
        it_v--;
        k = *it_v;
    }
    
    int j = 0;
    auto it_need = pos[need].lower_bound(i);
    if (it_need != pos[need].begin()) {
        it_need--;
        j = *it_need;
    }
    
    if (j == 0) return 0;
    if (j >= k) return j;
    else return 0;
}

int main() {
    n = read(), m = read(), w = read();
    for (int i = 1; i <= n; i++) {
        val[i] = read();
    }
    
    build(1, n, 1);
    
    for (int i = 1; i <= n; i++) {
        int pre_val = get_pre(i);
        update(i, pre_val, 1, n, 1);
        pos[val[i]].insert(i);
    }
    
    int cnt = 0;
    for (int i = 1; i <= m; i++) {
        int op, x, y;
        op = read(), x = read(), y = read();
        if (op == 1) {
            int old_val = val[x];
            int new_val = y;
            set<int> affected;
            affected.insert(x);
            
            auto it = pos[old_val].upper_bound(x);
            if (it != pos[old_val].end()) {
                affected.insert(*it);
            }
            
            it = pos[w - old_val].upper_bound(x);
            if (it != pos[w - old_val].end()) {
                affected.insert(*it);
            }
            
            pos[old_val].erase(x);
            val[x] = new_val;
            pos[new_val].insert(x);
            
            it = pos[new_val].upper_bound(x);
            if (it != pos[new_val].end()) {
                affected.insert(*it);
            }
            
            it = pos[w - new_val].upper_bound(x);
            if (it != pos[w - new_val].end()) {
                affected.insert(*it);
            }
            
            for (int p : affected) {
                int new_pre = get_pre(p);
                update(p, new_pre, 1, n, 1);
            }
        } else {
            int l = x ^ cnt;
            int r = y ^ cnt;
            if (l > r) swap(l, r);
            if (l < 1) l = 1;
            if (r > n) r = n;
            int max_pre = query(l, r, 1, n, 1);
            if (max_pre >= l) {
                printf("Yes\n");
                cnt++;
            } else {
                printf("No\n");
            }
        }
    }
    return 0;
}