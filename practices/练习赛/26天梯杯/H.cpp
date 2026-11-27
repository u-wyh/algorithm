#include<bits/stdc++.h>
using namespace std;

int n;
string s;
string s1,s2;

int main()
{
    cin>>n>>s;
    while(n--){
        int op;
        cin>>op;
        if(op==1){
            cin>>s1;
            auto pos=s.find(s1);
            if(pos!=string::npos){
                cout<<pos;
            }
            else{
                cout<<-1;
            }
        }
        else if(op==2){
            cin>>s1>>s2;
            auto pos=s.find(s1);
            if(pos==string::npos){
                cout<<s;
            }
            else{
                string s5=s.substr(pos+s1.length());
                string s4=s.substr(0,pos);
                s=s4+s2+s5;
                cout<<s;
            }
        }
        else{
            char c1,c2;
            cin>>c1>>c2>>s2;
            int len=s2.length();
            s1="";
            s1+=c1;
            s1+=c2;
            // cout<<s1<<endl;
            auto pos=0;
            pos=s.find(s1,pos);
            while(pos!=string::npos){
                string s5=s.substr(pos+1);
                string s4=s.substr(0,pos+1);
                s=s4+s2+s5;
                pos=s.find(s1,pos+len+1);
            }
            cout<<s;
        }
        if(n){
            cout<<endl;
        }
    }
    return 0;
}