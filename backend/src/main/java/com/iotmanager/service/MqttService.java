package com.iotmanager.service;


import java.nio.charset.StandardCharsets;
import java.util.UUID;

import org.eclipse.paho.client.mqttv3.IMqttClient;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.springframework.stereotype.Service;

@Service
public class MqttService {

    private static final String MQTT_BROKER = "tcp://mosquitto:1883";
    private static final String CLIENT_ID = UUID.randomUUID().toString();

    private IMqttClient client;

    public MqttService() {
        this.client = null;
    }

    public void publishCommand(String deviceSerial, String command) {
        try {
            if (client == null || !client.isConnected()) {
                reconnect();
            }

            String topic = "device/" + deviceSerial + "/cmd";
            MqttMessage message = new MqttMessage(command.getBytes(StandardCharsets.UTF_8));
            message.setQos(1);
            message.setRetained(false);

            client.publish(topic, message);
        } catch (MqttException e) {
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
            }
        } catch (MqttException e) {
        }
    }

    public boolean isConnected() {
        return client != null && client.isConnected();
    }
}
