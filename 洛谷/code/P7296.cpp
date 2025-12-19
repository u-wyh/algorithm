#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
char s[MAXN];
int arr[MAXN];
int pos[MAXN];
int f[1<<20];
int match[20][20];

int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++){
        arr[i]=s[i];
    }
    sort(arr+1,arr+n+1);
    m=unique(arr+1,arr+n+1)-arr-1;
    for(int i=1;i<=n;i++){
		pos[i]=lower_bound(arr+1,arr+m+1,s[i])-arr-1;
        //cout<<pos[i]<<' ';
    }
    //cout<<endl;
    for(int i=1;i<n;i++){
        match[pos[i]][pos[i+1]]++;
    }
    memset(f,0x3f,sizeof(f));
    f[0]=1;
    for(int s=1;s<(1<<m);s++){
        for(int i=0;i<m;i++){
            if(s&(1<<i)){
                int tmp=f[s^(1<<i)];
                for(int j=0;j<m;j++){
                    if(s&(1<<j)){
                        tmp+=match[i][j];
                    }
                }
                f[s]=min(f[s],tmp);
            }
        }
    }
    cout<<f[(1<<m)-1];
    return 0;
}