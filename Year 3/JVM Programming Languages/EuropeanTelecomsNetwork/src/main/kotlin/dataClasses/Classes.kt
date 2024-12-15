package dataClasses

/**
 * Creates a new [Node] inside the graph pointing too a [name]
 *
 * @param name The name of the node
 *
 * @author Naomi
 */
data class Node(val name: String, val index: Int)

/**
 * Creates a new [Edge] inside the graph showing the relationship between two [Node]'s via their [weight]
 *
 * @param from The first node in the connection
 * @param to The second node in the connection
 * @param weight The weight of the connection between the nodes
 *
 * @author Naomi
 */
data class Edge(val from: Node, val to: Node, val weight: Int)

/**
 * Simply stores two values that are a pair
 *
 * @param first First value
 * @param second Second value
 *
 * @author Naomi
 */
data class Pair<T, U>(val first: T, val second: U)
