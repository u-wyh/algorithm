#include<bits/stdc++.h>
using namespace std;
const int MAXN = 46;
const int MAXM = 1 << 23;

long arr[MAXN];
long lsum[MAXM];
long rsum[MAXM];
int n;
long w;

int f(int i, int e, long s, long* ans, int j) {
    if (s > w) {
        return j;
    }
    // s <= w
    if (i == e) {
        //表示到了可以选择的最后一个物品了  记录可行答案的值  填入相应的答案记录数组中
        ans[j++] = s;
    } else {
        // 不要arr[i]位置的数
        j = f(i + 1, e, s, ans, j);
        // 要arr[i]位置的数
        j = f(i + 1, e, s + arr[i], ans, j);
    }
    return j;
}
//递归函数  会一直递归到i==e

long compute(){
    int lsize = f(0, n >> 1, 0, lsum, 0);
    int rsize = f(n >> 1, n, 0, rsum, 0);
    sort(lsum, lsum+lsize);
    sort(rsum, rsum+rsize);
    long ans = 0;
    for (int i = lsize - 1, j = 0; i >= 0; i--) {
        while (j < rsize && lsum[i] + rsum[j] <= w) {
            ans=max(ans,lsum[i] + rsum[j]);
            j++;
        }
    }
    return ans;
}

int main()
{
    cin>>w>>n;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    cout<<compute();
    return 0;
}

