#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 200000; // 最大居民数量

struct Person {
    int a, b; // 对侧居民的家和办公室坐标
};

Person p[MAXN]; // 存储对侧居民
int pl[MAXN * 2]; // 存储所有对侧居民的坐标（用于K=1的情况）

// 比较函数：按家和办公室坐标和排序
bool cmp(const Person &x, const Person &y) {
    return x.a + x.b < y.a + y.b;
}

int main() {
    int k, n; // k: 桥的数量上限, n: 居民数量
    cin >> k >> n;
    long long ans = 0; // 总距离
    int tot = 0; // 对侧居民数量
    int cnt = 0; // 所有对侧居民坐标数量（2 * tot）
    
    // 读取输入数据
    for (int i = 0; i < n; i++) {
        char c1, c2;
        int x1, x2;
        cin >> c1 >> x1 >> c2 >> x2;
        
        // 处理同侧居民
        if (c1 == c2) {
            ans += abs(x2 - x1); // 直接计算距离
        } else {
            // 处理对侧居民
            ans++; // 过桥的固定距离1
            p[tot].a = x1;
            p[tot].b = x2;
            pl[cnt++] = x1;
            pl[cnt++] = x2;
            tot++;
        }
    }
    
    // K=1的情况：只建一座桥
    if (k == 1) {
        // 排序所有坐标
        sort(pl, pl + cnt);
        // 取中位数（对于偶数个点，取中间任意一个都可以）
        int mid = pl[cnt / 2];
        // 计算所有点到中位数的距离和
        for (int i = 0; i < cnt; i++) {
            ans += abs(pl[i] - mid);
        }
        cout << ans << endl;
    } else {
        // K=2的情况：建两座桥
        
        // 如果没有对侧居民，直接输出结果
        if (tot == 0) {
            cout << ans << endl;
            return 0;
        }
        
        // 按家和办公室坐标和排序对侧居民
        sort(p, p + tot, cmp);
        
        // pre[i]: 前i个对侧居民使用一座桥的最小距离和
        // suf[i]: 从第i个到最后一个对侧居民使用一座桥的最小距离和
        vector<long long> pre(tot + 1, 0);
        vector<long long> suf(tot + 2, 0);
        
        // 使用对顶堆动态计算最小距离和
        // q1: 大顶堆，存储较小的一半点
        // q2: 小顶堆，存储较大的一半点
        priority_queue<int> q1;
        priority_queue<int, vector<int>, greater<int>> q2;
        
        // s1: 大顶堆中所有点的和
        // s2: 小顶堆中所有点的和
        long long s1 = 0, s2 = 0;
        
        // 计算前缀最小距离和 pre[i]
        for (int i = 0; i < tot; i++) {
            // 将当前居民的两个点加入大顶堆
            q1.push(p[i].a);
            q1.push(p[i].b);
            s1 += p[i].a + p[i].b;
            
            // 保持堆的平衡：将大顶堆的最大值移动到小顶堆
            int top = q1.top();
            q1.pop();
            s1 -= top;
            s2 += top;
            q2.push(top);
            
            // 如果大顶堆的最大值大于小顶堆的最小值，交换它们
            if (!q1.empty() && !q2.empty() && q1.top() > q2.top()) {
                int t1 = q1.top();
                int t2 = q2.top();
                q1.pop();
                q2.pop();
                q1.push(t2);
                q2.push(t1);
                // 更新两个堆的和
                s1 = s1 - t1 + t2;
                s2 = s2 - t2 + t1;
            }
            
            // 计算前i+1个居民的最小距离和
            // 对于偶数个点，最小距离和 = 小顶堆的和 - 大顶堆的和
            pre[i + 1] = s2 - s1;
        }
        
        // 清空堆，准备计算后缀最小距离和
        while (!q1.empty()) q1.pop();
        while (!q2.empty()) q2.pop();
        s1 = 0;
        s2 = 0;
        
        // 计算后缀最小距离和 suf[i]
        for (int i = tot - 1; i >= 0; i--) {
            // 将当前居民的两个点加入大顶堆
            q1.push(p[i].a);
            q1.push(p[i].b);
            s1 += p[i].a + p[i].b;
            
            // 保持堆的平衡：将大顶堆的最大值移动到小顶堆
            int top = q1.top();
            q1.pop();
            s1 -= top;
            s2 += top;
            q2.push(top);
            
            // 如果大顶堆的最大值大于小顶堆的最小值，交换它们
            if (!q1.empty() && !q2.empty() && q1.top() > q2.top()) {
                int t1 = q1.top();
                int t2 = q2.top();
                q1.pop();
                q2.pop();
                q1.push(t2);
                q2.push(t1);
                // 更新两个堆的和
                s1 = s1 - t1 + t2;
                s2 = s2 - t2 + t1;
            }
            
            // 计算从第i+1个到最后一个居民的最小距离和
            suf[i + 1] = s2 - s1;
        }
        
        // 枚举所有可能的分组点，找到最小总距离
        long long min_val = 1e18;
        for (int i = 0; i <= tot; i++) {
            // 前i个居民使用第一座桥，后tot-i个居民使用第二座桥
            min_val = min(min_val, pre[i] + suf[i + 1]);
        }
        
        // 加上最小分组距离和
        ans += min_val;
        cout << ans << endl;
    }
    
    return 0;
}