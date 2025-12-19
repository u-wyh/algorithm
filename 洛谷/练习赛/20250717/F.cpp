#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,m;
char s[MAXN<<1];
int ans[MAXN];
int len;

int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d %d",&n,&m);
        scanf("%s",s+1);
        int one=0;
        for(int i=1;i<=n;i++){
            if(s[i]=='0'){
                s[i+n]='0';
            }
            else{
                one=i;
                break;
            }
        }
        int t=0;
        len=0;
        for(int i=one+1;i<=one+n-1;i++){
            if(s[i]=='0'){
                t++;
            }
            else{
                ans[++len]=t;
                // cout<<t<<' ';
                t=0;
            }
        }
        ans[++len]=t;
        sort(ans+1,ans+len+1);
        int res=max(0,ans[len]-m-1);
        for(int i=1;i<len;i++){
            res+=max(0,ans[i]-2*m);
        }
        cout<<res<<endl;
    }
    return 0;
}