package com.iotmanager.model;

import java.util.ArrayList;
import java.util.List;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Entity
@Data
@NoArgsConstructor
@AllArgsConstructor
public class Programming {

	@Id
	@GeneratedValue
	private Long id;

	private String name;

	@OneToOne
	@JoinColumn(name = "device_id", unique = true)
	private Device device;

	@OneToMany(mappedBy = "programming", cascade = CascadeType.ALL, orphanRemoval = true)
	private List<Event> events = new ArrayList<>();
}
