#include<bits/stdc++.h>
using namespace std;
#define int long long

int one[33];
int len;
int ans[200];
int cnt;

signed main()
{
    int T;
    cin>>T;
    while(T--){
        int a,b,c;
        cin>>a>>b>>c;
        if(a==b&&b==c){
            cout<<0<<endl<<endl;
            continue;
        }
        if(a==b&&a==0){
            cout<<-1<<endl;
            continue;
        }
        if(a*4<b){
            ans[++cnt]=3;
            ans[++cnt]=4;
            b=a;
            a=a^b;
        }
        len=0;
        for(int i=0;i<=31;i++){
            if((c>>i)&1){
                one[++len]=i;
            }
        }
        cnt=0;
        while(b!=1){
            ans[++cnt]=2;
            b>>=1;
        }
        if(a!=1){
            b=a^b;
            a=1;
            ans[++cnt]=4;
            ans[++cnt]=3;
        }
        while(b!=1){
            ans[++cnt]=2;
            b>>=1;
        }
        for(int i=len;i>=2;i--){
            for(int j=1;j<=ans[len]-ans[len-1]+1;j++){
                ans[++cnt]=1;
            }
            ans[++cnt]=3;
        }
        if(one[1]!=0){
            for(int i=1;i<=one[1];i++){
                ans[++cnt]=1;
            }
        }
        ans[++cnt]=2;
        ans[++cnt]=4;
        // if(cnt>64){
        //     cout<<-1<<endl;
        //     continue;
        // }
        cout<<cnt<<endl;
        for(int i=1;i<=cnt;i++){
            cout<<ans[i]<<' ';
        }
        cout<<endl;
    }
    return 0;
}