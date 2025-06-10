package com.iotmanager.controller;

import java.util.List;
import java.util.Optional;

import org.eclipse.paho.client.mqttv3.MqttException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.iotmanager.model.Device;
import com.iotmanager.service.DeviceService;
import com.iotmanager.service.MqttService;

@RestController
@RequestMapping("/api/devices")
public class DeviceController {

    @Autowired
    private DeviceService deviceService;
    
    @GetMapping
    public List<Device> list() {
        return deviceService.getAllDevices();
    }

    @GetMapping("/{id}")
    public ResponseEntity<Device> get(@PathVariable Long id) {
        return deviceService.getDeviceById(id)
            .map(ResponseEntity::ok)
            .orElse(ResponseEntity.notFound().build());
    }

    @PostMapping
    public Device create(@RequestBody Device device) {
        return deviceService.saveDevice(device);
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<?> delete(@PathVariable Long id) {
        deviceService.deleteDevice(id);
        return ResponseEntity.noContent().build();
    }
    
    @PostMapping("/{id}/toggle")
    public ResponseEntity<?> toggle(@PathVariable Long id) {
        Optional<Device> deviceOpt = deviceService.getDeviceById(id);
        if (deviceOpt.isEmpty()) return ResponseEntity.notFound().build();

        Device device = deviceOpt.get();
        device.setStatus(!device.isStatus());
        deviceService.saveDevice(device);

     
        return ResponseEntity.ok(device);
    }

}
