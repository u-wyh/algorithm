#include<bits/stdc++.h>
using namespace std;

string aim[105];
string s;
string pos="<censored>";
int n,k;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>aim[i];
    }
    cin>>k;
    getchar();
    getline(cin,s);
    int ans=0;
    for(int i=1;i<=n;i++){
        while(s.find(aim[i])!=string::npos){
            ans++;
            s.replace(s.find(aim[i]),aim[i].size(),pos);
        }
    }
    if(ans>=k){
        cout<<ans<<endl<<"He Xie Ni Quan Jia!";
    }
    else{
        cout<<s<<endl;
    }
    return 0;
}