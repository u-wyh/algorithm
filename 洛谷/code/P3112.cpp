// https://www.luogu.com.cn/problem/P3112
// 题意：输入奶牛数 N、目标高度 H，以及每头牛的高度、重量和力量（力量指它上方能承受的最大总重量）。
// 选出一部分牛叠成一摞，使得总高度至少为 H，且每头牛上方叠的牛总重量不超过它的力量。
// 在所有达标的叠法中，最大化还能额外放到最顶端的重量（安全系数）；若怎么叠都达不到 H 则输出 Mark is too tall。
// 输出最大安全系数或 Mark is too tall。
// 数据范围：2 <= N <= 20，1 <= H <= 10^9，高度、重量和力量均为不超过 10^9 的正整数。
#include<bits/stdc++.h>
// 算法标签：状态压缩、贪心
using namespace std;

struct node{
    int h,w,p;
}nums[20];
int n,H;
int h[1<<20];
int w[1<<20];

bool cmp(node a,node b){
    return (a.w+a.p)>(b.w+b.p);
}

int fun(int k){
    for(int i=0;i<=20;i++){
        //cout<<pow(2,i)<<endl;
        if(pow(2,i)==k){
            return i;
        }
    }
    return 0;
}

int main()
{
    cin>>n>>H;
    for(int i=1;i<=n;i++){
        cin>>nums[i].h>>nums[i].w>>nums[i].p;
    }
    sort(nums+1,nums+n+1,cmp);
//    cout<<endl;
//    for(int i=1;i<=n;i++){
//        cout<<nums[i].h<<' '<<nums[i].w<<' '<<nums[i].p<<endl;
//    }
//    cout<<endl;
    h[0]=0;
    //cout<<endl;
    for(int i=1;i<(1<<n);i++){
        int k=i&(-i);
        int tmp=fun(k)+1;
        h[i]=nums[tmp].h+h[i-k];
        w[i]=nums[tmp].w+w[i-k];
        //cout<<i<<' '<<h[i]<<' '<<w[i]<<endl;
    }
    //cout<<endl;
    int ans=-1e9;
    for(int i=1;i<(1<<n);i++){
        if(h[i]>=H){
            int f=0;
            int tmp=1e9;
            int j,k=i,K=0;
            while(k){
                //cout<<666<<endl;
                j=k&-k;
                K+=j;
                int temp=fun(j)+1;
                //cout<<i<<' '<<h[i]<<' '<<temp<<endl;
                if(nums[temp].p<w[i^K]){
                    f=1;
                    break;
                }
                tmp=min(tmp,nums[temp].p-w[i^K]);
                k^=j;
            }
            if(f==0){
                ans=max(ans,tmp);
            }
        }
    }
    if(ans<0){
        cout<<"Mark is too tall"<<endl;
    }
    else{
        cout<<ans<<endl;
    }
    return 0;
}
