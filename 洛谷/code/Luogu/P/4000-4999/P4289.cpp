#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1<<16;

int change[24][2]={{1,2},{1,5},{2,3},{2,6},{3,4},{3,7},{4,8},
                   {5,6},{5,9},{6,10},{6,7},{7,8},{7,11},{8,12},
                   {9,10},{9,13},{10,11},{10,14},{11,12},{11,15},{12,16},{13,14},{14,15},{15,16}};

int sta[MAXN];
int fa[MAXN];
deque<int>ans;

int st,en;
int nums1[MAXN],cnt1;
int nums2[MAXN],cnt2;
int lt=1,rt=1,tl=1,tr=1;
bool okay=false;
bool flag1=false;
bool flag2=false;

void bfs(int num,int op){
    // cout<<num<<' '<<op<<endl;
    for(int i=0;i<24;i++){
        int a=(num>>change[i][0])&1;
        int b=(num>>change[i][1])&1;
        if(a==b){
            continue;
        }
        int temp=num;
        temp-=(a<<change[i][0]);
        temp-=(b<<change[i][1]);
        temp+=(a<<change[i][1]);
        temp+=(b<<change[i][0]);
        if(sta[temp]==0){
            fa[temp]=num;
            sta[temp]=op;
            if(op==1){
                nums1[++cnt1]=temp;
                if(!flag1){
                    flag1=true;
                    lt=cnt1;
                }
                rt=cnt1;
            }
            else{
                nums2[++cnt2]=temp;
                if(!flag2){
                    flag2=true;
                    tl=cnt2;
                }
                tr=cnt2;
            }
        }
        else{
            if(sta[temp]!=op){
                ans.push_back(i);
                okay=true;
                if(op==1){
                    st=num,en=temp;
                }
                else{
                    st=temp,en=num;
                }
                return ;
            }
            else{
                continue;
            }
        }
    }
}

void compute(){
    while(true){
        flag1=false;
        int a=lt,b=rt;
        for(int i=a;i<=b;i++){
            bfs(nums1[i],1);
            if(okay){
                return;
            }
        }

        flag2=false;
        a=tl,b=tr;
        // cout<<"   "<<a<<' '<<b<<endl;
        for(int i=a;i<=b;i++){
            bfs(nums2[i],2);
            if(okay){
                return;
            }
        }
    }
}

int main()
{
    for(int i=0;i<=23;i++){
        change[i][0]-=1;
        change[i][1]-=1;
    }
    for(int i=0;i<16;i++){
        char c;
        cin>>c;
        st+=(c-'0')*(1<<i);
    }
    nums1[++cnt1]=st;
    sta[st]=1;
    fa[st]=0;

    for(int i=0;i<16;i++){
        char c;
        cin>>c;
        en+=(c-'0')*(1<<i);
    }
    nums2[++cnt2]=en;
    sta[en]=2;
    fa[en]=0;

    if(st==en){
        cout<<0<<endl;
        return 0;
    }

    compute();

    while(st){
        ans.push_front(st);
        st=fa[st];
    }
    ans.pop_front();

    while(en){
        ans.push_back(en);
        en=fa[en];
    }
    ans.pop_back();

    cout<<ans.size()<<endl;
    return 0;
}