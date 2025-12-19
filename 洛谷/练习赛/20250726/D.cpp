#include<bits/stdc++.h>
using namespace std;

int a,b,c;
double aval,bval,cval;
double all,average;

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>a>>b>>c;
        double val;
        aval=0,bval=0,cval=0;
        for(int i=1;i<=a;i++){
            cin>>val;
            aval+=val;
        }
        for(int i=1;i<=b;i++){
            cin>>val;
            bval+=val;
        }
        for(int i=1;i<=c;i++){
            cin>>val;
            cval+=val;
        }
        all=(aval+bval+cval);
        average=all/3;
        if(aval==average&&bval==average&&cval==average){
            cout<<"0.00 0.00 0.00 0.00 0.00 0.00"<<endl;
            continue;
        }
        aval-=average;
        bval-=average;
        cval-=average;
        double t=aval*bval*cval;
        if(t==0){
            if(aval==0){
                if(bval<0){
                    printf("0.00 0.00 0.00 %.2lf 0.00 0.00 0.00",cval);
                }
                else{
                    printf("0.00 0.00 0.00 0.00 0.00 0.00 %.2lf",bval);
                }
            }
            else if(bval==0){
                if(aval<0){
                    printf("0.00 %.2lf 0.00 0.00 0.00 0.00 0.00",cval);
                }
                else{
                    printf("0.00 0.00 0.00 0.00 0.00 %.2lf 0.00",aval);
                }
            }
            else{
                if(aval<0){
                    printf("%.2lf 0.00 0.00 0.00 0.00 0.00 0.00",bval);
                }
                else{
                    printf("0.00 0.00 %.2lf 0.00 0.00 0.00 0.00",aval);
                }
            }
            cout<<endl;
        }
        else if(t>0){
            if(aval>0){
                printf("0.00 0.00 %.2lf 0.00 %.2lf 0.00",-bval,-cval);
            }
            else if(bval>0){
                printf("%.2lf 0.00 0.00 0.00 0.00 %.2lf",-aval,-cval);
            }
            else{
                printf("0.00 %.2lf 0.00 %.2lf 0.00 0.00",-aval,-bval);
            }
            cout<<endl;
        }
        else{
            if(aval<0){
                printf("%.2lf %.2lf 0.00 0.00 0.00 0.00",bval,cval);
            }
            else if(bval<0){
                printf("0.00 0.00 %.2lf %.2lf 0.00 0.00",aval,cval);
            }
            else{
                printf("0.00 0.00 0.00 0.00 %.2lf %.2lf",aval,bval);
            }
            cout<<endl;
        }
    }
    return 0;
}