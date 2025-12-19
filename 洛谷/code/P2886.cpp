#include<bits/stdc++.h>
using namespace std;

int t,n,st,en;
int m;
int arr[205];
struct node{
    int w,u,v;
}nums[105];

vector<vector<int>> multiply(vector<vector<int>>a,vector<vector<int>>b){
    int n=a.size();
    int m=b[0].size();
    int k=a[0].size();
    vector<vector<int>> ans(n,vector<int>(m,1e9));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int p = 0; p < k; p++) {
                ans[i][j] = min(ans[i][j], a[i][p] + b[p][j]);
            }
        }
    }
    return ans;
}

vector<vector<int>> power(vector<vector<int>> a,int p){
    int n=a.size();
    vector<vector<int>> base(n,vector<int>(n,1e9));
    for(int i=0;i<n;i++){
        base[i][i]=0;
    }
    while(p){
        if(p&1){
            base=multiply(base,a);
        }
        p>>=1;
        a=multiply(a,a);
    }
    return base;
}

int find(int val){
    int l=0,r=m,ans;
    while(l<=r){
        int mid=(l+r)/2;
        if(arr[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    cin>>t>>n>>st>>en;
    arr[++m]=st,arr[++m]=en;
    for(int i=1;i<=n;i++){
        cin>>nums[i].w>>nums[i].u>>nums[i].v;
        arr[++m]=nums[i].u,arr[++m]=nums[i].v;
    }
    sort(arr+1,arr+2*n+2+1);
    m=0;
    for(int i=1;i<=2*n+2;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    st=find(st)-1,en=find(en)-1;
    vector<vector<int>> edge(m,vector<int>(m,1e9));
    for(int i=1;i<=n;i++){
        nums[i].u=find(nums[i].u)-1;
        nums[i].v=find(nums[i].v)-1;
        edge[nums[i].u][nums[i].v]=nums[i].w;
        edge[nums[i].v][nums[i].u]=nums[i].w;
    }
    edge=power(edge,t);
    cout<<edge[st][en];
    return 0;
}
