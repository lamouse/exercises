import java.io.DataOutputStream;
import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Scanner;

/**
 * Created by sora on 16/11/09 -009.
 */
public class SockTest {

    public static void main(String[] args) {
        try {
           Socket client = new Socket("192.168.239.131",8088);
            Scanner scanner = new Scanner(System.in);
            DataOutputStream dataOutputStream = new DataOutputStream(client.getOutputStream());
            int localPort = client.getLocalPort();
            InetAddress localAddress = client.getLocalAddress();
            System.out.println("本地地址: " + localAddress + "本地端口: " + localPort);
            for (;;){
                System.out.println("输入一条数据:");
                String s = scanner.nextLine();
                System.out.println("读入数据:" + s);
                dataOutputStream.writeUTF(s);
                dataOutputStream.flush();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
