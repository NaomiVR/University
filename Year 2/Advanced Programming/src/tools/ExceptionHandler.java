package tools;

import java.io.IOException;
import java.net.UnknownHostException;
import java.util.logging.*;

public class ExceptionHandler {
    Logger logger = LogManager.getLogManager().getLogger(Logger.GLOBAL_LOGGER_NAME);

    public void ioHandler (IOException error) {
        logger.log(Level.SEVERE, String.format("IOException: %s", error.getMessage()));
    }

    public void unknownHandler (UnknownHostException error) {
        logger.log(Level.SEVERE, String.format("Unknown host exception: %s", error.getMessage()));
    }

    public void infoHandler (String message) {
        logger.log(Level.INFO, message);
    }
}
