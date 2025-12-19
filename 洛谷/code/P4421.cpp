#include<bits/stdc++.h>
using namespace std;

map<string,int>cnt;
map<string,int>ok;
int n;
string str[20005];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>str[i];
    }
    //cout<<endl;
    for(int i=1;i<=n;i++){
        //cout<<i<<':'<<endl;
        for(int j=1;j<=str[i].length();j++){
            for(int k=0;k+j<=str[i].length();k++){
                string s1=str[i].substr(k,j);
                if(ok[s1]!=i){
                    //cout<<s1<<endl;
                    cnt[s1]++;
                    ok[s1]=i;
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        ans+=cnt[str[i]];
    }
    ans-=n;
    cout<<ans<<endl;
    return 0;
}
