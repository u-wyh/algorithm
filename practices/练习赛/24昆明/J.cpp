#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int val[MAXN];
string name;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--){
        cin>>n>>name;
        for(int i=1;i<=n;i++){
            cin>>val[i];
        }
        if(n<=2){
            cout<<"Alice"<<endl;
            continue;
        }
        int cnt=0;
        for(int i=1;i<=n;i++){
            if(val[i]!=i){
                cnt++;
            }
        }
        if(cnt==0){
            cout<<"Alice"<<endl;
            continue;
        }
        if(cnt==2){
            cout<<name<<endl;
            continue;
        }
        if(cnt==3&&n==3){
            if(name=="Bob"){
                cout<<"Alice"<<endl;
                continue;
            }
        }
        cout<<"Bob"<<endl;
    }
    return 0;
}