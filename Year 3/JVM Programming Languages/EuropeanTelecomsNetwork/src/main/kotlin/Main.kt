import cliRelated.Prettifier
import dataClasses.FileReader
import dataClasses.Graph
import guiClasses.Gui
import mstAlgorithms.KruskalMST

/**
 * The main function that is called when run from the command line interface (CLI)
 * 
 * Arguments:
 *  - [args]
 * 
 * Usage:
 *  - kotlin MainKt.class <run_method> <file_path>
 * 
 * @param args The arguments passed by the command line interface (CLI)
 *
 * @author Naomi
 */
fun main(args: Array<String>)
{
    if (args.isEmpty())
    {
        println("Usage: kotlin MainKt.class <run_method> <file_path>")
        println("<run_method> refers to either GUI or CLI")
        return
    }

    if (args[0] == "CLI")
    {
        val filePath = args[1]

        val fileReader = FileReader()
        val graph = Graph()
        val prettier = Prettifier()

        val nestedList = fileReader.read(filePath)
        val locationMap = fileReader.createMap(nestedList)
        val populatedGraph = graph.createGraph(locationMap)

        val kMST = KruskalMST().kruskalMST(populatedGraph)

        prettier.printMST(kMST, populatedGraph.nodes[0])
    }
    else if (args[0] == "GUI")
    {
        Gui()
    }
}
