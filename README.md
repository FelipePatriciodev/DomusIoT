# DomusIoT
Description: Plataforma de controle remoto e agendamento de dispositivos IoT via MQTT.
from pathlib import Path

DomusIoT é uma plataforma open source para controle remoto e agendamento de dispositivos IoT, com interface web amigável, comunicação via MQTT e arquitetura escalável.

## ✨ Funcionalidades

- Cadastro, edição e remoção de dispositivos
- Ligar e desligar dispositivos remotamente
- Agendamento de horários de funcionamento
- Monitoramento em tempo real via MQTT
- Autenticação segura com JWT
- Interface web com Java + Vaadin
- Firmware para ESP32 com PlatformIO

## 🧱 Tecnologias Utilizadas

- **Backend:** Java, Spring Boot, Vaadin
- **Firmware IoT:** C/C++, ESP32, PlatformIO
- **Broker MQTT:** Mosquitto
- **Testes Automatizados:** Python (Pytest, MQTT)
- **Infraestrutura:** Docker, AWS (EC2, RDS, S3), GitHub Actions
- **Banco de Dados:** MySQL

## 🗂️ Estrutura do Projeto
```text
iot-device-manager/
├── backend/          # Backend Java + Spring Boot + Vaadin
├── firmware/         # Código do dispositivo ESP32 (C/C++)
├── tests/            # Testes automatizados (API, MQTT, integração)
├── infrastructure/   # Docker, Mosquitto, Terraform (AWS)
├── docs/             # Documentação técnica
├── .github/          # CI/CD com GitHub Actions
├── README.md
└── LICENSE
```


## 🚀 Objetivo

Fornecer uma plataforma genérica, extensível e amigável para controle de dispositivos IoT — reduzindo a dependência de apps proprietários e tornando o ecossistema mais aberto e interoperável.

## 🛠️ Como Contribuir

1. Fork o repositório
2. Crie sua branch: `git checkout -b minha-feature`
3. Faça commit das suas alterações: `git commit -m 'feat: minha nova feature'`
4. Envie para o repositório remoto: `git push origin minha-feature`
5. Abra um Pull Request

## 📜 Licença

[MIT License](LICENSE)
