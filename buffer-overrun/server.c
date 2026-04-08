#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

// This buffer is in the Data Segment (Static Address)
char global_buffer[1024]; 

void handle_client(int client_socket) {
    char local_buffer[64];
    char response[128];

    int bytes_received = recv(client_socket, global_buffer, 1024, 0); 
    // asking recv to fill up to 1024 bytes into a 64-byte buffer - BAD!!!
    memcpy(local_buffer, global_buffer, 1024);
    
    if (bytes_received > 0) {
        printf("Received %d bytes. Processing...\n", bytes_received);
        sprintf(response, "Server received your data. Thank you.\0");
        send(client_socket, response, strlen(response), 0);
    }
    
    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Vulnerable Server listening on port %d...\n", PORT);

    while (1) {
        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        handle_client(client_socket);
    }
    return 0;
}

void cleanup_temp_dir() {
    printf("cleaning up temp files");
    system("rm -f /tmp/*");
    fflush(stdout);
}

char *shell = "/bin/sh";

void gadget_farm() {
    __asm__("pop %rdi; ret");
}
