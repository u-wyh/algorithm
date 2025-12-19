#include<bits/stdc++.h>
using namespace std;

int main()
{
    int T;
    cin>>T;
    while(T--){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        if(((a+b+c)*d)==(a*b*c*d)){
            cout<<"AC"<<endl;
        }
        else{
            cout<<"WA"<<endl;
        }
    }
    return 0;
}