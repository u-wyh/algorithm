#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int s[MAXN];
int t[MAXN];

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>s[i];
        }
        for(int i=1;i<=n;i++){
            cin>>t[i];
        }
        sort(s+1,s+n+1);
        sort(t+1,t+n+1);
        bool flag=false,flag1=false,flag2=false;
        for(int i=1;i<=n;i++){
            if(s[i]!=t[i]){
                flag=true;
                break;
            }
        }
        if(!flag){
            cout<<"Yes"<<endl;
            continue;
        }
        for(int i=1;i<n;i++){
            if(s[i]+1==s[i+1]){
                flag1=true;
            }
            if(t[i]+1==t[i+1]){
                flag2=true;
            }
        }
        if(!flag1||!flag2){
            cout<<"No"<<endl;
            continue;
        }
        int t1=0,t2=0;
        for(int i=1;i<=n;i++){
            if(s[i]%2==0){
                t1++;
            }
            else{
                t2++;
            }
            if(t[i]%2==0){
                t1--;
            }
            else{
                t2--;
            }
        }
        if(t1||t2){
            cout<<"No"<<endl;
        }
        else{
            cout<<"Yes"<<endl;
        }
    }
    return 0;
}