// https://www.luogu.com.cn/problem/P4409
// 题意：n 名将军围成一圈（1 和 n 相邻），第 i 人需 a_i 枚不同颜色的勋章且相邻两人不能有同色勋章，求至少需要铸造多少种颜色的勋章。
// 数据范围：1 <= n <= 2 * 10^4，1 <= a_i <= 10^5。
#include<bits/stdc++.h>
using namespace std;

int n,sum,ans;
int arr[20005];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        sum+=arr[i];
        ans=max(arr[i]+arr[i-1],ans);
    }
    if(n==1){
        cout<<arr[1]<<endl;
        return 0;
    }
    ans=max(ans,arr[1]+arr[n]);
    ans=max(ans,(sum+n/2-1)/(n/2));
    cout<<ans<<endl;
    return 0;
}
