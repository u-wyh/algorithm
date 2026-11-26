// https://www.luogu.com.cn/problem/P11231
// 题意：有 n 只怪兽，攻击力和防御力都是 r[i]。
// 每只未退出的怪兽最多主动攻击另一个怪兽一次，只有攻击者更强时，被攻击者才退出。
// 安排攻击次序，使结束时留下的怪兽尽可能少。
// 数据范围：1 ≤ n ≤ 10^5，1 ≤ r[i] ≤ 10^5。

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int nums[MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    sort(nums+1,nums+n+1);
    int u=1;
    for(int i=2;i<=n;i++){
        if(nums[i]>nums[u]){
            u++;
        }
    }
    cout<<(n-u+1)<<endl;
    return 0;
}