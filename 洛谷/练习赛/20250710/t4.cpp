#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n;
char s[MAXN];

int main()
{
    int T;
    cin>>T;
    while(T--){
        int n;
        scanf("%d",&n);
        scanf("%s",s+1);
        int cnt=0;
        for(int i=1;i<=n-2;i++){
            if(s[i]=='0'){
                cnt++;
            }
        }
        if(cnt==0||(cnt==1&&s[n-2]!='0')){
            cout<<-1<<endl;
            continue;
        }
        if(cnt==1){
            cout<<(n-1)<<endl;
        }
        else{
            cout<<n<<endl;
        }
        int one=1;
        int zero=1;
        for(int i=1;i<=n-2;i++){
            if(s[i]=='0'){
                cout<<zero<<' '<<(i+1)<<endl;
                zero=i+1;
            }
            else{
                cout<<one<<' '<<(i+1)<<endl;
                one=i+1;
            }
        }
        cout<<one<<' '<<n<<endl;
        if(cnt!=1){
            cout<<1<<' '<<zero<<endl;
        }
    }
    return 0;
}