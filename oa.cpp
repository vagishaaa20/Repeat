#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int main(){
    int n; 
    if(!(cin>>n)) return 0;
    vector<vector<int>> g(n+1, vector<int>(n+1));
    int mx=0;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){ cin>>g[i][j]; mx=max(mx,g[i][j]); }
    int a,b,c,d; cin>>a>>b>>c>>d;

    int M = max(mx,2)+1;
    vector<int> spf(M,0);
    for(int i=2;i<M;i++){
        if(!spf[i]){
            for(long long j=i;j<M;j+=i) if(!spf[(int)j]) spf[(int)j]=i;
        }
    }
    const long long INF = 1e18;
    auto w=[&](int v)->long long{ return v>1? (long long)spf[v] : INF; };

    vector<vector<long long>> dist(n+1, vector<long long>(n+1, INF));
    priority_queue<pair<long long,pair<int,int>>, vector<pair<long long,pair<int,int>>>, greater<>> pq;
    dist[a][b]=0;
    pq.push({0,{a,b}});
    int dx[4]={1,-1,0,0}, dy[4]={0,0,1,-1};
    while(!pq.empty()){
        auto [du,p]=pq.top(); pq.pop();
        int x=p.first,y=p.second;
        if(du>dist[x][y]) continue;
        for(int k=0;k<4;k++){
            int nx=x+dx[k], ny=y+dy[k];
            if(nx<1||nx>n||ny<1||ny>n) continue;
            long long nd=max(du, w(g[nx][ny]));
            if(nd<dist[nx][ny]){
                dist[nx][ny]=nd;
                pq.push({nd,{nx,ny}});
            }
        }
    }
    long long ans = dist[c][d];
    if(a==c && b==d) ans=0;
    cout << ans << "\n";
    return 0;
}