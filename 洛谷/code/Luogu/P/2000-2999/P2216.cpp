#include<bits/stdc++.h>
using namespace std;

int a,b,n,ans=1e9;
int nums[1005][1005],q[1005];
int rowmin[1005][1005],rowmax[1005][1005];
int colmin[1005][1005],colmax[1005][1005];

int main()
{
    cin>>a>>b>>n;
    for(int i=1;i<=a;i++){
        for(int j=1;j<=b;j++){
            cin>>nums[i][j];
        }
    }
    for(int row=1;row<=a;row++){
        int h=0,t=0;
        for(int i=1;i<=b;i++){
            while(h<t&&i-q[h]>=n)
                h++;
            while(h<t&&nums[row][q[t-1]]<nums[row][i])
                t--;
            q[t++]=i;
            if(i>=n)
                rowmax[row][i-n+1]=nums[row][q[h]];
        }
        h=0,t=0;
        for(int i=1;i<=b;i++){
            while(h<t&&i-q[h]>=n)
                h++;
            while(h<t&&nums[row][q[t-1]]>nums[row][i])
                t--;
            q[t++]=i;
            if(i>=n)
                rowmin[row][i-n+1]=nums[row][q[h]];
        }
    }
    for(int col=1;col<=b-n+1;col++){
        int h=0,t=0;
        for(int i=1;i<=a;i++){
            while(h<t&&i-q[h]>=n)
                h++;
            while(h<t&&rowmax[q[t-1]][col]<rowmax[i][col])
                t--;
            q[t++]=i;
            if(i>=n)
                colmax[i-n+1][col]=rowmax[q[h]][col];
        }
        h=0,t=0;
        for(int i=1;i<=a;i++){
            while(h<t&&i-q[h]>=n)
                h++;
            while(h<t&&rowmin[q[t-1]][col]>rowmin[i][col])
                t--;
            q[t++]=i;
            if(i>=n)
                colmin[i-n+1][col]=rowmin[q[h]][col];
        }
    }
    for(int i=1;i<=a-n+1;i++){
        for(int j=1;j<=b-n+1;j++){
            ans=min(ans,colmax[i][j]-colmin[i][j]);
        }
    }
    cout<<ans<<endl;
    return 0;
}

