// https://atcoder.jp/contests/abc224/tasks/abc224_c
#include<bits/stdc++.h>
using namespace std;

int n;
struct Point{
    long long x,y;
};
Point nums[305];
Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}
long long operator*(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}
long long cross(Point a,Point b,Point c){
    return (b-a)*(c-a);
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
    }

    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            for(int k=j+1;k<=n;k++){
                if(cross(nums[i],nums[j],nums[k])!=0){
                    ans++;
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}