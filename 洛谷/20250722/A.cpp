#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1505;

int n;
struct node{
    int val,sub;
}nums[MAXN];
int ans[MAXN][MAXN];
int tmp[MAXN];

bool cmp(node a,node b){
    return a.val<b.val;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>nums[i].val;
            nums[i].sub=i;
        }
        sort(nums+1,nums+n+1,cmp);
        for(int i=1;i<=n;i++){
            // cout<<i<<"   :"<<nums[i].val<<endl;
            for(int j=0;j<nums[i].val;j++){
                tmp[j+1]=j;
            }
            for(int j=nums[i].val+1;j<=i;j++){
                tmp[j]=0;
            }

            // for(int j=1;j<=i;j++){
            //     cout<<tmp[j]<<' ';
            // }
            // cout<<endl;

            int last=0;
            for(int j=1;j<i;j++){
                if(tmp[j]==nums[j].val){
                    if(last){
                        swap(tmp[last],tmp[j]);
                        last=0;
                    }
                    else{
                        last=j;
                    }
                }
            }
            if(last){
                swap(tmp[last],tmp[i]);
            }

            // for(int j=1;j<=i;j++){
            //     cout<<tmp[j]<<' ';
            // }
            // cout<<endl;

            int x=nums[i].sub;
            for(int j=1;j<=i;j++){
                int y=nums[j].sub;
                ans[x][y]=ans[y][x]=tmp[j];
            }
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                cout<<ans[i][j]<<' ';
            }
            cout<<endl;
        }
    }
    return 0;
}