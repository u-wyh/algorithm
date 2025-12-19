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
