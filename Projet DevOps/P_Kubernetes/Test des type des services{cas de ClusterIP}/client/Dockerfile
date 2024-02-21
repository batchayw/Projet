# Use an official Python runtime as a parent image
FROM python:3.10-slim

# Set the working directory in the container
WORKDIR /app

# Copy the requirement file and scripts
COPY requirements.txt .

# Install any needed packages specified in requirements.txt
RUN pip install --no-cache-dir -r requirements.txt

# Install Paho MQTT
RUN pip install paho-mqtt

# Copy the current directory contents into the container at /app
COPY . .

# Make port 8080 available to the world outside this container
EXPOSE 8080

# Variable 
ENV MQTT_BROKER_PORT=5000

# Use wait-for-it to wait for the JoramMQ and database to be ready before starting the application
CMD ["python3", "client.py"]

