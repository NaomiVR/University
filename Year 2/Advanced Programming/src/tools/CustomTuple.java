package tools;

import java.io.*;
import java.net.*;

public class CustomTuple {
    String clientName;
    BufferedReader clientReader;
    PrintWriter clientWriter;
    InetAddress clientIP;
    int clientPort;
    Socket clientSocket;
    boolean isCoordinator;

    public CustomTuple(String clientName, BufferedReader clientReader, PrintWriter clientWriter, InetAddress clientIP,
                       int clientPort, Socket clientSocket, boolean isCoordinator) {
        this.clientName = clientName;
        this.clientReader = clientReader;
        this.clientWriter = clientWriter;
        this.clientIP = clientIP;
        this.clientPort = clientPort;
        this.clientSocket = clientSocket;
        this.isCoordinator = isCoordinator;
    }

    public String getName() {
        return clientName;
    }

    public BufferedReader getBufferedReader() {
        return clientReader;
    }

    public PrintWriter getPrintWriter() {
        return clientWriter;
    }

    public InetAddress getInetAddress() {
        return clientIP;
    }

    public int getPort() {
        return clientPort;
    }

    public Socket getSocket() {
        return clientSocket;
    }

    public boolean getCoordinator() {
        return isCoordinator;
    }

    public void setCoordinator(boolean isCoordinator) {
        this.isCoordinator = isCoordinator;
    }
}
