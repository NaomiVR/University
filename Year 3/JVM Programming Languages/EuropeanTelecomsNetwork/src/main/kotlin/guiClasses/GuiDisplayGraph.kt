package guiClasses

import com.mxgraph.layout.mxOrganicLayout
import com.mxgraph.swing.mxGraphComponent
import com.mxgraph.model.mxCell
import com.mxgraph.util.mxConstants
import com.mxgraph.view.mxGraph
import com.mxgraph.view.mxStylesheet

import dataClasses.Edge
import dataClasses.Node

/**
 * This class provides the overlay GUI for displaying a completed minimum spanning tree
 *
 * Methods:
 *  [visualise][guiClasses.GuiDisplayGraph.visualise]
 *  [style][guiClasses.GuiDisplayGraph.style]
 *
 * Internal Imports:
 *  [Edge][dataClasses.Edge]
 *  [Node][dataClasses.Node]
 *
 * External Imports:
 *  [mxOrganicLayout][com.mxgraph.layout.mxOrganicLayout]
 *  [mxGraphComponent][com.mxgraph.swing.mxGraphComponent]
 *  [mxCell][com.mxgraph.model.mxCell]
 *  [mxConstants][com.mxgraph.util.mxConstants]
 *  [mxGraph][com.mxgraph.view.mxGraph]
 *  [mxStylesheet][com.mxgraph.view.mxStylesheet]
 *
 * @property graph
 * @property graphComponent
 *
 * @author Naomi
 */
class GuiDisplayGraph
{
    private val graph = mxGraph()
    val graphComponent = mxGraphComponent(graph)


    init
    {
        style()
    }

    /**
     * Processes the minimum spanning tree to be displayed using jgraphx
     *
     * @param mst
     *
     * @author Naomi
     */
    fun visualise(mst: List<Edge>)
    {
        val parent = graph.defaultParent
        graph.model.beginUpdate()

        val vertexMap = mutableMapOf<Node, mxCell>()
        for (node in mst.flatMap { listOf(it.from, it.to) }.distinct())
        {
            val vertex = graph.insertVertex(parent, null, node.name, 100.0, 100.0, 80.0, 30.0)
            vertexMap[node] = vertex as mxCell
        }

        for (edge in mst)
        {
            val source = vertexMap[edge.from]
            val target = vertexMap[edge.to]
            graph.insertEdge(parent, null, edge.weight.toString(), source, target)
        }

        val layout = mxOrganicLayout(graph)
        layout.execute(parent)

        graph.model.endUpdate()
    }

    /**
     * Simply sets the style of jgraphx object, specifically the Node style
     *
     * @author Naomi
     */
    private fun style()
    {
        val stylesheet = mxStylesheet()

        stylesheet.defaultVertexStyle = mapOf(
            mxConstants.STYLE_SHAPE to mxConstants.SHAPE_RECTANGLE,
            mxConstants.STYLE_FILLCOLOR to "#F0F0F0",
            mxConstants.STYLE_STROKECOLOR to "#B0B0B0",
            mxConstants.STYLE_FONTCOLOR to "#303030",
            mxConstants.STYLE_FONTSIZE to "12",
            mxConstants.STYLE_ALIGN to mxConstants.ALIGN_CENTER,
            mxConstants.STYLE_VERTICAL_ALIGN to mxConstants.ALIGN_MIDDLE
        )

        graph.stylesheet = stylesheet
        graph.gridSize = 150
        graph.isAutoSizeCells = true
        graph.isCellsEditable = false
        graph.isCellsMovable = false
        graph.isLabelMovable(false)
    }
}