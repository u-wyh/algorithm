#include<bits/stdc++.h>
using namespace std;

int n,m;
string str[35];

string pos1="easy";
string pos2="qiandao";
string ans="Wo AK le";

int main()
{
    cin>>n>>m;
    getchar();
    for(int i=1;i<=n;i++){
        getline(cin,str[i]);
    }
    for(int i=1;i<=n;i++){
        if(str[i].find(pos1)==string::npos&&str[i].find(pos2)==string::npos){
            m--;
            if(m==-1){
                ans=str[i];
                break;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}