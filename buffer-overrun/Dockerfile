# force x86_64 architecture to bypass Apple Silicon hardware protections
FROM --platform=linux/amd64 ubuntu:24.04

RUN apt-get update && apt-get install -y gcc libc6-dev-i386 netcat-traditional

COPY server.c .

# Disable all protections: No canary, executable stack, no position-independent code
RUN gcc -fno-stack-protector -z execstack -no-pie server.c -o server

EXPOSE 4444
EXPOSE 8080
CMD ["./server"]
