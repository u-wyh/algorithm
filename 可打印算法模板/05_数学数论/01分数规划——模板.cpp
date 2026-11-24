// 用途：在 n 对数中删去 k 对，使剩余数的 Σx/Σy 最大。
// 时间：O(n log n log(R/ε))，每轮排序选出最大的 k 个结余。
// 空间：O(n)。
// 注意：分母需为正；二分取上界作百分数四舍五入，n<=1000。
// 例题：https://www.luogu.com.cn/problem/P10505
// 题意：删去 k 对数，使剩余数对的总分子除总分母最大。
// 思路：二分答案 x，将每对变为 a-xb，选最大的 n-k 项判断和是否非负。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1001;

struct node {
    double x,y,r;
}arr[MAXN];
int n,k;

bool cmp(node a,node b){
    return a.r>b.r;
}

bool check(double x) {
    // x固定的情况下，得到所有数据的结余
    for (int i = 1; i <= n; i++) {
        arr[i].r = arr[i].x - x * arr[i].y;
    }
    // 结余从大到小排序
    sort(arr + 1, arr + n + 1, cmp);
    // 最大k个结余的累加和
    double sum = 0;
    for (int i = 1; i <= k; i++) {
        sum += arr[i].r;
    }
    return sum >= 0;
}

int main()
{
    cin>>n>>k;
    while((n+k)!=0){
        k = n - k;
        for (int i = 1; i <= n; i++) {
            cin>>arr[i].x;
        }
        for (int i = 1; i <= n; i++) {
            cin>>arr[i].y;
        }
        double l = 0, r = 0, x;
        for (int i = 1; i <= n; i++) {
            r += arr[i].x;
        }
        // 固定迭代次数，保持 l 可行、r 不可行的二分边界。
        for (int iter = 0; iter < 70; ++iter) {
            x = (l + r) / 2;
            if (check(x)) {
                l = x;
            } else {
                r = x;
            }
        }
        cout<<llround(r * 100.0)<<endl;
        cin>>n>>k;
    }
    return 0;
}
