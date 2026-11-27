// https://www.luogu.com.cn/problem/P5980
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n;
struct node{
    int l,a;
};
node nums1[MAXN];
node nums2[MAXN];

bool cmp(node a,node b){
    return a.a<b.a;
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int l,a,b;
        cin>>l>>a>>b;
        nums1[i]={l,a};
        nums2[i]={l,b};
    }
    sort(nums1+1,nums1+n+1,cmp);
    sort(nums2+1,nums2+n+1,cmp);

    int i=1,j=1;
    int sum1=0,sum2=0;
    bool flag=true;
    while(i<=n&&j<=n){
        // cout<<i<<' '<<j<<endl;
        int len=min(nums1[i].l,nums2[j].l);
        // cout<<len<<endl;
        sum1+=len*nums1[i].a;
        sum2+=len*nums2[j].a;
        if(sum1>sum2){
            flag=false;
            break;
        }

        nums1[i].l-=len;
        nums2[j].l-=len;

        if(nums1[i].l==0){
            i++;
        }
        if(nums2[j].l==0){
            j++;
        }
    }
    if(sum1!=sum2){
        flag=false;
    }

    if(flag){
        cout<<"TAK"<<endl;
    }
    else{
        cout<<"NIE"<<endl;
    }
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
