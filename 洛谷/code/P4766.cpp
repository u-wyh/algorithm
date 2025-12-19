#include<bits/stdc++.h>
using namespace std;

int n,m;

int a[305];
int b[305];
int d[305];

int st[605];
int en[605];
int cost[605];

int help[605];

int f[605][605];

int find(int val){
    int l=1,r=m,ans=1;
    while(l<=r){
        int mid=(l+r)/2;
        if(help[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        m=1;
        for(int i=1;i<=n;i++){
            cin>>a[i]>>d[i]>>b[i];
            help[2*i-1]=a[i];
            help[2*i]=b[i];
        }
        sort(help+1,help+2*n+1);
        for(int i=2;i<=2*n;i++){
            if(help[i]!=help[i-1]){
                help[++m]=help[i];
            }
        }
        for(int i=1;i<=n;i++){
            a[i]=find(a[i]);
            b[i]=find(b[i]);
        }
        for(int i=1;i<=m;i++){
            st[i]=INT_MAX;
            en[i]=INT_MIN,cost[i]=INT_MIN;
        }
        for(int i=1;i<=n;i++){
            for(int j=a[i];j<=b[i];j++){
                st[j]=min(st[j],a[i]);
                en[j]=max(en[j],b[i]);
                cost[j]=max(cost[j],d[i]);
            }
        }
        // for(int i=1;i<=m;i++){
        //     cout<<i<<": "<<st[i]<<' '<<en[i]<<' '<<cost[i]<<endl;
        // }
        for(int i=1;i<=m;i++){
            for(int j=1;j<=m;j++){
                f[i][j]=INT_MAX;
            }
        }
        for(int len=1;len<=m;len++){
            for(int l=1;l<=m-len+1;l++){
                int r=l+len-1;
                for(int k=l;k<=r;k++){
                    f[l][r]=min(f[l][r],cost[k]+(st[k]<=l?0:f[l][st[k]-1])+(en[k]>=r?0:f[en[k]+1][r]));
                }
                cout<<l<<' '<<r<<' '<<f[l][r]<<endl;
            }
        }
        cout<<f[1][m]<<endl;
    }
    return 0;
}