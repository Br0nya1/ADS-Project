#include<stdio.h>
#include<stdlib.h>

struct Unit{
    int deg;
    int dir[4]; // up down left right
    int dx,ry;
    //dx: the x-index of unit which is modified by this unit at direction "down"
    //ry: the r-index of unit which is modified by this unit at direction "right"
}pos[102][102];

int vis[102][102]; // if the unit has a fence

int n,m;

void dfs(int x,int y); // main searching function
int findDown(int x,int y); // find and modify if the fence can extend down
int findRight(int x,int y); // find and modify if the fence can extend right
void backDown(int x,int y); // backtrack from down
void backRight(int x,int y); // backtrack from right
void output();

int main(){
    scanf("%d%d",&n,&m); // input the size of the garden
    for(int x=1;x<=n;x++){
        for(int y=1;y<=m;y++){
            scanf("%d",&pos[x][y].deg); // input the degree of each unit
        }
    }
    dfs(1,1); // start from point (1,1)
    puts("No Solution!");
    return 0;
}

void dfs(int x,int y){
    if(y>m){
        //the solution has been found!
        output(),exit(0);
    }
    if(pos[x][y].deg>=3) return;
    if(pos[x][y].deg==2){
        if(!findDown(x,y)) return;
        if(!findRight(x,y)){
            backDown(x,y); // the information at diraction "down" has been modified(at line 42), so backtracking is needed
            return;
        }
        if(x<n) dfs(x+1,y); // if it is not at the last row, go down by one step
        else dfs(1,y+1);  // if it is at the last row, then go to the top of next column
        backDown(x,y);
        backRight(x,y);
        // backtrack both directions
    }
    else if(pos[x][y].deg==1){
        if(findDown(x,y)) { // modify "down"
            if(x<n) dfs(x+1,y); // if it is not at the last row, go down by one step
            else dfs(1,y+1);  // if it is at the last row, then go to the top of next column
            backDown(x,y); // backtrack "down"
        }
        if(findRight(x,y)) { // modify "right"
            if(x<n) dfs(x+1,y); // if it is not at the last row, go down by one step
            else dfs(1,y+1);  // if it is at the last row, then go to the top of next column
            backRight(x,y); // backtrack "right"
        }
    }
    else { // if the degree is 0
        if(x<n) dfs(x+1,y); // if it is not at the last row, go down by one step
        else dfs(1,y+1);  // if it is at the last row, then go to the top of next column
    }
}

int findDown(int x,int y){
    // 
    for(int i=x+1;i<=n;i++){
        if(pos[i][y].deg){
            pos[x][y].deg--;
            pos[x][y].dir[1]=1; // tag "down"
            pos[x][y].dx=i; // record its x-index
            pos[i][y].deg--;
            pos[i][y].dir[0]=1; // tag "up"
            vis[i][y]=1;
            for(int id=x+1;id<=i;id++) vis[id][y]=1; // add a fence tag between two ends
            return 1;
        }
        if(vis[i][y]) return 0;
    }
    return 0;
}

int findRight(int x,int y){
    for(int j=y+1;j<=m;j++){
        if(pos[x][j].deg){
            pos[x][y].deg--;
            pos[x][y].dir[3]=1; //tag "right"
            pos[x][y].ry=j; // record its y-index
            pos[x][j].deg--;
            pos[x][j].dir[2]=1; // tag "left"
            vis[x][j]=1;
            for(int id=y+1;id<=j;id++) vis[x][id]=1; // add a fence tag between two ends
            return 1;
        }
        if(vis[x][j]) return 0;
    }
    return 0;
}

void backDown(int x,int y){
    pos[x][y].deg++;
    pos[x][y].dir[1]=0; // change back "down"
    int dx=pos[x][y].dx;
    pos[dx][y].deg++;
    pos[dx][y].dir[0]=0; // change back "up"
    for(int i=x+1;i<=dx;i++) vis[i][y]=0;
}

void backRight(int x,int y){ 
    pos[x][y].deg++;
    pos[x][y].dir[3]=0; // change back "right"
    int ry=pos[x][y].ry;
    pos[x][ry].deg++;
    pos[x][ry].dir[2]=0; // change back "left"
    for(int j=y+1;j<=ry;j++) vis[x][j]=0;
}

void output(){ // output the solution
    puts("");
    for(int x=1;x<=n;x++){
        for(int y=1;y<=m;y++){
            if(pos[x][y].dir[0] || pos[x][y].dir[1] || pos[x][y].dir[2] || pos[x][y].dir[3]){ // check if it is a connector
                printf("%d %d",x,y); // the position of connector
                for(int i=0;i<4;i++) printf(" %d",pos[x][y].dir[i]); // the information of each direction
                puts("");
            }
        }
    }
}


/*
5 6
0 0 2 0 0 2
1 3 3 1 0 0
2 2 1 0 0 2
0 0 0 0 0 1
2 0 2 0 0 2

5 6
0 0 2 0 0 2
1 3 3 1 0 0
2 2 1 0 0 1
0 0 0 0 0 1
2 0 2 0 0 2

3 5
1 1 2 0 1
1 0 3 0 2
1 2 1 0 1

4 4
0 1 1 0
2 0 0 1
1 0 0 0
0 1 1 0

4 4
0 1 0 0
2 1 0 0
1 0 0 0
0 1 0 0
*/