package com.iotmanager.dto;

import java.util.List;

public class DeviceCommandDTO {
    private Integer interval_min; // Opcional
    private Integer output_status; // Opcional
    private List<ScheduleEntry> schedules; // Opcional

    public Integer getInterval_min() { return interval_min; }
    public void setInterval_min(Integer interval_min) { this.interval_min = interval_min; }

    public Integer getOutput_status() { return output_status; }
    public void setOutput_status(Integer output_status) { this.output_status = output_status; }

    public List<ScheduleEntry> getSchedules() { return schedules; }
    public void setSchedules(List<ScheduleEntry> schedules) { this.schedules = schedules; }

    public static class ScheduleEntry {
        private int hour;
        private int minute;
        private int state;

        public int getHour() { return hour; }
        public void setHour(int hour) { this.hour = hour; }

        public int getMinute() { return minute; }
        public void setMinute(int minute) { this.minute = minute; }

        public int getState() { return state; }
        public void setState(int state) { this.state = state; }
    }
}