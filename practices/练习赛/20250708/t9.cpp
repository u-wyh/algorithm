#include<bits/stdc++.h>
using namespace std;

int n,d,h;
double ans;

int main()
{
    cin>>n>>d>>h;
    for(int t=0;t<=n;t++){
        //枚举在什么时候处罚技能1
        for(int st=0;st<(1<<n);st++){
            //状态压缩表示暴击是否被触发
            double hq=h;
            int mofa=0;
            bool skill=false;
            bool flag=false;//表示是否免疫后续伤害
            double all=0;//收到的总伤害

            for(int i=1;i<=n;i++){
                if(hq<0){
                    break;
                }

                mofa+=10;

                double harm=d;
                if(t!=0&&i>=t){
                    harm*=1.2;
                }
                if(st&(1<<(i-1))){
                    harm*=2;
                }
                all+=harm;

                if(flag){
                    continue;
                }
                if(hq-harm<=0){
                    if(!skill){
                        skill=true;
                        hq=1;
                        hq+=h/100.0*mofa;
                        hq=min(1.0*h,hq);
                        if(mofa>=100){
                            flag=true;
                        }
                        mofa=0;
                    }
                    else{
                        hq-=harm;
                    }
                }
                else{
                    hq-=harm;
                }
            }
            ans=max(ans,1.2*all);
        }
    }
    printf("%.2lf\n",ans);
    return 0;
}