// 用途：二维网格单点赋值，并求子矩形元素之和。
// 时间：单次 O(log n log m)。
// 空间：O(nm)。
// 注意：坐标从 0 开始输入，内部从 1 开始；n,m≤2000。
// 例题：https://leetcode.cn/problems/range-sum-query-2d-mutable/
// 题意：修改一个格子的值，查询左上角到右下角矩形的元素和。
// 思路：二维树状数组维护前缀和，矩形用四个前缀容斥。
#include<bits/stdc++.h>
using namespace std;

int n,m;
long long nums[2005][2005];
long long tree[2005][2005];

int lowbit(int i) {
    return i & -i;
}

//将数组中(x,y)位置上的数字加上v
void add(int x, int y, long long v) {
    for (int i = x; i <= n; i += lowbit(i)) {
        for (int j = y; j <= m; j += lowbit(j)) {
            tree[i][j] += v;
        }
    }
}

//这个函数的作用是计算从(1,1)到(x,y)之间的累加和
long long sum(int x, int y) {
    long long ans = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        for (int j = y; j > 0; j -= lowbit(j)) {
            ans += tree[i][j];
        }
    }
    return ans;
}

//在这道题目中  题目的意思是将(x,y)位置上的数字变为v
//这其实等价于将这个位置上的数字加上改后的数字减去当前的数字
//这实际上是为了解决输入时的问题
void update(int x, int y, long long v) {
    add(x + 1, y + 1, v - nums[x + 1][y + 1]);
    nums[x + 1][y + 1] = v;
}

// 实际二维数组的位置是(x,y)
// 树状数组上的位置是(x+1, y+1)
long long sumRegion(int a, int b, int c, int d) {
	return sum(c + 1, d + 1) - sum(a, d + 1) - sum(c + 1, b) + sum(a, b);
}

// 输入 n m、初始矩阵、q；操作 1 x y v 为赋值，2 a b c d 为矩形求和。
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            long long value;
            cin>>value;
            update(i,j,value);
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            long long value;
            cin >> x >> y >> value;
            update(x, y, value);
        } else {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            cout << sumRegion(a, b, c, d) << '\n';
        }
    }
    return 0;
}
