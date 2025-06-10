package com.iotmanager.repository;

import org.springframework.data.jpa.repository.JpaRepository;

import com.iotmanager.model.Event;

public interface EventRepository extends JpaRepository<Event, Long> {
	
}