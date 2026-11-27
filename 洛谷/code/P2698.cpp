// https://www.luogu.com.cn/problem/P2698
// 题意：N 滴水在 (x,y) 处以每秒 1 单位下落，在 x 轴放花盆（边沿对齐也算接住）。
// 求使接到的第一滴与最后一滴水时间差 >= D 的最小花盆宽度 W，无解输出 -1。
// 数据范围：1 <= N <= 10^5，1 <= D <= 10^6，0 <= x, y <= 10^6。
#include<bits/stdc++.h>
// 算法标签：双指针、单调队列、排序
using namespace std;

struct node{
    int x,y;
};
int n,d;
node nums[100005];
int maxq[100005],minq[100005],maxh,maxt,minh,mint;

void push(int r) {
    while (maxh < maxt && nums[maxq[maxt - 1]].y <= nums[r].y) {
        maxt--;
    }
    maxq[maxt++] = r;
    while (minh < mint && nums[minq[mint - 1]].y >= nums[r].y) {
        mint--;
    }
    minq[mint++] = r;
}

void pop(int l) {
    if (maxh < maxt && maxq[maxh] == l) {
        maxh++;
    }
    if (minh < mint && minq[minh] == l) {
        minh++;
    }
}

bool ok() {
    int max1 = maxh < maxt ? nums[maxq[maxh]].y:0;
    int min1 = minh < mint ? nums[minq[minh]].y:0;
    return max1 - min1 >=d;
}

int compute(){
    int ans=1e9;
    for(int l=0,r=0;l<n;l++){
        while(!ok()&&r<n){
            push(r++);
        }
        if(ok()){
            ans=min(ans,nums[r-1].x-nums[l].x);
        }
        pop(l);
    }
    return ans;
}

bool cmp(node a,node b){
    return a.x<b.x;
}

int main()
{
    cin>>n>>d;
    for(int i=0;i<n;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    sort(nums,nums+n,cmp);
    int ans=compute();
    if(ans==1e9)
        ans=-1;
    cout<<ans;
    return 0;
}
