import Message.CommandType;
import Message.Message;

import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class Main {
    public static void main(String[] args) {
        ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(1);

        Runnable task = () -> {
            System.out.println("Running task at " + java.time.LocalTime.now());
            Main.runTask();
        };

        boolean isSchedule = true;
        if (isSchedule) {
            scheduler.scheduleAtFixedRate(task, 1, 10, TimeUnit.SECONDS);
        } else {
            Main.runTask();
        }
    }

    private static void runTask() {
        Main main = new Main();
        main.sendMessage();
    }

    private void sendMessage() {
        ServerInfo serverInfo = new ServerInfo();

        SerialConnection serialConnection = new SerialConnection("ttyUSB0", 9600);
        ServerInfoDto serverInfoDto = serverInfo.collect();
        Message message = new Message();
        message.add(CommandType.CPU_LOAD.value, new byte[]{serverInfoDto.getCpuLoad()});
        message.add(CommandType.IP_ADDRESS.value, serverInfoDto.getIpAddressList());
        System.out.println(serverInfoDto.toString());
        serialConnection.send(message.generate());
    }
}