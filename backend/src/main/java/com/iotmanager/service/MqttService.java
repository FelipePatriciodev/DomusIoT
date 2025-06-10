package com.iotmanager.service;


import org.eclipse.paho.client.mqttv3.*;
import org.springframework.stereotype.Service;

import java.nio.charset.StandardCharsets;
import java.util.UUID;

@Service
public class MqttService {

    private static final String MQTT_BROKER = "tcp://mosquitto:1883";
    private static final String CLIENT_ID = UUID.randomUUID().toString();

    private IMqttClient client;

    public MqttService() throws MqttException {
        client = new MqttClient(MQTT_BROKER, CLIENT_ID);
        MqttConnectOptions options = new MqttConnectOptions();
        options.setAutomaticReconnect(true);
        options.setCleanSession(true);
        client.connect(options);
    }

    public void publishCommand(String deviceSerial, String command) throws MqttException {
        if (!client.isConnected()) {
            reconnect();
        }

        String topic = "device/" + deviceSerial + "/cmd";
        MqttMessage message = new MqttMessage(command.getBytes(StandardCharsets.UTF_8));
        message.setQos(1);
        message.setRetained(false);

        client.publish(topic, message);
        System.out.printf("Publish command '%s' to  %s%n", command, topic);
    }

    private void reconnect() throws MqttException {
        if (!client.isConnected()) {
            MqttConnectOptions options = new MqttConnectOptions();
            options.setAutomaticReconnect(true);
            options.setCleanSession(true);
            client.connect(options);
        }
    }
}
