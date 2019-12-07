#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <limits.h>
using namespace std;

//The function of getting the minimum distance
int minDistance(int dist[], bool sptSet[],int size) 
{ 
    // Initialize min value 
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < size; v++) 
        if (sptSet[v] == false && dist[v] <= min) 
            min = dist[v], min_index = v; 
  
    return min_index; 
} 

int printSolution(int distNew[],int size,int tree1[]) 
{ 
    printf("Routing table(<Destination> <Cost> <Next hop>):\n"); 
    for (int i = 1; i < size; i++) {
        cout<<i<<" "<<distNew[i]<<" "<<tree1[i]<<endl;
    }
         
    printf("Minimum path tree(represented by edge):");

    
} 


int main(){
    //Get data from the .txt file
    
    ifstream original("Adj.txt");
    int k;
    string line;
    for (k=0;getline(original, line);++k);
    //cout<<k;
    original.close();
    ifstream input("Adj.txt");
    //get how many element in the .txt file
    int size;
    
    string oneline;
    istringstream ss;
    getline(input,oneline);
    ss.str(oneline);
    ss>>size;
    //initialize the variables
    int source[k-1];
    int dest[k-1];
    int distance[k-1];
    int counter=0;
    string newline;
     for(int i=0;i<k-1;++i){
         getline(input,newline);
         istringstream ss1;
         ss1.str(newline);
         ss1>>source[counter]>>dest[counter]>>distance[counter];
         counter=counter+1;
         
     }
     //intialize the matrix
     int Fmatrix[size][size];
    //set it all to zeros
     for(int i=0;i<size;++i){
        for(int j=0;j<size;++j){
            Fmatrix[i][j]=0;
            
        }
    }
    //get the values in
     for(int i=0;i<size;++i){
         for(int j=0;j<k-1;j++){
            if(source[j]==i){
                Fmatrix[i][dest[j]]=distance[j];
                
                
            }
        }
     } 



    int tree1[size]={};    //The tree of the next hop
    vector < vector<int> > tree2;    //The tree of the minimum path 
    int distNew[size];
    bool sptSet[size];
    for (int i = 0; i < size; i++){
        distNew[i] = INT_MAX, sptSet[i] = false; 
        tree2.push_back(vector<int>());
    }
    distNew[0]=0;
    for (int count = 0; count < size - 1; count++) { 
        // Pick the minimum distance vertex from the set of vertices not 
        // yet processed. u is always equal to src in the first iteration. 
        int u = minDistance(distNew, sptSet,size);
        //cout<<u;
        sptSet[u] = true; 
        
         // Update dist value of the adjacent vertices of the picked vertex.
         // In here we want to get the minimum path tree 


        // Update dist value of the adjacent vertices of the picked vertex. 
        for (int v = 0; v < size; v++) {
            
            // Update dist[v] only if is not in sptSet, there is an edge from 
            // u to v, and total weight of path from src to  v through u is 
            // smaller than current value of dist[v] 
            if (!sptSet[v] && Fmatrix[u][v] && distNew[u] != INT_MAX 
                && distNew[u] + Fmatrix[u][v] < distNew[v]) {
                //This part is the calculation of the minimum path tree
                //cout<<u<<v<<" "<<endl;
                tree2[v].push_back(u);
                tree2[v].push_back(v);

                if(u==0){
                    tree1[v]=v;
                    //cout<<tree1[v]<<endl;
                }
                else{
                 for(int p=0;p<size;p++){
                     if(u==tree1[p]){
                         tree1[v]=u;
                     }
                     else{
                         tree1[v]=tree1[u];
                     }
                 }
                }
                //This part is the calculation of the minimum cost to the index
                distNew[v] = distNew[u] + Fmatrix[u][v];
                
                } 
        }
    }
    
    printSolution(distNew,size,tree1);


    for (int i = 0; i < tree2.size(); i++)
{
    cout<<"\n";
    for (int j = 0; j < tree2[i].size(); j++)
    {
    while(tree2[i].size()>2){
        tree2[i].erase(tree2[i].begin());
        
    }
       
       cout << tree2[i][j]<<" ";

    }
}




}