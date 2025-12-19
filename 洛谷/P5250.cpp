#include<bits/stdc++.h>
using namespace std;

int n,opt,length;
set<int >ds;
int main()
{
    cin>>n;
    while(n--){
        cin>>opt>>length;
        if(opt==1)
            if(ds.find(length)!=ds.end())
                cout<<"Already Exist"<<endl;
            else
                ds.insert(length);
        else if(ds.empty())
            cout<<"Empty"<<endl;
        else{
            auto i=ds.lower_bound(length),j=i;
            if(j!=ds.begin())
                --j;
            if(i!=ds.end()&&length-(*j)>(*i)-length)
                j=i;
            cout<<(*j)<<endl,ds.erase(j);
        }
    }
    return 0;
}
