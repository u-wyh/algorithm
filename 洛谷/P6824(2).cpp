#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e3+5;

int n,k;
int maxans=0;
int tree[MAXN][2];
int pass[MAXN];
int cnt=1;
int high;

void insert(int num) {
    int cur = 1;
    pass[cur]++;
    for (int i = high, path; i >= 0; i--) {
        path = (num >> i) & 1;
        if (tree[cur][path] == 0) {
            tree[cur][path] = ++cnt;
        }
        cur = tree[cur][path];
        pass[cur]++;
    }
}

int query(int x){
    int u=1,ans=0;
    for(int i=(1<<high);i>0;i>>=1){
        int a=x&i;
        int b=k&i;
        if(b){
            ans+=pass[tree[u][1-(a^b)]];
        }
        u=tree[u][a^b];
        if(u==0){
            return ans;
        }
    }
    return ans+pass[u];
}

int main()
{
    cin>>n>>k;
    int nums[n+1];
    int maxans=k;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        maxans=max(maxans,nums[i]);
    }
    maxans*=2;
    high=32-__builtin_clz(maxans);//选择出有效的位数  即不要前缀0
    cout<<maxans<<' '<<high<<' '<<(1<<high)<<endl;
    for(int i=1;i<=n;i++){
        insert(nums[i]);
    }
    for(int i=1;i<=cnt;i++){
        cout<<setw(3)<<i<<": "<<tree[i][0]<<", "<<tree[i][1]<<", "<<pass[i]<<endl;
    }
    int ans=0;
    for(int i=0;i<=MAXN;i++){
        ans=max(ans,query(i));
        if(ans==n)
            break;
    }
    cout<<ans;
    return 0;
}
