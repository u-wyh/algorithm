#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
char s[MAXN];
char t[MAXN];
char ans[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int main()
{
    scanf("%d %s %s",&n,s+1,t+1);
    int diff=0;
    for(int i=1;i<=n;i++){
        if(s[i]!=t[i]){
            diff++;
        }
    }
    if(diff%2==1){
        cout<<-1<<endl;
        return 0;
    }
    int b=0;
    for(int i=1;i<=n;i++){
        if(s[i]!=t[i]&&t[i]=='1'){
            b++;
        }
    }
    int need=2*b-diff;
    if(need<0){
        need*=-1;
        need/=2;
        for(int i=n;i>=1;i--){
            if(s[i]=='1'&&t[i]=='0'&&need){
                ans[i]='1';
                need--;
            }
            else{
                ans[i]='0';
            }
        }
    }
    else{
        need/=2;
        for(int i=n;i>=1;i--){
            if(t[i]=='1'&&s[i]=='0'&&need){
                ans[i]='1';
                need--;
            }
            else{
                ans[i]='0';
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i];
    }
    return 0;
}