package tests;

import tools.ExceptionHandler;

import java.io.IOException;
import java.net.UnknownHostException;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class ExceptionHandlerTest {

    @Test
    void testIOExceptionHandling() {
        ExceptionHandler handler = new ExceptionHandler();
        IOException exception = new IOException("Test IOException");
        assertDoesNotThrow(() -> handler.ioHandler(exception));
    }

    @Test
    void testUnknownHostExceptionHandling() {
        ExceptionHandler handler = new ExceptionHandler();
        UnknownHostException exception = new UnknownHostException("Test UnknownHostException");
        assertDoesNotThrow(() -> handler.unknownHandler(exception));
    }

    @Test
    void testInfoHandler() {
        ExceptionHandler handler = new ExceptionHandler();
        assertDoesNotThrow(() -> handler.infoHandler("Test info message"));
    }
}
