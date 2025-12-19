#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;

int n;
int nums[MAXN];
int val[MAXN];//val[i]表示i的随机哈希值
int ans[MAXN];//表示从1到i的随机哈希值的异或结果
int pre[MAXN];//对于当前的数组 记录哈希前缀和
int res;//记录答案

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=1;i<=n;i++){
        val[i]=rand()/double(RAND_MAX)*10000000;
        ans[i]=ans[i-1]^val[i];
    }
    for(int i=1;i<=n;i++){
        pre[i]=pre[i-1]^val[nums[i]];
    }
    int j=1;
    //枚举每个数字从左往右的答案  必须跨过1  看看这个位置上能不能是答案
    for(int i=1;i<=n;i++){
        if(nums[i]==1){
            //单独的一个1  就是一个答案
            res++;
            j=1;
        }
        else{
            j=max(j,nums[i]);
            if(i>=j&&(pre[i]^pre[i-j])==ans[j]){
                res++;
            }
        }
    }

    //逆置数组
    for(int i=1;n-i+1>=i;i++){
        swap(nums[i],nums[n-i+1]);
    }

    for(int i=1;i<=n;i++){
        pre[i]=pre[i-1]^val[nums[i]];
    }
    j=1;
    for(int i=1;i<=n;i++){
        if(nums[i]==1){
            j=1;
        }
        else{
            j=max(j,nums[i]);
            if(i>=j&&(pre[i]^pre[i-j])==ans[j]){
                res++;
            }
        }
    }
    cout<<res<<endl;
    return 0;
}