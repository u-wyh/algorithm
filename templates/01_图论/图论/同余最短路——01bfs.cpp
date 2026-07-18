// 正整数倍的最小数位和
// 给定一个整数k，求一个k的正整数倍s，使得在十进制下，s的数位累加和最小
// 2 <= k <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/AT_arc084_b
// 测试链接 : https://atcoder.jp/contests/abc077/tasks/arc084_b
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
//01bfs的优势是他可以不用排序  时间复杂度少一个log
//但是他只能用于边权为0或者1的图
#include<bits/stdc++.h>
using namespace std;
const int MAXK = 100001;

int k;
deque<pair<int, int>> dq; // 将 deque 重命名为 dq
bool visit[MAXK];

int bfs() {
    //这个是01bfs得到最短路
    dq.clear();
    dq.push_front({1, 1});//初始的时候  1%k=1    所以1是初始值
    memset(visit, false, sizeof(visit));

    while (!dq.empty()) {
        auto cur = dq.front();
        dq.pop_front();
        int mod = cur.first;
        int cost = cur.second;

        if (!visit[mod]) {
            //如果这个数字以前没有访问过  那么继续
            visit[mod] = true;
            if (mod == 0) {
                //得到%k=0的最小值
                return cost;
            }
            dq.push_front({(mod * 10) % k, cost});//这是是乘10  边权为0  从头加入
            dq.push_back({(mod + 1) % k, cost + 1});//这个是加1  边权为1  从尾加入
        }
    }
    return -1;
}

int main() {
    cin >> k;
    cout << bfs() << endl;
    return 0;
}