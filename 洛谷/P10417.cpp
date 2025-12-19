#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n,m;
long long k;
int a[MAXN],b[MAXN];

int find(int val,int l,int r){
    int ans=r+1;
    while(l<=r){
        int mid=(l+r)/2;
        if(b[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

bool check(int limit){
    long long ans=0;
    int l=1,r=m;
    for(int i=1;i<=n;i++){
        if(a[i]>limit){
            break;
        }
        r=find(limit-a[i]+1,l,r);
        r--;
        ans+=r;
    }
    return ans>=k;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=m;i++){
        cin>>b[i];
    }
    sort(a+1,a+n+1);
    sort(b+1,b+m+1);
    int l=a[1]+b[1],r=a[n]+b[m],ans=1;
    while(l<=r){
        int mid=(1ll*l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}