#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long

ll k,n,a[3000005],q_mx[3000005],q_mn[3000005];
ll head_mx,head_mn,tail_mx,tail_mn,len,pre;

int main()
{
    scanf("%lld%lld",&k,&n);
    len=0;
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    q_mx[1]=1;
    q_mn[1]=1;
    pre=1;
    head_mx=1;
    tail_mx=1;
    head_mn=1;
    tail_mn=1;
    for(int i=2;i<=n;i++){
        while(head_mx<=tail_mx&&a[q_mx[tail_mx]]<a[i])
            tail_mx--;
        while(head_mn<=tail_mn&&a[q_mn[tail_mn]]>a[i])
            tail_mn--;
        q_mx[++tail_mx]=i;
        q_mn[++tail_mn]=i;
        while(a[q_mx[head_mx]]-a[q_mn[head_mn]]>k){
            if(q_mx[head_mx]<q_mn[head_mn]){
                pre=q_mx[head_mx]+1;
                head_mx++;
            }else {
                pre=q_mn[head_mn]+1;
                head_mn++;
            }
        }
        len=max(len,i-pre+1);
    }
    printf("%lld",len);
}
