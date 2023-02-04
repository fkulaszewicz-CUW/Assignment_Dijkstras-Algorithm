#include <iostream>
using namespace std;

// Structure to keep track of if a node has been visited and
// of the current shortest distance of each node
struct nodeList
{
    bool isVisited;
    int currentNodeDistance;
};

// Print the node path
void printPath (int path[], int i) {
    if (path[i] > 4 || path[i] < 0)
    {
        return;
    }
    printPath(path, path[i]);
    char toLetter = 65 + i;
    cout << toLetter << " ";
}

int main()
{
    // Directed graph
    int directedGraph[5][5] = {
        {0, 10, 0, 0, 3},
        {0, 0, 2, 0, 4},
        {0, 0, 0, 9, 0},
        {0, 0, 7, 0, 0},
        {0, 1, 8, 2, 0}};

    int numOfNodes = 5;

    // For asking the user the start and end node
    char startNode;
    char endNode;
    cout << "Please pick a starting node (A - E): ";
    cin >> startNode;
    cout << "Please pick an ending node (A - E): ";
    cin >> endNode;

    int startingNode = startNode - 65;
    int endingNode = endNode - 65;

    // Initialize all of the nodes
    nodeList nodes[numOfNodes];
    int path[numOfNodes];

    for (int i = 0; i < numOfNodes; i++)
    {
        nodes[i].isVisited = false;
        nodes[i].currentNodeDistance = INT_MAX;
        path[0] = -1;
    }
    nodes[startingNode].currentNodeDistance = 0;

    // Dijkstras Algorithm
    for (int i = 0; i < numOfNodes - 1; i++)
    {
        int currentMinimumDistance = INT_MAX;
        int nodeID;
        for (int i = 0; i < numOfNodes; i++)
        {
            if (nodes[i].isVisited == false && nodes[i].currentNodeDistance <= currentMinimumDistance)
            {
                currentMinimumDistance = nodes[i].currentNodeDistance;
                nodeID = i;
            }
        }
        nodes[nodeID].isVisited = true;
        for (int i = 0; i < numOfNodes; i++)
        {
            int tempDistance = nodes[nodeID].currentNodeDistance + directedGraph[nodeID][i];
            if (directedGraph[nodeID][i] && nodes[i].isVisited == false)
            {
                if (tempDistance < nodes[i].currentNodeDistance && nodes[nodeID].currentNodeDistance != INT_MAX)
                {
                    nodes[i].currentNodeDistance = tempDistance;
                    path[i] = nodeID;
                }
            }
        }
    }

    // Print out the results
    for (int i = 0; i < numOfNodes; i++)
    {
        char toLetter = 65 + i;
        if (endingNode == i)
        {
            if (nodes[i].currentNodeDistance == INT_MAX)
            {
                cout << "Node cannot be reached!" << endl;
            }
            else
            {
                cout << "Total cost from " << startNode << " to " << endNode << ": " << nodes[i].currentNodeDistance << endl;
                cout << "Path taken: " << startNode << " ";
                printPath(path, i);
                cout << endl;
            }
        }
    }
}