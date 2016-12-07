#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

// a structure to represent an edge in graph
struct Edge
{
    //頂點 頂點 權重
    int src, dest;
    float weight;
};

// a structure to represent a graph
struct Graph
{
    // V-> Number of vertices, E-> Number of edges
    int V, E;

    // graph is represented as an array of edges
    struct Edge* edge;
};

struct subset
{
    int parent;
    int rank;
};

// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );
    graph->V = V;
    graph->E = E;

    graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );

    return graph;
}

// A utility function to find set of an element i
// (uses path compression technique)
int find(struct subset subsets[], int i)
{
    // find root and make root as parent of i (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;

    // If ranks are same, then make one as root and increment
    // its rank by one
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// The main function to check whether a given graph contains cycle or not
int isCycle( struct Graph* graph )
{
    int V = graph->V;
    int E = graph->E;

    // Allocate memory for creating V sets
    struct subset *subsets =
        (struct subset*) malloc( V * sizeof(struct subset) );

    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Iterate through all edges of graph, find sets of both
    // vertices of every edge, if sets are same, then there is
    // cycle in graph.
    for(int e = 0; e < E; ++e)
    {
        //如果weight=-1，代表該邊暫時無法使用
        if(graph->edge[e].weight==-1) continue;

        int x = find(subsets, graph->edge[e].src);
        int y = find(subsets, graph->edge[e].dest);

        if (x == y)
            return 1;

        Union(subsets, x, y);
    }

    //輸出集合
    printf("\n----Set----\n");
    printf(" V parents\n");
    for (int v = 0; v < V; ++v)
    {
        printf("% 2d % 7d\n",v+1,subsets[v].parent+1);
    }

    return 0;
}

//排序edge
bool edge_sort (struct Edge i,struct Edge j)
{
    return (i.weight<j.weight);
}



void Kruskal(struct Graph * graph)
{
    cout << "\n***********Kruskal algorithm*************" <<endl;

    //依照edge權重排序edge
    std::sort (graph->edge,graph->edge+graph->E, edge_sort);

    //印出排序後的edge
    printf("\n----After sorting edge----\n src dest weight\n");
    for (int i=0; i<graph->E; ++i)
    {
        printf("% 4d % 4d % 3.2f\n",graph->edge[i].src,graph->edge[i].dest,graph->edge[i].weight);
    }

    /*創造新的graph，從edge權重 小->大，逐一把edge放入new_graph(weight:-1 => weight: orignal )，若有cycle則跳過此edge*/
    struct Graph* new_graph = createGraph(graph->V, graph->E);

    for (int e=0; e < graph->E ; ++e)
    {
        new_graph->edge[e].src = graph->edge[e].src;
        new_graph->edge[e].dest = graph->edge[e].dest;
        //new_graph->edge[e].weight= graph->edge[e].weight;
        new_graph->edge[e].weight= -1;
    }

    for (int e=0; e< graph->E ; ++e)
    {
        //放入新邊
        new_graph->edge[e].weight =graph->edge[e].weight;

        if (isCycle(new_graph))
        {
            //remove this edge
            new_graph->edge[e].weight= -1;
        }
        else
        {
            //do nothing
        }
    }

    /*MST已生成*/
    printf("\n----MST----\n");

    //列出MST中所含的邊
    printf("   v    v weight\n");
    for (int e = 0; e < new_graph->E; ++e)
    {
        //此邊無法使用
        if (new_graph->edge[e].weight==-1) continue;

        //列出此邊包含的兩點和權重
        printf("% 4d % 4d % 3.2f\n",new_graph->edge[e].src+1,new_graph->edge[e].dest+1,new_graph->edge[e].weight);
    }

}

// Driver program to test above functions
int main()
{
    /*讀取資料*/
    ifstream user_file;
    user_file.open("test2.txt");
    std::vector<struct Edge> user_input; //用來放使用者輸入的edge
    int V,E; //使用者輸入的資料，當中的V&E個數

    if (user_file.is_open())
    {
        string line;
        char oneline[20],*del;

        //資料已給我們總頂點數，便不用再計算出總點點數
        getline(user_file,line);
        V=atoi(line.c_str());

        while (!user_file.eof())
        {
            //一行資料依序紀錄:頂點 頂點 權重，將資料組合成tmp_edge
            int idx=0;
            struct Edge tmp_edge;

            getline(user_file,line); //Read one line
            strcpy(oneline,line.c_str());
            del = strtok(oneline," "); //split it by whitespace

            while(del!=NULL)
            {
                //調整v的數值(-1)，顯示(printf)的時候再加回來(+1)
                if (idx==0)
                {
                    tmp_edge.src=atoi(del)-1;
                }
                else if (idx==1)
                {
                    tmp_edge.dest=atoi(del)-1;
                }
                else if (idx==2)
                {
                    tmp_edge.weight=atof(del);
                }

                //讀取下一項
                idx++;
                del = strtok(NULL," ");
            }

            //儲存tmp_edge至vector
            user_input.push_back(tmp_edge);
        }
        user_file.close();
    }
    else
    {
        cout << "File not exist!";
        exit;
    }

    //依據V&E分配Graph空間
    E=user_input.size();
    struct Graph* graph = createGraph(V, E);
    cout << "V:"<<graph->V<<" E:"<<graph->E<<endl;

    //寫入剛儲存的edge至graph
    for (std::vector<struct Edge>::iterator it = user_input.begin(); it != user_input.end(); ++it)
    {
        int i=(it-user_input.begin());
        graph->edge[i].src = (*it).src;
        graph->edge[i].dest = (*it).dest;
        graph->edge[i].weight= (*it).weight;
        printf("edge:% 2d ",i+1);
        cout << "data: " <<(*it).src+1 << " " <<(*it).dest+1 << " " <<(*it).weight <<endl;
    }

    //檢驗此graph是否含有cycle
    if (isCycle(graph))
        printf( "Graph contains cycle\n" );
    else
        printf( "Graph doesn't contain cycle\n" );

    /*Kruskal's algorithm*/
    Kruskal(graph);

    return 0;
}
