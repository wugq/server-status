package Message;

public class ACKMessageHandler implements MessageHandler {

  @Override
  public void handle(byte[] newData) {
    System.out.println("ACK received. Data:" + new String(newData));
  }
}
