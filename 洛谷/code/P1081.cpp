#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e12;
const int MAXN = 1e5+5;
const int MAXH = 17;

int n,m,x0;
struct node{
    int pos,h;
    int pre,suf;
};
node nums[MAXN];
int pos[MAXN];

int ga[MAXN],gb[MAXN];
// [i][j][k]表示出发的时候是a(0)或者b(1)开始  从i城市出发  走了2的j次方天
// f数组表示到了那个城市  da表示a走了多久  db表示b走了多久
int f[MAXN][MAXH][2];
int da[MAXN][MAXH][2];
int db[MAXN][MAXH][2];

int la,lb;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

bool cmp(node a,node b){
    return a.h<b.h;
}

void compute(int s,int x){
    la=0,lb=0;
    int k=0;
    for(int i=MAXH-1;i>=0;i--){
        if(f[s][i][k]&&da[s][i][k]+db[s][i][k]<=x){
            x-=da[s][i][k]+db[s][i][k];
            la+=da[s][i][k],lb+=db[s][i][k];
            if(i==0){
                k^=1;
            }
            s=f[s][i][k];
        }
    }
}

signed main()
{
    n=read();

    for(int i=1;i<=n;i++){
        nums[i].h=read();
        nums[i].pos=i;
    }
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        nums[i].pre=i-1;
        nums[i].suf=i+1;
        pos[nums[i].pos]=i;
    }

    nums[0].h=INF,nums[0].pre=0;
    nums[n+1].h=INF,nums[n+1].suf=n+1;
    gb[n-1]=n;
    for(int i=1;i<=n-2;i++){
        int v=pos[i];

        int l=nums[v].pre;
        int r=nums[v].suf;
        int choose;
        if(abs(nums[r].h-nums[v].h)<abs(nums[v].h-nums[l].h)){
            gb[i]=nums[r].pos;
            choose=r;
        }
        else{
            gb[i]=nums[l].pos;
            choose=l;
        }

        int l1=nums[v].pre;
        int l2=nums[l1].pre;
        int r1=nums[v].suf;
        int r2=nums[r1].suf;
        // cout<<i<<":  "<<l<<' '<<r<<' '<<choose<<' '<<l1<<' '<<l2<<' '<<r1<<' '<<r2<<endl;
        int disl,disr;
        if(choose==l){
            disl=abs(nums[v].h-nums[l2].h);
            disr=abs(nums[r1].h-nums[v].h);
            if(disr<disl){
                ga[i]=nums[r1].pos;
            }
            else{
                ga[i]=nums[l2].pos;
            }
        }
        else{
            disl=abs(nums[v].h-nums[l1].h);
            disr=abs(nums[r2].h-nums[v].h);
            if(disr<disl){
                ga[i]=nums[r2].pos;
            }
            else{
                ga[i]=nums[l1].pos;
            }
        }

        nums[nums[v].pre].suf=nums[v].suf;
        nums[nums[v].suf].pre=nums[v].pre;
    }

    // cout<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<ga[i]<<' ';
    // }
    // cout<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<gb[i]<<' ';
    // }
    // cout<<endl;

    for(int i=1;i<=n;i++){
        f[i][0][0]=ga[i];
        f[i][0][1]=gb[i];

        if(ga[i]!=0){
            da[i][0][0]=abs(nums[pos[i]].h-nums[pos[ga[i]]].h);
        }
        da[i][0][1]=0;

        if(gb[i]!=0){
            db[i][0][1]=abs(nums[pos[i]].h-nums[pos[gb[i]]].h);
        }
        db[i][0][0]=0;
    }

    // for(int i=1;i<=n;i++){
    //     cout<<i<<": "<<f[i][0][0]<<' '<<f[i][0][1]<<' '<<da[i][0][0]<<' '<<da[i][0][1]<<' '<<db[i][0][0]<<' '<<db[i][0][1]<<endl;
    // }
    // cout<<endl;

    // 2的1次方需要特判处理
    for(int i=1;i<=n;i++){
        f[i][1][0]=f[f[i][0][0]][0][1];
        f[i][1][1]=f[f[i][0][1]][0][0];

        da[i][1][0]=da[i][0][0]+da[f[i][0][0]][0][1];
        da[i][1][1]=da[i][0][1]+da[f[i][0][1]][0][0];

        db[i][1][0]=db[i][0][0]+db[f[i][0][0]][0][1];
        db[i][1][1]=db[i][0][1]+db[f[i][0][1]][0][0];
    }

    for(int k=2;k<MAXH;k++){
        for(int i=1;i<=n;i++){
            f[i][k][0]=f[f[i][k-1][0]][k-1][0];
            f[i][k][1]=f[f[i][k-1][1]][k-1][1];

            da[i][k][0]=da[i][k-1][0]+da[f[i][k-1][0]][k-1][0];
            da[i][k][1]=da[i][k-1][1]+da[f[i][k-1][1]][k-1][1];

            db[i][k][0]=db[i][k-1][0]+db[f[i][k-1][0]][k-1][0];
            db[i][k][1]=db[i][k-1][1]+db[f[i][k-1][1]][k-1][1];
        }
    }

    x0=read();
    int ans=1,ansa=1,ansb=0;
    for(int i=1;i<=n;i++){
        compute(i,x0);
        if(lb==0){
            la=1;
        }
        if((la*ansb<lb*ansa)||((la*ansb==lb*ansa)&&(nums[pos[i]].h>nums[pos[ans]].h))){
            ans=i;
            ansa=la,ansb=lb;
        }
    }
    cout<<ans<<endl;

    m=read();
    while(m--){
        int s,x;
        s=read(),x=read();
        compute(s,x);
        cout<<la<<' '<<lb<<endl;
    }
    return 0;
}