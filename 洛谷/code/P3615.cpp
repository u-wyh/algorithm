#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,m;
string s[MAXN];
int times[MAXN];

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>s[i]>>times[i];
    }
    int all=0;
    int ans=1;
    for(int i=m;i>=1;i--){
        int len=s[i].length();
        int t=times[i];

        int now=0;
        int maxx=0;
        for(int j=len-1;j>=0;j--){
            if(s[i][j]=='F'){
                now--;
            }
            else{
                now++;
            }
            maxx=max(maxx,now);
        }

        if(now>0){
            ans=max(ans,all+(t-1)*now+maxx);
        }
        else{
            ans=max(ans,maxx+all);
        }
        all+=t*now;
    }
    if(all>0){
        cout<<-1<<endl;
    }
    else{
        cout<<(ans-1)<<endl;
    }
    return 0;
}