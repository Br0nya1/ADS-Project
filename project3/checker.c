#include<stdio.h>
#include<stdlib.h>

int read(){
    int s=0,f=1;
    char ch=getchar();
    for(;ch<'0' || ch>'9';ch=getchar()) if(ch=='-') f=-1;
    for(;ch>='0' && ch<='9';ch=getchar()) s=s*10+ch-'0';
    return s*f;
}

struct Unit{
    int deg;
    int dir[4]; // up down left right
}pos[102][102];

int vis[102][102];

int n,m;

void Error(){
    puts("Error!");
    exit(0);
}

void modifyDown(int x,int y){
    pos[x][y].dir[1]=0;
    for(int i=x+1;i<=n;i++){
        if(pos[i][y].deg){
            if(!pos[i][y].dir[0]) Error();
            pos[i][y].dir[0]=0;
            return;
        }
        if(vis[i][y]) Error();
        vis[i][y]=1;  // key checker of points with no degree
    }
    Error();
}

void modifyRight(int x,int y){
    pos[x][y].dir[3]=0;
    for(int j=y+1;j<=m;j++){
        if(pos[x][j].deg){
            if(!pos[x][j].dir[2]) Error();
            pos[x][j].dir[2]=0;
            return;
        }
        if(vis[x][j]) Error();
        vis[x][j]=1;  // key checker of points with no degree
    }
    Error();
}

int main(){
    n=read(),m=read();
    int cnt=0;
    for(int x=1;x<=n;x++){
        for(int y=1;y<=m;y++){
            if(pos[x][y].deg=read()) cnt++;
        }
    }
    for(int i=1;i<=cnt;i++) {
        int x=read(),y=read(),deg=0;
        for(int i=0;i<4;i++) deg+=(pos[x][y].dir[i]=read());
        if(deg!=pos[x][y].deg) Error();
    }
    for(int x=1;x<=n;x++){
        for(int y=1;y<=m;y++){
            if(pos[x][y].dir[0] || pos[x][y].dir[2]) Error();
            if(pos[x][y].dir[1]) modifyDown(x,y);
            if(pos[x][y].dir[3]) modifyRight(x,y);
        }
    }
    puts("Correct Answer!");
}