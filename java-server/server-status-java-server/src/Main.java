public class Main {
    public static void main(String[] args) {
        ServerInfo serverInfo = new ServerInfo();

        SerialConnection serialConnection = new SerialConnection("ttyUSB0", 9600);
        serialConnection.send(serverInfo.collect().toJson());
    }
}