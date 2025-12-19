#include<bits/stdc++.h>
using namespace std;
#define int long long

long long a[100010],c[100010],top,n,t;

//int fun(long long num){
//    int l = 1, r = top, ans = 0; // 将 ans 初始化为 0，表示如果找不到则应该插入的位置
//    while(l <= r){
//        int mid = l + (r - l) / 2; // 避免整数溢出
//        if(c[mid] >= num){
//            ans = mid; // 更新 ans 为当前 mid，因为 c[mid] >= num
//            r = mid - 1; // 继续在左半部分查找
//        } else {
//            l = mid + 1; // 在右半部分查找
//        }
//    }
//    return ans;
//}

int fun(long long num){
    int l=1,r=top,ans=0;
    while(l<=r){
        //cout<<666<<endl;
        int mid=l+(r-l)/2;
        if(c[mid]>num){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

signed main()
{
    long long p,v;
    cin>>n>>t;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",&p,&v);
        a[i]=p+v*t;
    }
    for(int i=n;i>=1;i--)
    {
        if(!top||a[i]>=c[top])
            c[++top]=a[i];
        else{
            int t=fun(a[i]);
            //system("pause");
            c[t]=a[i];
        }
    }
    printf("%lld\n",top);
}
