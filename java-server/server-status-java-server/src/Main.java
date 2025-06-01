import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class Main {
    public static void main(String[] args) {
        ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(1);

        Runnable task = () -> {
            System.out.println("Running task at " + java.time.LocalTime.now());
            Main main = new Main();
            main.sendMessage();
        };

        scheduler.scheduleAtFixedRate(task, 1, 10, TimeUnit.SECONDS);
    }

    private void sendMessage() {
        ServerInfo serverInfo = new ServerInfo();

        SerialConnection serialConnection = new SerialConnection("ttyUSB0", 9600);
        ServerInfoDto serverInfoDto = serverInfo.collect();
        System.out.println(serverInfoDto.toJson());
        serialConnection.send(serverInfoDto.toTTL());
    }
}