package dataClasses

import org.junit.jupiter.api.BeforeEach
import org.junit.jupiter.api.Test
import org.junit.jupiter.api.Assertions.*


class GraphTest
{
    private lateinit var graph: Graph

    @BeforeEach
    fun setUp()
    {
        graph = Graph()
    }

    @Test
    fun testCreateGraphEmptyMap()
    {
        val locationMap: Map<String, List<Pair<String, Int>>> = emptyMap()

        graph = graph.createGraph(locationMap)
        assertEquals(0, graph.nodes.size)
        assertEquals(0, graph.edges.size)
    }

    @Test
    fun testCreateGraphSingleLocation()
    {
        val locationMap: Map<String, List<Pair<String, Int>>> = mapOf("A" to emptyList())

        graph = graph.createGraph(locationMap)
        assertEquals(1, graph.nodes.size)
        assertEquals("A", graph.nodes[0].name)
        assertEquals(0, graph.edges.size)
    }

    @Test
    fun testCreateGraphMultipleLocations()
    {
        val locationMap: Map<String, List<Pair<String, Int>>> = mapOf(
            "A" to emptyList(),
            "B" to emptyList(),
            "C" to emptyList()
        )

        graph = graph.createGraph(locationMap)
        assertEquals(3, graph.nodes.size)
        assertTrue(graph.nodes.any { it.name == "A" })
        assertTrue(graph.nodes.any { it.name == "B" })
        assertTrue(graph.nodes.any { it.name == "C" })
        assertEquals(0, graph.edges.size)
    }

    @Test
    fun testCreateGraphWithConnections()
    {
        val locationMap: Map<String, List<Pair<String, Int>>> = mapOf(
            "A" to listOf(Pair("B", 5), Pair("C", 2)),
            "B" to listOf(Pair("A", 1), Pair("C", 3)),
            "C" to listOf(Pair("A", 4), Pair("B", 6))
        )

        graph = graph.createGraph(locationMap)

        assertEquals(3, graph.nodes.size)
        assertTrue(graph.nodes.any { it.name == "A" })
        assertTrue(graph.nodes.any { it.name == "B" })
        assertTrue(graph.nodes.any { it.name == "C" })

        assertEquals(6, graph.edges.size)

        val edgeAB = graph.edges.find { it.from.name == "A" && it.to.name == "B" }
        assertNotNull(edgeAB)
        assertEquals(5, edgeAB!!.weight)

        val edgeBC = graph.edges.find { it.from.name == "B" && it.to.name == "C" }
        assertNotNull(edgeBC)
        assertEquals(3, edgeBC!!.weight)
    }
}