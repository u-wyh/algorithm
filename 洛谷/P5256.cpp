#include<bits/stdc++.h>
using namespace std;
#define int long long
const int BASE = 499;
const int MAXN = 1e6+5;
const int MAXM = 1e5+5;

int n,m;
char s1[MAXN];
char s2[MAXM];
int nums1[MAXN];
int nums2[MAXM];
int vis[30];
int nextpos[MAXN];

int p[MAXN];

int hashval(){
    int ans=nums2[1];
    for(int i=2;i<=m;i++){
        ans=ans*BASE+nums2[i];
    }
    return ans;
}

signed main()
{
    int T;
    cin>>T;
    p[0]=1;
    for(int i=1;i<MAXM;i++){
        p[i]=p[i-1]*BASE;
    }
    while(T--){
        scanf("%s %s",s1+1,s2+1);
        n=strlen(s1+1);
        m=strlen(s2+1);
        for(int i=1;i<=27;i++){
            vis[i]=0;
        }
        for(int i=1;i<=n;i++){
            if(s1[i]>='a'&&s1[i]<='z'){
                int v=s1[i]-'a'+1;
                if(vis[v]==0){
                    nums1[i]=0;
                }
                else{
                    nums1[i]=i-vis[v];
                    nextpos[vis[v]]=i;
                }
                vis[v]=i;
            }
            else{
                nums1[i]=-1*(s1[i]-'A'+1);
            }
        }
        for(int i=1;i<=27;i++){
            vis[i]=0;
        }
        for(int i=1;i<=m;i++){
            if(s2[i]>='a'&&s2[i]<='z'){
                int v=s2[i]-'a'+1;
                if(vis[v]==0){
                    nums2[i]=0;
                }
                else{
                    nums2[i]=i-vis[v];
                }
                vis[v]=i;
            }
            else{
                nums2[i]=-1*(s2[i]-'A'+1);
            }
        }
        int ans=0;

        int val2=hashval();
        int val1=nums1[1];
        for(int i=2;i<=m;i++){
            val1=val1*BASE+nums1[i];
        }
        if(val1==val2){
            ans++;
        }
        for(int i=m+1;i<=n;i++){
            if(nums1[i-m]>=0){
                int pos=nextpos[i-m];
                if(pos==0){

                }
                else if(pos>=i){
                    nums1[pos]=0;
                }
                else{
                    val1-=p[i-pos-1]*nums1[pos];
                }
            }
            else{
                val1-=nums1[i-m]*p[m-1];
            }
            val1=val1*BASE+nums1[i];
            if(val1==val2){
                ans++;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}