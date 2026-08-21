#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n,m;
int cnt[MAXN][27];
string str;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>str;
        for(int p=1;p<=n;p++){
            cnt[p-1][str[p-1]-'a'+1]++;
        }
    }
    int limit=(m+1)/2;
    for(int i=0;i<n;i++){
        int ans=0;
        for(int j=1;j<=26;j++){
            if(cnt[i][j]>=limit){
                ans=j;
                break;
            }
        }
        str[i]='a'+ans-1;
    }
    cout<<str<<endl;
    return 0;
}