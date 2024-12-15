package tests;

import tools.CustomTuple;

import java.io.*;
import java.net.*;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class CustomTupleTest {

    @Test
    void testCustomTupleCreation() {
        BufferedReader reader = null;
        PrintWriter writer = null;
        InetAddress address = null;
        int port = 8080;
        Socket socket = null;
        boolean isCoordinator = false;

        CustomTuple customTuple = new CustomTuple("TestClient", reader, writer, address, port, socket, isCoordinator);
        assertNotNull(customTuple);
    }
}
