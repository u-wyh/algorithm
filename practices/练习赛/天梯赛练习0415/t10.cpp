#include<bits/stdc++.h>
using namespace std;

int n,m;
unordered_map<string,vector<string>>mp;

string compute(string s){
    string str;
    str+=to_string(s[0]);
    for(int i=1;i<s.size();i++){
        if(s[i-1]==' '&&s[i]!=' '){
            str+=to_string(s[i]);
        }
    }
    return str;
}

int main()
{
    cin>>n;
    getchar();
    string s;
    for(int i=1;i<=n;i++){
        getline(cin,s);
        mp[compute(s)].push_back(s);
    }
    cin>>m;
    getchar();
    for(int i=1;i<=m;i++){
        getline(cin,s);
        string tmp=compute(s);
        if(mp[tmp].size()==1){
            cout<<mp[tmp][0]<<endl;
        }
        else if(mp[tmp].size()>1){
            sort(mp[tmp].begin(),mp[tmp].end());
            cout<<mp[tmp][0];
            for(int j=1;j<(int)mp[tmp].size();j++){
                cout<<"|"<<mp[tmp][j];
            }
            cout<<endl;
        }
        else{
            cout<<s<<endl;
        }
    }
    return 0;
}