#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int val[MAXN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    sort(val+1,val+n+1);
    int ans=0;
    for(int i=1;i<=n;i++){
        if(val[i]<=ans){
            ans++;
        }
        else{
            ans--;
        }
    }
    cout<<ans<<' ';
    ans=0;
    for(int i=n;i>=1;i--){
        if(val[i]<=ans){
            ans++;
        }
        else{
            ans--;
        }
    }
    cout<<ans<<endl;
    return 0;
}