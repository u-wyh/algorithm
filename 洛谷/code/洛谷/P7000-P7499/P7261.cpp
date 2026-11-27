// https://www.luogu.com.cn/problem/P7261
// 题意：长为 n 的颜色序列（颜色 1..c），
// m 次询问区间 [a, b] 内是否存在出现次数严格大于区间长度一半的颜色，
// 若存在输出 yes 和该颜色
// 否则输出 no。
// 数据范围：1 <= m <= 10^4，3 <= n <= 3*10^5，
// 1 <= c <= 10^4，1 <= a <= b <= n。
//P7261
// 算法标签：莫队
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int MAXM = 1e4+5;
const int MAXC = 1e4+5;

int n,m,c;
struct node{
    int l,r,id,k;
}nums[MAXM];
int arr[MAXN];
int pos[MAXN];
int cnt[MAXC];
int ans[MAXM];

//奇偶性排序优化
bool cmp(node a,node b) {
	return (pos[a.l] ^ pos[b.l]) ? pos[a.l] < pos[b.l] : ((pos[a.l] & 1) ? a.r < b.r : a.r > b.r);
}
//对于左端点在同一奇数块的区间，右端点按升序排列，反之降序。这个东西也是看着没用，但实际效果显著。

int main()
{
    cin>>n>>c;
    int siz=sqrt(n);
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        pos[i]=i/siz;
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>nums[i].l>>nums[i].r;
        nums[i].k=nums[i].r-nums[i].l+1;
        nums[i].id=i;
    }
    sort(nums+1,nums+m+1,cmp);
    int l=1,r=0;
    for(int i=1;i<=m;i++){
        while(nums[i].l<l) cnt[arr[--l]]++;
        while(nums[i].r>r) cnt[arr[++r]]++;
        while(nums[i].l>l) cnt[arr[l++]]--;
        while(nums[i].r<r) cnt[arr[r--]]--;
        int k=nums[i].k/2+1;
        for(int j=1;j<=c;j++){
            if(cnt[j]>=k){
                ans[nums[i].id]=j;
                break;
            }
        }
    }
    for(int i=1;i<=m;i++){
        if(ans[i]){
            cout<<"yes "<<ans[i]<<endl;
        }
        else{
            cout<<"no"<<endl;
        }
    }
    return 0;
}
