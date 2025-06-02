package Message;

public enum CommandType {
    CPU_LOAD(1), IP_ADDRESS(2);

    public static void main(String[] args) {
        System.out.println(CommandType.CPU_LOAD.value);
        System.out.println(CommandType.IP_ADDRESS.value);
    }

    public final byte value;

    CommandType(int value) {
        if (value > 200) {
            throw new IllegalArgumentException("Value must be less than 200.");
        }
        this.value = (byte) value;
    }
}
