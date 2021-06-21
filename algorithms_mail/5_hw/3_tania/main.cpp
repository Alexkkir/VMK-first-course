#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <vector>
using namespace std;

typedef struct cell{
    int x;
    int y;
} cell;


int find(set<std::pair<int,int>> &alive,int x, int y,int n,int m)
{
    int f=0;
    if (x<0 || y<0 || x>n-1 || y>m-1){
        return 0;
    }
    if (x>0 && y>0 && alive.count({x-1,y-1})==1){
        f++;
    }
    if (x>0 && alive.count({x-1,y})==1){
        f++;
    }
    if (x<n-1 && y>0 && alive.count({x+1,y-1})==1){
        f++;
    }
    if (x<n-1 && alive.count({x+1,y})==1){
        f++;
    }
    if (x<n-1 && y<m-1 && alive.count({x+1,y+1})==1){
        f++;
    }
    if (y<m-1 && alive.count({x,y+1})==1){
        f++;
    }
    if (x>0 && y<m-1 && alive.count({x-1,y+1})==1){
        f++;
    }
    if (y>0 && alive.count({x,y-1})==1){
        f++;
    }
    return f;
}

int main(void) {
    int n,m,l,k;
    scanf("%d%d%d%d",&n,&m,&l,&k);
    int mas[n][m];
    //mas=(int**) malloc (sizeof(int*)*n);
    for (int i=0;i<n;i++){
        //mas[i]=(int *) malloc (sizeof(int)*m);
        for (int j=0;j<m;j++){
            mas[i][j]=0;
        }
    }
    set <std::pair<int,int>> alive;
    for (int i=0;i<l;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        alive.insert({x,y});
    }
    std::vector<std::pair<int,int>> alive1;
    std::vector<std::pair<int,int>> dead;
    for (int ss=0;ss<k;ss++){
        for (auto it : alive){
            int x=(it).first,y=(it).second;
            int f=find (alive,x,y,n,m);
            if (f==3){
                if (alive.count({x,y})==0){
                    alive1.push_back({x,y});
                }
            } else if (f!=2 && alive.count({x,y})==1){
                dead.push_back({x,y});
            }
            if (x<n-1 && y<m-1){
                f=find (alive,x+1,y,n,m);
                if (f==3){
                    if (alive.count({x+1,y})==0){
                        alive1.push_back({x+1,y});
                    }
                } else if (f!=2 && alive.count({x+1,y})==1){
                    dead.push_back({x+1,y});
                }
            }
            if (x<n-1 && y<m-1){
                f=find (alive,x+1,y+1,n,m);
                if (f==3){
                    if (alive.count({x+1,y+1})==0){
                        alive1.push_back({x+1,y+1});
                    }
                } else if (f!=2 && alive.count({x+1,y+1})==1){
                    dead.push_back({x+1,y+1});
                }
            }

            if (y<m-1){
                f=find (alive,x,y+1,n,m);
                if (f==3){
                    if (alive.count({x,y+1})==0){
                        alive1.push_back({x,y+1});
                    }
                } else if (f!=2 && alive.count({x,y+1})==1){
                    dead.push_back({x,y+1});
                }
            }

            if (x>0 && y<m-1){
                f=find (alive,x-1,y+1,n,m);
                if (f==3){
                    if (alive.count({x-1,y+1})==0){
                        alive1.push_back({x-1,y+1});
                    }
                } else if (f!=2 && alive.count({x-1,y+1})==1){
                    dead.push_back({x-1,y+1});
                }
            }

            if (x>0){
                f=find (alive,x-1,y,n,m);
                if (f==3){
                    if (alive.count({x-1,y})==0){
                        alive1.push_back({x-1,y});
                    }
                } else if (f!=2 && alive.count({x-1,y})==1){
                    dead.push_back({x-1,y});
                }
            }

            if (x>0 && y>0){
                f=find (alive,x-1,y-1,n,m);
                if (f==3){
                    if (alive.count({x-1,y-1})==0){
                        alive1.push_back({x-1,y-1});
                    }
                } else if (f!=2 && alive.count({x-1,y-1})==1){
                    dead.push_back({x-1,y-1});
                }
            }
            if (y>0){
                f=find (alive,x,y-1,n,m);
                if (f==3){
                    if (alive.count({x,y-1})==0){
                        alive1.push_back({x,y-1});
                    }
                } else if (f!=2 && alive.count({x,y-1})==1){
                    dead.push_back({x,y-1});
                }
            }

            if (x<n-1 && y>0){
                f=find (alive,x+1,y-1,n,m);
                if (f==3){
                    if (alive.count({x+1,y-1})==0){
                        alive1.push_back({x+1,y-1});
                    }
                } else if (f!=2 && alive.count({x+1,y-1})==1){
                    dead.push_back({x+1,y-1});
                }
            }
        }
        for (unsigned long aa=alive1.size();aa>0;aa--){
            if (alive.count(alive1[aa-1])==0){
                alive.insert(alive1[aa-1]);
                alive1.pop_back();
            }
        }
        for (unsigned long aa=dead.size();aa>0;aa--){
            if (alive.count(dead[aa-1])==1){
                alive.erase(dead[aa-1]);
                dead.pop_back();
            }
        }
    }
    for (auto it1: alive){
        printf("%d %d\n",(it1).first,(it1).second);
    }
    return 0;
}
