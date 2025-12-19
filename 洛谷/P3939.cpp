#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

vector<int>vec[MAXN];
int arr[MAXN];
bool vis[MAXN];
int n,m;

int compute(int lt,int rt,int c){
    int ans1=0,ans2=vec[c].size();
    int l=0,r=vec[c].size()-1;
    while(l<=r){
        int mid=(l+r)/2;
        if(vec[c][mid]>=lt){
            ans1=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    l=0,r=vec[c].size()-1;
    while(l<=r){
        int mid=(l+r)/2;
        if(vec[c][mid]>rt){
            ans2=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans2-ans1;
}

void change(int c,int pos,int idea){
    int l=0,r=vec[c].size()-1,ans=0;
    while(l<=r){
        int mid=(l+r)/2;
        if(vec[c][mid]>=pos){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    vec[c][ans]=idea;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        vec[arr[i]].push_back(i);
    }
    for(int i=1;i<=n;i++){
        if(!vis[arr[i]]){
            vec[arr[i]].push_back(0);
            vec[arr[i]].push_back(INT_MAX);
            sort(vec[arr[i]].begin(),vec[arr[i]].end());
            vis[arr[i]]=true;
        }
    }
    for(int i=1;i<=m;i++){
        int op,l,r,c;
        cin>>op>>l;
        if(op==1){
            cin>>r>>c;
            cout<<compute(l,r,c)<<endl;
        }
        else{
            if(arr[l]!=arr[l+1]){
                change(arr[l],l,l+1);
                change(arr[1+l],l+1,l);
                int tmp=arr[l];
                arr[l]=arr[l+1];
                arr[l+1]=tmp;
            }
        }
    }
    return 0;
}
