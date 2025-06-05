package com.iotmanager.model;

import java.util.ArrayList;
import java.util.List;

import jakarta.persistence.CascadeType;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.Id;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.OneToMany;
import jakarta.persistence.OneToOne;

@Entity
public class Programming {
    @Id @GeneratedValue
    private Long id;

    private String name;

    @OneToOne
    @JoinColumn(name = "device_id", unique = true)
    private Device device;

    @OneToMany(mappedBy = "programming", cascade = CascadeType.ALL, orphanRemoval = true)
    private List<Event> events = new ArrayList<>(); 
    
    public Programming() {}
   
	public Programming(Long id, String name, Device device, List<Event> events) {
		super();
		this.id = id;
		this.name = name;
		this.device = device;
		this.events = events;
	}

	public Long getId() {
		return id;
	}

	public void setId(Long id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public Device getDevice() {
		return device;
	}

	public void setDevice(Device device) {
		this.device = device;
	}
    
    
}
