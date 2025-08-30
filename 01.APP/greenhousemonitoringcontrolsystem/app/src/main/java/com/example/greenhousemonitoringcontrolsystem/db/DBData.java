package com.example.greenhousemonitoringcontrolsystem.db;

public class DBData {
    private String temp;
    private String humi;
    private String light;
    private String trhumi;
    private String createDateTime;

    @Override
    public String toString() {
        return "DBData{" +
                "temp='" + temp + '\'' +
                ", humi='" + humi + '\'' +
                ", light='" + light + '\'' +
                ", trhumi='" + trhumi + '\'' +
                ", createDateTime='" + createDateTime + '\'' +
                '}';
    }

    public String getCreateDateTime() {
        return createDateTime;
    }

    public void setCreateDateTime(String createDateTime) {
        this.createDateTime = createDateTime;
    }

    public String getTemp() {
        return temp;
    }

    public void setTemp(String temp) {
        this.temp = temp;
    }

    public String getHumi() {
        return humi;
    }

    public void setHumi(String humi) {
        this.humi = humi;
    }

    public String getLight() {
        return light;
    }

    public void setLight(String light) {
        this.light = light;
    }

    public String getTrhumi() {
        return trhumi;
    }

    public void setTrhumi(String trhumi) {
        this.trhumi = trhumi;
    }
}
