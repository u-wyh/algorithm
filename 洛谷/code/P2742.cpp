// https://www.luogu.com.cn/problem/P2742
//这道题采用分治法来解决凸包问题  
//基本思路是把所有的点都放在二维坐标系里面。那么横坐标最小和最大的两个点分别是P1 、 Pn 
//P1、Pn一定是凸包上的点。直线P1、Pn把点集分成了两部分，即上面和下面两部分，分别叫做上包和下包。
//对上包：求距离直线P1、Pn最远的点，假设为点Pmax。
//作直线   P1、Pmax   Pn、Pmax，把直线P1Pmax左侧的点当成是上包，把直线PnPmaxPnPmax右侧的点也当成是上包。
//重复操作  对下包也作类似操作。
//上包部分找上包  下包部分找下包
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;

int n;
struct node {
    double x, y;
    node(double x = 0, double y = 0) : x(x), y(y) {}
    bool operator<(const node& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

node nums[MAXN];
node hull[MAXN];
int hullsize;

double cross(const node& a, const node& b, const node& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double dis(const node& a, const node& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

void findhull(int l, int r, node a, node b, node* tmp) {
    if (l > r) return;

    double maxdist = -1;
    int id = -1;
    for (int i = l; i <= r; i++) {
        double d = fabs(cross(a, b, tmp[i]));
        if (d > maxdist) {
            maxdist = d;
            id = i;
        }
    }
    node c = tmp[id];
    hull[++hullsize] = c;

    swap(tmp[id], tmp[r]);

    int p = l;
    for (int i = l; i < r; i++) {
        if (cross(a, c, tmp[i]) > 0) {
            swap(tmp[i], tmp[p++]);
        }
    }
    int q = p;
    for (int i = p; i < r; i++) {
        if (cross(c, b, tmp[i]) > 0) {
            swap(tmp[i], tmp[q++]);
        }
    }

    findhull(l, p - 1, a, c, tmp);
    findhull(p, q - 1, c, b, tmp);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf %lf", &nums[i].x, &nums[i].y);
    }

    if (n == 1) {
        printf("0.00\n");
        return 0;
    }
    if (n == 2) {
        printf("%.2f\n", dis(nums[1], nums[2]));
        return 0;
    }

    sort(nums + 1, nums + n + 1);

    hullsize = 0;
    hull[++hullsize] = nums[1];
    hull[++hullsize] = nums[n];

    node tmp1[MAXN], tmp2[MAXN];
    int cnt1 = 0, cnt2 = 0;

    // 正确划分上下包
    for (int i = 2; i < n; i++) {
        double d = cross(nums[1], nums[n], nums[i]);
        if (d > 0) {
            tmp1[++cnt1] = nums[i];  // 上包存入 tmp1
        } else if (d < 0) {
            tmp2[++cnt2] = nums[i];  // 下包存入 tmp2
        }
    }

    // 正确传入上下包数组
    findhull(1, cnt1, nums[1], nums[n], tmp1);  // 上包
    findhull(1, cnt2, nums[n], nums[1], tmp2);  // 下包

    // 按极角排序（逆时针）
    node ref = hull[1];
    sort(hull + 2, hull + hullsize + 1, [&](const node& a, const node& b) {
        double c = cross(ref, a, b);
        if (fabs(c) < 1e-9) {
            return dis(ref, a) < dis(ref, b);
        }
        return cross(ref, a, b) < 0;  // 修正排序规则
    });

    // 计算凸包周长（形成闭环）
    double ans = dis(hull[hullsize], hull[1]);  // 首尾相连
    for (int i = 1; i < hullsize; i++) {
        ans += dis(hull[i], hull[i + 1]);
    }

    printf("%.2f\n", ans);
    return 0;
}