package mstAlgorithms

import dataClasses.Graph
import dataClasses.Edge

/**
 * This class provides a method of creating a Minimum Spanning Tree using Prim's algorithm, adjusted to use a custom [Graph]
 * instead of an adjacency matrix
 *
 * Internal Imports:
 *  - [Graph]
 *  - [Edge][dataClasses.Edge]
 */
class PrimMST
{
    private lateinit var selected: MutableList<Boolean>
    private lateinit var parent: MutableList<Int>
    private lateinit var key: MutableList<Int>

    /**
     * How it works:
     *  1. Start at an arbitrary node
     *  2. From the node choose the path/edge with the minimum weight
     *  3. This leads to a new node, set that as current node
     *  4. Once tree is updated, choose the next minimum weight connected to the WHOLE tree
     *      - If it creates a cycle, skip it
     *  5. Repeat step 3 and 4 until finished
     *
     * Reference:
     *  - https://stackabuse.com/courses/graphs-in-python-theory-and-implementation/lessons/minimum-spanning-trees-prims-algorithm/
     *
     *  @param graph
     *  @return A completed Minimum Spanning Tree
     */
    fun primMST(graph: Graph): List<Edge>
    {
        val numNodes = graph.nodes.size
        val (selected, parent, key) = initializeMST(numNodes)

        for (i in 0..<numNodes - 1) {
            val minIndex = minKeyIndex(selected, key)
            selected[minIndex] = true
            updateKey(graph, selected, parent, key, minIndex)
        }

        return constructMST(graph, parent)
    }

    /**
     * Handles the initialization of the data structures
     *
     * @param numNodes
     * @return A triple containing initialized data structures for population by main algorithm
     */
    private fun initializeMST(numNodes: Int): Triple<MutableList<Boolean>, MutableList<Int>, MutableList<Int>>
    {
        selected = MutableList(numNodes) { false }  // Keeps track of visited nodes
        parent = MutableList(numNodes) { 0 }           // Stores parent of each node in MST
        key = MutableList(numNodes) { Int.MAX_VALUE }   // Stores weight to include a node in MST
        key[0] = 0  // Set weight of first node to 0 (included in MST)
        return Triple(selected, parent, key)
    }

    /**
     * This function find the next unvisited node with the smallest weight
     *
     * @param selected
     * @param key
     * @return The next smallest node index
     */
    private fun minKeyIndex(selected: List<Boolean>, key: List<Int>): Int
    {
        var minKey = Int.MAX_VALUE
        var minIndex = 0
        for (v in key.indices)
        {
            if (!selected[v] && key[v] < minKey)
            {
                minKey = key[v]
                minIndex = v
            }
        }
        return minIndex
    }

    /**
     * This function updates the key values for the neighbours of the included node
     *
     * @param graph
     * @param selected
     * @param parent
     * @param key
     * @param minIndex
     */
    private fun updateKey(graph: Graph, selected: MutableList<Boolean>, parent: MutableList<Int>, key: MutableList<Int>, minIndex: Int)
    {
        for (edge in graph.edges)
        {
            val to = edge.to.index  // Get the index of the neighbor node
            if (graph.edges.any { it.from.index == minIndex && it.to.index == to }
                && !selected[to] && edge.weight < key[to])
            {
                parent[to] = minIndex  // Update parent information for neighbor (used for reconstructing MST)
                key[to] = edge.weight  // Update weight of neighbor to the lower edge weight
            }
        }
    }

    /**
     * This function constructs the MST based on the parent node information
     *
     * @param graph
     * @param parent
     * @return A completed Minimum Spanning Tree
     */
    private fun constructMST(graph: Graph, parent: List<Int>): List<Edge>
    {
        val mst = mutableListOf<Edge>()
        for (i in 1..<graph.nodes.size)
        {
            val from = parent[i]
            mst.add(Edge(graph.nodes[from], graph.nodes[i], key[i])) // Add edges based on parent-child relationships
        }
        return mst
    }
}