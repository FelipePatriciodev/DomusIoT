package com.iotmanager.repository;

import java.util.Optional;

import org.springframework.data.jpa.repository.JpaRepository;

import com.iotmanager.model.Device;

public interface DeviceRepository extends JpaRepository<Device, Long> {
    Optional<Device> findBySerial(String serial);
}
