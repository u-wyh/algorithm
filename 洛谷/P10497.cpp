#include<bits/stdc++.h>
using namespace std;
int n,a[10001],s,st[10001];
bool vis[10001];
int main()
{
  cin>>n;
  for(int i = 2;i <= n;i++)
    cin>>a[i];
  for(int i = n;i >= 1;i--){
    s = 0;
    for(int j = 1;j <= n;j++)
      if(vis[j] == 0)
      {
            s++;
        if(s == a[i] + 1)
        {
            vis[j] = 1;
            st[i] = j;
            break;
        }
      }
  }
  for(int i = 1;i <= n;i++) cout<<st[i]<<'\n';
  return 0;
}
