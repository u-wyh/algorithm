#include<bits/stdc++.h>
using namespace std;

int n;
int h[1000005],m[1000005],st[1000005];
int r=0,ans=0;

inline int read(){
    int a=0,f=1; char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1; c=getchar();}
    while (c>='0'&&c<='9') {a=a*10+c-'0'; c=getchar();}
    return a*f;
}

//使用单调栈做法
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        h[i]=read(),m[i]=read();

    for(int i=1;i<=n;i++){
        while(r>0&&h[st[r-1]]>h[i]){
            r--;
            ans=max(ans,m[i]+((r>0)?m[st[r-1]]:0));
            //这个单调栈里面的数据是上面的数据大  下面的数据小
            //那么当一个比目前栈最顶的数据小  那么弹出顶上的数据并结算：
            //因为弹出的数据比即将进入的数据大，所以即将进入的这个数据就是这个弹出数据右边最近的
        }
        st[r++]=i;
    }

    for(int i=1;i<r;i++){
        ans=max(ans,m[st[i-1]]);
    }
    cout<<ans;
    return 0;
}
