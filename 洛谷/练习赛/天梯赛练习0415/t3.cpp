#include<bits/stdc++.h>
using namespace std;

int main()
{
    int a,b;
    cin>>a>>b;
    if(a==2||b==1){
        cout<<"-"<<endl;
        if(a==2){
            cout<<"stop"<<endl;
        }
        else if(a==1){
            cout<<"move"<<endl;
        }
        else{
            cout<<"stop"<<endl;
        }
    }
    else if(a==1){
        cout<<"dudu"<<endl<<"move"<<endl;
    }
    else{
        cout<<"biii"<<endl<<"stop"<<endl;
    }
    return 0;
}