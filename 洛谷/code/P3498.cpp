#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int BASE = 1313131;

int n;
int s1[MAXN],s2[MAXN];
long long h1[MAXN],h2[MAXN];
long long p[MAXN];
map<long long ,int>m;
int ans=0;
int t[MAXN],cnt=0;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s1[i];
    }
    p[0]=1;
    for(int i=1;i<=n;i++){
        p[i]=p[i-1]*BASE;
    }
    for(int i=1;i<=n;i++){
        h1[i]=h1[i-1]*BASE+s1[i];
    }
    for(int i=n;i>=1;i--){
        h2[i]=h2[i+1]*BASE+s1[i];
    }
    for(int k=1;k<=n;k++){
        int tmp=0;
        for(int i=1;i+k-1<=n;i+=k){
            if((n-i+1)/k+tmp<ans){
                continue;
            }
            int j=i+k-1;
            long long val1=h1[j]-h1[i-1]*p[k];
            long long val2=h2[i]-h2[j+1]*p[k];
            if(m[val1]!=k&&m[val2]!=k){
                tmp++;
                m[val1]=k;
                m[val2]=k;
            }
        }
        if(tmp>ans){
            ans=tmp;
            cnt=1;
            t[cnt]=k;
        }
        else if(tmp==ans){
            cnt++;
            t[cnt]=k;
        }
    }
    cout<<ans<<' '<<cnt<<endl;
    for(int i=1;i<=cnt;i++){
        cout<<t[i]<<' ';
    }
    return 0;
}
