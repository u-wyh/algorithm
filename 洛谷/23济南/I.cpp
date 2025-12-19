#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

int n;
int val[MAXN];

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>val[i];
        }
        vector<pair<int,int>>vec;
        for(int i=1;i<=n;i++){
            if(val[i]!=i){
                for(int j=n;j>=i;j--){
                    if(val[i]>val[j]){
                        vec.push_back({i,j});
                        sort(val+i,val+j+1);
                        break;
                    }
                }
            }
        }
        cout<<vec.size()<<endl;
        for(int i=0;i<(int)vec.size();i++){
            cout<<vec[i].first<<' '<<vec[i].second<<endl;
        }
    }
    return 0;
}