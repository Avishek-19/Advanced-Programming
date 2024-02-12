/*
student Id:220219
Name: Avishek Paul
Project : find the triangular path in a graph
*/
#include <stdio.h>

struct Node
{
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
};

// Function to add a node to the array of nodes
int addNode(struct Node *p, int nid, int count)
{
    int i = 0, ncount = count;
    // Check if the node already exists
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid)
        {
            break;
        }
    }
    // If the node doesn't exist, add it to the array
    if (i == count)
    {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}

// Function to add an adjacent node with a cost to a given node
void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int count)
{
    int i = 0, index;
    // Find the node to which we want to add an adjacent node
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid1)
        {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c + 1;

            break;
        }
    }
}

// Function to find triangles in the graph
void findTriangles(struct Node *p, int count)
{
    // Iterate over all possible combinations of three nodes
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            for (int k = j + 1; k < count; k++)
            {
                int node1 = p[i].nodeid;
                int node2 = p[j].nodeid;
                int node3 = p[k].nodeid;
                int edge1 = 0, edge2 = 0, edge3 = 0;
                // Check if each pair of nodes forms an edge
                for (int x = 0; x < p[i].adjcount; x++)
                {
                    if (p[i].adjs[x] == node2 || p[i].adjs[x] == node3)
                    {
                        edge1++;
                    }
                }
                for(int y = 0; y < p[j].adjcount; y++)
                {
                    if (p[j].adjs[y] == node1 || p[j].adjs[y] == node3)
                    {
                        edge2++;
                    }
                }
                for(int z = 0; z < p[k].adjcount; z++)
                {
                    if (p[k].adjs[z] == node1 || p[k].adjs[z] == node2)
                    {
                        edge3++;
                    }
                }
                // If all edges are present, we have found a triangle
                if (edge1 == 2 && edge2 == 2 && edge3 == 2)
                {
                    printf("Triangle found: %d %d %d \n", node1, node2, node3);
                }
            }
        }
    }
}


int main()
{
    struct Node nodes[50];
    int nodecount = 0;
    int n1 = 0, n2 = 0, c = 0;

    // Input loop to read nodes and edges until the user inputs -9
    while (1)
    {
        printf("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c == -9)
        {
            break;
        }
        // Add nodes and edges
        nodecount = addNode(&nodes[0], n1, nodecount);
        nodecount = addNode(&nodes[0], n2, nodecount);

        addAdjacent(&nodes[0], n1, n2, c, nodecount);
        addAdjacent(&nodes[0], n2, n1, c, nodecount);
    }

    // Find triangles in the graph
    findTriangles(nodes, nodecount);

    return 0;
}

