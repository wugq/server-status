import com.fazecast.jSerialComm.SerialPort;

public class SerialConnection {
    private final SerialPort comPort;

    SerialConnection(String port, int baudRate) {
        comPort = SerialPort.getCommPort(port);
        comPort.setBaudRate(baudRate);
    }

    public void send(String message) {
        this.send(message.getBytes());
    }

    public void send(byte[] message) {
        if (!comPort.openPort()) {
            throw new Error("Failed to open Port.");
        }

        try {
            comPort.getOutputStream().write(message);
            comPort.getOutputStream().flush();
        } catch (Exception e) {
            e.printStackTrace();
            throw new Error("Failed to send message.");
        } finally {
            comPort.closePort();
        }
    }
}
