#include<bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 2e5 + 5;
const int MAXT = MAXN * 40;
const int MAXH = 25;

int n, m, t, p;

int a[MAXN];

// b[i] 表示第 i 层的分裂点是这一行的第几个节点
int b[MAXN];

// birth[i] 表示最终缝隙序列中，第 i 个位置的出生层数
int birth[MAXN];

// final[i] 表示第 i 层出现的缝隙在最终缝隙序列中的位置
int final[MAXN];

int bitTree[MAXN];

int cntt;
int root[MAXN];
int sz[MAXT];
int ls[MAXT];
int rs[MAXT];

// minn[i][j] 表示最终缝隙序列中，从 i 开始长度为 2^j 的区间最小出生层
int minn[MAXN][MAXH];
int lg_2[MAXN];

int lowbit(int x){
    return x & -x;
}

int tri(int x){
    return x * (x + 1) / 2;
}

// ---------------- 树状数组：倒推 final / birth ----------------

void add(int x, int v){
    while(x <= n){
        bitTree[x] += v;
        x += lowbit(x);
    }
}

int bitQuery(int x){
    int ans = 0;
    while(x){
        ans += bitTree[x];
        x -= lowbit(x);
    }
    return ans;
}

// 查询当前第 k 个 1 的位置
int calc(int k){
    int l = 1, r = n, ans = n;

    while(l <= r){
        int mid = (l + r) >> 1;

        if(bitQuery(mid) >= k){
            ans = mid;
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }

    return ans;
}

// ---------------- 可持久化线段树 ----------------

// 插入一个最终缝隙位置 pos
int insert(int pos, int l, int r, int i){
    int rt = ++cntt;

    ls[rt] = ls[i];
    rs[rt] = rs[i];
    sz[rt] = sz[i] + 1;

    if(l < r){
        int mid = (l + r) >> 1;

        if(pos <= mid){
            ls[rt] = insert(pos, l, mid, ls[rt]);
        }
        else{
            rs[rt] = insert(pos, mid + 1, r, rs[rt]);
        }
    }

    return rt;
}

// 查询版本 i 中，[jobl, jobr] 里有多少个已经出现的缝隙
int segQuery(int jobl, int jobr, int l, int r, int i){
    if(i == 0 || jobl > r || jobr < l){
        return 0;
    }

    if(jobl <= l && r <= jobr){
        return sz[i];
    }

    int mid = (l + r) >> 1;
    int ans = 0;

    if(jobl <= mid){
        ans += segQuery(jobl, jobr, l, mid, ls[i]);
    }

    if(jobr > mid){
        ans += segQuery(jobl, jobr, mid + 1, r, rs[i]);
    }

    return ans;
}

// 查询版本 i 中，第 k 个已经出现的缝隙在最终序列中的位置
int kth(int k, int l, int r, int i){
    if(l == r){
        return l;
    }

    int mid = (l + r) >> 1;
    int leftSize = sz[ls[i]];

    if(k <= leftSize){
        return kth(k, l, mid, ls[i]);
    }
    else{
        return kth(k - leftSize, mid + 1, r, rs[i]);
    }
}

// ---------------- ST 表：查询最终缝隙区间最小出生层 ----------------

// 查询最终缝隙序列中 [l, r] 的最小出生层
int getMinBirth(int l, int r){
    if(l > r){
        swap(l, r);
    }

    int len = r - l + 1;
    int k = lg_2[len];

    return min(minn[l][k], minn[r - (1 << k) + 1][k]);
}

// ---------------- 预处理 ----------------

void prepare(){
    // 倒推每个缝隙的最终位置
    for(int i = 1; i <= n; i++){
        add(i, 1);
    }

    for(int i = n; i >= 1; i--){
        int pos = calc(b[i]);

        final[i] = pos;
        birth[pos] = i;

        add(pos, -1);
    }

    // 建可持久化线段树
    root[0] = 0;

    for(int i = 1; i <= n; i++){
        root[i] = insert(final[i], 1, n, root[i - 1]);
    }

    // 建 ST 表
    lg_2[0] = -1;

    for(int i = 1; i <= n; i++){
        lg_2[i] = lg_2[i >> 1] + 1;
    }

    p = lg_2[n];

    for(int i = 1; i <= n; i++){
        minn[i][0] = birth[i];
    }

    for(int j = 1; j <= p; j++){
        for(int i = 1; i + (1 << j) - 1 <= n; i++){
            minn[i][j] = min(
                minn[i][j - 1],
                minn[i + (1 << (j - 1))][j - 1]
            );
        }
    }
}

// ---------------- 核心查询 ----------------

// 根据全局节点编号，求它在哪一层
int getLevel(int x){
    int l = 1;
    int r = n + 1;
    int ans = n + 1;

    while(l <= r){
        int mid = (l + r) >> 1;

        if(tri(mid) >= x){
            ans = mid;
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }

    return ans;
}

// 第 level 层第 pos 个节点，往上跳到 target 层后，是 target 层第几个节点
int lift(int level, int pos, int target){
    if(level == target){
        return pos;
    }

    if(pos == 1){
        return 1;
    }

    // 当前点左边有 pos - 1 个缝隙
    int gapRank = pos - 1;

    // 当前层第 gapRank 个缝隙，在最终缝隙序列中的位置
    int finalPos = kth(gapRank, 1, n, root[level - 1]);

    // target 层中，finalPos 左边还存在多少个缝隙
    int leftCnt = segQuery(1, finalPos, 1, n, root[target - 1]);

    // 节点位置 = 左边缝隙数 + 1
    return leftCnt + 1;
}

// 第 level 层第 pos 个点的全局编号
int getId(int level, int pos){
    return tri(level - 1) + pos;
}

// 求 x 和 y 的 LCA
int solve(int x, int y){
    int lx = getLevel(x);
    int ly = getLevel(y);

    int px = x - tri(lx - 1);
    int py = y - tri(ly - 1);

    // 先把更深的节点提到同一层
    if(lx > ly){
        px = lift(lx, px, ly);
        lx = ly;
    }
    else if(ly > lx){
        py = lift(ly, py, lx);
        ly = lx;
    }

    int level = lx;

    // 如果已经是同一个点，直接返回
    if(px == py){
        return getId(level, px);
    }

    if(px > py){
        swap(px, py);
    }

    // 当前层中，px 和 py 之间的缝隙编号是 px 到 py - 1
    int leftGapFinalPos = kth(px, 1, n, root[level - 1]);
    int rightGapFinalPos = kth(py - 1, 1, n, root[level - 1]);

    // 它们之间最早出生的缝隙，决定 LCA 所在层
    int lcaLevel = getMinBirth(leftGapFinalPos, rightGapFinalPos);

    // 把左边这个点跳到 lcaLevel，得到 LCA 的层内位置
    int lcaPos = lift(level, px, lcaLevel);

    return getId(lcaLevel, lcaPos);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> t;

    for(int i = 1; i <= n; i++){
        cin >> a[i];

        // 把全局编号转成第 i 层的层内位置
        b[i] = a[i] - tri(i - 1);
    }

    prepare();

    int total = tri(n + 1);
    int lastAns = 0;

    while(m--){
        int x, y;
        cin >> x >> y;

        x = ((x - 1 + t * lastAns) % total) + 1;
        y = ((y - 1 + t * lastAns) % total) + 1;

        lastAns = solve(x, y);

        cout << lastAns << '\n';
    }

    return 0;
}