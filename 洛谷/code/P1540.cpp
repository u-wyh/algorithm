// P1540 [NOIP 2010 提高组] 机器翻译
// FIFO cache simulation
// 若单词不在内存中（未命中），查词典次数 +1，将其加入内存
// 内存已满时，清除最早进入内存的单词（FIFO）

#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    queue<int> q;          // 模拟内存队列（存储单词顺序）
    unordered_set<int> inMem;  // 快速判断单词是否在内存中
    int cnt = 0;           // 查词典次数

    for (int i = 0; i < N; ++i) {
        int word;
        cin >> word;

        if (inMem.count(word)) {
            // 内存中已存在，直接使用，不查词典
            continue;
        }

        // 未命中，需要查词典
        ++cnt;

        if ((int)q.size() >= M) {
            // 内存已满，移除最早进入的单词
            int old = q.front();
            q.pop();
            inMem.erase(old);
        }

        // 存入新单词
        q.push(word);
        inMem.insert(word);
    }

    cout << cnt << '\n';
    return 0;
}
