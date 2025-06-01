import oshi.SystemInfo;
import oshi.hardware.CentralProcessor;

import java.lang.management.ManagementFactory;
import java.lang.management.OperatingSystemMXBean;
import java.net.*;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;

public class ServerInfo {
    public ServerInfoDto collect() {
        ServerInfoDto serverInfoDto = new ServerInfoDto();
        serverInfoDto.setCpuLoad(getCpuLoadString());
        serverInfoDto.setSysLoad(getSysLoadString());
        serverInfoDto.setIpAddress(String.join(",", getIpAddressList()));
        return serverInfoDto;
    }

    private String getSysLoadString() {
        return String.format("%.2f", getSysLoad());
    }

    private double getCpuLoad() {
        SystemInfo si = new SystemInfo();
        CentralProcessor processor = si.getHardware().getProcessor();

        return processor.getSystemCpuLoad(1000) * 100;
    }

    private String getCpuLoadString() {
        return String.format("%.0f", getCpuLoad());
    }

    private double getSysLoad() {
        OperatingSystemMXBean bean = ManagementFactory.getOperatingSystemMXBean();
        return bean.getSystemLoadAverage();
    }

    private List<String> getIpAddressList() {
        List<String> ipAddressList = new ArrayList<>();
        try {
            Enumeration<NetworkInterface> interfaces = NetworkInterface.getNetworkInterfaces();
            while (interfaces.hasMoreElements()) {
                List<InterfaceAddress> ip = interfaces.nextElement().getInterfaceAddresses();
                ip.forEach(address -> {
                    if (address.getAddress().isLinkLocalAddress()) {
                        return;
                    }
                    if (address.getAddress().isLoopbackAddress()) {
                        return;
                    }
                    ipAddressList.add(address.getAddress().getHostAddress());
                });
            }
        } catch (SocketException e) {
            throw new RuntimeException(e);
        }
        return ipAddressList;
    }
}
