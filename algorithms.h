

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "graph.h"
#include <string>

using namespace std;

void BFS(const Graph& graph, string startID);

void DFS(const Graph& graph, string startID);

void findPath(const Graph& graph,
              string sourceID,
              string destinationID);

void findCommonConnections(const Graph& graph,
                           string firstID,
                           string secondID);

void depthAnalysis(const Graph& graph,
                   string startID,
                   int maxDepth);

#endif
