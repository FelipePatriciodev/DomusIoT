package com.iotmanager.dto;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class DeviceCommandDTO {
    private Integer intervalMin;
    private Integer outputStatus;
    private List<ScheduleEntry> schedules;

    @Data
    @NoArgsConstructor
    @AllArgsConstructor
    public static class ScheduleEntry {
        private int hour;
        private int minute;
        private int state;
    }
}
