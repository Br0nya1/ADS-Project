#include<stdio.h>
#include<stdlib.h>

int main(){
    freopen("in2.txt","w",stdout);
    for(int i=1;i<=50;i++){
        printf("1 ");
        for(int j=1;j<=48;j++) printf("2 ");
        if(i==1 || i==50) printf("2 \n");
        else printf("3 \n");
    }
}