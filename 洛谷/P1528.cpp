#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;
const int MAXM = 1050;

int n,m;
int arr[MAXN];
int nums[MAXM];
int pre[MAXM];
int sum;

int totalCake;
int needCake;
int wasteCake;

bool sub_DFS(int toTest, int origin)            // origin：遍历蛋糕数组的起点
{
    /* 结束递归 */
    if(toTest<1)
        return true;                            // 已经完成1~toTest的人的喂食，测试通过
    if(totalCake-wasteCake<needCake)
        return false;                           // 总蛋糕小于总需求，必然失败，停止搜索

    /* 搜索 */
    bool flag = false;
    for(int i=origin;i<=n;++i)                  // 遍历蛋糕，尝试将蛋糕喂给第toTest号人
    {
        if(arr[i]>=nums[toTest])
        {
            needCake-=nums[toTest];            // 喂食：消耗蛋糕，满足需求
            totalCake-=nums[toTest];
            arr[i]-=nums[toTest];

            bool wasted = false;                // 回溯：是否使用了蛋糕渣优化
            if(arr[i]<nums[1])                // 优化：蛋糕渣不能满足最低需求，不可用
            {
                wasteCake+=arr[i];             // 此蛋糕渣将被浪费，设置优化启动的标志
                wasted = true;
            }
            if(nums[toTest]==nums[toTest-1])  // 下一个测试对象的嘴和当前的嘴一样大
            {
                if(sub_DFS(toTest-1,i))         // 优化：从当前的位置继续遍历蛋糕列表
                    flag = true;                // 优化：找到解决方案，就不再继续搜索
            }
            else if(sub_DFS(toTest-1,1))        // 无法优化，直接递归。
                flag = true;                    // 优化：同上分支

            /* 回溯 */
            if(wasted)                          // 若做了优化，则撤回
                wasteCake-=arr[i];
            arr[i]+=nums[toTest];             // 撤回全部变化
            totalCake+=nums[toTest];
            needCake+=nums[toTest];

            if(flag)
                return true;
        }
    }

    /* 结束递归 */
    return false;                               // 无法找到合适的蛋糕，测试失败
}

inline bool DFS(int toTest)                     // DFS：检查答案toTest是否可行
{
    /* 准备变量 */
    totalCake = sum;
    needCake = pre[toTest];
    wasteCake = 0;

    /* 启动递归 */
    return sub_DFS(toTest,1);
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        sum+=arr[i];
    }
    sort(arr+1,arr+n+1);
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>nums[i];
    }
    sort(nums+1,nums+m+1);
    for(int i=1;i<=m;i++){
        pre[i]=pre[i-1]+nums[i];
    }
    int l=0,r=m;
    for(int i=1;i<=m;i++){
        if(nums[i]>arr[n]){
            r=i-1;
            break;
        }
        if(pre[i]>sum){
            r=i-1;
            break;
        }
    }
    int ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(DFS(mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    cout<<ans<<endl;
    return 0;
}
