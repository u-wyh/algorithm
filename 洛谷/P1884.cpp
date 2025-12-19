#include<bits/stdc++.h>
using namespace std;
#define MAXN 4010

int n,btop,ctop;
int a[MAXN][4];
int b[MAXN],c[MAXN];
int f[MAXN][MAXN];
map<int ,int >Map;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=0;j<4;j++){
            cin>>a[i][j];
            b[++btop]=a[i][j];
        }
    }
    sort(b+1,b+btop+1);
    b[0]=-1000000007;
    for(int i=1;i<=btop;i++){
        if(b[i]!=b[i-1]){
            c[++ctop]=b[i];
            Map[b[i]]=ctop;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<4;j++){
            a[i][j]=Map[a[i][j]];
        }
    }
    for(int k=1;k<=n;k++){
        for(int i=a[k][0];i<a[k][2];i++){
            f[i][a[k][3]]++;
            f[i][a[k][1]]--;
        }
    }
    for(int i=1;i<ctop;i++)
        for(int j=1;j<ctop;j++)
            f[i][j]+=f[i][j-1];
    long long ans=0;
    for(int i=1;i<ctop;i++){
        for(int j=1;j<ctop;j++){
            if(f[i][j]){
                ans+=(long long)(c[i+1]-c[i])*(c[j+1]-c[j]);
            }
        }
    }
    cout<<ans;
    return 0;
}
