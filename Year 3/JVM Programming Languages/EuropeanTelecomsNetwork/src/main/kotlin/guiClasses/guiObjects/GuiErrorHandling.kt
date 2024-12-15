package guiClasses.guiObjects

import javax.swing.JOptionPane
import javax.swing.JFrame

/**
 * A small object that simply takes a parent frame and a message, using them to display a Message Dialog
 *
 * Methods:
 *  [showErrorDialog][showErrorDialog]
 *
 * External Imports:
 *  [JOptionPane][javax.swing.JOptionPane]
 *  [JFrame][javax.swing.JFrame]
 *
 *  @author Naomi
 */
object GuiErrorHandling
{
    /**
     * Function taking a parent JFrame and a message to be displayed on a message dialog
     *
     * @param frame
     * @param message
     *
     * @author Naomi
     */
    fun showErrorDialog(frame: JFrame, message: String)
    {
        JOptionPane.showMessageDialog(frame, message, "Error", JOptionPane.ERROR_MESSAGE)
    }
}
