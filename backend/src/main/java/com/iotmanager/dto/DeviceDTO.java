package com.iotmanager.dto;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class DeviceDTO {
	private Long id;
	private String serial;
	private double latitude;
	private double longitude;
	private boolean status;
}
