package Message;

public enum CommandType {
  CPU_LOAD('C'),
  IP_ADDRESS('I'),
  SYN('S');

  public static void main(String[] args) {
    System.out.println(CommandType.CPU_LOAD.value);
    System.out.println(CommandType.IP_ADDRESS.value);
  }

  public final byte value;

  CommandType(char value) {
    this.value = (byte) value;
  }
}
