// https://www.luogu.com.cn/problem/P3531
// 题意：输入字符串长度 n，
// 以及两个长度为 n 的大写字母串 a 和 b（保证 a 可重排为 b）。
// 每次可以交换串 a 中相邻的两个字符。
// 输出将 a 变成 b 所需的最少交换次数。
// 数据范围：1 <= n <= 10^6，a, b 仅含大写字母。
//P3531
// 算法标签：树状数组、逆序对、贪心
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

vector<int> nums[26]; // 假设您想为每个字母分配一个vector，但这里只使用了nums[1]
int cnt[26];
int arr[MAXN];
int n;
int tree[MAXN];

int lowbit(int i) {
	return i & -i;
}

void add(int i, int v) {
    while (i <= n) {
        tree[i] += v;
        i += lowbit(i);
    }
}

// 1~i范围的累加和
int sum(int i) {
    int ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}

int main()
{
    cin>>n;
    string str1,str2;
    cin>>str1>>str2;
    for(int i=1;i<=n;i++){
        nums[str2[i-1]-'A'].push_back(i);
    }
    for(int i=1;i<=n;i++){
        int k=str1[i-1]-'A';
        arr[i]=nums[k][cnt[k]];
        cnt[k]++;
        //nums[k].erase(nums[k].begin());
    }
//    for(int i=1;i<=n;i++){
//        cout<<arr[i]<<' ';
//    }
    long long ans=0;
    for(int i=n;i>=1;i--){
        add(arr[i],1);
        ans+=sum(arr[i]-1);
    }
    cout<<ans<<endl;
    return 0;
}
