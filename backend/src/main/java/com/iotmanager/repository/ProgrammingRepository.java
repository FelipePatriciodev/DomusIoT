package com.iotmanager.repository;

import org.springframework.data.jpa.repository.JpaRepository;

import com.iotmanager.model.Programming;

public interface ProgrammingRepository extends JpaRepository<Programming, Long> {
	
}