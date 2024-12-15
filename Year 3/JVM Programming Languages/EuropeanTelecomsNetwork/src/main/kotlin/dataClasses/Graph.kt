package dataClasses

/**
 * This class provides methods and a structure to create a node/edge based graph
 *
 * Methods:
 *  - [createGraph][dataClasses.Graph.createGraph]
 *  - [addNode][dataClasses.Graph.addNode]
 *  - [addEdge][dataClasses.Graph.addEdge]
 *
 * Internal Imports:
 *  - [Node][dataClasses.Node]
 *  - [Edge][dataClasses.Edge]
 *  - [Pair][dataClasses.Pair]
 *
 * Assumptions:
 *  - The graph is un-directional
 *
 *  @property nodes A mutable list containing all nodes in the graph
 *  @property edges A mutable list containing all edges connecting valid nodes in the graph
 *
 *  @author Naomi
 */
class Graph
{
    val nodes = mutableListOf<Node>()
    val edges = mutableListOf<Edge>()

    /**
     * This function is called to populate the [Graph][dataClasses.Graph] after the object has been instantiated, taking a [Map] as an
     * argument, stored as [locationMap]. It will loop over the [locationMap] for each key, using the [addNode][dataClasses.Graph.addNode]
     * function to store each new key as a new [Node]. It will then repeat the for each instead this time it will find
     * the key as a [Node] in the graph, store it in a value, and using that key it will find a second [Node] in the
     * [Pair] related to the key before creating a new [Edge] using [addEdge][dataClasses.Graph.addEdge] using both nodes and the weight.
     *
     * @param locationMap
     * @return Returns the populated graph
     *
     * @author Naomi
     */
    fun createGraph(locationMap: Map<String, List<Pair<String, Int>>>) : Graph
    {
        val graph = Graph()
        var indexCounter = 0

        locationMap.keys.forEach { location ->
            graph.addNode(Node(location, indexCounter++))
        }

        locationMap.forEach { (location1, adjacentLocations) ->
            val node1 = graph.nodes.find { it.name == location1 }!!
            adjacentLocations.forEach { (location2, weight) ->
                val node2 = graph.nodes.find { it.name == location2 }!!
                graph.addEdge(Edge(node1, node2, weight))
            }
        }

        return graph
    }

    /**
     * Adds a [node] into the graphs list of [nodes]
     *
     * @param node
     *
     * @author Naomi
     */
    private fun addNode(node: Node)
    {
        nodes.add(node)
    }

    /**
     * Adds an [edge] into the graphs list of [edges]
     *
     * @param edge
     *
     * @author Naomi
     */
    private fun addEdge(edge: Edge)
    {
        edges.add(edge)
    }
}
