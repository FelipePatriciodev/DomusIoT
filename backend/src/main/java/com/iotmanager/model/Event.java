package com.iotmanager.model;

import java.time.LocalTime;

import jakarta.persistence.Entity;
import jakarta.persistence.EnumType;
import jakarta.persistence.Enumerated;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.Id;
import jakarta.persistence.ManyToOne;

@Entity
public class Event {
    @Id @GeneratedValue
    private Long id;

    @Enumerated(EnumType.STRING)
    private ActionType action;

    private LocalTime time;

    @ManyToOne
    private Programming programming;
    
    public Event() {}
    
    public Event(Long id, ActionType action, LocalTime time, Programming programming) {
		super();
		this.id = id;
		this.action = action;
		this.time = time;
		this.programming = programming;
	}

	public enum ActionType {
        TURN_ON,
        TURN_OFF
    }

	public Long getId() {
		return id;
	}

	public void setId(Long id) {
		this.id = id;
	}

	public ActionType getAction() {
		return action;
	}

	public void setAction(ActionType action) {
		this.action = action;
	}

	public LocalTime getTime() {
		return time;
	}

	public void setTime(LocalTime time) {
		this.time = time;
	}

	public Programming getProgramming() {
		return programming;
	}

	public void setProgramming(Programming programming) {
		this.programming = programming;
	}
    
    
}
