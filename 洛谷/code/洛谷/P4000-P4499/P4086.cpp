// https://www.luogu.com.cn/problem/P4086
// 题意：第一行输入问题总数 N，第二行输入 N 个问题的得分。
// 选择去掉前 K 个问题（1 <= K <= N-2），
// 对剩下的 N-K 个问题去掉一个最低分后取平均值作为最终成绩。
// 按升序输出所有能使最终成绩达到最大值的 K，每行一个。
// 数据范围：3 <= N <= 100000，
// 每题得分在 [0, 10000] 内（1 <= K <= N-2）。
// 算法标签：前缀和、枚举
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int n;
int arr[MAXN],minarr[MAXN],ans[MAXN];
long long sum[MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        sum[i]=sum[i-1]+arr[i];
        //printf("%3d",sum[i]);
    }
    //printf("\n");
    minarr[n]=arr[n];
    for(int i=n-1;i>=1;i--){
        minarr[i]=min(minarr[i+1],arr[i]);
    }
    /*
    for(int i=1;i<=n;i++){
        printf("%3d",minarr[i]);
    }
    printf("\n");
    */
    int sz=1;
    long long K=0;
    for(int i=1;i<=(n-2);i++){
        long long temp=(sum[n]-sum[i]-minarr[i+1]);
        //printf("%lld %lld\n",temp,K);
        if(K*(n-i-1)<=temp){
            if(K*(n-i-1)==temp){
                ans[sz++]=i;
            }else{
                K=temp/(n-i-1);
                sz=1;
                ans[sz++]=i;
            }
        }
    }
    for(int i=1;i<sz;i++)
        cout<<ans[i]<<endl;
    return 0;
}
