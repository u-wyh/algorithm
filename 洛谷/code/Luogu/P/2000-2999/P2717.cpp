#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,k;
int nums[MAXN];
int arr[MAXN],m=1;//前缀和数组  要去重  m是实际有效数组长度
int tree[MAXN];//树状数组统计信息

bool cmp(int a,int b){
    return a>b;
}

void add(int i, int c) {
    while (i <= m) {
        tree[i] += c;
        i += i & -i;
    }
}

int sum(int i) {
    int ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= i & -i;
    }
    return ans;
}

int ranking(int v){
    int left = 1, right = m, mid, ans = 0;
    while (left <= right) {
        mid = (left + right) / 2;
        if (arr[mid] >= v) {
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
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        nums[i]-=k;
        arr[i]=arr[i-1]+nums[i];//完成前缀和数组统计
    }
    sort(arr+1,arr+n+1,cmp);
    for(int i=2;i<=n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    int ans=0;
    int temp=0;
    for(int i=1;i<=n;i++){
        temp+=nums[i];
        ans+=sum(ranking(temp));
        if(temp<=0){
            ans++;
        }
        add(ranking(temp),1);
    }
    cout<<ans<<endl;
    return 0;
}
