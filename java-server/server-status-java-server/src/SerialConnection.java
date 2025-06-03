import Message.MessageHandler;
import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;
import java.util.Arrays;
import lombok.Getter;

public class SerialConnection {
  private final SerialPort comPort;

  @Getter private boolean isOpen = false;

  private MessageHandler messageHandler;

  SerialConnection(String port, int baudRate) {
    comPort = SerialPort.getCommPort(port);
    comPort.setBaudRate(baudRate);
  }

  public void onDataReceived(MessageHandler messageHandler) {
    this.messageHandler = messageHandler;
  }

  public void setOnDataReceived() {
    if (!this.isOpen || this.messageHandler == null) {
      return;
    }

    MessageHandler messageHandler = this.messageHandler;
    comPort.addDataListener(
        new SerialPortDataListener() {
          @Override
          public int getListeningEvents() {
            return SerialPort.LISTENING_EVENT_DATA_RECEIVED;
          }

          @Override
          public void serialEvent(SerialPortEvent serialPortEvent) {
            messageHandler.handle(serialPortEvent.getReceivedData());
          }
        });
  }

  public static String[] getPorts() {
    return Arrays.stream(SerialPort.getCommPorts())
        .map(SerialPort::getSystemPortPath)
        .toArray(String[]::new);
  }

  public void openPort() {
    if (comPort.openPort()) {
      isOpen = true;
      this.setOnDataReceived();
    }
  }

  public void closePort() {
    comPort.flushDataListener();
    comPort.removeDataListener();
    comPort.closePort();
    isOpen = false;
  }

  public void send(String message) {
    this.send(message.getBytes());
  }

  public void send(byte[] message) {
    if (!isOpen) {
      throw new Error("Port is not open.");
    }

    try {
      comPort.getOutputStream().write(message);
      comPort.getOutputStream().flush();
    } catch (Exception e) {
      e.printStackTrace();
      throw new Error("Failed to send message.");
    }
  }
}
