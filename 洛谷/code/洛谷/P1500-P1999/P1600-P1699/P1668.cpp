// https://www.luogu.com.cn/problem/P1668
// 题意：一天有 1 到 T 号时段，每头牛可以在闭区间 [S,E] 值班。
// 挑尽量少的牛，使每个时段都至少有一头牛覆盖。无解输出 -1。
// 数据范围：1 ≤ N ≤ 25000，1 ≤ T ≤ 10^6，
// 1 ≤ S ≤ E ≤ T。
// 算法标签：贪心、排序

#include<bits/stdc++.h>
using namespace std;

struct node{
    int st,en;
}nums[25005];
int n,t;

bool cmp(node a,node b){
    if(a.st==b.st){
        return a.en>b.en;
    }
    return a.st<b.st;
}

int fun(int x,int tmp){
    int ans=-1,temp=tmp;
    for(int i=x;i<=n;i++){
        if(nums[i].st>tmp){
            //cout<<i<<' '<<tmp<<endl;
            break;
        }
        if(nums[i].st<=tmp&&nums[i].en>=temp){
            temp=nums[i].en;
            ans=i;
        }
    }
    return ans;
}

int main()
{
    cin>>n>>t;
    int en=0;
    for(int i=1;i<=n;i++){
        cin>>nums[i].st>>nums[i].en;
        en=max(en,nums[i].en);
    }
    sort(nums+1,nums+n+1,cmp);
//    for(int i=1;i<=n;i++){
//        cout<<' '<<nums[i].st<<' '<<nums[i].en<<endl;
//    }
    if(nums[1].st!=1||en<t){
        cout<<-1<<endl;
        return 0;
    }
    int tmp=nums[1].en+1,ans=1,k=1;
    while(tmp<=t){
        k=fun(k+1,tmp);
        //cout<<' '<<k<<endl;
        if(k==-1){
            cout<<-1<<endl;
            return 0;
        }
        tmp=nums[k].en+1;
        ans++;
    }
    cout<<ans;
    return 0;
}
