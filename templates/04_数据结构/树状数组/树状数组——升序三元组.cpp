// 升序三元组数量
// 给定一个数组arr，如果i < j < k且arr[i] < arr[j] < arr[k]
// 那么称(i, j, k)为一个升序三元组
// 返回arr中升序三元组的数量
// 测试链接 : https://www.luogu.com.cn/problem/P1637
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
//其实这道题还是很有挑战的  有一定的思维难度  比较不错
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 30001;
int arr[MAXN];
int Sort[MAXN];
// 维护信息 : 课上讲的up1数组
// tree1不是up1数组，是up1数组的树状数组
long tree1[MAXN];
// 维护信息 : 课上讲的up2数组
// tree2不是up2数组，是up2数组的树状数组
//举个例子说明区别 ：tree[2]实际上是up[2]up[1]的结合
long tree2[MAXN];
int n, m;

int lowbit(int i) {
    return i & -i;
}

void add(long* tree, int i, long c) {
    while (i <= m) {
        tree[i] += c;
        i += lowbit(i);
    }
}

long sum(long* tree, int i) {
    long ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}

int Rank(int v) {
    int l = 1, r = m, mid;
    int ans = 0;
    while (l <= r) {
        mid = (l + r) / 2;
        if (Sort[mid] >= v) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

long compute() {
    sort(Sort+1, Sort+n + 1);
    m = 1;
    for (int i = 2; i <= n; i++) {
        if (Sort[m] != Sort[i]) {
            Sort[++m] = Sort[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        arr[i] = Rank(arr[i]);
    }
    long ans = 0;
    for (int i = 1; i <= n; i++) {
        // 查询以当前值做结尾的升序三元组数量
        ans += sum(tree2, arr[i] - 1);
        // 更新以当前值做结尾的升序一元组数量  其实就是前面小于自己的数字的数量
        add(tree1, arr[i], 1);
        // 更新以当前值做结尾的升序二元组数量
        add(tree2, arr[i], sum(tree1, arr[i] - 1));
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        Sort[i]=arr[i];//复制数组  用于排序和去重
    }
    cout<<compute();
    return 0;
}