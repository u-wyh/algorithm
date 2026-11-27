// https://www.luogu.com.cn/problem/P4305
// 题意：多组数据，每组给 n 个整数，去掉重复数字，只保留每个数第一次出现的位置并按原序输出。
// 数据范围：1 <= T <= 50，1 <= n <= 5e4，数值在 32 位有符号整数范围内。
#include<bits/stdc++.h>
// 算法标签：哈希表
using namespace std;

int t,n;
unordered_map<int ,bool>ds;

int main()
{
    cin>>t;
    while(t--){
        cin>>n;
        int x;
        while(n--){
            cin>>x;
            if(!ds[x]){
                cout<<x<<' ';
                ds[x]=1;
            }
        }
        ds.clear();
        printf("\n");
    }
    return 0;
}
