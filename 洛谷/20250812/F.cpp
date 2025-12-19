#include<bits/stdc++.h>
using namespace std;
#define int long long

int sx1,sy1,sx2,sy2,tx1,ty1,tx2,ty2;
int sop,top;

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

signed main()
{
    int T=read();
    while(T--){
        sx1=read(),sy1=read(),sx2=read(),sy2=read(),tx1=read(),ty1=read(),tx2=read(),ty2=read();
        if(sx1==sx2){
            sop=2;
        }
        else{
            sop=1;
        }

        if(tx1==tx2){
            top=2;
        }
        else{
            top=1;
        }

        int ans=0;
        if(sop==top){
            if(sop==2){
                ans=2*max(abs(sx1-tx1),abs(max(sy1,sy2)-max(ty1,ty2)));
            }
            else{
                ans=2*max(abs(sy1-ty1),abs(max(sx1,sx2)-max(tx1,tx2)));
            }
        }
        else{
            if(sop==1){
                swap(sx1,tx1);
                swap(sx2,tx2);
                swap(sy1,ty1);
                swap(sy2,ty2);
                sop=2;
            }
            if(sop==2){
                int dx,dy;
                dx=min(abs(max(tx1,tx2)-sx1),abs(min(tx1,tx2)-sx1));
                dy=min(abs(max(sy1,sy2)-ty1),abs(min(sy1,sy2)-ty1));
                ans=max(dx,dy)*2+1;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}