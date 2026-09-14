#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using ULL = unsigned long long;
using i128 = __int128_t;

const int MAXN = 100;
const int MAXM = 305;

int n, m;
LL C, cost[MAXN];

int eu[MAXM], ev[MAXM];

int head[MAXN], rhead[MAXN];
int to[MAXM], nxt[MAXM], rto[MAXM], rnxt[MAXM];
int cnt, rcnt;

int dh[MAXN], rdh[MAXN];
int dto[MAXM], dnxt[MAXM], rdto[MAXM], rdnxt[MAXM];
int dcnt, rdcnt;

int d1[MAXN], dn[MAXN];

ULL pre[MAXN], suf[MAXN];

deque<LL> L[MAXN], R[MAXN];

void addEdge(int u, int v){
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;

    rto[++rcnt] = u;
    rnxt[rcnt] = rhead[v];
    rhead[v] = rcnt;
}

void addDag(int u, int v){
    dto[++dcnt] = v;
    dnxt[dcnt] = dh[u];
    dh[u] = dcnt;

    rdto[++rdcnt] = u;
    rdnxt[rdcnt] = rdh[v];
    rdh[v] = rdcnt;
}

void bfs(int s, int h[], int t[], int ne[], int dis[]){
    memset(dis, -1, sizeof(int) * (n + 1));

    queue<int> q;
    q.push(s);
    dis[s] = 0;

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(int e = h[u]; e; e = ne[e]){
            int v = t[e];

            if(dis[v] == -1){
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
}

ULL add(ULL a, ULL b){
    ULL inf = ~0ULL;
    if(inf - a < b) return inf;
    return a + b;
}

int lg(ULL x){
    if(x == 0) return 0;
    return 64 - __builtin_clzll(x);
}

int midLayer;

void dfs1(int u, LL sum){
    if(sum > C) return;

    if(d1[u] == midLayer){
        L[u].push_back(sum);
        return;
    }

    for(int e = dh[u]; e; e = dnxt[e]){
        int v = dto[e];
        dfs1(v, sum + cost[v]);
    }
}

void dfs2(int u, LL sum){
    if(sum > C) return;

    if(d1[u] == midLayer + 1){
        R[u].push_back(sum);
        return;
    }

    for(int e = rdh[u]; e; e = rdnxt[e]){
        int v = rdto[e];
        dfs2(v, sum + cost[v]);
    }
}

ULL calc(deque<LL>& a, deque<LL>& b){
    if(a.empty() || b.empty()) return 0;

    deque<LL> *small = &a;
    deque<LL> *large = &b;

    if(small->size() > large->size()){
        swap(small, large);
    }

    ULL ans = 0;

    // 两边差距大：枚举小的一边 + 二分
    if((ULL)small->size() * lg(large->size())
       <= small->size() + large->size()){

        for(LL x : *small){
            ans += upper_bound(
                large->begin(),
                large->end(),
                C - x
            ) - large->begin();
        }
    }

    // 两边比较接近：双指针
    else{
        int p = large->size() - 1;

        for(LL x : *small){
            while(p >= 0 && x + (*large)[p] > C){
                p--;
            }

            ans += p + 1;
        }
    }

    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> C;

    for(int i = 1; i <= n; i++){
        cin >> cost[i];
    }

    for(int i = 1; i <= m; i++){
        cin >> eu[i] >> ev[i];
        addEdge(eu[i], ev[i]);
    }

    bfs(1, head, to, nxt, d1);
    bfs(n, rhead, rto, rnxt, dn);

    if(d1[n] == -1){
        cout << 0 << '\n';
        return 0;
    }

    int D = d1[n];

    if(D == 0){
        cout << (cost[1] <= C) << '\n';
        return 0;
    }

    // 建最短路DAG
    for(int i = 1; i <= m; i++){
        int u = eu[i];
        int v = ev[i];

        if(d1[u] != -1 && dn[v] != -1 &&
           d1[u] + 1 + dn[v] == D){

            addDag(u, v);
        }
    }

    // pre[u] : 1 -> u 的最短路条数
    pre[1] = 1;

    for(int k = 0; k < D; k++){
        for(int u = 1; u <= n; u++){
            if(d1[u] != k) continue;

            for(int e = dh[u]; e; e = dnxt[e]){
                int v = dto[e];
                pre[v] = add(pre[v], pre[u]);
            }
        }
    }

    // suf[u] : u -> n 的最短路条数
    suf[n] = 1;

    for(int k = D; k > 0; k--){
        for(int u = 1; u <= n; u++){
            if(d1[u] != k) continue;

            for(int e = rdh[u]; e; e = rdnxt[e]){
                int v = rdto[e];
                suf[v] = add(suf[v], suf[u]);
            }
        }
    }

    // 找最合适的分界线 k | k+1
    i128 best = -1;

    for(int k = 0; k < D; k++){

        ULL lc = 0, rc = 0;

        for(int u = 1; u <= n; u++){
            if(d1[u] == k)
                lc = add(lc, pre[u]);

            if(d1[u] == k + 1)
                rc = add(rc, suf[u]);
        }

        i128 work = (i128)lc + rc;

        for(int u = 1; u <= n; u++){
            if(d1[u] == k)
                work += (i128)pre[u] * lg(pre[u]);

            if(d1[u] == k + 1)
                work += (i128)suf[u] * lg(suf[u]);
        }

        for(int u = 1; u <= n; u++){
            if(d1[u] != k) continue;

            for(int e = dh[u]; e; e = dnxt[e]){
                int v = dto[e];

                ULL a = pre[u];
                ULL b = suf[v];

                ULL small = min(a, b);
                ULL large = max(a, b);

                work += min(
                    (i128)small * lg(large),
                    (i128)a + b
                );
            }
        }

        if(best == -1 || work < best){
            best = work;
            midLayer = k;
        }
    }

    // 枚举左右半路径费用
    dfs1(1, cost[1]);
    dfs2(n, cost[n]);

    for(int u = 1; u <= n; u++){
        if(d1[u] == midLayer)
            sort(L[u].begin(), L[u].end());

        if(d1[u] == midLayer + 1)
            sort(R[u].begin(), R[u].end());
    }

    ULL ans = 0;

    // 枚举跨过分界线的边
    for(int u = 1; u <= n; u++){
        if(d1[u] != midLayer) continue;

        for(int e = dh[u]; e; e = dnxt[e]){
            int v = dto[e];

            ans += calc(L[u], R[v]);
        }
    }

    // ULL自然溢出，就是模2^64
    cout << ans << '\n';

    return 0;
}