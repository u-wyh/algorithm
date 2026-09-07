#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m,k;

vector<int>pos[MAXN];
int rt[MAXN];
int val[MAXN];
int nums[MAXN];
bool vis[MAXN];
int len;

int find(int x){
    int l=1,r=len,ans=len;
    while(l<=r){
        int mid=(l+r)>>1;
        if(nums[mid]<=x){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    return ans;
}

int block;
int length;

void join(int x){
    int sz=(int)pos[x].size();
    block+=sz;
    length+=sz;
    for(int i=0;i<sz;i++){
        int p=pos[x][i];
        vis[p]=true;
        if(vis[p-1]){
            block--;
        }
    }
}

void del(int x){
    int sz=(int)pos[x].size();
    length-=sz;
    // block+=sz;
    // for(int i=0;i<sz;i++){
    //     int p=pos[x][i];
    //     vis[p]=false;

    // }
    for(int i=sz-1;i>=0;i--){
        int p=pos[x][i];
        vis[p]=false;
        if(val[p-1]==x){
            continue;
        }
        if(val[p+1]==x){
            if(vis[rt[p]+1]==vis[p-1]){
                if(vis[p-1]){
                    block++;
                }
                else{
                    block--;
                }
            }
        }
        else{
            if(vis[p+1]==vis[p-1]){
                if(vis[p-1]){
                    block++;
                }
                else{
                    block--;
                }
            }
        }
    }
}

bool check(int limit){
    block=0,length=0;
    for(int i=1;i<=n;i++){
        vis[i]=false;
    }
    int r=0;
    for(int l=1;l<=len;l++){
        int val=nums[l]+limit;
        int nr=find(val);
        while(r+1<=nr){
            join(r+1);
            r++;
        }
        if(block<=m+1&&length>=k){
            return true;
        }
        del(l);
    }
    return false;
}

void solve(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        nums[i]=val[i];
    }
    for(int i=1;i<=n;i++){
        rt[i]=i;
    }
    for(int i=n-1;i>=1;i--){
        if(val[i]==val[i+1]){
            rt[i]=rt[i+1];
        }
    }
    sort(nums+1,nums+n+1);
    len=1;
    for(int i=2;i<=n;i++){
        if(nums[i]!=nums[i-1]){
            nums[++len]=nums[i];
        }
    }
    for(int i=1;i<=len;i++){
        pos[i].clear();
    }
    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
        pos[val[i]].push_back(i);
    }
    for(int i=1;i<=n;i++){
        vis[i]=false;
    }

    int l=1,r=nums[len],ans=r;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
/*
3
6 0 3
1 6 5 9 7 12
6 1 3
1 6 5 9 7 12
10 2 5
8 6 1 7 3 12 15 5 1 9


4 2 5
*/