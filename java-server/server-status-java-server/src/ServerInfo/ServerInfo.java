package ServerInfo;

import oshi.SystemInfo;
import oshi.hardware.CentralProcessor;

import java.net.*;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;

public class ServerInfo {
  public static void main(String[] args) {
    ServerInfo serverInfo = new ServerInfo();
    serverInfo.getIpAddressList();
    serverInfo.collect();
  }

  public ServerInfoDto collect() {
    ServerInfoDto serverInfoDto = new ServerInfoDto();

    getIpAddressList()
        .forEach(
            address -> {
              serverInfoDto.addIPAddress(address.getAddress());
            });

    serverInfoDto.setCpuLoad((byte) (int) getCpuLoad());
    return serverInfoDto;
  }

  private double getCpuLoad() {
    SystemInfo si = new SystemInfo();
    CentralProcessor processor = si.getHardware().getProcessor();

    return processor.getSystemCpuLoad(1000) * 100;
  }

  private List<InetAddress> getIpAddressList() {
    List<InetAddress> ipAddressList = new ArrayList<>();
    try {
      Enumeration<NetworkInterface> interfaces = NetworkInterface.getNetworkInterfaces();
      while (interfaces.hasMoreElements()) {
        List<InterfaceAddress> ip = interfaces.nextElement().getInterfaceAddresses();
        ip.forEach(
            address -> {
              if (address.getAddress().isLinkLocalAddress()) {
                return;
              }
              if (address.getAddress().isLoopbackAddress()) {
                return;
              }
              ipAddressList.add(address.getAddress());
            });
      }
    } catch (SocketException e) {
      throw new RuntimeException(e);
    }
    return ipAddressList;
  }
}
