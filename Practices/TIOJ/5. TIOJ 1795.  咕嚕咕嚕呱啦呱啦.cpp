#include <bits/stdc++.h>
#define MaxVertices 100000
#define MaxEdges 300000

using namespace std;

struct edge{
    int head, tail, weight;
    edge(){};
    edge(int a, int b, int c){
        head = a, tail = b, weight = c;
    }
};
vector<edge> Edges;

bool cmpBig(edge a, edge b){
    return a.weight > b.weight;
}

bool cmpSmall(edge a, edge b){
    return a.weight < b.weight;
}

int parent[MaxVertices], Size[MaxEdges];

void Initialize(int vertices){
    for (int i = 0; i < vertices; ++i) {
        parent[i] = i;
        Size[i] = 1;
    }
}

int Find(int a){
    return (a == parent[a] ? a : parent[a] = Find(parent[a]));
}

void setUnion(int a, int b){
    a = Find(a), b = Find(b);
    if(Size[a] < Size[b]){
        Size[b] += Size[a];
        parent[a] = b;
    }
    else{
        Size[a] += Size[b];
        parent[b] = a;
    }
}
int Kruskal(){
    int answer = 0;
    for (int i = 0; i < Edges.size(); ++i) {
        int head = Find(Edges[i].head), tail = Find(Edges[i].tail);
        if(head == tail) continue;
        answer += Edges[i].weight;
        setUnion(head, tail);
    }
    return answer;
}

int main(){
    int vertices, edges, request, head, tail, weight;
    cin >> vertices >> edges >> request;
    Edges.resize(edges);
    for (int i = 0; i < edges; ++i) {
        cin >> head >> tail >> weight;
        Edges[i] = edge(head, tail, weight);
    }
    Initialize(vertices);
    sort(Edges.begin(), Edges.end(), cmpBig);
    int big = Kruskal();
    Initialize(vertices);
    sort(Edges.begin(), Edges.end(), cmpSmall);
    int small = Kruskal();
    if (small <= request && request <= big) cout << "TAK" << endl;
    else cout << "NIE" << endl;

    return 0;
}

// 題目 : https://tioj.ck.tp.edu.tw/problems/1795

// Reference : https://miohitokiri5474.github.io/code/TIOJ-1795/