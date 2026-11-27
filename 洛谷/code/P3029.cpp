// https://www.luogu.com.cn/problem/P3029
// 题意：输入奶牛数 N，以及每头牛在直线上的位置 x 坐标和对应的品种 ID。
// 选取直线上的一个闭区间拍摄照片，要求照片内包含牛群中所有出现过的不同品种（至少各一头）。
// 照片成本等于区间内奶牛的最大 x 坐标与最小 x 坐标之差，求最小成本。
// 输出一行一个整数，表示满足条件的照片最小成本。
// 数据范围：对于 100% 的数据，1 <= N <= 50000，x 坐标与品种 ID 均为正整数且不超过 10^9。
#include<bits/stdc++.h>
// 算法标签：双指针、离散化、排序
using namespace std;
const int MAXN = 50005;

struct node{
    int pos,id;
}nums[MAXN];
int arr[MAXN];
int q[MAXN];
int n,m;
int ans=INT_MAX;

bool cmp(node a,node b){
    return a.pos<b.pos;
}

// 当前的指标值是v，返回这是第几号指标
int Rank(int v) {
	int left = 1, right = m, mid;
	int ans = 0;
	while (left <= right) {
		mid = (left + right) / 2;
		if (arr[mid] <= v) {
			ans = mid;
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].pos>>nums[i].id;
        arr[i]=nums[i].id;
    }
    sort(arr+1,arr + n + 1);
    m = 1;
    for (int i = 2; i <= n; i++) {
        if (arr[m] != arr[i]) {
            arr[++m] = arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i].id=Rank(nums[i].id);
    }
    sort(nums+1,nums+n+1,cmp);
    int cnt[m+1];
    for(int i=0;i<=m;i++){
        cnt[i]=0;
    }
    int kind=0;
    int head=1,tail=1;
    for(int i=1;i<=n;i++){
        q[tail++]=i;
        if(cnt[nums[i].id]==0){
            kind++;
        }
        cnt[nums[i].id]++;
        while(head<tail&&cnt[nums[q[head]].id]>1){
            cnt[nums[q[head]].id]--;
            head++;
        }
        if(kind==m){
            ans=min(ans,nums[q[tail-1]].pos-nums[q[head]].pos);
        }
    }
    cout<<ans<<endl;
    return 0;
}
