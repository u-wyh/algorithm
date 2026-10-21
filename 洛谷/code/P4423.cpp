// https://www.luogu.com.cn/problem/P4423
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const double INF = 1e30;

int n;
struct node{
    int x,y;
};
node nums[MAXN];
node tmp[MAXN];
node temp[MAXN];
double ans;

bool cmp(node &a,node &b){
    return a.x<b.x;
}

bool cmpy(node &a,node &b){
    return a.y<b.y;
}

double dist(const node &a,const node &b){
    double dx=a.x-b.x;
    double dy=a.y-b.y;
    return sqrt(dx*dx+dy*dy);
}

double calc(const node &a,const node &b,const node &c){
    return dist(a,b)+dist(b,c)+dist(a,c);
}

double solve(int l,int r){
    if(r-l+1<=3){
        double ans=INF;
        for(int i=l;i<=r;i++){
            for(int j=i+1;j<=r;j++){
                for(int k=j+1;k<=r;k++){
                    ans=min(ans,calc(nums[i],nums[j],nums[k]));
                }
            }
        }
        sort(nums+l,nums+r+1,cmpy);
        return ans;
    }
    int mid=(l+r)>>1;
    double midx=nums[mid].x;
    double d=min(solve(l,mid),solve(mid+1,r));

    int p1=l,p2=mid+1;
    int p=l;
    while(p1<=mid&&p2<=r){
        if(nums[p1].y<nums[p2].y){
            tmp[p++]=nums[p1];
            p1++;
        }
        else{
            tmp[p++]=nums[p2];
            p2++;
        }
    }
    while(p1<=mid){
        tmp[p++]=nums[p1++];
    }
    while(p2<=r){
        tmp[p++]=nums[p2++];
    }
    for(int i=l;i<=r;i++){
        nums[i]=tmp[i];
    }

    int cnt=0;
    for(int i=l;i<=r;i++){
        if(fabs(nums[i].x-midx)<d/2){
            temp[++cnt]=nums[i];
        }
    }
    for(int i=1;i<=cnt;i++){
        int limit=min(cnt,i+16);
        for(int j=i+1;j<=limit;j++){
            if(temp[j].y-temp[i].y>=d/2){
                break;
            }
            double dij=dist(temp[i],temp[j]);
            if(dij>d/2){
                continue;
            }
            for(int k=j+1;k<=limit;k++){
                if(temp[k].y-temp[i].y>=d/2){
                    break;
                }
                double dik=dist(temp[i],temp[k]);
                if(dik>d/2){
                    continue;
                }
                double djk=dist(temp[j],temp[k]);
                d=min(d,dij+dik+djk);
            }
        }
    }
    return d;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
    }

    sort(nums+1,nums+n+1,cmp);

    double ans=solve(1,n);

    cout<<fixed<<setprecision(6)<<ans<<"\n";
    return 0;
}