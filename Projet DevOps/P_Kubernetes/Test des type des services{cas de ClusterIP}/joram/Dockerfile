# Utilisation de l'image de base openjdk:8
FROM openjdk:8

# Get JoramMQ
COPY ./jorammq-mqtt-trial-1.18.0.zip /tmp/jorammq-mqtt-1.18.0.zip
RUN cd /tmp \
    && jar -xf jorammq-mqtt-1.18.0.zip \
    && mv jorammq-mqtt-1.18.0 /home/jorammq \
    && rm -f /tmp/jorammq-mqtt-1.18.0.zip \
    && chmod a+x /home/jorammq/bin/*

# Expose ports
EXPOSE 1883/tcp

# Set environment variables
ENV JORAMMQ_HOME=/home/jorammq
ENV PATH=$JORAMMQ_HOME/bin:$PATH

# This environment variable below allows launching the JoramMQ server in foreground, avoiding Docker to exit.
ENV JORAMMQ_IN_DOCKER=true

# Using exec allows passing the SIGTERM to the Java process (pid 1) during container shutdown
WORKDIR $JORAMMQ_HOME
CMD ["bin/jorammq-server"]

HEALTHCHECK --interval=1m --timeout=10s --retries=3 CMD ["bin/jorammq-admin", "-exec", "getStatusInfo", "tcp-1883"] | grep "RUNNING"

