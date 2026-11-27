// https://www.luogu.com.cn/problem/B3666
// 题意：序列起初为空，进行 n 次操作，第 i 次在末尾加入 x[i]。
// 每次找出所有严格大于右侧每个数的位置。
// 输出这些位置编号的按位异或和。编号从 1 开始。
// 数据范围：1 ≤ n ≤ 10^6，1 ≤ x[i] < 2^64。
// 算法标签：单调栈

#include <bits/stdc++.h>

int n, ans;
std::vector<int> stk;
std::array<unsigned long long, 1000005> a;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a.at(i);
    while (stk.size() && (a.at(i) >= a.at(stk.back()))) {
      ans ^= stk.back();
      stk.pop_back();
    }
    stk.push_back(i);
    ans ^= i;
    std::cout << ans << '\n';
  }
}
