#include<bits/stdc++.h>
using namespace std;

int main()
{
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    if(c>=a&&d>=a){
        cout<<c<<"-Y "<<d<<"-Y"<<endl;
        cout<<"huan ying ru guan"<<endl;
    }
    else if(c<a&&d<a){
        cout<<c<<"-N "<<d<<"-N"<<endl;
        cout<<"zhang da zai lai ba"<<endl;
    }
    else {
        int e=max(c,d);
        int f=min(c,d);
        if(e<b&&e>=a){
            if(e==c)
                cout<<e<<"-Y "<<f<<"-N"<<endl;
            else
                cout<<f<<"-N "<<e<<"-Y"<<endl;
            if(e==c){
                cout<<1;
            }
            else{
                cout<<2;
            }
            cout<<": huan ying ru guan";
        }
        else if(e>=b){
            cout<<c<<"-Y "<<d<<"-Y"<<endl;
            if(e==c){
                cout<<"qing 1 zhao gu hao 2";
            }
            else{
                cout<<"qing 2 zhao gu hao 1";
            }
        }
    }
    return 0;
}