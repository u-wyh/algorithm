#include<bits/stdc++.h>
using namespace std;

struct meeting{
    int st,en,val;
}nums[150005];
int n;
int dp[150005];

bool cmp(meeting a,meeting b){
    return a.en<b.en;
}

// 0...i范围上的会议，根据结束日期排序了
// 找到结束时间<s，最右的会议编号
// 如果不存在这样的会议返回-1
int find(int i, int s) {
	int l = 1, r = i, mid;
	int ans = 0;
	while (l <= r) {
		mid = (l + r) / 2;
		if (nums[mid].en < s) {
			ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].st>>nums[i].en;
        nums[i].val=nums[i].en-nums[i].st+1;
    }
    sort(nums+1,nums+n+1,cmp);
    for(int i=1 ; i<=n ; ++i) {
		dp[i]=max(dp[i-1],dp[find(i-1,nums[i].st)]+nums[i].val);
	}
    cout<<dp[n]<<endl;
    return 0;
}

