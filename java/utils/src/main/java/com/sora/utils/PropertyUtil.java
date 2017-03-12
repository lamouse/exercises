package com.sora.utils;

import sun.reflect.Reflection;

import java.io.*;
import java.net.URL;
import java.util.*;

/**
 * Created by sora on 17/03/06 -006.
 */
public class PropertyUtil {
    private InputStream in;
    private OutputStream out;
    private Map<String, String> keyMap = new HashMap<String, String>();
    private String listSplitStr = ".";
    private char keyValueSplitChar = '=';


    public PropertyUtil(InputStream in){
        this.in = in;
        readFile();
    }

    /**
     *
     * @param path file path
     * @throws FileNotFoundException
     * @auther sora
     */
    public PropertyUtil(String path) throws FileNotFoundException {
        try {
            path = Class.forName(Thread.currentThread().getStackTrace()[2].getClassName()).getResource("/").getPath() + path;

        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
        in = new FileInputStream(path);
        readFile();
    }
    public PropertyUtil(File file) throws FileNotFoundException {
        this(new FileInputStream(file));
    }
    private void readFile(){
        List<String> fileInfo = new ArrayList<String>();
        Scanner scanner = new Scanner(in);
        String line;
        while(scanner.hasNextLine()){
            /**
             * remove this first and last space character
             */
            line = scanner.nextLine().trim();
            if(line.charAt(0) == '#'){
                continue;
            }
            Pair<String, String> pair = parseKeyValue(line);
            if(pair != null){
                keyMap.put(pair.getKey(), pair.getValue());
            }
        }
    }

    public Integer getInteger(String key){
        return keyMap.get(key) == null? null:Integer.parseInt(keyMap.get(key).trim());
    }

    /**
     *
     * @param key
     * @return
     * get interList if key not found or key not has value return a empty List<Integer>
     */
    public List<Integer> getIntegerList(String key){
        List<Integer> integers = new ArrayList<Integer>();
        if(keyMap.get(key) != null){
            String[] split = keyMap.get(key).split(listSplitStr);
            for(int i = 0; i < split.length; i++){
                integers.add(Integer.parseInt(split[i].trim()));
            }
        }

        return integers;
    }

    public String getString(String key){
        return keyMap.get(key);
    }

    /**
     *
     * @param key
     * @return if key not found return empty List<String>
     */
    public List<String> getStringList(String key){
        List<String> strings = new ArrayList<String>();
        String[] split = keyMap.get(key).split(listSplitStr);
        for(int i = 0; i < split.length; i++){
            strings.add(split[i].trim());
        }
        return strings;
    }

    public Double getDouble(String key){
        return keyMap.get(key) == null? null:Double.parseDouble(keyMap.get(key).trim());
    }

    public List<Double> getDoubleList(String key){
        ArrayList<Double> doubles = new ArrayList<Double>();
        if(keyMap.get(key) != null){
            String[] split = keyMap.get(key).split(listSplitStr);
            for (int i = 0; i < split.length; i++) {
                doubles.add(Double.parseDouble(split[i]));
            }
        }
        return doubles;
    }


    private Pair<String, String> parseKeyValue(String str){
        int keyIndex = str.indexOf(keyValueSplitChar);
        if (keyIndex == -1){
            return null;
        }
        String key = str.substring(0, keyIndex).trim();
        String value = str.substring(keyIndex+1);
        return new Pair<String, String>(key, value);
    }

    public class Pair<K, V>{
        private K key;
        private V value;
        public Pair(K key, V value){
            this.key = key;
            this.value = value;
        }
        public K getKey(){
            return key;
        }

        public void setKey(K key) {
            this.key = key;
        }

        public V getValue() {
            return value;
        }

        public void setValue(V value) {
            this.value = value;
        }
    }
}
