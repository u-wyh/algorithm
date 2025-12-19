#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;

int n,cnt=0;
struct node{
    int a,b;
}nums[MAXN];

bool cmp(node a,node b){
    return a.b==b.b?a.a<b.a:a.b<b.b;
}

signed main()
{
    cin>>n;
    int maxn=0;
    for(int i=1;i<=n;i++){
        int a,b;
        cin>>a>>b;
        maxn=max(maxn,max(a,b));
        if(a>b){
            nums[++cnt].a=a;
            nums[cnt].b=b;
        }
    }
    sort(nums+1,nums+cnt+1,cmp);
    int ans=LLONG_MAX,sum=0,lasa=0;
    for(int i=1;i<=cnt;i++){
        ans=min(ans,sum+maxn-nums[i].b);
        //相当于每次到达i i以后得全部是第二种方法  即先到最大然后减少
        //ans记录的是在i之前  最小的花费是多少
		sum+=2*(max(0ll,nums[i].a-max(lasa,nums[i].b)));
		//比如 （5,1）（7,3）  应该是变为（7,1）即（5,1）+（7，5）  因为5大于3
		lasa=max(lasa,nums[i].a);
    }
    ans=min(sum,ans)+maxn;
    cout<<ans<<endl;
    return 0;
}
