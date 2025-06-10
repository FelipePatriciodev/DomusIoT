package com.iotmanager.service;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.iotmanager.model.Device;
import com.iotmanager.model.Programming;
import com.iotmanager.repository.DeviceRepository;
import com.iotmanager.repository.ProgrammingRepository;

@Service
public class ProgrammingService {

    @Autowired
    private ProgrammingRepository programmingRepository;

    @Autowired
    private DeviceRepository deviceRepository;

    public Programming createProgramming(Programming programming, Long deviceId) {
        Device device = deviceRepository.findById(deviceId)
                .orElseThrow(() -> new RuntimeException("Device not found"));

        programming.setDevice(device);
        return programmingRepository.save(programming);
    }

    public List<Programming> getAll() {
        return programmingRepository.findAll();
    }
}
