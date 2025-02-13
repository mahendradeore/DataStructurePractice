#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<queue>
#include <functional>
#include<climits>
using namespace std;

struct compare{
    bool operator()(pair<std::string,int> &a, pair<std::string,int> &b){
        return a.second > b.second;
    }
};
void  dijkstra(map<string, vector<pair<string, int>>> & graph, std::string & start){
     map<string, int> dist;

     for (const auto &st : graph){
      dist[st.first]  = INT_MAX;
     }
     dist[start] = 0;
     priority_queue<pair<string, int>, vector<pair<std::string,int>>,compare> pq;
     //priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    //declare using lamda
    //priority_queue<pair<string, int>, vector<pair<std::string,int>>,function <bool(pair<std::string,int>,pair<std::string,int>)>> pq;
   // pq= priority_queue<pair<string, int>, vector<pair<std::string,int>>,function <bool(pair<std::string,int>,pair<std::string,int>)>>([](pair<string, int> a, pair<string, int> b){
      //  return a.second > b.second;
    //});
    //priority_queue<pair<string, int>, vector<pair<string, int>>, function<bool(pair<string, int>, pair<string, int>)>> pq;
    pq.push(make_pair(start,0));
    //track processed node
    //map<std::string,bool> processed;

    while (!pq.empty())
    {
        pair<string,int> pt = pq.top();
        string node = pt.first;
        int nodeDist = pt.second;
        pq.pop();
//not needed
    //    if(processed[node])
    //         continue;
    //     /* code */

        for (const auto & neighbour :graph[node]){
            string nnode = neighbour.first;
            int wt = neighbour.second;

            if(dist[node]+wt < dist[nnode]){
                dist[nnode] = dist[node]+wt;
                pq.push(make_pair(nnode,dist[nnode]));
            }
        }
    }
    
    for (const auto & a:dist){
        std::cout <<"Distance from Strat Node ["<< start << "] to Node = "<< a.first <<", is dist = "<<a.second <<std::endl;
    }

}

int main() {
    // Graph represented as an adjacency list
    map<string, vector<pair<string, int>>> graph;

    // Adding edges to the graph (node, neighbor, weight)
    graph["A"].push_back(make_pair("B", 4));
    graph["A"].push_back(make_pair("C", 2));
    graph["B"].push_back(make_pair("C", 5));
    graph["B"].push_back(make_pair("D", 10));
    graph["C"].push_back(make_pair("D", 3));
    graph["D"].push_back(make_pair("E", 7));
    graph["E"].push_back(make_pair("A", 1));

    string start = "A"; // Starting node for Dijkstra's algorithm

    dijkstra(graph, start);

    return 0;
}