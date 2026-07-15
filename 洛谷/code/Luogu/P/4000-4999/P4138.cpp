#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e3+5;

int n;
struct node{
    int val,cost;
}nums[MAXN];
int f[MAXN];
int arr[MAXN];
int s[MAXN];
int cnta,cntb;
int sum=0;
int cnt=0;

bool cmp(int a,int b){
    return a>b;
}

int main()
{
    cnt=1;
    cin>>n;
    for(int i=1;i<=n;i++){
        int u,v;
        cin>>u>>v;
        if(u==0){
            if(v<=0){
                //i--,n--;
            }
            else{
                ++cntb;
                arr[cntb]=v;
            }
        }
        else{
            if(v>=0){
                cnt+=v-1,sum+=v;
            }
            else{
                ++cnta;
                nums[cnta].val=u-1,nums[cnta].cost=v;
            }
        }
    }
    cnt=min(cnt,n);

    for(int i=0;i<=2000;i++){
        f[i]=-1e9;
    }
    for(int i=0;i<=cnt;i++){
        f[i]=0;
    }
    for(int i=1;i<=cnta;i++){
        for(int j=2000;j>=nums[i].val;j--){
            f[j]=max(f[j],f[j-nums[i].val]+nums[i].cost);
        }
    }
    for(int i=n-1;i>=0;i--){
        f[i]=max(f[i+1],f[i]);
    }
    sort(arr+1,arr+cntb+1,cmp);
    for(int i=1;i<=2000;i++){
        s[i]=s[i-1]+arr[i];
    }
    int ans=0;
    for(int i=0;i<=2000;i++){
        ans=max(ans,f[i]+s[i]);
    }
    cout<<(ans+sum)<<endl;
    return 0;
}
