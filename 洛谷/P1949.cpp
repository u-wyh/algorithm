#include<bits/stdc++.h>
using namespace std;
const int MAXN = 7000000;

int st,en;

int sta[MAXN];
int dis[MAXN];
int p[7]={1,100000,10000,1000,100,10,1};
int nums1[MAXN],cnt1;
int nums2[MAXN],cnt2;
int lt=1,rt=1,tl=1,tr=6;
int flag;

inline int fun1(int num){
    int c=num/1000000;
    if(c==1){
        return num;
    }
    int tmp=num;
    int a=(tmp/100000)%10;
    int b=(tmp/p[c])%10;
    tmp-=a*100000;
    tmp-=b*p[c];
    tmp+=a*p[c];
    tmp+=b*100000;
    return tmp;
}

inline int fun2(int num){
    int c=num/1000000;
    if(c==6){
        return num;
    }
    int tmp=num;
    int a=tmp%10;
    int b=(tmp/p[c])%10;
    tmp-=a;
    tmp-=b*p[c];
    tmp+=a*p[c];
    tmp+=b;
    return tmp;
}

inline int fun3(int num){
    int c=num/1000000;
    int tmp=num;
    int a=(tmp/p[c])%10;
    if(a==9){
        return num;
    }
    tmp+=p[c];
    return tmp;
}

inline int fun4(int num){
    int c=num/1000000;
    int tmp=num;
    int a=(tmp/p[c])%10;
    if(a==0){
        return num;
    }
    tmp-=p[c];
    return tmp;
}

inline int fun5(int num){
    int c=num/1000000;
    if(c==6){
        return num;
    }
    return num+1000000;
}

inline int fun6(int num){
    int c=num/1000000;
    if(c==1){
        return num;
    }
    return num-1000000;
}

void bfs(int num,int op){
    for(int i=1;i<=6;i++){
        int val;
        if(i==1){
            val=fun1(num);
        }
        else if(i==2){
            val=fun2(num);
        }
        else if(i==3){
            val=fun3(num);
        }
        else if(i==4){
            val=fun4(num);
        }
        else if(i==5){
            val=fun5(num);
        }
        else{
            val=fun6(num);
        }
        if(sta[val]==0){
            dis[val]=dis[num]+1;
            sta[val]=op;
            if(op==1){
                nums1[++cnt1]=val;
            }
            else{
                nums2[++cnt2]=val;
            }
        }
        else if(sta[val]!=op){
            flag=dis[val]+dis[num]+1;
            return ;
        }
    }
}

void compute(){
    while(true){
        for(int i=lt;i<=rt;i++){
            bfs(nums1[i],1);
            if(flag){
                return ;
            }
        }
        lt=rt+1;
        rt=cnt1;

        for(int i=tl;i<=tr;i++){
            bfs(nums2[i],2);
            if(flag){
                return ;
            }
        }
        tl=tr+1;
        tr=cnt2;
    }
}

int main()
{
    // cout<<fun1(3123456)<<endl;
    // cout<<fun2(3123456)<<endl;
    // cout<<fun3(3123456)<<endl;
    // cout<<fun4(3123456)<<endl;
    // cout<<fun5(3123456)<<endl;
    // cout<<fun6(3123456)<<endl;
    cin>>st>>en;
    if(st==en){
        cout<<0<<endl;
        return 0;
    }
    memset(dis,-1,sizeof(dis));
    nums1[++cnt1]=st+1000000;
    dis[st+1000000]=0;
    sta[st+1000000]=1;

    nums2[++cnt2]=en+1000000;
    nums2[++cnt2]=en+2000000;
    nums2[++cnt2]=en+3000000;
    nums2[++cnt2]=en+4000000;
    nums2[++cnt2]=en+5000000;
    nums2[++cnt2]=en+6000000;
    dis[en+1000000]=0;
    dis[en+2000000]=0;
    dis[en+3000000]=0;
    dis[en+4000000]=0;
    dis[en+5000000]=0;
    dis[en+6000000]=0;
    sta[en+1000000]=2;
    sta[en+2000000]=2;
    sta[en+3000000]=2;
    sta[en+4000000]=2;
    sta[en+5000000]=2;
    sta[en+6000000]=2;
    compute();
    cout<<flag<<endl;
    return 0;
}