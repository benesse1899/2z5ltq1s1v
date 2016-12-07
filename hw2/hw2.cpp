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
    //���I ���I �v��
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
        //�p�Gweight=-1�A�N�����ȮɵL�k�ϥ�
        if(graph->edge[e].weight==-1) continue;

        int x = find(subsets, graph->edge[e].src);
        int y = find(subsets, graph->edge[e].dest);

        if (x == y)
            return 1;

        Union(subsets, x, y);
    }

    //��X���X
    printf("\n----Set----\n");
    printf(" V parents\n");
    for (int v = 0; v < V; ++v)
    {
        printf("% 2d % 7d\n",v+1,subsets[v].parent+1);
    }

    return 0;
}

//�Ƨ�edge
bool edge_sort (struct Edge i,struct Edge j)
{
    return (i.weight<j.weight);
}



void Kruskal(struct Graph * graph)
{
    cout << "\n***********Kruskal algorithm*************" <<endl;

    //�̷�edge�v���Ƨ�edge
    std::sort (graph->edge,graph->edge+graph->E, edge_sort);

    //�L�X�Ƨǫ᪺edge
    printf("\n----After sorting edge----\n src dest weight\n");
    for (int i=0; i<graph->E; ++i)
    {
        printf("% 4d % 4d % 3.2f\n",graph->edge[i].src,graph->edge[i].dest,graph->edge[i].weight);
    }

    /*�гy�s��graph�A�qedge�v�� �p->�j�A�v�@��edge��Jnew_graph(weight:-1 => weight: orignal )�A�Y��cycle�h���L��edge*/
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
        //��J�s��
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

    /*MST�w�ͦ�*/
    printf("\n----MST----\n");

    //�C�XMST���ҧt����
    printf("   v    v weight\n");
    for (int e = 0; e < new_graph->E; ++e)
    {
        //����L�k�ϥ�
        if (new_graph->edge[e].weight==-1) continue;

        //�C�X����]�t�����I�M�v��
        printf("% 4d % 4d % 3.2f\n",new_graph->edge[e].src+1,new_graph->edge[e].dest+1,new_graph->edge[e].weight);
    }

}

// Driver program to test above functions
int main()
{
    /*Ū�����*/
    ifstream user_file;
    user_file.open("test2.txt");
    std::vector<struct Edge> user_input; //�Ψө�ϥΪ̿�J��edge
    int V,E; //�ϥΪ̿�J����ơA����V&E�Ӽ�

    if (user_file.is_open())
    {
        string line;
        char oneline[20],*del;

        //��Ƥw���ڭ��`���I�ơA�K���ΦA�p��X�`�I�I��
        getline(user_file,line);
        V=atoi(line.c_str());

        while (!user_file.eof())
        {
            //�@���ƨ̧Ǭ���:���I ���I �v���A�N��ƲզX��tmp_edge
            int idx=0;
            struct Edge tmp_edge;

            getline(user_file,line); //Read one line
            strcpy(oneline,line.c_str());
            del = strtok(oneline," "); //split it by whitespace

            while(del!=NULL)
            {
                //�վ�v���ƭ�(-1)�A���(printf)���ɭԦA�[�^��(+1)
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

                //Ū���U�@��
                idx++;
                del = strtok(NULL," ");
            }

            //�x�stmp_edge��vector
            user_input.push_back(tmp_edge);
        }
        user_file.close();
    }
    else
    {
        cout << "File not exist!";
        exit;
    }

    //�̾�V&E���tGraph�Ŷ�
    E=user_input.size();
    struct Graph* graph = createGraph(V, E);
    cout << "V:"<<graph->V<<" E:"<<graph->E<<endl;

    //�g�J���x�s��edge��graph
    for (std::vector<struct Edge>::iterator it = user_input.begin(); it != user_input.end(); ++it)
    {
        int i=(it-user_input.begin());
        graph->edge[i].src = (*it).src;
        graph->edge[i].dest = (*it).dest;
        graph->edge[i].weight= (*it).weight;
        printf("edge:% 2d ",i+1);
        cout << "data: " <<(*it).src+1 << " " <<(*it).dest+1 << " " <<(*it).weight <<endl;
    }

    //���禹graph�O�_�t��cycle
    if (isCycle(graph))
        printf( "Graph contains cycle\n" );
    else
        printf( "Graph doesn't contain cycle\n" );

    /*Kruskal's algorithm*/
    Kruskal(graph);

    return 0;
}
