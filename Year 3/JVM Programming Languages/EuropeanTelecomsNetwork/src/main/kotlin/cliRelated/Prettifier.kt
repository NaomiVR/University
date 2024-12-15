package cliRelated

import dataClasses.Edge
import dataClasses.Node

/**
 * A class to prettify the generated minimum spanning tree and print it to the command line interface in a
 * human-readable manner
 *
 * Methods:
 *  [printMST][printMST]
 *
 * Internal Imports:
 *  [Edge][dataClasses.Edge]
 *  [Node][dataClasses.Node]
 *
 * @author Naomi
 */
class Prettifier
{
    /**
     * Prints out the minimum spanning tree
     *
     * @param mst
     * @param root
     *
     * @author Naomi
     */
    fun printMST(mst: List<Edge>, root: Node)
    {
        val adjacencyList = mutableMapOf<Node, MutableList<Node>>()
        var totalWeight = 0

        mst.forEach { edge ->
            totalWeight += edge.weight
        }

        mst.forEach { edge ->
            adjacencyList.computeIfAbsent(edge.from) { mutableListOf() }.add(edge.to)
            adjacencyList.computeIfAbsent(edge.to) { mutableListOf() }.add(edge.from)
        }

        val visited = mutableSetOf<Node>()

        fun printNode(node: Node, depth: Int, prefix: String = "", isLast: Boolean = true)
        {
            visited.add(node)

            val connector = if (depth == 0) "" else if (isLast) "+-- " else "|-- "
            println("$prefix$connector${node.name}")

            val children = adjacencyList[node]?.filter { it !in visited } ?: emptyList()

            children.forEachIndexed { index, child ->
                val newPrefix = if (isLast) "$prefix    " else "$prefix|   "
                printNode(child, depth + 1, newPrefix, index == children.lastIndex)
            }
        }

        println("Total weight: $totalWeight")
        printNode(root, 0)
    }
}
