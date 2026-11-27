#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n;
int val[MAXN];
int sum[MAXN];
int ans[MAXN];

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>val[i];
        }
        sort(val+1,val+n+1);
        for(int i=1;i<=n;i++){
            sum[i]=sum[i-1]+val[i];
        }
        for(int i=1;i<=n;i++){
            ans[i]=0;
        }

        int now=n;
        for(int i=n;i>=3;i--){
            if(val[i]>=sum[i-1]&&i==now){
                now--;
                continue;
            }
            // if(val[i]>=sum[i-1]||now<=2){
            //     continue;
            // }
            if(val[i]>=(sum[i-1]-sum[i-now])||now<=2){
                continue;
            }
            int l=3,r=now,res=now;
            while(l<=r){
                int mid=(l+r)>>1;
                if(val[i]<(sum[i-1]-sum[i-mid])){
                    res=mid;
                    r=mid-1;
                }
                else{
                    l=mid+1;
                }
            }
            // cout<<i<<":  "<<res<<endl;
            for(int j=res;j<=now;j++){
                ans[j]=sum[i]-sum[i-j];
            }
            now=res-1;
        }

        for(int i=1;i<=n;i++){
            cout<<ans[i]<<' ';
        }
        cout<<endl;
    }
    return 0;
}
/*
1
5
1 2 3 4 5
*/