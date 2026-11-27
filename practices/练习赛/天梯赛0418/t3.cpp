#include<bits/stdc++.h>
using namespace std;

int main()
{
    string t;
    cin>>t;
    if(t.size()==6){
        cout<<t[0]<<t[1]<<t[2]<<t[3]<<'-'<<t[4]<<t[5];
    }
    else{
        if((t[0]-'0')*10+(t[1]-'0')<22){
            cout<<"20"<<t[0]<<t[1]<<'-'<<t[2]<<t[3];
        }
        else{
            cout<<"19"<<t[0]<<t[1]<<'-'<<t[2]<<t[3];
        }
    }
    return 0;
}