// https://www.luogu.com.cn/problem/P3939
// 题意：长度为 n 的序列第 i 个元素颜色为 a_i。依次执行 m 个操作：
// 1. 1 l_j r_j c_j：
// 查询区间 [l_j, r_j] 内颜色为 c_j 的兔子数量；
// 2. 2 x_j：交换第 x_j 和第 x_j + 1 只兔子的位置。
// 数据范围：
// n <= 3 * 10^5，1 操作次数 <= 3 * 10^5，2
// 操作次数 <= 3 * 10^5
// 1 <= a_i, c_j <= 3 * 10^5，
// 1 <= l_j < r_j <= n，1 <= x_j < n。
// 难度评分：1300（洛谷分级换算）
// 算法标签：二分查找、模拟
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

vector<int>vec[MAXN];
int arr[MAXN];
bool vis[MAXN];
int n,m;

int compute(int lt,int rt,int c){
    int ans1=0,ans2=vec[c].size();
    int l=0,r=vec[c].size()-1;
    while(l<=r){
        int mid=(l+r)/2;
        if(vec[c][mid]>=lt){
            ans1=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    l=0,r=vec[c].size()-1;
    while(l<=r){
        int mid=(l+r)/2;
        if(vec[c][mid]>rt){
            ans2=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans2-ans1;
}

void change(int c,int pos,int idea){
    int l=0,r=vec[c].size()-1,ans=0;
    while(l<=r){
        int mid=(l+r)/2;
        if(vec[c][mid]>=pos){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    vec[c][ans]=idea;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        vec[arr[i]].push_back(i);
    }
    for(int i=1;i<=n;i++){
        if(!vis[arr[i]]){
            vec[arr[i]].push_back(0);
            vec[arr[i]].push_back(INT_MAX);
            sort(vec[arr[i]].begin(),vec[arr[i]].end());
            vis[arr[i]]=true;
        }
    }
    for(int i=1;i<=m;i++){
        int op,l,r,c;
        cin>>op>>l;
        if(op==1){
            cin>>r>>c;
            cout<<compute(l,r,c)<<endl;
        }
        else{
            if(arr[l]!=arr[l+1]){
                change(arr[l],l,l+1);
                change(arr[1+l],l+1,l);
                int tmp=arr[l];
                arr[l]=arr[l+1];
                arr[l+1]=tmp;
            }
        }
    }
    return 0;
}
