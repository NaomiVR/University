package guiClasses

import java.awt.event.ActionListener
import java.awt.event.ActionEvent
import java.awt.event.WindowAdapter
import java.awt.event.WindowEvent

/**
 * This is a proxy class to mass assign listeners to the buttons and actions used in the main Gui
 *
 * Methods:
 *  [actionPerformed][actionPerformed]
 *  [windowClosing][windowClosing]
 *
 * External Imports:
 *  [ActionListener][java.awt.event.ActionListener]
 *  [ActionEvent][java.awt.event.ActionEvent]
 *  [WindowAdapter][java.awt.event.WindowAdapter]
 *  [WindowAdapter][java.awt.event.WindowEvent]
 *
 *  @author Naomi
 */
class GuiListeners(private val gui: Gui): ActionListener, WindowAdapter()
{
    override fun actionPerformed(e: ActionEvent)
    {
        when (e.source)
        {
            gui.chooseFileButton -> gui.getPath()
            gui.generateMSTButton -> gui.genMST()
        }
    }


    override fun windowClosing(e: WindowEvent?)
    {
        gui.mainFrame.dispose()
    }
}
