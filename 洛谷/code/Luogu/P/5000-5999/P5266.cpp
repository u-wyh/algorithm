#include<bits/stdc++.h>
using namespace std;

int n,opt,num,ans;
string name;
map<string ,int >ds;

int main()
{
    cin>>n;
    while(n--){
        cin>>opt;
        if(opt==1){
            cin>>name>>num;
            ds[name]=num;
            cout<<"OK"<<endl;
        }else if(opt ==2){
            cin>>name;
            if(ds.find(name)!=ds.end())
                cout<<ds[name]<<endl;
            else
                cout<<"Not found"<<endl;
        }else if(opt==3){
            cin>>name;
            if(ds.find(name)!=ds.end()){
                ds.erase(ds.find(name));
                cout<<"Deleted successfully"<<endl;
            }else
                cout<<"Not found"<<endl;
        }else
            cout<<ds.size()<<endl;
    }
    return 0;
}
