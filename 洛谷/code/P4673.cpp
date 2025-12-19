#include <bits/stdc++.h>
#define MAXN 500010
using namespace std;

int n, m, p, t, tote;
int dist[MAXN], ans[MAXN];
//dist表示到达这个点最长乘车时间
//ans其实是一个记录数组 就是用于辅助记录答案的  他记录的是这条边对应的起点的dist值

struct Bus {
    int x, t, idx, dist;
} b[MAXN];

void build(int x, int t, int idx, int dist) {
    b[++tote] = {x, t, idx, dist};
}

// 最终时间相同时，乘车时间越长排越前面。
// 最终时间不同时，最终时间更长排越后面。
bool cmp(const Bus &x, const Bus &y) {
    return (x.t == y.t) ? (x.dist > y.dist) : (x.t < y.t);
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> m >> p >> t;
    
    for (int i = 1, s, t, a, b, c, d; i <= m; i++) {
        cin >> s >> t >> a >> b >> c >> d;
        build(s, a, i, 0);
        build(t, d, i, c - b);
    }
    
    build(n + 1, t, 0, -0x3f3f3f3f);
    sort(b + 1, b + tote + 1, cmp);
    
    memset(dist, 250, sizeof(dist));
    dist[1] = 0;
    
    for (int i = 1; i <= tote; i++) {
        if (b[i].x == n + 1) {
            break;
        }
        if (!b[i].dist) {
            ans[b[i].idx] = dist[b[i].x];
        } else {
            dist[b[i].x] = max(dist[b[i].x], ans[b[i].idx] + b[i].dist);
			//排序方式保证了一条路的起点一定在终点之前被访问过
        }
		// 接下来枚举每个点，若为起点则将对应的 ans 赋为到该点的 dist 值，
		// 若为终点，则用该点的 ans+ 到该点那班车车上所花的时间值（即 bdist?）更新该点的 dist 值。 
		// 若到达 p 点时 distp? 值小于零输出 ?1，若不是则输出 t?distp?。
    }
    
    (dist[p] < 0) ? cout << "-1" : cout << t - dist[p];
    return 0;
}