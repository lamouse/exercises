package com.sora.utils;

/**
 * Created by sora on 17/03/26 -026.
 * RC4加密算法 参考维基百科https://zh.wikipedia.org/wiki/RC4
 */
public class RC4 {
    private String key = "123456";

    /**
     *
     * @param key
     * @param length
     * @return
     * 通过key生成一个s盒子, length表示盒子的长度, 盒子长度大于0
     */
    private static byte[] sBox(byte[] key, int length){
        byte[] s = new byte[length];
        for(int i = 0; i < s.length;i++)
            s[i] = (byte) i;
        if(key == null || key.length == 0){
            return s;
        }
        int j = 0;
        //打乱S盒子
        for(int i = 0; i < s.length; i++){
            j = (j + 0xff & s[i] + 0xff & key[i % key.length]) % s.length;
            byte tmp = s[i];
            s[i] = s[j];
            s[j] = tmp;
        }
        return s;
    }

    /**
     *
     * @param input
     * @param key
     * @param length
     * @return
     * RC4 加密解密方法 input表示输入长度, key代表加密串, length代表加密长度 length > 0
     */
    public static byte[] encodeDecode(byte[] input, byte[] key, int length){
        byte[] s = new byte[input.length];
        int i = 0, j = 0;
        byte[] bytes = sBox(key, length);
        for(int k = 0; k < input.length; k++){
            i = (i + 1) % bytes.length;
            j = (j + 0xff & bytes[i]) % bytes.length;
            byte tmp = bytes[i];
            bytes[i] = bytes[j];
            bytes[j] = tmp;
            s[k] = (byte) (input[k] ^ bytes[(0xff & bytes[i] + 0xff & bytes[j]) % bytes.length]);
        }
        return s;
    }

    public static void main(String[] args) {
        byte[] bytes = encodeDecode("都是".getBytes(), "".getBytes(), 100);
        System.out.println(new String(encodeDecode(bytes, "".getBytes(), 100)));
        byte[] bytes1 = sBox("54532".getBytes(), 12);
        for (int i = 0; i < bytes1.length; i++){
            System.out.println(0xff & bytes1[i]);
        }
    }
}
