#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int LIMIT = 65;

int n,k,m;
int st[MAXN][LIMIT];
int pos[MAXN];
int power;

signed main()
{
    cin>>n>>k>>m;
    for(int i=1;i<=n;i++){
        cin>>pos[i];
    }
    power=log2(m);
    int head = 1, tail = k + 1;
    for(int i = 1; i <= n; i++) {
        while(tail + 1 <= n && pos[tail + 1] - pos[i] < pos[i] - pos[head])
            head++, tail++;
        if(pos[tail] - pos[i] > pos[i] - pos[head])
            st[i][0] = tail;
        else
            st[i][0] = head;
    }
    for(int i=1;i<=power;i++){
        for(int j=1;j<=n;j++){
            st[j][i]=st[st[j][i-1]][i-1];
        }
    }
    for(int i=1;i<=n;i++){
        int temp=m,ans=i;
        for(int j=power;j>=0;j--){
            if(temp<(1<<j)){
                continue;
            }
            temp-=(1<<j);
            ans=st[ans][j];
            if(temp==0){
                break;
            }
        }
        cout<<ans<<' ';
    }
    return 0;
}
