#include <iostream>
#include <vector>

class Graph {
private:
    std::vector<std::vector<int>> g;
public:
  Graph(int NumberOfPicks){
    g.resize(NumberOfPicks);
  }
  void addEdge(int u, int v){
    g[u].push_back(v);
  }
  int size(){
    return g.size();
  } 
};
class OrderProvider{
private:
const Graph& graph;
std::vector<int> currentOrder;
std::vector<bool>  visited;
public:
  OrderProvider(Graph& g):graph(g), currentOrder(), visited(){}
};


int main() {
  std::cout << "Hello World!\n";
Graph q(5);
  q.addEdge(0,1);
  q.addEdge(2,3);
  q.addEdge(2,1);
  q.addEdge(3,4);
  std::cout << "Hello World!\n";

}