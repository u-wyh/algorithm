#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int LIMIT = 17;

int stmax[MAXN][LIMIT];
int stmin[MAXN][LIMIT];
int arr[MAXN];
int log_2[MAXN];
int n,k,ans;

void build(int n){
    log_2[0]=-1;
    for(int i=1;i<=n;i++){
        log_2[i]=log_2[i>>1]+1;
        stmax[i][0]=arr[i];
        stmin[i][0]=arr[i];
    }
    for(int i=1;i<=log_2[n];i++){
        for(int j=1;j<=n;j++){
            stmax[j][i]=max(stmax[j][i-1],stmax[(j+(1<<(i-1)))>n?n:(j+(1<<(i-1)))][i-1]);
            stmin[j][i]=min(stmin[j][i-1],stmin[(j+(1<<(i-1)))>n?n:(j+(1<<(i-1)))][i-1]);
        }
    }
}

inline int query(int l,int r){
    int p=log_2[r-l+1];
    int maxans=max(stmax[l][p],stmax[r-(1<<p)+1][p]);
    int minans=min(stmin[l][p],stmin[r-(1<<p)+1][p]);
    return maxans-minans;
}

bool check(int x){
    int cnt=0;
    for(int i=1;i+x-1<=n;i++){
        if(query(i,i+x-1)>=ans){
            cnt++;
        }
        if(cnt>=k){
            return true;
        }
    }
    return false;
}

int main()
{
    int t;
    cin>>t;
    while(t--){
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>arr[i];
        }
        build(n);
        int len=n-k+1;
        ans=2e9;
        for(int i=1;i<=k;i++){
            ans=min(ans,query(i,i+len-1));
        }
        cout<<ans<<' ';
        int l=2,r=len,ans1=len;
        while(l<=r){
            int mid=(l+r)/2;
            if(check(mid)){
                ans1=mid;
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
        cout<<ans1<<endl;
    }
    return 0;
}
