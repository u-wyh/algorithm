#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e3+5;

int n,m;
map<string,vector<string>>mp1;
map<string,vector<string>>mp2;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        string a,b;
        cin>>a>>b;
        mp1[a].push_back(b);
        mp2[b].push_back(a);
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        string t;
        cin>>t;
        bool flag=false;
        for(string s:mp1[t]){
            for(string ss:mp2[s]){
                if(ss!=t){
                    flag=true;
                    cout<<ss<<' ';
                    break;
                }
            }
            if(flag){
                break;
            }
        }
        if(!flag){
            cout<<t<<' ';
        }
    }
    return 0;
}