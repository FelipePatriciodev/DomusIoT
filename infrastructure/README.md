# DomusIoT - Infrastructure

This project contains the Docker infrastructure for the **DomusIoT** system, including services for MySQL database, MQTT broker (Eclipse Mosquitto), and the Spring backend.

## Prerequisites

- [Docker](https://docs.docker.com/get-docker/)
- [Docker Compose](https://docs.docker.com/compose/install/)

---

## Project Structure

```
infrastructure/
├── docker-compose.yml
├── .env                  # Must be created by the user
├── mosquitto/            # Must be created by the user
│   ├── config/
│   │   └── mosquitto.conf
│   ├── data/
│   └── log/
```

---

## 1. Creating the `.env` file

Create a `.env` file inside the `infrastructure/` directory with the following content:

```env
MYSQL_DATABASE=mysql_user
MYSQL_ROOT_PASSWORD=mysql_password

SPRING_DATASOURCE_URL=jdbc:mysql://mysql:3306/example
SPRING_DATASOURCE_USERNAME=spring_user
SPRING_DATASOURCE_PASSWORD=spring_pass
```

---

## 2. Setting up the `mosquitto/` directory

Create the directory structure for Mosquitto and add the `mosquitto.conf` configuration file:

```bash
mkdir -p mosquitto/config mosquitto/data mosquitto/log
```

### Basic example for `mosquitto/config/mosquitto.conf`:

```conf
persistence true
persistence_location /mosquitto/data/
log_dest file /mosquitto/log/mosquitto.log

listener 1883
allow_anonymous true
```

---

## 3. Starting the containers

After configuring the `.env` file and Mosquitto structure, run:

```bash
docker-compose up --build
```

This will start the following services:

- `mysql`: MySQL database
- `mosquitto`: MQTT broker
- `backend`: Spring Boot backend application

---

## Notes

- The `.env` file and the `mosquitto/` directory are listed in `.gitignore`, so they are **not versioned**. Make sure to share them manually if needed.
- You can check container logs with `docker-compose logs -f`.

---

## Stopping the containers

```bash
docker-compose down
```

---

Feel free to open an issue or contact the team if you need any help.
