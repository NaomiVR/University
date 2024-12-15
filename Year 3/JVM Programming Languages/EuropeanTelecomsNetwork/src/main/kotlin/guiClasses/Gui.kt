package guiClasses

import java.awt.event.KeyEvent
import java.awt.*
import javax.swing.*

import guiClasses.guiObjects.GuiErrorHandling.showErrorDialog
import guiClasses.guiObjects.GuiUtils.validateFilePath
import guiClasses.guiObjects.GuiUtils.parseData
import guiClasses.guiObjects.GuiUtils.generateMST
import guiClasses.guiObjects.GuiUtils.newFrame

/**
 * This class provides a full method creating a graphical user interface using Swing
 *
 * Methods:
 *  [setLayout][guiClasses.Gui.setLayout]
 *  [getPath][guiClasses.Gui.getPath]
 *  [genMST][guiClasses.Gui.genMST]
 *
 * Internal Imports:
 *  [showErrorDialog][guiClasses.guiObjects.GuiErrorHandling.showErrorDialog]
 *  [validateFilePath][guiClasses.guiObjects.GuiUtils.validateFilePath]
 *  [parseData][guiClasses.guiObjects.GuiUtils.parseData]
 *  [generateMST][guiClasses.guiObjects.GuiUtils.generateMST]
 *  [newFrame][guiClasses.guiObjects.GuiUtils.newFrame]
 *
 *  @property filePath
 *  @property mainFrame
 *  @property mainPanel
 *  @property fileChooser
 *  @property chooseFileButton
 *  @property generateMSTButton
 *  @property algorithmGroup
 *  @property primsAlgRButton
 *  @property kruskalsAlgRButton
 *  @property mstLabel
 *  @property mstSizeLabel
 *  @property mstVisualiser
 *  @property mstComponent
 *
 *  @author Naomi
 */
class Gui
{
    private lateinit var filePath: String

    private val mainPanel = JPanel(GridBagLayout())
    private val fileChooser = JFileChooser()
    private val mstLabel = JLabel("Size of the MST:")
    private val mstSizeLabel = JLabel("N/A")
    private val algorithmGroup = ButtonGroup()

    val mainFrame = JFrame("European Telecoms Network")
    val primsAlgRButton = JRadioButton("Prim's - DISABLED")
    val kruskalsAlgRButton = JRadioButton("Kruskal's")
    val chooseFileButton = JButton("Choose File")
    val generateMSTButton = JButton("Generate MST")

    private val mstVisualiser = GuiDisplayGraph()
    private val mstComponent = mstVisualiser.graphComponent

    /**
     * Initialise the GUI on creation of new object instance by setting default values for the mainFrame including
     * size. Alongside applying listeners to necessary applications and setting the layout of the mainPanel attached
     * to the mainFrame.
     *
     * @author Naomi
     */
    init
    {
        mainFrame.defaultCloseOperation = WindowConstants.EXIT_ON_CLOSE
        mainFrame.isVisible = true
        mainFrame.isResizable = false
        mainFrame.setSize(300, 150)

        mainPanel.registerKeyboardAction(
            { mainFrame.dispose() },
            KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0),
            JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT
        )

        val guiListeners = GuiListeners(this)
        mainFrame.addWindowListener(guiListeners)
        chooseFileButton.addActionListener(guiListeners)
        generateMSTButton.addActionListener(guiListeners)

        setLayout()

        mainFrame.contentPane.add(mainPanel, BorderLayout.NORTH)
    }

    /**
     * Sets the layout of the GUI application by adding each component object to the [mainPanel] in a specific location.
     *
     * @author Naomi
     */
    private fun setLayout()
    {
        val constraints = GridBagConstraints()

        algorithmGroup.add(primsAlgRButton)
        algorithmGroup.add(kruskalsAlgRButton)

        constraints.gridx = 0
        constraints.gridy = 0
        constraints.anchor = GridBagConstraints.NORTHWEST
        mainPanel.add(chooseFileButton, constraints)

        constraints.gridx = 1
        constraints.gridy = 0
        mainPanel.add(generateMSTButton, constraints)

        constraints.gridx = 0
        constraints.gridy = 1
        mainPanel.add(primsAlgRButton, constraints)

        constraints.gridx = 0
        constraints.gridy = 2
        mainPanel.add(kruskalsAlgRButton, constraints)

        constraints.gridx = 0
        constraints.gridy = 3
        mainPanel.add(mstLabel, constraints)

        constraints.gridx = 1
        constraints.gridy = 3
        mainPanel.add(mstSizeLabel, constraints)
    }

    /**
     * This function gets the absolute path to the file the user in question chooses inside the [fileChooser] object.
     *
     * @return Absolute system path to file if its valid
     *
     * @author Naomi
     */
    fun getPath()
    {
        val result: Int = fileChooser.showOpenDialog(null)
        if (result == JFileChooser.APPROVE_OPTION)
        {
            val selectedFile = fileChooser.selectedFile
            filePath = selectedFile.absolutePath
        }

        if (validateFilePath(filePath)) { return } else { showErrorDialog(mainFrame, "Invalid File Path") }
    }

    /**
     * This function uses utility functions to handle the data inside the chosen valid file to create a valid MST,
     * given that each step also produces a valid data structure, using [parseData] and [generateMST].
     *
     * @author Naomi
     */
    fun genMST()
    {
        val graph = parseData(filePath, mainFrame)
        if (graph != null)
        {
            val mst = generateMST(graph, this, mainFrame)
            if (mst != null)
            {
                val displayFrame = newFrame("MST Display", mstComponent)
                if (displayFrame != null)
                {
                    displayFrame.isVisible = true
                }
                mstVisualiser.visualise(mst)
            }
            else
            {
                showErrorDialog(mainFrame, "Invalid MST")
            }
        }
        else
        {
            showErrorDialog(mainFrame, "Invalid Graph")
        }
    }
}
