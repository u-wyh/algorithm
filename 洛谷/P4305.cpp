#include<bits/stdc++.h>
using namespace std;

int t,n;
unordered_map<int ,bool>ds;

int main()
{
    cin>>t;
    while(t--){
        cin>>n;
        int x;
        while(n--){
            cin>>x;
            if(!ds[x]){
                cout<<x<<' ';
                ds[x]=1;
            }
        }
        ds.clear();
        printf("\n");
    }
    return 0;
}
