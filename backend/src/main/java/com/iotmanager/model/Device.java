package com.iotmanager.model;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.Id;
import jakarta.persistence.OneToOne;

@Entity
public class Device {
	@Id
	@GeneratedValue
	private Long id;

	private String serial;
	private double latitude;
	private double longitude;
	private boolean status;
	@OneToOne(mappedBy = "device")
	private Programming programming;
	
	public Device() {}
	
	public Device(Long id, String serial, double latitude, double longitude, boolean status, Programming programming) {
		super();
		this.id = id;
		this.serial = serial;
		this.latitude = latitude;
		this.longitude = longitude;
		this.status = status;
		this.programming = programming;
	}

	public Long getId() {
		return id;
	}

	public void setId(Long id) {
		this.id = id;
	}

	public String getSerial() {
		return serial;
	}

	public void setSerial(String serial) {
		this.serial = serial;
	}

	public double getLatitude() {
		return latitude;
	}

	public void setLatitude(double latitude) {
		this.latitude = latitude;
	}

	public double getLongitude() {
		return longitude;
	}

	public void setLongitude(double longitude) {
		this.longitude = longitude;
	}

	public boolean isStatus() {
		return status;
	}

	public void setStatus(boolean status) {
		this.status = status;
	}

	public Programming getProgramming() {
		return programming;
	}

	public void setProgramming(Programming programming) {
		this.programming = programming;
	}

}
