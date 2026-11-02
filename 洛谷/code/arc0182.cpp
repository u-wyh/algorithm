// https://atcoder.jp/contests/arc018/tasks/arc018_2
#include<bits/stdc++.h>
using namespace std;
#define int long long

struct Point{
    int x,y;
};
int n;
Point nums[105];
Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}
int operator*(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}
int cross(Point a,Point b,Point c){
    return (b-a)*(c-a);
}

signed main()
{
    int ans=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            for(int k=j+1;k<=n;k++){
                int val=cross(nums[i],nums[j],nums[k]);
                if(val && (val%2==0)){
                    ans++;
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}