package Message;

public enum MessageCharacter {
    START('<'), END('>'), SEPARATOR('#');

    public final byte value;

    public static void main(String[] args) {
        System.out.println(MessageCharacter.START.value);
        System.out.println(MessageCharacter.END.value);
        System.out.println(MessageCharacter.SEPARATOR.value);
    }

    MessageCharacter(char value) {
        this.value = (byte) value;
    }
}
