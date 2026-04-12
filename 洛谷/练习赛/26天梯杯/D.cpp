#include<bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    while(getline(cin,s)){
        int len=s.length();
        if(s[len-1]=='#'){
            for(int i=0;i<len-1;i++){
                cout<<s[i];
            }
            break;
        }
        cout<<s<<endl;
    }
    return 0;
}