package guiClasses.guiObjects

import java.awt.BorderLayout
import java.awt.Component
import java.awt.Dimension
import javax.swing.JFrame
import java.io.File
import java.io.IOException

import guiClasses.guiObjects.GuiErrorHandling.showErrorDialog
import dataClasses.Edge
import dataClasses.FileReader
import dataClasses.Graph
import guiClasses.Gui
import mstAlgorithms.KruskalMST
//import mstAlgorithms.PrimMST

/**
 * A large object containing utility functions to avoid clogging up the main Gui class.
 *
 * Methods:
 *  [newFrame][newFrame]
 *  [validateFilePath][validateFilePath]
 *  [parseData][parseData]
 *  [generateMST][generateMST]
 *
 * Internal Imports:
 *  [showErrorDialog][guiClasses.guiObjects.GuiErrorHandling.showErrorDialog]
 *  [Edge][dataClasses.Edge]
 *  [FileReader][dataClasses.FileReader]
 *  [Graph][dataClasses.Graph]
 *  [Gui][guiClasses.Gui]
 *  [KruskalMST][mstAlgorithms.KruskalMST]
 *
 * External Imports:
 *  [BorderLayout][java.awt.BorderLayout]
 *  [Component][java.awt.Component]
 *  [Dimension][java.awt.Dimension]
 *  [JFrame][javax.swing.JFrame]
 *  [File][java.io.File]
 *  [IOException][java.io.IOException]
 *
 *  @author Naomi
 */
object GuiUtils
{
    /**
     * Global utility function to create a new frame window containing a single object
     *
     * @param frameName
     * @param component
     *
     * @return The new frame if it is successfully created
     *
     * @author Naomi
     */
    fun newFrame(frameName: String? = null, component: Component? = null): JFrame?
    {
        if (frameName != null && component != null)
        {
            val frame = JFrame(frameName)
            frame.defaultCloseOperation = JFrame.DISPOSE_ON_CLOSE
            frame.layout = BorderLayout()

            frame.contentPane.add(component, BorderLayout.CENTER)
            frame.size = Dimension(2200, 350)

            return frame
        }

        return null
    }

    /**
     * Validates the chosen filepath to ensure the file exists and is accessible
     *
     * @param filePath
     *
     * @return true or false if file is valid
     *
     * @author Naomi
     */
    fun validateFilePath(filePath: String): Boolean
    {
        val file = File(filePath)
        return file.exists() && file.isFile
    }

    /**
     * Reads the data from a validated file and parses its data into a state that can be worked with by the rest of the
     * program
     *
     * @param filePath
     * @param frame
     *
     * @return The graph structure if it exists
     *
     * @author Naomi
     */
    fun parseData(filePath: String, frame: JFrame): Graph?
    {
        try
        {
            val fileReader = FileReader()
            val graph = Graph()

            val nestedList = fileReader.read(filePath)
            val locationMap = fileReader.createMap(nestedList)
            val populatedGraph = graph.createGraph(locationMap)

            return populatedGraph
        }
        catch (e: IOException)
        {
            showErrorDialog(frame, "Error reading file: ${e.message}")
            return null
        }
    }

    /**
     * Generates a minimum spanning tree from the parsed data structure and chosen algorithm
     *
     * @param graph
     * @param gui
     * @param frame
     *
     * @return Minimum spanning tree if it exists
     *
     * @author Naomi
     */
    fun generateMST(graph: Graph, gui: Gui, frame: JFrame): List<Edge>?
    {
        lateinit var mst: List<Edge>

        try
        {
            if (gui.primsAlgRButton.isSelected)
            {
                // Disabled due to bad algorithm functionality
                /*val prims = PrimMST()
                mst = prims.primMST(graph)*/
            }
            else if (gui.kruskalsAlgRButton.isSelected)
            {
                val kruskals = KruskalMST()
                mst = kruskals.kruskalMST(graph)
            }

            return mst
        }
        catch (e: Exception)
        {
            showErrorDialog(frame, "Error generating MST: ${e.message}")
            return null
        }
    }
}
