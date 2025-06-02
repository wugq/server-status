package Message;

/**
 * Message Format
 * MESSAGE_START
 * MESSAGE_LENGTH
 * MESSAGE_TYPE
 * MESSAGE_DATA
 * MESSAGE_END
 */
public class Message {
    private final byte[] message;
    private int messageIndex;

    public static void main(String[] args) {
        Message message = new Message();
        message.add(CommandType.CPU_LOAD.value, new byte[]{100});
        message.add(CommandType.IP_ADDRESS.value, new byte[]{127, 0, 0, 1});
        message.add(CommandType.IP_ADDRESS.value, new byte[]{192 - 256, 168 - 256, 0, 123});
        byte[] msg = message.generate();
        System.out.println(msg);
    }

    public Message() {
        this.message = new byte[250];
        this.messageIndex = 0;
        this.message[messageIndex++] = MessageCharacter.START.value;
        this.message[messageIndex++] = 0;
    }

    public void add(byte messageType, byte[] message) {
        this.message[messageIndex++] = MessageCharacter.SEPARATOR.value;
        this.message[messageIndex++] = messageType;
        for (int i = 0; i < message.length; i++) {
            this.message[messageIndex++] = message[i];
        }
    }

    public byte[] generate() {
        this.message[messageIndex++] = MessageCharacter.END.value;
        this.message[1] = (byte) (this.messageIndex & 0xFF);

        byte[] theMessage = new byte[this.messageIndex];
        System.arraycopy(this.message, 0, theMessage, 0, theMessage.length);

        return theMessage;
    }
}


//int i = 234;
//byte b = (byte) i;
//System.out.println(b); // -22
//int i2 = b & 0xFF;
//System.out.println(i2); // 234
