#include<bits/stdc++.h>
using namespace std;

int n,m;
map<string,int>mp;
map<string,int>id;
int cnt=0;
string str[10005];
int nums[10005][105];
vector<int>vec;

bool cmp(int a,int b){
    if(mp[str[a]]==mp[str[b]]){
        for(int i=1;i<=m;i++){
            if(nums[a][i]!=nums[b][i]){
                return nums[a][i]<nums[b][i];
            }
        }
    }
    else{
        return mp[str[a]]>mp[str[b]];
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>nums[i][j];
            if(j==1)
                str[i]+=to_string(nums[i][j]);
            else{
                str[i]+=' ';
                str[i]+=to_string(nums[i][j]);
            }
        }
        mp[str[i]]++;
        if(mp[str[i]]==1){
            cnt++;
            vec.push_back(i);
        }
    }
    cout<<cnt<<endl;
    sort(vec.begin(),vec.end(),cmp);
    for(int i=0;i<(int)vec.size();i++){
        cout<<mp[str[vec[i]]]<<' '<<str[vec[i]]<<endl;
    }
    return 0;
}