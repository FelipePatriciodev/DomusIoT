package com.iotmanager.model;

import java.time.LocalTime;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Entity
@Data
@NoArgsConstructor
@AllArgsConstructor
public class Event {

	@Id
	@GeneratedValue
	private Long id;

	@Enumerated(EnumType.STRING)
	private ActionType action;

	private LocalTime time;

	@ManyToOne
	private Programming programming;

	public enum ActionType {
		TURN_ON,
		TURN_OFF
	}
}
