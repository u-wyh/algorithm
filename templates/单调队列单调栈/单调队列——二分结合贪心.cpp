// 你可以安排的最多任务数目
// 给你 n 个任务和 m 个工人。每个任务需要一定的力量值才能完成
// 需要的力量值保存在下标从 0 开始的整数数组 tasks 中，
// 第i个任务需要 tasks[i] 的力量才能完成
// 每个工人的力量值保存在下标从 0 开始的整数数组workers中，
// 第j个工人的力量值为 workers[j]
// 每个工人只能完成一个任务，且力量值需要大于等于该任务的力量要求值，即workers[j]>=tasks[i]
// 除此以外，你还有 pills 个神奇药丸，可以给 一个工人的力量值 增加 strength
// 你可以决定给哪些工人使用药丸，但每个工人 最多 只能使用 一片 药丸
// 给你下标从 0 开始的整数数组tasks 和 workers 以及两个整数 pills 和 strength
// 请你返回 最多 有多少个任务可以被完成。
// 测试链接 : https://leetcode.cn/problems/maximum-number-of-tasks-you-can-assign/
#include<bits/stdc++.h>
using namespace std;

int n,m,s,pills;
int workers[10000],tasks[10000];
int h,t;
int q[10005];

bool check(int tl,int tr,int wl,int wr){
    //要完成任务的编号区间是tl到tr
    //完成这些任务的工人编号区间是wl到wr
    //并且一定是这些工人来做这些任务 都要匹配上 看看最少需要几颗药丸
    //这道题利用的是双端队列  这个队列里装着的是解锁的任务
    //对于每一个工人 我们都必须为他分配一个任务  否则最终答案对不上
    h=t=0;
    int cnt=0;
    for(int i=wl,j=tl;i<=wr;i++){
        //任务指针j从最小的开始 不回退
        for(;j<=wr&&tasks[j]<=workers[i];j++){
            //如果当前的工人力量大于任务难度  那么直接解锁任务  并将任务加入队列
            q[t++]=j;
        }
        //然后检查队列里有没有元素
        if(h<t&&tasks[q[h]]<=workers[i]){
            //如果有元素并比自己小  那么就将这个作为自己的任务
            h++;
        }else{
            //如果有元素但是这个之比自己要大（说明这是之前工人吃了药加进来的）
            //那么这个工人也要吃药  继续解锁任务  直到无法继续解锁
            for(;j<=wr&&tasks[j]<=workers[i]+s;j++){
                q[t++]=j;
            }
            if(h<t){
                //将队列里最后一个元素移除  这样可以最大程度上的利用药效
                cnt++;
                t--;
            }else{
                //如果在吃了一颗药之后 还是不行 说明这个人没有任务可以做
                //那么直接结束
                return false;
            }
        }
    }
    return cnt<=pills;
}

int main()
{
    cin>>n>>m>>s>>pills;
    for(int i=0;i<n;i++)
        cin>>workers[i];
    for(int j=0;j<m;j++)
        cin>>tasks[j];
    sort(workers,workers+n);
    sort(tasks,tasks+m);
    int ans=-1;
    for (int l = 0, r = min(m, n), mid; l <= r;) {
        // m中点，一定要完成的任务数量
        mid = (l + r) / 2;
        if (check(0, mid - 1,n-mid,n-1)) {
            //如果做mid个任务 一定是这些任务和这些工人  这是最优的情况了
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout<<ans<<endl;
    return 0;
}