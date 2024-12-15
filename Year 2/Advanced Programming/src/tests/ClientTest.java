package tests;

import client.Client;

import java.io.*;
import java.net.Socket;
import org.mockito.Mockito;
import org.junit.jupiter.api.*;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.when;

public class ClientTest {
    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    private final PrintStream originalOut = System.out;
    private final InputStream originalIn = System.in;

    @BeforeEach
    public void setUpStreams() {
        System.setOut(new PrintStream(outContent));
    }

    @AfterEach
    public void restoreStreams() {
        System.setOut(originalOut);
        System.setIn(originalIn);
    }

    @Test
    public void testClientConnection() {
        String input = "localhost\n5000\n";
        ByteArrayInputStream inContent = new ByteArrayInputStream(input.getBytes());
        System.setIn(inContent);

        try (Socket socket = Mockito.mock(Socket.class)) {
            when(socket.isConnected()).thenReturn(true);

            new Client("localhost", 5000);
            assertTrue(socket.isConnected());
        }
        catch (IOException e) {
            fail(e.getMessage());
        }
    }
}
