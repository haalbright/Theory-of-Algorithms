// Write code and submit this file.
// Do not modify any code outside the functions for each question.

#include <iostream>

using namespace std;

#define NUMNODES 6
#define PERMUTATIONS 720

struct GraphNode;

struct ListNode {
  GraphNode* graph_node;
  ListNode* next;
  ListNode(GraphNode *g, ListNode* n) : graph_node(g), next(n) {};
};

struct GraphNode {
  int id;
  int mark;
  ListNode* outlinks;
  int num_inlinks;
};

void AddLink(GraphNode* from, GraphNode* to) {
  from->outlinks = new ListNode(to, from->outlinks);
  to->num_inlinks++;
}

// Q1. 20 points
// Implement this function to print topologically sorted ids of input graph.
// Assume input graph has NUMNODES number of nodes.
// Use the method described in class:
// Step 1: Find all sources and add to source list.
// Step 2: For each node in source list, print it, remove all outlinks.
//         If removal of outlinks causes new source, add it to source list.
// Your function may destroy the input graph.
// You do not have to take care of memory leak.
// Assume input is a directed acyclic graph.
// Your implementation should be O(|V|+|E|) time,
// where |V| is the number of vertices and |E| is the number of edges.
void TopologicalSort(GraphNode graph[]){
  ListNode* sources=NULL;
  for (int i=0; i<NUMNODES; i++){
    if (graph[i].num_inlinks==0){
      sources= new ListNode(&graph[i], sources);
    }
  }
  cout<<"My topological sort order: "<<endl;
  while (sources!=NULL){
    GraphNode* n=sources->graph_node;
    sources=sources->next;
    cout<< n->id<<" ";
    while (n->outlinks!=NULL){
      (n->outlinks)->graph_node->num_inlinks--;
      if ((n->outlinks)->graph_node->num_inlinks==0){
        sources=new ListNode((n->outlinks)->graph_node, sources);
      }
      n->outlinks=n->outlinks->next;
    }

  }

}

// Q2. 5 points
// Write recursive algorithm to, given two nodes p and c,
// return true if p is an ancestor of c, false otherwise.
// Assume that, before the initial call to this function,
// all marks have been initialized to 0.
bool IsAncestor(GraphNode* p, GraphNode*c) {//this is always false
  ListNode* sources=NULL;
  sources=p->outlinks;
  if (p->id==c->id){
    return true;
  }
  else if (p->outlinks==NULL){
    return false;
  }
  while(sources!=NULL){
    p=sources->graph_node;
    if (IsAncestor(p,c)) {
      return true;
    }
    sources=sources->next;
  }
  return false;
  cout<<" "<<endl;
}

// Q3. 5 points
// Given an order, determine if the order is a valid topologically sorted
// order of the given graph.
// Inputs graph and order are both arrays of length NUMNODES.
// Assume that the integers in the order array represent the IDs of the nodes
// in the graph.
bool IsTopologicalOrder(GraphNode graph[], int order[]) {
  GraphNode *anc=NULL;
  GraphNode *child=NULL;
  for (int i=0; i<NUMNODES-1; i++){
    anc=&graph[order[i]];
    child=&graph[order[i+1]];
    if (IsAncestor(anc,child)==false){
      return false;
    }
  }
  return true;
  // ListNode* sources=NULL; //i think this isnt correct
  // for (int i=0; i<NUMNODES; i++){
  //   if (graph[i].num_inlinks==0){
  //     sources= new ListNode(&graph[i], sources);
  //   }
  // }
  // int count=0;
  // int index=0;
  // while (sources!=NULL){
  //   GraphNode* n=sources->graph_node;
  //   sources=sources->next;
  //   if (n->id==order[index]){
  //     count++;
  //   }
  //   index++;
  //   while (n->outlinks!=NULL){
  //     (n->outlinks)->graph_node->num_inlinks--;
  //     if ((n->outlinks)->graph_node->num_inlinks==0){
  //       sources=new ListNode((n->outlinks)->graph_node, sources);
  //     }
  //     n->outlinks=n->outlinks->next;
  //   }
  //
  // }
  // if (count==NUMNODES){
  //   return true;
  // }
  // return false;
}

int permutations[PERMUTATIONS][NUMNODES];
int factorials[NUMNODES+1];

void GenerateFactorials() {
  factorials[0] = factorials[1] = 1;
  for (int i = 2; i <= NUMNODES; i++) {
    factorials[i] = factorials[i-1] * i;
  }
}

void GeneratePermutations(int start, int n) {
  if (n==0) return;
  int num_permutations = factorials[n-1];
  for (int i = 0; i < NUMNODES; i++) {
    // Check if this is a permissible number.
    bool found = false;
    for (int ind = 0; ind < NUMNODES - n; ind++) {
      if (permutations[start][ind] == i) {
	found = true;
	break;
      }
    }
    if (!found) {
      for (int j = 0; j < num_permutations; j++) {
	permutations[start+j][NUMNODES-n] = i;
      }
      GeneratePermutations(start, n - 1);
      start += num_permutations;
    }
  }
}

// Q4. 5 points
// Try all possible orders (you can use the permutations[][] array).
// If an order is a valid topological order of the given graph,
// print the order.
void TopologicalSortBruteForce(GraphNode graph[]) {
  GraphNode *anc=NULL;
  GraphNode *child=NULL;
  cout<<"Topological sort permutations:"<<endl;
  for (int i=0; i<PERMUTATIONS; i++){
    bool order=true;
    for (int k=0; k<NUMNODES-1; k++){
      anc=&graph[permutations[i][k]];
      child=&graph[permutations[i][k+1]];
      for (int k=0; k<NUMNODES-1; k++){
      for(int j = k+1; j < NUMNODES; j++){

        anc=&graph[permutations[i][j]];
        child=&graph[permutations[i][k]];
        if (IsAncestor(anc,child)){
            order=false;
            break;
        }
      }
    }
    }
    if (order==true){
      for (int k=0; k<NUMNODES; k++){
        cout<<permutations[i][k]<<" ";
      }
      cout<<endl;
    }
  }

}

int main() {
  // Part 1: Set up the graph.
  GraphNode graph[NUMNODES];
  // Initialized graph nodes.
  for (int i = 0; i < NUMNODES; i++) {
    graph[i].id = i;
    graph[i].outlinks = nullptr;
    graph[i].num_inlinks = 0;
  }
  // Add some links.
  AddLink(&graph[3], &graph[5]);
  AddLink(&graph[1], &graph[4]);
  AddLink(&graph[4], &graph[5]);
  AddLink(&graph[5], &graph[0]);
  AddLink(&graph[2], &graph[0]);
  AddLink(&graph[1], &graph[2]);

  // Part 2: Topological sort by brute force method.
  // First generate permutations that may be helpful.
  GenerateFactorials();
  GeneratePermutations(0, 6);
  // testIsAncestor(graph);
  TopologicalSortBruteForce(graph);
  // This prints:
  // 1 2 3 4 5 0
  // 1 2 4 3 5 0
  // 1 3 2 4 5 0
  // 1 3 4 2 5 0
  // 1 3 4 5 2 0
  // 1 4 2 3 5 0
  // 1 4 3 2 5 0
  // 1 4 3 5 2 0
  // 3 1 2 4 5 0
  // 3 1 4 2 5 0
  // 3 1 4 5 2 0

  // Part 3: Call topological sort to print graph in topological sorted order.
  // Note that calling this function destroys the graph.
  TopologicalSort(graph);
  // This prints 3 1 4 5 2 0 or some other valid topologically sorted order.

  return 0;
}
