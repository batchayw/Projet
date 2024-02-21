# Use an official Python runtime as a parent image
FROM python:3.10-slim

# Set the working directory in the container
WORKDIR /app

# Copy the requirement file
COPY requirements.txt .

# Install any needed packages specified in requirements.txt
RUN pip install --no-cache-dir -r requirements.txt

# Install Paho MQTT
RUN pip install paho-mqtt

# Copy the current directory contents into the container at /app
COPY . .

# Make port 5000 available to the world outside this container
EXPOSE 5000

# Set environment variables
ENV MQTT_BROKER_PORT=1883

# Use wait-for-it to wait for the JoramMQ and database to be ready before starting the application
CMD ["python3", "server.py"]
