#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n, m;
double xval[MAXN], yval[MAXN];

// 线段树节点
double sx[MAXN<<2];
double sy[MAXN<<2];
double sxx[MAXN<<2];
double sxy[MAXN<<2];
double si[MAXN<<2];    // ∑i
double sii[MAXN<<2];   // ∑i²
double len[MAXN<<2];   // 区间长度
bool change[MAXN<<2] = {0}; // 覆盖标记
double cx[MAXN<<2] = {0};   // 覆盖的S
double cy[MAXN<<2] = {0};   // 覆盖的T
double ax[MAXN<<2] = {0};   // 加法标记Δx
double ay[MAXN<<2] = {0};   // 加法标记Δy

struct node {
    double sx, sy, sxx, sxy;
};

// 专用浮点数读入函数
inline double readd() {
    double x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    if (ch == '.') {
        double fraction = 1.0;
        ch = getchar();
        while (ch >= '0' && ch <= '9') {
            x += (ch - '0') * (fraction /= 10);
            ch = getchar();
        }
    }
    return x * f;
}

// 更稳健的平方和计算（避免大整数）
double calc_sii(int l, int r) {
    double sum = 0;
    for (int i = l; i <= r; i++) {
        sum += (double)i * i;
    }
    return sum;
}

void up(int i) {
    sx[i] = sx[i<<1] + sx[i<<1|1];
    sy[i] = sy[i<<1] + sy[i<<1|1];
    sxx[i] = sxx[i<<1] + sxx[i<<1|1];
    sxy[i] = sxy[i<<1] + sxy[i<<1|1];
}

void build(int l, int r, int i) {
    len[i] = (double)(r - l + 1);
    si[i] = (double)(l + r) * len[i] / 2.0;
    sii[i] = calc_sii(l, r);  // 更稳健的计算方式
    
    // 初始化懒标记
    change[i] = false;
    cx[i] = cy[i] = 0.0;
    ax[i] = ay[i] = 0.0;
    
    if (l == r) {
        sx[i] = xval[l];
        sy[i] = yval[l];
        sxx[i] = xval[l] * xval[l];
        sxy[i] = xval[l] * yval[l];
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i<<1);
        build(mid+1, r, i<<1|1);
        up(i);
    }
}

// 修改为double参数
void updatelazy(double s, double t, int i) {
    change[i] = true;
    cx[i] = s;
    cy[i] = t;
    ax[i] = ay[i] = 0.0;  // 清除加法标记
    
    // 使用浮点数计算
    sx[i] = s * len[i] + si[i];
    sy[i] = t * len[i] + si[i];
    sxx[i] = s * s * len[i] + 2.0 * s * si[i] + sii[i];
    sxy[i] = s * t * len[i] + s * si[i] + t * si[i] + sii[i];
}

// 修改为double参数
void addlazy(double s, double t, int i) {
    // 增量更新统计值
    sxy[i] += t * sx[i] + s * sy[i] + s * t * len[i];
    sxx[i] += s * s * len[i] + 2.0 * s * sx[i];
    sx[i] += s * len[i];
    sy[i] += t * len[i];
    
    // 累加加法标记
    ax[i] += s;
    ay[i] += t;
}

void down(int i) {
    if (change[i]) {
        change[i] = false;
        updatelazy(cx[i], cy[i], i<<1);
        updatelazy(cx[i], cy[i], i<<1|1);
    }
    if (ax[i] != 0.0 || ay[i] != 0.0) {
        addlazy(ax[i], ay[i], i<<1);
        addlazy(ax[i], ay[i], i<<1|1);
        ax[i] = ay[i] = 0.0;
    }
}

// 修改为double参数
void update(int jobl, int jobr, double jobs, double jobt, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        updatelazy(jobs, jobt, i);
        return;
    }
    
    down(i);
    int mid = (l + r) >> 1;
    if (jobl <= mid) update(jobl, jobr, jobs, jobt, l, mid, i<<1);
    if (jobr > mid) update(jobl, jobr, jobs, jobt, mid+1, r, i<<1|1);
    up(i);
}

// 修改为double参数
void add(int jobl, int jobr, double jobs, double jobt, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        addlazy(jobs, jobt, i);
        return;
    }
    
    down(i);
    int mid = (l + r) >> 1;
    if (jobl <= mid) add(jobl, jobr, jobs, jobt, l, mid, i<<1);
    if (jobr > mid) add(jobl, jobr, jobs, jobt, mid+1, r, i<<1|1);
    up(i);
}

node query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return {sx[i], sy[i], sxx[i], sxy[i]};
    }
    
    down(i);
    int mid = (l + r) >> 1;
    node res = {0, 0, 0, 0};
    
    if (jobl <= mid) {
        node left = query(jobl, jobr, l, mid, i<<1);
        res = left;
    }
    if (jobr > mid) {
        node right = query(jobl, jobr, mid+1, r, i<<1|1);
        if (jobl <= mid) {
            res.sx += right.sx;
            res.sy += right.sy;
            res.sxx += right.sxx;
            res.sxy += right.sxy;
        } else {
            res = right;
        }
    }
    return res;
}

int main() {
    n = (int)readd(), m = (int)readd();
    for (int i = 1; i <= n; i++) {
        xval[i] = readd();
    }
    for (int i = 1; i <= n; i++) {
        yval[i] = readd();
    }
    build(1, n, 1);
    
    for (int i = 1; i <= m; i++) {
        int op, l, r;
        op = (int)readd();
        l = (int)readd();
        r = (int)readd();
        
        if (op == 1) {
            node res = query(l, r, 1, n, 1);
            double nlen = r - l + 1;
            double numerator = nlen * res.sxy - res.sx * res.sy;
            double denominator = nlen * res.sxx - res.sx * res.sx;
            
            // 处理分母接近0的情况
            if (fabs(denominator) < 1e-9) {
                printf("0.0000000000\n");
            } else {
                printf("%.10f\n", numerator / denominator);
            }
        } else {
            double s = readd(), t = readd();
            if (op == 2) {
                add(l, r, s, t, 1, n, 1);
            } else if (op == 3) {
                update(l, r, s, t, 1, n, 1);
            }
        }
    }
    return 0;
}