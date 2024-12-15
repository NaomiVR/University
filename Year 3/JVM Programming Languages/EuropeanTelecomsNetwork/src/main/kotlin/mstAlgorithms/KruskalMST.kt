package mstAlgorithms

import dataClasses.Graph
import dataClasses.Edge

/**
 * This class provides a method of creating a Minimum Spanning Tree using Kruskal's algorithm, adjusted to use a custom [Graph]
 * instead of an adjacency matrix
 *
 * Internal Imports:
 *  - [Graph]
 *  - [Edge][dataClasses.Edge]
 */
class KruskalMST
{
    /**
     * How it works:
     *  1. Sort every edge in the graph by its given weight
     *  2. Pick the edge with the smallest weight and add it to the MST
     *      - If it creates a loop, skip that edge
     *  3. Repeat until the MST is constructed with every node connected inside it
     *
     * Reference:
     *  - https://stackabuse.com/courses/graphs-in-python-theory-and-implementation/lessons/minimum-spanning-trees-kruskals-algorithm/
     *
     *  @param graph
     *  @return A completed Minimum Spanning Tree
     */
    fun kruskalMST(graph: Graph): List<Edge>
    {
        // Sort all edges by their weight in ascending order
        val edges = graph.edges.sortedBy { it.weight }

        // Initialize data structures
        val numNodes = graph.nodes.size
        val parent = MutableList(numNodes) { it } // Initially, each node is its own parent (represents a separate set)
        val subtreeSizes = MutableList(numNodes) { 0 } // Stores the size of each set
        val mst = mutableListOf<Edge>() // List to store the edges in the MST
        var edgesIncluded = 0 // Counter for the number of edges added to the MST

        // Iterate through sorted edges
        for (edge in edges)
        {
            // Find the root nodes of the sets containing the source and destination nodes
            val u = find(parent, edge.from.index)
            val v = find(parent, edge.to.index)

            // If the source and destination nodes belong to different sets (no cycle formation), add the edge to the MST and merge the sets
            if (u != v)
            {
                edgesIncluded++
                mst.add(edge)
                connectSubtrees(parent, subtreeSizes, u, v)
            }

            // Check if the MST is complete
            if (edgesIncluded == numNodes - 1)
            {
                break
            }
        }
        return mst
    }

    // Finds the root node of a subtree containing node `i`
    private fun find(parent: MutableList<Int>, i: Int): Int
    {
        if (parent[i] != i)
        {
            parent[i] = find(parent, parent[i])
        }
        return parent[i]
    }

    // Connects subtrees containing nodes `x` and `y`
    private fun connectSubtrees(parent: MutableList<Int>, subtreeSizes: MutableList<Int>, x: Int, y: Int)
    {
        val xRoot = find(parent, x)
        val yRoot = find(parent, y)

        if (xRoot == yRoot) return

        if (subtreeSizes[xRoot] < subtreeSizes[yRoot])
        {
            parent[xRoot] = yRoot
        } else if (subtreeSizes[xRoot] > subtreeSizes[yRoot])
        {
            parent[yRoot] = xRoot
        } else
        {
            parent[yRoot] = xRoot
            subtreeSizes[xRoot]++
        }
    }
}
