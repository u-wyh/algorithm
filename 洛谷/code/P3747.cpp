#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 5e4 + 5; // 元素数量上限
const int MAXH = 30;      // 欧拉函数迭代层数上限
const int MAXB = 1e4 + 5; // 分块数组维度上限
const int BLOCK = 1e4;    // 分块大小

int n, m, p, c, len; // n:元素数, m:操作数, p:模值, c:底数, len:phi数组长度
int val[MAXN];       // 原始元素值

// 核心数组定义
int phi[MAXH];                       // 欧拉函数迭代序列(phi[0]=p, phi[1]=φ(p), ...)
int s1[MAXB][MAXH], s2[MAXB][MAXH];  // 分块预处理幂值(s1[i][k]=c^(i*BLOCK) mod phi[k])
bool b1[MAXB][MAXH], b2[MAXB][MAXH]; // 分块标记(是否超过phi[k])
bool bj[MAXN][MAXH][MAXH];           // 标记指数是否超过phi[k]

// f[i][j][k]:第i个元素经j次操作后 mod phi[k]的结果
// g[i][k]:第i个元素在mod phi[k]下稳定的最小操作次数
int f[MAXN][MAXH][MAXH];
int g[MAXN];

// 线段树相关
int tree[MAXN << 2]; // 线段树节点值(区间和 mod p)
int now[MAXN << 2];  // 记录每个元素当前操作次数
bool tag[MAXN << 2]; // 标记元素是否已稳定(操作次数达g[i][0])

// 快速读入
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int get_phi(int x)
{
    int ans = x;
    for (int i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            ans = ans / i * (i - 1);
            while (x % i == 0)
                x /= i;
        }
    }
    if (x > 1)
        ans = ans / x * (x - 1);
    return ans;
}

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

void prepare()
{
    int x = p;
    phi[0] = p;
    while (x != 1)
    {
        x = get_phi(x);
        phi[++len] = x;
    }
    phi[++len] = 1;
    for (int i = 0; i <= len;i++){
        g[i] = gcd(c, phi[i]);
    }
        for (int j = 0; j <= len; j++)
        {
            s2[0][j] = 1;
            for (int i = 1; i <= BLOCK; i++)
            {
                s2[i][j] = s2[i - 1][j] * c;
                if (s2[i][j] >= phi[j])
                {
                    s2[i][j] %= phi[j];
                    b2[i][j] = 1;
                }
                b2[i][j] |= b2[i - 1][j];
            }
        }
    for (int j = 0; j <= len; j++)
    {
        s1[0][j] = 1;
        b1[1][j] = b2[BLOCK][j];
        for (int i = 1; i <= BLOCK; i++)
        {
            s1[i][j] = s1[i - 1][j] * s2[BLOCK][j];
            if (s1[i][j] >= phi[j])
            {
                s1[i][j] %= phi[j];
                b1[i][j] = 1;
            }
            b1[i][j] |= b1[i - 1][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int k = 0; k <= len; k++)
        {
            f[i][0][k] = val[i] % phi[k];
            if (val[i] >= phi[k])
                bj[i][0][k] = 1;
        }
        for (int j = 1; j <= len; j++)
        {
            f[i][j][len] = 0;
            for (int k = 0; k < len; k++)
            {
                f[i][j][k] = s1[f[i][j - 1][k + 1] / BLOCK][k] * s2[f[i][j - 1][k + 1] % BLOCK][k];
                bj[i][j][k] = (b1[f[i][j - 1][k + 1] / BLOCK][k] || b2[f[i][j - 1][k + 1] % BLOCK][k]);
                if (f[i][j][k] >= phi[k])
                {
                    f[i][j][k] %= phi[k];
                    bj[i][j][k] = 1;
                }
                if (g[k] && bj[i][j - 1][k + 1])
                {
                    f[i][j][k] = f[i][j][k] * s1[phi[k + 1] / BLOCK][k] % phi[k] * s2[phi[k + 1] % BLOCK][k];
                    if (f[i][j][k] >= phi[k])
                    {
                        f[i][j][k] %= phi[k];
                        bj[i][j][k] = 1;
                    }
                    bj[i][j][k] = (bj[i][j][k] || b1[phi[k + 1] / BLOCK][k] || b2[phi[k + 1] % BLOCK][k]);
                }
            }
        }
    }
    return;
}

void up(int i)
{
    tag[i] = (tag[i << 1] && tag[i << 1 | 1]);
    tree[i] = (tree[i << 1] + tree[i << 1 | 1]) % p;
}

void build(int l, int r, int i)
{
    if (l == r)
    {
        now[i] = 0;
        tag[i] = (now[i] >= len);

        tree[i] = f[l][0][0] % p;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, i << 1);
    build(mid + 1, r, i << 1 | 1);
    up(i);
}

void update(int jobl, int jobr, int l, int r, int i)
{
    if (tag[i])
        return;
    if (jobl <= l && r <= jobr)
    {
        if (l == r)
        {
            now[i]++;

            if (now[i] >= len)
            {
                now[i] = len;
                tag[i] = true;
            }

            tree[i] = f[l][now[i]][0] % p;
            return;
        }

        int mid = (l + r) >> 1;
        update(jobl, jobr, l, mid, i << 1);
        update(jobl, jobr, mid + 1, r, i << 1 | 1);
        up(i);
    }
    else
    {
        int mid = (l + r) >> 1;
        if (jobl <= mid)
            update(jobl, jobr, l, mid, i << 1);
        if (jobr > mid)
            update(jobl, jobr, mid + 1, r, i << 1 | 1);
        up(i);
    }
}

int query(int jobl, int jobr, int l, int r, int i)
{
    if (jobl <= l && r <= jobr)
    {
        return tree[i] % p;
    }
    long long ans = 0;
    int mid = (l + r) >> 1;
    if (jobl <= mid)
        ans = (ans + query(jobl, jobr, l, mid, i << 1)) % p;
    if (jobr > mid)
        ans = (ans + query(jobl, jobr, mid + 1, r, i << 1 | 1)) % p;
    return ans % p;
}

signed main()
{
    n = read(), m = read(), p = read(), c = read();
    for (int i = 1; i <= n; i++)
    {
        val[i] = read();
    }
    prepare();
    build(1, n, 1);

    while (m--)
    {
        int op = read(), l = read(), r = read();
        if (op == 0)
        {

            update(l, r, 1, n, 1);
        }
        else
        {

            printf("%lld\n", query(l, r, 1, n, 1));
        }
    }
    return 0;
}
/*
1 4 3 2
0
0 1 1
0 1 1
0 1 1
1 1 1
*/