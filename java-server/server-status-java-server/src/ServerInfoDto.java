import com.google.gson.Gson;
import lombok.Data;

@Data
public class ServerInfoDto {
    private String cpuLoad;
    private String sysLoad;
    private String ipAddress;

    public String toJson() {
        Gson gson = new Gson();
        return gson.toJson(this);
    }

    public String toTTL() {
        return String.format("C:%s;S:%s;I:%s", cpuLoad, sysLoad, ipAddress);
    }
}
