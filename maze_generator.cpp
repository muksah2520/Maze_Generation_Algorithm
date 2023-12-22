#include <iostream>
#include <unordered_map>
#include <random>
#include <fstream>
using namespace std;
class DSU{
public:
    vector<int> v;
    vector<int> rank;
    DSU(int n){
        v=vector<int>(n,-1);
        rank=vector<int>(n,0);
    }
    int find(int a){
        if(v[a]==-1){
            return a;
        }
        else{
            v[a]=find(v[a]);
            return v[a];
        }
    }
    void union1(int a,int b){
        int f1=find(a);
        int f2=find(b);
        if(f1==f2){
            return;
        }
        else{
            if(rank[a]>rank[b]){
                v[f2]=f1;
            }
            else if(rank[a]<rank[b]){
                v[f1]=f2;
            }
            else{
                v[f2]=f1;
                rank[a]++;
            }
        }
    }
};

void randomvector(int size,vector<int>& v){

    vector<int> m(size,0);
    while(v.size()!=size){
        //cout<<"g"<<endl;
        int a=rand()%size;
        if(m[a]==0){
            v.push_back(a);
            m[a]=1;
        }
    }
}
pair<int,int> stdformat(int i,int n){
    int b=i%n;
    int a=i/n;
    pair<int,int> p(a,b);
    return p;
}

string forgui(int v1,int v2,int n){
      int a1;
      a1=v1/n;
      string s="";
      //corresponding to v1
      int vv1=v1+a1;
      if(v2==v1+1){
          s+=to_string(vv1+1);
          s+=" ";
          s+=to_string(vv1+1+n+1);
      }
      else{
          s+=to_string(vv1+n+1);
          s+=" ";
          s+=to_string(vv1+n+1+1);
      }
      return s;
}
void edgesfiller(int n,vector<pair<int,int>>& edges){
    for(int i=0;i<n*n;i++){
        if((i+1)%n==0 and i!=n*n-1){
            pair<int,int> p1;
            p1.first=i;
            p1.second=i+n;
            edges.push_back(p1);
        }
        else if((i+1)%n==0 and i==n*n-1){
            continue;
        }
        else if(i<=n*n-1 and i>=n*n-n){
            pair<int,int> p1;
            p1.first=i;
            p1.second=i+1;
            edges.push_back(p1);
        }
        else{
            pair<int,int> p1;
            pair<int,int> p2;
            p1.first=i;
            p1.second=i+1;
            p2.first=i;
            p2.second=i+n;
            edges.push_back(p1);
            edges.push_back(p2);
        }
    }
}

//generating a n*n maze
//for a n*n maze, no. of edges: 2*n*(n-1)
                                //n-->n+1
int main(){
     int n;
     cout<<"Enter the dimension of maze you want to generate";
     cin>>n;
     vector<pair<int,int>> edges;
     edgesfiller(n,edges);
     vector<int> v;
     randomvector(edges.size(),v);
     vector<pair<int,int>> randomedges;
     for(int i=0;i<edges.size();i++){
         randomedges.push_back(edges[v[i]]);
     }
     DSU d(n*n);
    
     vector<pair<int,int>> stdrandomedges;
     edgesfiller(n+1,stdrandomedges);
     unordered_map<string,int> m;
     vector<int> edgechk(2*(n+1)*n,1);
     for(int i=0;i<stdrandomedges.size();i++){
         int v1=stdrandomedges[i].first;
         int v2=stdrandomedges[i].second;
         string s=to_string(v1)+" "+to_string(v2);
         m[s]=i;
     }
     for(int i=0;i<randomedges.size();i++){
         pair<int,int> e=randomedges[i];
         int v1=e.first;
         int v2=e.second;
         if(d.find(v1)==d.find(v2)){
             continue;
         }
         else{
             d.union1(v1,v2);
             string s=forgui(v1,v2,n);
             edgechk[m[s]]=0;
         }
     }
    vector<pair<pair<int,int>,pair<int,int>>> finaledges;//these actually have to be there
     for(int i=0;i<edgechk.size();i++){
         if(edgechk[i]){
             pair<int,int> e=stdrandomedges[i];
             int v1=e.first;
             int v2=e.second;
             pair<int,int> p1=stdformat(v1,n+1);
             pair<int,int> p2=stdformat(v2,n+1);
             pair<pair<int,int>,pair<int,int>> p(p1,p2);
             finaledges.push_back(p);
         }
     }
     ofstream o;
     o.open("maze_edges.txt");
     for(auto& i: finaledges){
         o<<"("<<"("<<i.first.first<<","<<i.first.second<<")"<<","<<"("<<i.second.first<<","<<i.second.second<<")"<<")"<<",";
     }
     o.close();
}