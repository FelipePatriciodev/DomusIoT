<p align="center">
  <img src="docs/icon-DomusIoT.svg" alt="DomusIoT Logo" width="200"/>
</p>

<p align="center">
  <em>DomusIoT is an open source platform for remote control and scheduling of IoT devices. It offers a user-friendly web interface, real-time MQTT communication, and a scalable architecture.</em>
</p>
<p align="center">
  <img src="https://img.shields.io/badge/Java-ED8B00?style=for-the-badge&logo=java&logoColor=white" alt="Java" />
  <img src="https://img.shields.io/badge/Spring_Boot-6DB33F?style=for-the-badge&logo=spring-boot&logoColor=white" alt="Spring Boot" />
  <img src="https://img.shields.io/badge/MySQL-4479A1?style=for-the-badge&logo=mysql&logoColor=white" alt="MySQL" />
  <img src="https://img.shields.io/badge/Next.js-000000?style=for-the-badge&logo=next.js&logoColor=white" alt="Next.js" />
  <img src="https://img.shields.io/badge/Tailwind_CSS-06B6D4?style=for-the-badge&logo=tailwind-css&logoColor=white" alt="Tailwind CSS" />
  <img src="https://img.shields.io/badge/Docker-2496ED?style=for-the-badge&logo=docker&logoColor=white" alt="Docker" />
  <img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++" />
  <img src="https://img.shields.io/badge/C-555555?style=for-the-badge&logo=c&logoColor=white" alt="C" />
</p>


---

## ✨ Features

- ⚙️ Register, edit, and remove devices  
- 🔌 Turn devices on and off remotely  
- 💡 Control 110V/220V loads (e.g., lights, relays)  
- 📡 Real-time monitoring via MQTT  
- 🔐 Secure authentication using JWT  
- 🖥️ Web interface built with NextJS and Tailwind CSS  
- 🔧 Firmware for ESP32 using ESP-IDF  

---

## 🧱 Tech Stack

- **Backend:** ☕ Java, 🌱 Spring Boot  
- **Frontend:** ⚛️ NextJS, 🎨 Tailwind CSS  
- **Firmware:** 🛠️ C/C++, ESP32, ESP-IDF  
- **MQTT Broker:** 🛰️ Mosquitto  
- **Infrastructure:** 🐳 Docker  
- **Database:** 🗄️ MySQL  

---

## 🗂️ Project Structure
```text
DomusIoT/
├── backend/ # Java backend (Spring Boot)
├── frontend/ # NextJS project with Tailwind CSS
├── devices/ # ESP32 firmware code (C/C++)
├── infrastructure/ # Docker, Mosquitto config and project startup files
├── docs/ # Technical documentation
├── README.md
└── LICENSE
```

---

## 🚀 Purpose

Provide a general-purpose, extensible, and user-friendly platform for managing IoT devices — reducing dependency on proprietary systems and promoting an open, interoperable ecosystem.

---

## 🏗️ Starting the System

To start the **web system** and the **MQTT broker**, please check the instructions in the [`infrastructure/README.md`](infrastructure/README.md).

For details about our ESP32 project, see the README located at [`devices/domus_01/README.md`](devices/domus_01/README.md).

For details about our **MQTT protocol**, see the README located at [`devices/domus_01/MQTT_PROTOCOL.md`](devices/domus_01/MQTT_PROTOCOL.md).

---

## 🛠️ How to Contribute

1. Fork this repository  
2. Create a new branch: `git checkout -b my-feature`  
3. Commit your changes: `git commit -m 'feat: my new feature'`  
4. Push to your fork: `git push origin my-feature`  
5. Open a Pull Request  

---

## 📜 License

[MIT License](LICENSE)
