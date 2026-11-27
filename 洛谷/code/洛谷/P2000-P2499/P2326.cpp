// https://www.luogu.com.cn/problem/P2326
// 题意：t 组数据，每组有 n 个整数 w_i，
// 选两个数求按位与 w_i & w_j 的最大值。
// 每组输出 Case #x: ans。
// 数据范围：t <= 20，n <= 10^5，w_i <= 2^20。
// 算法标签：贪心、位运算
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int arr[MAXN],tmp[MAXN];

int main()
{
    int T,cnt=0;
    cin>>T;
    while(T--){
        cnt++;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>arr[i];
        }
        for(int k=20;k>=0;k--){
            int top=0;
            for(int i=1;i<=n;i++){
                if(arr[i]&(1<<k)){
                    tmp[++top]=arr[i];
                }
            }
            if(top>1){
                n=top;
                for(int i=1;i<=top;i++){
                    arr[i]=tmp[i];
                }
            }
        }
        printf("Case #%d: %d\n", cnt, arr[1]&arr[2]);
    }
    return 0;
}
