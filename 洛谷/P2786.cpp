#include<bits/stdc++.h>
using namespace std;

int n,mod;
map<string ,int>val;

int main()
{
    cin>>n>>mod;
    for(int i=1;i<=n;i++){
        string str;
        int v;
        cin>>str>>v;
        val[str]=v;
    }
    getchar();
    int ans=0;
    char c=getchar();
    string s="";
    while(c!=EOF){
        if(c!=' '&&c!=','&&c!='.'&&c!='!'&&c!='?'&&c!='\n'){
            s+=c;
        }
        else{
            ans+=val[s];
            ans%=mod;
            s="";
        }
        //ans%=mod;
        //cout<<ans<<endl;
        c=getchar();
    }
    ans%=mod;
    cout<<ans<<endl;
    return 0;
}
