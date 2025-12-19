#include<bits/stdc++.h>
using namespace std;

string s1,s2;

string compute(string s){
    string str;
    if(s.size()==0){
        return str;
    }
    for(int i=1;i<(int)s.size();i++){
        if(s[i]%2==s[i-1]%2){
            str+=max(s[i],s[i-1]);
        }
    }
    return str;
}

int main()
{
    cin>>s1>>s2;
    string s3=compute(s1);
    string s4=compute(s2);

    if(s3==s4){
        cout<<s3<<endl;
    }
    else{
        cout<<s3<<endl<<s4<<endl;
    }
    return 0;
}