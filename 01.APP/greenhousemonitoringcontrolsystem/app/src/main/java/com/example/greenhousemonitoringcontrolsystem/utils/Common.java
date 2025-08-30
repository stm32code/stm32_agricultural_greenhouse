package com.example.greenhousemonitoringcontrolsystem.utils;

import com.example.greenhousemonitoringcontrolsystem.bean.Send;
import com.example.greenhousemonitoringcontrolsystem.socket.SocketClientThread;
import com.google.gson.Gson;
import com.itfitness.mqttlibrary.MQTTHelper;

public class Common {
    public static String Port = "1883";
    public static String Sever = "tcp://iot-06z00axdhgfk24n.mqtt.iothub.aliyuncs.com" + ":" + Port;
//    public static String Port = "6002";
//    public static String Sever = "tcp://192.168.101.77" + ":" + Port;

    public static String ReceiveTopic = "/broadcast/h9sjsuVlfGs/test2";
    public static String PushTopic = "/broadcast/h9sjsuVlfGs/test1";
    public static String DriveID = "h9sjsuVlfGs.smart_app|securemode=2,signmethod=hmacsha256,timestamp=1706944983080|";
    public static String DriveName = "smart_app&h9sjsuVlfGs";
    public static String DrivePassword = "318d80ec2b071fdd4c7c1103f74aebd48afa96ef15b5250f711f9e6a0bcf7c13";
    public static String Drive2ID = "1181073144";
    public static String api_key = "l=yQf7V3jwBh10rp7rjt=5GUQfU=";
    public static boolean DeviceOnline = false;
    public static String LatestOnlineDate = "离线";
    public static MQTTHelper mqttHelper = null;
    public static String SOCKET_IP = "192.168.0.45"; //连接IP地址

    //     public static final String SOCKET_IP = "192.168.229.213"; //连接IP地址
    public static String SOCKET_PORT = "8080";  //连接端口号
    public static boolean SOCKET_CONNET = false; //是否连接
    public static final int SOCKET_CONNET_OK = 403;  //连接成功
    public static final int SOCKET_CONNET_ERROR = 400; //连接错误
    public static final int SOCKET_SEND_DATA = 401; //发送消息
    public static final int SOCKET_SEND_ERROR = 405; //发送失败
    public static final int SOCKET_RECEIVE_DATA = 402; //接收到消息
    public static final int SOCKET_RECEIVE_ERROR = 404; //接收错误
    public static boolean SOCKET_BUSY = false; //是否在忙
    public static SocketClientThread sClientThread = null;

    /***
     * 发送消息
     * @param cmd 指令控制
     * @param message 消息内容数组
     */
    public static void SocketSend(int cmd, String... message) {
        new Thread(() -> {
            if (Common.mqttHelper != null && Common.mqttHelper.getConnected()) {
                Send send = new Send();
                switch (cmd) {
                    case 1:
                        send.setFlage(Integer.parseInt(message[0]));
                        break;
                    case 2:
                        send.setPump(Integer.parseInt(message[0]));
                        break;
                    case 3:
                        send.setTemp_v(Integer.parseInt(message[0]));
                        send.setHumi_v(Integer.parseInt(message[1]));
                        send.setSoil_humi_v(Integer.parseInt(message[2]));
                        send.setLight_v(Integer.parseInt(message[3]));
                        break;
                    case 4:
                        send.setTime(Integer.parseInt(message[0]));
                        break;
                }
                send.setCmd(cmd);
                Common.mqttHelper.publish(PushTopic, new Gson().toJson(send), 1);
//                sClientThread.SendMessage(new Gson().toJson(send));
            }
        }).start();
    }
}
