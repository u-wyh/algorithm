#include <bits/stdc++.h>
using namespace std;

using LL = long long;

void solve(){
    int n,m;
    string s;
    cin>>n>>m>>s;
    if(s[1]=='4'||s[1]=='5'){
        cout<<"YES"<<endl;
    }
    else{
        if((m>=50)||(5*m>=n)){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}