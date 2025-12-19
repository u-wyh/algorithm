#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
char s[MAXN];
int cnt1;

int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",s+1);
        n=strlen(s+1);
        cnt1=0;
        for(int i=1;i<=n;i++){
            if(s[i]==')'){
                s[i]='(';
            }
            else if(s[i]==']'){
                s[i]='[';
            }
        }
        bool flag=false;
        for(int i=1;i<=n-2;i++){
            if(s[i]==s[i+1]&&s[i+1]==s[i+2]){
                flag=true;
                break;
            }
        }
        
        if(flag){
            cout<<"No"<<endl;
            continue;
        }
        for(int i=1;i<n;i++){
            if(s[i]==s[i+1]){
                cnt1++;
            }
        }
        if(cnt1>=3){
            cout<<"No"<<endl;
        }
        else{
            cout<<"Yes"<<endl;
        }
    }
    return 0;
}