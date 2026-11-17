
#include "algorithms.h"

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;


// Helper function: Find vertex index using ID
int getVertexIndex(const Graph& graph, string id)
{
    const vector<Vertex>& vertices = graph.getVertices();

    for (int i = 0; i < (int)vertices.size(); i++)
    {
        if (vertices[i].id == id)
        {
            return i;
        }
    }

    return -1;
}


// ==========================================
// 1. BREADTH FIRST SEARCH (BFS)
// Uses Queue
// ==========================================

void BFS(const Graph& graph, string startID)
{
    const vector<Vertex>& vertices = graph.getVertices();
    const vector<vector<int> >& adj = graph.getAdjacencyList();

    int start = getVertexIndex(graph, startID);

    if (start == -1)
    {
        cout << "\nEntity not found!\n";
        return;
    }

    vector<bool> visited(vertices.size(), false);

    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "\n===== BFS TRAVERSAL =====\n";

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        cout << vertices[current].name
             << " (" << vertices[current].id << ")";

        cout << " -> ";

        for (int i = 0; i < (int)adj[current].size(); i++)
        {
            int neighbour = adj[current][i];

            if (!visited[neighbour])
            {
                visited[neighbour] = true;
                q.push(neighbour);
            }
        }
    }

    cout << "END\n";
}


// ==========================================
// 2. DEPTH FIRST SEARCH (DFS)
// Uses Stack
// ==========================================

void DFS(const Graph& graph, string startID)
{
    const vector<Vertex>& vertices = graph.getVertices();
    const vector<vector<int> >& adj = graph.getAdjacencyList();

    int start = getVertexIndex(graph, startID);

    if (start == -1)
    {
        cout << "\nEntity not found!\n";
        return;
    }

    vector<bool> visited(vertices.size(), false);

    stack<int> st;

    st.push(start);

    cout << "\n===== DFS TRAVERSAL =====\n";

    while (!st.empty())
    {
        int current = st.top();
        st.pop();

        if (visited[current])
        {
            continue;
        }

        visited[current] = true;

        cout << vertices[current].name
             << " (" << vertices[current].id << ")";

        cout << " -> ";

        for (int i = (int)adj[current].size() - 1; i >= 0; i--)
        {
            int neighbour = adj[current][i];

            if (!visited[neighbour])
            {
                st.push(neighbour);
            }
        }
    }

    cout << "END\n";
}


// ==========================================
// 3. SHORTEST CONNECTION PATH
// Uses BFS and Parent Array
// ==========================================

void findPath(const Graph& graph,
              string sourceID,
              string destinationID)
{
    const vector<Vertex>& vertices = graph.getVertices();
    const vector<vector<int> >& adj = graph.getAdjacencyList();

    int source = getVertexIndex(graph, sourceID);
    int destination = getVertexIndex(graph, destinationID);

    if (source == -1 || destination == -1)
    {
        cout << "\nSource or destination not found!\n";
        return;
    }

    vector<bool> visited(vertices.size(), false);

    vector<int> parent(vertices.size(), -1);

    queue<int> q;

    visited[source] = true;
    q.push(source);

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        if (current == destination)
        {
            break;
        }

        for (int i = 0; i < (int)adj[current].size(); i++)
        {
            int neighbour = adj[current][i];

            if (!visited[neighbour])
            {
                visited[neighbour] = true;

                parent[neighbour] = current;

                q.push(neighbour);
            }
        }
    }

    if (!visited[destination])
    {
        cout << "\nNo connection path exists!\n";
        return;
    }

    vector<int> path;

    int current = destination;

    while (current != -1)
    {
        path.push_back(current);
        current = parent[current];
    }

    reverse(path.begin(), path.end());

    cout << "\n===== SHORTEST CONNECTION PATH =====\n";

    for (int i = 0; i < (int)path.size(); i++)
    {
        int index = path[i];

        cout << vertices[index].name
             << " (" << vertices[index].id << ")";

        if (i != (int)path.size() - 1)
        {
            cout << " -> ";
        }
    }

    cout << "\nTotal connections: "
         << path.size() - 1 << endl;
}


// ==========================================
// 4. FIND COMMON CONNECTIONS
// ==========================================

void findCommonConnections(const Graph& graph,
                           string firstID,
                           string secondID)
{
    const vector<Vertex>& vertices = graph.getVertices();
    const vector<vector<int> >& adj = graph.getAdjacencyList();

    int first = getVertexIndex(graph, firstID);
    int second = getVertexIndex(graph, secondID);

    if (first == -1 || second == -1)
    {
        cout << "\nEntity not found!\n";
        return;
    }

    cout << "\n===== COMMON CONNECTIONS =====\n";

    bool found = false;

    for (int i = 0; i < (int)adj[first].size(); i++)
    {
        int neighbour = adj[first][i];

        for (int j = 0; j < (int)adj[second].size(); j++)
        {
            if (neighbour == adj[second][j])
            {
                cout << vertices[neighbour].name
                     << " (" << vertices[neighbour].id << ")\n";

                found = true;
                break;
            }
        }
    }

    if (!found)
    {
        cout << "No common connections found.\n";
    }
}


// ==========================================
// 5. CONNECTION DEPTH ANALYSIS
// Uses BFS and Queue
// ==========================================

void depthAnalysis(const Graph& graph,
                   string startID,
                   int maxDepth)
{
    const vector<Vertex>& vertices = graph.getVertices();
    const vector<vector<int> >& adj = graph.getAdjacencyList();

    int start = getVertexIndex(graph, startID);

    if (start == -1)
    {
        cout << "\nEntity not found!\n";
        return;
    }

    if (maxDepth < 0)
    {
        cout << "\nDepth cannot be negative!\n";
        return;
    }

    vector<int> depth(vertices.size(), -1);

    queue<int> q;

    depth[start] = 0;
    q.push(start);

    cout << "\n===== CONNECTION DEPTH ANALYSIS =====\n";
cout << "Maximum depth: " << maxDepth << endl;


    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        cout << "Level " << depth[current] << ": "
             << vertices[current].name
             << " (" << vertices[current].id << ")\n";

        if (depth[current] == maxDepth)
        {
            continue;
        }

        for (int i = 0; i < (int)adj[current].size(); i++)
        {
            int neighbour = adj[current][i];

            if (depth[neighbour] == -1)
            {
                depth[neighbour] = depth[current] + 1;
                q.push(neighbour);
            }
        }
    }
}

