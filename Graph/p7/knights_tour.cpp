#include <iostream>
#include <vector>
#include <climits>
#include <cstring>
using namespace std;

const int N=9;
vector<pair<int,int>> g[N][N];
bool used[N][N];
int res[N][N];
int d_x[8]={2,-2,2,-2,1,1,-1,-1};
int d_y[8]={1,1,-1,-1,2,-2,2,-2};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n,m;
    cin>>m>>n;

    for(int i=1;i<=8;i++){
        for(int j=1;j<=8;j++){
            for(int k=0;k<8;k++){
                if(i+d_x[k]>=1 && j+d_y[k]>=1 && i+d_x[k]<=8 && j+d_y[k]<=8){
                    g[i][j].push_back({i+d_x[k],j+d_y[k]});
                }
            }
        }    
    }

    int cnt=1;
    int x=n,y=m;
    used[x][y]=true;
    res[x][y]=cnt;
    while(cnt<64){
        int min_moves=INT_MAX;
        int nxtx=-1,nxty=-1;

        for(auto pair:g[x][y]){
            int nx=pair.first;
            int ny=pair.second;
            if(used[nx][ny]) continue;

            int moves=0;
            for(auto p:g[nx][ny]){
                if(!used[p.first][p.second]){
                    moves++;
                }
            }

            if(min_moves>moves){
                min_moves=moves;
                nxtx=nx;
                nxty=ny;
            }else if(min_moves==moves){
                if(nx<nxtx){
                    nxty=ny;
                    nxtx=nx;
                }
                if(ny<nxty){
                    nxtx=nx;
                    nxty=ny;
                }
            }
        }

        x=nxtx;
        y=nxty;
        cnt++;
        res[x][y]=cnt;
        used[x][y]=true;
    }

    for(int i=1;i<=8;i++){
        for(int j=1;j<=8;j++){
            cout<<res[i][j]<<" ";
        }
        cout<<endl;
    }

}