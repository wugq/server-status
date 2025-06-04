package Serial;

import lombok.Data;

@Data()
public class ConnectionStatus {
  public SerialConnection connection;
  public boolean isValidConnection;
  public byte token;
}
