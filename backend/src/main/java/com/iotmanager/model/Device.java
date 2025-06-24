package com.iotmanager.model;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import java.time.LocalDateTime;

@Entity
@Data
@NoArgsConstructor
@AllArgsConstructor
public class Device {
	@Id
	@GeneratedValue
	private Long id;

	@Column(unique = true, nullable = false)
	private String serial;

	private double latitude;
	private double longitude;
	private boolean status;

  private LocalDateTime lastSeen;

	@OneToOne(mappedBy = "device")
	private Programming programming;
}
