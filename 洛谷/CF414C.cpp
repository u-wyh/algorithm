#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2100000;

int n,m,k;
int nums[MAXN];
int help[MAXN];

long long val1[MAXN<<2];
long long val2[MAXN<<2];
long long val3[MAXN<<2];
long long val4[MAXN<<2];
bool tag[MAXN<<2];

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

pair<long long,long long> mergesort(int l,int r){
    int mid=(l+r)/2;
    if(l==r)
        return {0,0};
    for(int i=l;i<=r;i++){
        help[i]=nums[i];
    }
    int i=l;
    int j=mid+1;
    long long cnt1=0;
    long long cnt2=0;
    int k=mid+1;
    for(int i=l;i<=mid;i++){
        while(k<=r&&nums[k]<=nums[i]){
            k++;
        }
        cnt2+=r+1-k;
    }
    for(int k=l;k<=r;k++){
        if(i==mid+1){
            nums[k]=help[j];
            j++;
        }
        else if(j==r+1){
            nums[k]=help[i];
            i++;
        }
        else if(help[i]<=help[j]){
            nums[k]=help[i];
            i++;
        }
        else if(help[j]<help[i]){
            nums[k]=help[j];
            j++;
            cnt1+=(mid-i+1);
        }
        else
            break;
    }
    return {cnt1,cnt2};
}

pair<long long,long long> merge(int l,int r,int i){
    if(l==r){
        val1[i]=0;
        val2[i]=0;
        return {0,0};
    }
    int mid=(l+r)/2;
    long long ans1=0,ans2=0;
    pair<long long,long long>tmp=merge(l,mid,i<<1);
    ans1+=tmp.first,ans2+=tmp.second;
    tmp=merge(mid+1,r,i<<1|1);
    ans1+=tmp.first,ans2+=tmp.second;

    tmp=mergesort(l,r);
    val3[i]=tmp.first,val4[i]=tmp.second;
    val1[i]=ans1,val2[i]=ans2;
    return {ans1+val3[i],ans2+val4[i]};
}

void up(int i){
    val1[i]=val1[i<<1]+val1[i<<1|1]+val3[i<<1]+val3[i<<1|1];
    val2[i]=val2[i<<1]+val2[i<<1|1]+val4[i<<1]+val4[i<<1|1];
}

void lazy(int i){
    swap(val1[i],val2[i]);
    swap(val3[i],val4[i]);
    tag[i]^=1;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1);
        lazy(i<<1|1);
        tag[i]=false;
    }
}

void update(int l,int r,int i,int u){
    if (l == r) {          // 叶子节点直接处理
        if (u == 0) lazy(i);
        return;
    }
    if(u==0){
        lazy(i);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        update(l,mid,i<<1,u-1);
        update(mid+1,r,i<<1|1,u-1);
        up(i);
    }
}

char buffer[20];
inline void write(long long x) {
    if (x == 0) putchar('0');
    else {
        int len = 0;
        while (x) buffer[len++] = x % 10 + '0', x /= 10;
        while (len--) putchar(buffer[len]);
    }
    putchar('\n');
}

int main()
{
    n=read();
    for(int i=1;i<=(1<<n);i++){
        nums[i]=read();
    }
    merge(1,(1<<n),1);
    m=read();
    while(m--){
        int u=read();
        update(1,(1<<n),1,n-u);
        write(val1[1]+val3[1]);
    }
    return 0;
}