package com.iotmanager.service;


import java.nio.charset.StandardCharsets;
import java.time.LocalDateTime;
import java.util.List;
import java.util.UUID;

import org.eclipse.paho.client.mqttv3.IMqttClient;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.iotmanager.dto.DeviceCommandDTO;
import com.iotmanager.model.Device;

import jakarta.annotation.PostConstruct;

@Service
public class MqttService {

    private static final String MQTT_BROKER = "tcp://mosquitto:1883";
    private static final String CLIENT_ID = UUID.randomUUID().toString();

    private IMqttClient client;

    @Autowired
    private DeviceService deviceService;

    public MqttService() {
        this.client = null;
    }

    public void publishCommand(String deviceSerial, DeviceCommandDTO command) {
        try {
            if (client == null || !client.isConnected()) {
                reconnect();
            }

            String topic = "/domus01/downlink/" + deviceSerial;

            ObjectMapper objectMapper = new ObjectMapper();
            String payload = objectMapper.writeValueAsString(command);

            System.out.println("✅ Publishing to topic: " + topic);
            System.out.println("📦 Payload: " + payload);

            MqttMessage message = new MqttMessage(payload.getBytes(StandardCharsets.UTF_8));
            message.setQos(1);
            message.setRetained(false);

            client.publish(topic, message);

        } catch (Exception e) {
            e.printStackTrace(); 
        }
    }

    public void subscribeToDevice(String deviceSerial) {
        try {
            if (client == null || !client.isConnected()) {
                reconnect();
            }

            String topic = "/domus01/uplink/" + deviceSerial;
            client.subscribe(topic, (t, msg) -> {
                String payload = new String(msg.getPayload(), StandardCharsets.UTF_8);
                System.out.println("📡 Message received from [" + t + "]: " + payload);

                try {
                    ObjectMapper mapper = new ObjectMapper();
                    DeviceCommandDTO uplink = mapper.readValue(payload, DeviceCommandDTO.class);

                    String serial = uplink.getDevice_id();
                    if (serial == null || serial.isBlank()) {
                        System.out.println("⚠️ device_id missing in uplink");
                        return;
                    }

                    Device device = deviceService.getDeviceBySerial(serial);
                    if (device == null) {
                        System.out.println("⚠️ Device with serial '" + serial + "' not found.");
                        return;
                    }

                    device.setStatus(uplink.getOutput_status() != null && uplink.getOutput_status() == 1);
                    device.setLastSeen(LocalDateTime.now());
                    deviceService.saveDevice(device);

                    System.out.println("✅ Updated device " + serial + " status and lastSeen");

                } catch (Exception e) {
                    System.out.println("❌ Error processing uplink message");
                    e.printStackTrace();
                }
            });
            System.out.println("✅ Subscribed to topic: " + topic);
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }

    @PostConstruct
    public void init() {
        try {
            reconnect();
            List<Device> devices = deviceService.getAllDevices();
            for (Device device : devices) {
                subscribeToDevice(device.getSerial());
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void reconnect() {
        try {
            if (client == null) {
                client = new MqttClient(MQTT_BROKER, CLIENT_ID);
            }

            if (!client.isConnected()) {
                MqttConnectOptions options = new MqttConnectOptions();
                options.setAutomaticReconnect(true);
                options.setCleanSession(true);
                client.connect(options);
                System.out.println("🔌 Connected to MQTT broker.");
            }
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }

    public boolean isConnected() {
        return client != null && client.isConnected();
    }
}

