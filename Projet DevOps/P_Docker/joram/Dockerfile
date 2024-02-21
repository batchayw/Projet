# Utilisation de l'image de base openjdk:8
FROM openjdk:8

# Get JoramMQ
COPY ./jorammq-mqtt-trial-1.18.0.zip /tmp/jorammq-mqtt-1.18.0.zip
RUN cd /tmp \
    && jar -xf jorammq-mqtt-1.18.0.zip \
    && mv jorammq-mqtt-1.18.0 /home/jorammq \
    && rm -f /tmp/jorammq-mqtt-1.18.0.zip \
    && chmod a+x /home/jorammq/bin/*

# Get sed command
COPY jorammq_org.xml /home/jorammq

# Affiche le contenu du répertoire du conteneur avant et après la copie du fichier
RUN ls -al
# Expose ports
# EXPOSE 1883/tcp

# Set environment variables
ENV MQTT_BROKER_PORT=$MQTT_BROKER_PORT
ENV JORAMMQ_HOME=/home/jorammq
ENV PATH=$JORAMMQ_HOME/bin:$PATH

# This environment variable below allows launching the JoramMQ server in foreground, avoiding Docker to exit.
ENV JORAMMQ_IN_DOCKER=true

WORKDIR $JORAMMQ_HOME

# Exécution
CMD ls -al && \
    sed -e "s/%MQTT_BROKER_PORT%/${MQTT_BROKER_PORT}/g" /home/jorammq/jorammq_org.xml > /home/jorammq/conf/jorammq.xml && \
    cat /home/jorammq/conf/jorammq.xml && \
    exec /bin/bash bin/jorammq-server

