package client;

import tools.ExceptionHandler;

import java.io.*;
import java.net.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Random;

import static java.lang.System.exit;

public class Client {
    Socket socket = null;
    boolean running = true;

    public Client(String address, int port) {
        ExceptionHandler handler = new ExceptionHandler();

        try  {
            socket = new Socket(address, port);
            PrintWriter writer = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader userInputReader = new BufferedReader(new InputStreamReader(System.in));

            handler.infoHandler(String.format("Connected to server on address: %s, port: %d", address, port));

            String userInput;
            Random rand = new Random();
            int id = rand.nextInt(1000000) + 1;
            System.out.println("Your ID is: " + id);

            writer.println(id);
            writer.flush();

            ResponseHandler tempHandler = new ResponseHandler();
            new Thread(tempHandler).start();

            while ((userInput = userInputReader.readLine()) != null) {
                if (!running) {writer.close(); exit(0);}
                writer.println(userInput);
            }
        }
        catch (UnknownHostException e) {
            handler.unknownHandler(e);
        }
        catch (IOException e) {
            handler.ioHandler(e);
        }
    }


    private class ResponseHandler implements Runnable {

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm:ss");
        ExceptionHandler handler = new ExceptionHandler();
        BufferedReader reader = null;

        public ResponseHandler() {
            try {
                reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            }
            catch (IOException e) {
                handler.ioHandler(e);
            }
        }

        @Override
        public void run() {
            String serverResponse;

            do {
                LocalDateTime currentTime = LocalDateTime.now();
                String formattedTime = formatter.format(currentTime);

                try {
                    serverResponse = reader.readLine();
                    System.out.printf("%s: %s%n", formattedTime, serverResponse);

                    if (serverResponse.equals("Quitting") || serverResponse.equals("You have been kicked from the server")) {
                        reader.close();
                        socket.close();
                        running = false;
                        exit(0);
                    }
                } catch (IOException e) {
                    running = false;
                    handler.ioHandler(e);
                }

            } while (running);
        }
    }


    public static void main(String[] args) {
        new Client("localhost", 5000);
    }
}