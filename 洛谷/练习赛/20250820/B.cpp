#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
struct node{
    int pos,val;
};
node nums1[MAXN];
node nums2[MAXN];
int len1,len2;
int nums[MAXN];
int ans[MAXN];

bool cmp(node a,node b){
    return a.val<b.val;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        len1=0,len2=0;
        for(int i=1;i<=n;i++){
            cin>>nums[i];
        }
        for(int i=1;i<=n;i++){
            char c;
            cin>>c;
            if(c=='0'){
                len2++;
                nums2[len2]={i,nums[i]};
            }
            else{
                len1++;
                nums1[len1]={i,nums[i]};
            }
        }
        sort(nums1+1,nums1+len1+1,cmp);
        sort(nums2+1,nums2+len2+1,cmp);
        
        for(int i=1;i<=len2;i++){
            ans[nums2[i].pos]=i;
        }
        for(int i=1;i<=len1;i++){
            ans[nums1[i].pos]=i+len2;
        }

        for(int i=1;i<=n;i++){
            cout<<ans[i]<<' ';
        }
        cout<<endl;
    }
    return 0;
}