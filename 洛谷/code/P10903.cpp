// https://www.luogu.com.cn/problem/P10903
// 题意：n 种商品的库存起初都是 0，第 i 条操作给编号 L 到 R 的库存各加 1。
// 对每个 i 分别考虑只跳过第 i 条、执行其他所有操作，输出最终仍为 0 的商品数。
// 数据范围：1 ≤ n,m ≤ 3 × 10^5，1 ≤ L ≤ R ≤ n。

#include<bits/stdc++.h>
using namespace std;

int n,m,ans=0;
int l[300005],r[300005],nums[300005],cnt[300005];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>l[i]>>r[i];
        nums[l[i]]+=1,nums[r[i]+1]+=-1;
    }
    for(int i=1;i<=n;i++){
        nums[i]+=nums[i-1];
        if(nums[i]==0)
            ans++;
        if(nums[i]==1)
            cnt[i]=cnt[i-1]+1;
        else
            cnt[i]=cnt[i-1];
        //printf("%3d",nums[i]);
    }
    //printf("\n");
    for(int i=1;i<=m;i++){
        cout<<ans+(cnt[r[i]]-cnt[l[i]-1])<<endl;
    }
    return 0;
}
