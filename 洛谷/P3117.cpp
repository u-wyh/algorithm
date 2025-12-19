#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;

int n;
int x[MAXN],y[MAXN];
int op[MAXN];

int tmpx[MAXN],tot=1;
int tmpy[MAXN],cnt=1;

int sum1[MAXN][MAXN];
int sum2[MAXN][MAXN];

int findx(int val){
    int l=1,r=tot,ans=1;
    while(l<=r){
        int mid=(l+r)/2;
        if(tmpx[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int findy(int val){
    int l=1,r=cnt,ans=1;
    while(l<=r){
        int mid=(l+r)/2;
        if(tmpy[mid]>=val){
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
    cin>>n;
    for(int i=1;i<=n;i++){
        char c;
        cin>>x[i]>>y[i]>>c;
        op[i]=(c=='H')?1:0;
        tmpx[i]=x[i],tmpy[i]=y[i];
    }
    sort(tmpx+1,tmpx+n+1);
    sort(tmpy+1,tmpy+n+1);
    for(int i=2;i<=n;i++){
        if(tmpx[i]!=tmpx[i-1]){
            tmpx[++tot]=tmpx[i];
        }
        if(tmpy[i]!=tmpy[i-1]){
            tmpy[++cnt]=tmpy[i];
        }
    }
    for(int i=1;i<=n;i++){
        x[i]=findx(x[i]);
        y[i]=findy(y[i]);
        if(op[i]){
            sum1[x[i]][y[i]]++;
        }
        else{
            sum2[x[i]][y[i]]++;
        }
    }

    for(int i=1;i<=tot;i++){
        for(int j=1;j<=cnt;j++){
            sum1[i][j]+=sum1[i-1][j]+sum1[i][j-1]-sum1[i-1][j-1];
            sum2[i][j]+=sum2[i-1][j]+sum2[i][j-1]-sum2[i-1][j-1];
        }
    }

    int ans=1,area=0;
    for(int x1=1;x1<=tot;x1++){
        for(int x2=x1;x2<=tot;x2++){
            int x=tmpx[x2]-tmpx[x1];
            int top=0,now=0;
            for(int y1=1;y1<=cnt;y1++){

                if((sum2[x2][y1]-sum2[x1-1][y1]-sum2[x2][y1-1]+sum2[x1-1][y1-1])!=0){
                    top=0;
                    now=0;
                    continue;
                }

                int k=sum1[x2][y1]-sum1[x1-1][y1]-sum1[x2][y1-1]+sum1[x1-1][y1-1];
                if(top==0){
                    if(k==0){
                        continue;
                    }
                    else{
                        top=y1;
                        if(ans<=k){
                            ans=k;
                            area=0;
                        }
                        now=k;
                    }
                }
                else{
                    if(k==0){
                        continue;
                    }
                    else{
                        int sum=now+k;
                        int s=x*(tmpy[y1]-tmpy[top]);
                        if(sum>ans||(sum==ans&&s<area)){
                            ans=sum;
                            area=s;
                        }
                    }
                    now+=k;
                }
            }
            // cout<<x1<<' '<<x2<<' '<<ans<<' '<<area<<endl;
        }
    }
    cout<<ans<<endl<<area<<endl;
    return 0;
}