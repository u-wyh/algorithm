#include<bits/stdc++.h>
using namespace std;

int n,m;
string ans;

int main()
{
    cin>>n>>m;
    getchar();
    ans="Wo AK le";
    string s1="qiandao";
    string s2="easy";
    for(int i=1;i<=n;i++){
        string str;
        getline(cin,str);
        if(str.find(s1)==string::npos&&str.find(s2)==string::npos){
            m--;
            if(m==-1){
                ans=str;
                break;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}