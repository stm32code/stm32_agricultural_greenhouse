package com.example.greenhousemonitoringcontrolsystem.bean;

public class Receive {
    private String temp;
    private String temp_v;
    private String humi;
    private String humi_v;
    private String soil_humi;
    private String soil_humi_v;
    private String led;
    private String light;
    private String light_v;
    private String pump;
    private String flage;

    @Override
    public String toString() {
        return "Receive{" +
                "temp='" + temp + '\'' +
                ", temp_v='" + temp_v + '\'' +
                ", humi='" + humi + '\'' +
                ", humi_v='" + humi_v + '\'' +
                ", soil_humi='" + soil_humi + '\'' +
                ", soil_humi_v='" + soil_humi_v + '\'' +
                ", led='" + led + '\'' +
                ", light='" + light + '\'' +
                ", light_v='" + light_v + '\'' +
                ", pump='" + pump + '\'' +
                ", flage='" + flage + '\'' +
                '}';
    }

    public String getTemp() {
        return temp;
    }

    public void setTemp(String temp) {
        this.temp = temp;
    }

    public String getTemp_v() {
        return temp_v;
    }

    public void setTemp_v(String temp_v) {
        this.temp_v = temp_v;
    }

    public String getHumi() {
        return humi;
    }

    public void setHumi(String humi) {
        this.humi = humi;
    }

    public String getHumi_v() {
        return humi_v;
    }

    public void setHumi_v(String humi_v) {
        this.humi_v = humi_v;
    }

    public String getSoil_humi() {
        return soil_humi;
    }

    public void setSoil_humi(String soil_humi) {
        this.soil_humi = soil_humi;
    }

    public String getSoil_humi_v() {
        return soil_humi_v;
    }

    public void setSoil_humi_v(String soil_humi_v) {
        this.soil_humi_v = soil_humi_v;
    }

    public String getLed() {
        return led;
    }

    public void setLed(String led) {
        this.led = led;
    }

    public String getLight() {
        return light;
    }

    public void setLight(String light) {
        this.light = light;
    }

    public String getLight_v() {
        return light_v;
    }

    public void setLight_v(String light_v) {
        this.light_v = light_v;
    }

    public String getPump() {
        return pump;
    }

    public void setPump(String pump) {
        this.pump = pump;
    }

    public String getFlage() {
        return flage;
    }

    public void setFlage(String flage) {
        this.flage = flage;
    }
}
