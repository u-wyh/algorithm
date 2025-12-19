#include<bits/stdc++.h>
using namespace std;
struct cow{
    int nex[2],sum,end;
}t[500001];
int a[10001];
inline int read()
{
    int data=0,w=1; char ch=0;
    while(ch!='-' && (ch<'0' || ch>'9')) ch=getchar();
    if(ch=='-') w=-1,ch=getchar();
    while(ch>='0' && ch<='9') data=data*10+ch-'0',ch=getchar();
    return data*w;
}
int main()
{
    ios::sync_with_stdio(false);
    int n,m,js=1;
    memset(t,0,sizeof(t));
    m=read();n=read();
    for (int i=1;i<=m;i++)
    {
        int len;
        len=read();
        for (int j=1;j<=len;j++) a[j]=read();
        int now=1;
        for (int j=1;j<=len;j++)
        {
            if (t[now].nex[a[j]]!=0) now=t[now].nex[a[j]];
            else
            {
                js++;
                t[now].nex[a[j]]=js;
                t[js].nex[1]=t[js].nex[0]=0;
                now=js;
            }
            t[now].sum++;
        }
        t[now].end++;
    }
    for (int i=1;i<=n;i++)
    {
        int len;
        len=read();
        for (int j=1;j<=len;j++) a[j]=read();
        int now=1,ans=0;
        bool flag=true;
        for (int j=1;j<=len;j++)
        {
            if (t[now].nex[a[j]]!=0) now=t[now].nex[a[j]];
            else
            {
                flag=false;
                break;
            }
            ans+=t[now].end;
        }
        if (!flag) cout<<ans<<endl;
        else cout<<ans+t[now].sum-t[now].end<<endl;
    }
    return 0;
}
