import Message.ACKMessageHandler;
import Message.CommandType;
import Message.Message;
import Message.MessageHandler;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;
import lombok.Data;

public class Main {
  private final Random random = new Random();

  private List<ConnectionStatus> connections;

  public static void main(String[] args) {
    ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(1);

    Runnable task =
        () -> {
          System.out.println("Running task at " + java.time.LocalTime.now());
          Main.runTask();
        };

    boolean isSchedule = false;
    if (isSchedule) {
      scheduler.scheduleAtFixedRate(task, 1, 10, TimeUnit.SECONDS);
    } else {
      Main.runTask();
    }
  }

  private static void runTask() {
    Main main = new Main();
    //  main.sendMessageServerInfo();
  }

  private void setTask() {
    ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(1);
    Runnable task =
        () -> {
          System.out.println("Running task at " + java.time.LocalTime.now());
        };
    scheduler.scheduleAtFixedRate(task, 1, 5, TimeUnit.SECONDS);
  }

  public Main() {
    this.setTask();
    this.connections = this.createConnectStatus();
    this.attachAckMessageHandler(this.connections);

    this.connections.forEach(
        connectionStatus -> {
          connectionStatus.connection.openPort();
          int tryCount = 0;
          int maxTryCount = 5;

          while (!connectionStatus.isValidConnection
              && connectionStatus.connection.isOpen()
              && tryCount++ < maxTryCount) {
            System.out.println("Waiting for connection.");
            sendMessageSYN(connectionStatus.connection, connectionStatus.token);
            try {
              TimeUnit.SECONDS.sleep(2);
            } catch (InterruptedException e) {
              throw new RuntimeException(e);
            }
          }
        });
  }

  private void attachAckMessageHandler(List<ConnectionStatus> connections) {
    for (ConnectionStatus connectionStatus : connections) {
      MessageHandler messageHandler = new ACKMessageHandler();
      connectionStatus.connection.onDataReceived(messageHandler);
    }
  }

  private List<ConnectionStatus> createConnectStatus() {
    String[] ports = SerialConnection.getPorts();
    ports = new String[] {"/dev/ttyUSB0"}; // TEST

    List<ConnectionStatus> connections = new ArrayList<>();


    for (String port : ports) {
      ConnectionStatus connectionStatus = new ConnectionStatus();
      connectionStatus.connection = new SerialConnection(port, 9600);
      connectionStatus.isValidConnection = false;
      connectionStatus.token = (byte) random.nextInt(200);

      connections.add(connectionStatus);
    }
    return connections;
  }

  private void sendMessageServerInfo(SerialConnection serialConnection) {
    ServerInfo serverInfo = new ServerInfo();
    ServerInfoDto serverInfoDto = serverInfo.collect();

    Message message = new Message();
    message.add(CommandType.CPU_LOAD.value, new byte[] {serverInfoDto.getCpuLoad()});
    message.add(CommandType.IP_ADDRESS.value, serverInfoDto.getIpAddressList());

    System.out.println(serverInfoDto);
    serialConnection.send(message.generate());
  }

  private void sendMessageSYN(SerialConnection serialConnection, byte token) {
    Message message = new Message();
    message.add(CommandType.SYN.value, new byte[] {token});

    serialConnection.send(message.generate());
  }
}

@Data()
class ConnectionStatus {
  public SerialConnection connection;
  public boolean isValidConnection;
  public byte token;
}
