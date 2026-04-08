# Use a lightweight Python image
FROM python:3.10-slim

# Install system utilities needed for the lab:
# - iputils-ping: So the 'ping' command actually exists
# - netcat-openbsd: To allow students to practice reverse shells
RUN apt-get update && apt-get install -y \
    iputils-ping \
    netcat-traditional \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /app

# Install Flask
RUN pip install --no-cache-dir flask

# Copy the server script into the container
COPY server.py .

# Expose the web server port
EXPOSE 8000
EXPOSE 4444

# Run the application
CMD ["python", "server.py"]
