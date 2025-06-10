# MQTT Communication Protocol – ESP32 Device

This document describes the JSON-based MQTT communication protocol used by an ESP32 device. The communication is divided into two main topics: `uplink` (device to server) and `downlink` (server to device).

---

## 📡 Uplink (`/domus01/uplink/<device_id>`)

The `uplink` topic is used by the device to send status updates at regular intervals.

### Payload Example:

```json
{"device_id":"01","interval_min":15,"output_status":1,"schedules":[{"hour":6,"minute":0,"state":1},{"hour":7,"minute":15,"state":0}]}
```

### Fields:

| Field           | Type    | Description                                                                |
|------------------|---------|----------------------------------------------------------------------------|
| `device_id`      | string  | Unique identifier for the device                                           |
| `interval_min`   | int     | Interval between uplink transmissions (in minutes)                         |
| `output_status`  | int     | Current output state: `0` (off), `1` (on)                                  |
| `schedules`      | array   | List of scheduled actions to set output state at specific times            |

---

## 🔧 Downlink (`/domus01/downlink/<device_id>`)

The `downlink` topic is used to configure the device. Commands are sent in a single JSON object with specific keys.

### Full Payload Example:

```json
{"interval_min":15,"output_status":1,"schedules":[{"hour":6,"minute":0,"state":1},{"hour":7,"minute":15,"state":0},{"hour":8,"minute":30,"state":1}]}
```

### Accepted Fields:

| Field           | Type    | Description                                                                 |
|------------------|---------|----------------------------------------------------------------------------|
| `interval_min`   | int     | Updates the uplink interval                                                 |
| `output_status`  | int     | Immediately sets the output state (`0` or `1`)                              |
| `schedules`      | array   | Replaces current schedule with a new list                                  |

> **Note:** When `schedules` is sent, all previous schedule entries are overwritten.

---

## ✅ Example of `mosquitto_pub` Command

```bash
mosquitto_pub -h localhost -t /domus01/downlink/01 -m '{"interval_min":15,"output_status":1,"schedules":[{"hour":6,"minute":0,"state":1},{"hour":7,"minute":15,"state":0}]}'
```

---

## ℹ️ Notes

- The device supports up to `10` schedule entries.
- Time format is 24-hour (`hour: 0–23`, `minute: 0–59`).
- `state` must be `0` (off) or `1` (on).

---

## 📥 Topics

| Direction | Base Topic                 | Example                        |
|-----------|----------------------------|--------------------------------|
| Uplink    | `/domus01/uplink/<id>`     | `/domus01/uplink/01`           |
| Downlink  | `/domus01/downlink/<id>`   | `/domus01/downlink/01`         |

---

## 📲 Compatibility

Designed for **ESP32** devices using **ESP-IDF**. JSON parsing is implemented in C.
