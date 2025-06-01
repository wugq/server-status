import com.google.gson.Gson;
import lombok.Data;

@Data
public class ServerInfoDto {
    private String cpuLoad;
    private String sysLoad;
    private String ipAddress;

    public String toJson() {
        Gson gson = new Gson();
        String json = gson.toJson(this);
        return json;
    }
}
