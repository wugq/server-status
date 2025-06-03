import com.google.gson.Gson;
import lombok.AccessLevel;
import lombok.Getter;
import lombok.Setter;

public class ServerInfoDto {
  @Getter(AccessLevel.NONE)
  @Setter(AccessLevel.NONE)
  public final byte supportedIpAddressNumber = 3;

  @Getter private byte cpuLoad;

  private final byte[] ipAddressList = new byte[1 + 4 * supportedIpAddressNumber];

  private byte getIpAddressNumber() {
    return ipAddressList[0];
  }

  public static void main(String[] args) {
    ServerInfoDto serverInfoDto = new ServerInfoDto();
    serverInfoDto.setCpuLoad(10);
    serverInfoDto.addIPAddress(new byte[] {127, 0, 0, 1});
    serverInfoDto.addIPAddress(new byte[] {192 - 256, 168 - 256, 0, 123});

    serverInfoDto.getIpAddressList();
    serverInfoDto.getCpuLoad();

    System.out.println(new Gson().toJson(serverInfoDto));
  }

  public byte[] getIpAddressList() {
    byte[] ipAddressList = new byte[1 + this.ipAddressList[0] * 4];
    System.arraycopy(this.ipAddressList, 0, ipAddressList, 0, ipAddressList.length);
    return ipAddressList;
  }

  public void setCpuLoad(int number) {
    if (number > 100) {
      return;
    }
    this.cpuLoad = (byte) number;
  }

  public void addIPAddress(byte[] ipAddress) {
    if (ipAddress.length != 4) {
      return;
    }
    if (getIpAddressNumber() >= supportedIpAddressNumber) {
      return;
    }

    int startPosition = 1 + 4 * getIpAddressNumber();
    System.arraycopy(ipAddress, 0, ipAddressList, startPosition, 4);
    ipAddressList[0] = (byte) (getIpAddressNumber() + 1);
  }

  public String toString() {
    return new Gson().toJson(this);
  }
}
