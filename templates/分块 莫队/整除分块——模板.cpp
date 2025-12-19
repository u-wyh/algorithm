// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2521
// 这道题是整除分块的模板题  时间复杂度是O(根号n)级别的
// 因为对于i小于根号n的情况而言  最多也就只有根号n个数字  那么最多分成根号n个块
// 对于i大于根号n的数字而言   n/根号n是小于等于根号n的   最多也就只是分成根号n个块
#include<bits/stdc++.h>
using namespace std;
#define int long long

int compute(int n){
    if(n<=0){
        return 0;
    }
    int l=1,r;
    int ans=0;
    while(l<=n){
        int k=n/l;
        r=n/k;
        ans+=k*(r-l+1);
        l=r+1;
    }
    return ans;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        cout<<compute(n)<<endl;
    }
    return 0;
}