package tests;

import client.Server;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class ServerTest {

    @Test
    void testServerInitialisation() {
        Server server = new Server(5000);
        assertNotNull(server);
    }
}
