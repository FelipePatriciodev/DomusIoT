FROM eclipse-temurin:17-jdk-alpine
WORKDIR /app

# Copy fristh the wrapper and pom.xml to approve the cache
COPY .mvn/ .mvn
COPY mvnw pom.xml ./

RUN chmod +x mvnw && ./mvnw dependency:go-offline

# Code
COPY src/ src/
COPY src/main/resources/ src/main/resources/

RUN ./mvnw clean package -DskipTests

EXPOSE 8080
CMD ["java", "-jar", "target/backend-0.0.1-SNAPSHOT.jar"]
