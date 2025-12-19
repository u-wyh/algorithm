#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9;

int n,m;
int change[26][26];//表示这两个字母可以形成什么
int f[105][105];//表示从i到j这个区间可以形成一个什么字母
int dp[105][105];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        char a,b,c;
        cin>>a>>b>>c;
        change[b-'A'][c-'A']|=(1<<(a-'A'));
    }
    cin>>m;
    while(m--){
        string str;
        cin>>str;
        int len=str.size();
        str=' '+str;
        for(int i=0;i<=len;i++){
            for(int j=0;j<=len;j++){
                f[i][j]=0;
                dp[i][j]=INF;
            }
        }
        for(int i=1;i<=len;i++){
            f[i][i]|=(1<<(str[i]-'A'));
        }
        for(int l=2;l<=len;l++){
            for(int i=1;i<=len-l+1;i++){
                int j=i+l-1;
                for(int k=i;k<j;k++){
                    for(int a=0;a<26;a++){
                        if(f[i][k]&(1<<a)){
                            for(int b=0;b<26;b++){
                                if(f[k+1][j]&(1<<b)){
                                    f[i][j]|=change[a][b];
                                }
                            }
                        }
                    }
                }
            }
        }

        for(int l=1;l<=len;l++){
            for(int i=1;i<=len-l+1;i++){
                int j=i+l-1;
                if(f[i][j]&(1<<('S'-'A'))){
                    dp[i][j]=1;
                    continue;
                }
                for(int k=i;k<j;k++){
                    dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
                }
            }
        }

        if(dp[1][len]>=len){
            cout<<"NIE"<<endl;
        }
        else{
            cout<<dp[1][len]<<endl;
        }
    }
    return 0;
}