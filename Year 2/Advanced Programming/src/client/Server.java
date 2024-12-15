package client;

import tools.CustomTuple;
import tools.ExceptionHandler;

import java.io.*;
import java.net.*;
import java.util.*;

public class Server {
    boolean serverRunning = true;
    Map<String, CustomTuple> clients = new HashMap<>();

    public Server(int port) {
        ExceptionHandler handler = new ExceptionHandler();

        try (ServerSocket server = new ServerSocket()) {
            server.bind(new InetSocketAddress("localhost", port));
            handler.infoHandler(String.format("Server started on address: %s, port: %d", server.getInetAddress(), port));

            do {
                Socket client = server.accept();
                handler.infoHandler(String.format("New client connected: %s", client.getInetAddress().getHostAddress()));

                ClientHandler clientSock = new ClientHandler(client);

                new Thread(clientSock).start();

            } while (serverRunning);
        }
        catch (IOException e) {
            serverRunning = false;
            handler.ioHandler(e);
        }
    }

    private class ClientHandler implements Runnable {
        private final Socket socket;
        private String clientName;
        private PrintWriter writer;
        private BufferedReader reader;
        boolean coordinator = false;
        boolean running = true;
        ExceptionHandler handler = new ExceptionHandler();
        private ClientHandler(Socket socket) {
            this.socket = socket;
        }

        @Override
        public void run() {
            if (clients.isEmpty()) {
                coordinator = true;
            }

            try {
                writer = new PrintWriter(socket.getOutputStream(), true);
                reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));

                clientName = reader.readLine();
                CustomTuple clientInfo = new CustomTuple(clientName, reader, writer, socket.getInetAddress(),
                        socket.getPort(), socket, coordinator);
                clients.put(clientName, clientInfo);

                sendCoordinator();

                String message;
                while ((message = reader.readLine()) != null) {
                    handleClientMessage(message);
                }
            }
            catch (IOException e) {
                handler.ioHandler(e);
                handleClientDisconnect();
            }
        }

        private void handleClientMessage(String message) {
            String[] parts = message.split(" ", 2);
            String command = parts[0].toLowerCase();
            String argument = parts.length > 1 ? parts[1] : "";

            System.out.println("Client: " + clientName + " Command: " + command  + ", Argument: " + argument);


            switch (command) {
                case "/commands" -> {
                    String commands = """
                            /commands (no argument)
                            /list (no argument)
                            /msg clientName message
                            /broadcast message
                            /exit (no arguments)
                            /kick clientName""";
                    writer.println(commands);
                }
                case "/list" -> sendClientList();
                case "/msg" -> {
                    String[] msgParts = argument.split(" ", 2);
                    String recipient = msgParts[0];
                    String msgContent = msgParts[1];
                    sendMessageToClient(recipient, msgContent);
                }
                case "/broadcast" -> sendBroadcastMessage(argument);
                case "/exit" -> {
                    writer.println("Quitting");
                    clientExit();
                }
                case "/kick" -> {
                    if (clients.get(clientName).getCoordinator()) {
                        kickClient(argument);
                    }
                    else {
                        writer.println("Cannot use command without coordinator status");
                    }
                }
                default -> writer.println("Invalid command, type /commands to show a list of commands and format");
            }
        }

        private void handleClientDisconnect() {
            for (Map.Entry<String, CustomTuple> entry : clients.entrySet()) {
                entry.getValue().getPrintWriter().println(String.format("Client: %s has disconnected", clientName));
            }

            try {
                coordinator = clients.get(clientName).getCoordinator();

                if (writer != null) {
                    writer.close();
                }
                if (reader != null) {
                    reader.close();
                }
                if (socket != null) {
                    socket.close();
                }

                if (coordinator) {
                    pickRandomCoordinator();
                }

                clients.remove(clientName);
            }
            catch (IOException e) {
                handler.ioHandler(e);
            }
        }

        private void sendClientList() {
            StringBuilder clientList = new StringBuilder();
            InetAddress clientIP;
            int clientPort;

            for (Map.Entry<String, CustomTuple> entry : clients.entrySet()) {
                clientName = entry.getKey();
                clientIP = entry.getValue().getInetAddress();
                clientPort = entry.getValue().getPort();

                clientList.append(clientName).append(":").append(clientIP).append(":").append(clientPort).append(", ");
            }


            writer.println("Client list: " + clientList);
        }

        private void sendMessageToClient(String recipient, String message) {
            CustomTuple clientInfo = clients.get(recipient);
            PrintWriter recipientWriter = clientInfo.getPrintWriter();
            if (recipientWriter != null) {
                recipientWriter.println(String.format("DM from %s: %s", clientName, message));
            }
            else {
                writer.println(String.format("Client: %s is not connected", recipient));
            }
        }

        private void sendBroadcastMessage(String message) {
            for (Map.Entry<String, CustomTuple> entry : clients.entrySet()) {
                if (!entry.getKey().equals(clientName)) {
                    entry.getValue().getPrintWriter().println(String.format("Broadcast message from %s: %s",
                            clientName, message));
                }
            }
        }

        private void clientExit() {
            try {
                writer.close();
                reader.close();
                socket.close();

                coordinator = clients.get(clientName).getCoordinator();

                clients.remove(clientName);

                if (coordinator) {
                    pickRandomCoordinator();
                }

                running = false;
            }
            catch (IOException e) {
                handler.ioHandler(e);
            }
        }

        private void kickClient(String clientName) {
            CustomTuple clientInfo = clients.get(clientName);
            if (clientInfo != null) {
                PrintWriter clientWriter = clientInfo.getPrintWriter();
                if (clientWriter != null) {
                    clientWriter.println("You have been kicked from the server");
                    clientWriter.flush();
                }

                try {
                    clientInfo.getBufferedReader().close();
                    assert clientWriter != null;
                    clientWriter.close();
                    clientInfo.getSocket().close();
                }
                catch (IOException e) {
                    handler.ioHandler(e);
                }

                clients.remove(clientName);
            }
        }

        private void sendCoordinator() {
            if (!coordinator) {
                for (Map.Entry<String, CustomTuple> entry : clients.entrySet()) {
                    if (entry.getValue().getCoordinator()) {
                        writer.println(String.format("Coordinator ID: %s", entry.getValue().getName()));
                    }
                }
            }
        }

        private void pickRandomCoordinator() {
            List<CustomTuple> infolist = new ArrayList<>(clients.values());
            int random = new Random().nextInt(infolist.size());
            CustomTuple clientInfo = infolist.get(random);

            clientInfo.setCoordinator(true);
            clientInfo.getPrintWriter().println("You're now the coordinator");
        }
    }

    public static void main(String[] args) {
        new Server(5000);
    }
}