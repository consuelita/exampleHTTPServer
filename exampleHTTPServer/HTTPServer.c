//
//  HTTPServer.c
//  exampleHTTPServer
//
//  Created by Adelita Schule on 5/31/18.
//  Copyright © 2018 Operator Foundation. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Socket Headers
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

// If you run this in xcode let's make sure we can find the html file
//#define MAC_OS_X
//
//#ifdef MAC_OS_X
//#define INV_FILE /Volume/.../inventory.data
//#else
//#define INV_FILE inventory.data
//#endif

/// Note: This is a very basic implementaion that does not take into account the different kinds of HTTP requests you can get
/// This implementation assumes a GET request

int main()
{
    /// Body
    // The file pointer to hold the data we will send as the body of the response
    FILE *html_data;
    
    // Open an html file and read it
    html_data = fopen("index.html"/*the file to open*/, "r"/*w = write to file, r = read file*/);
    
    // String to store the html of the file
    char response_data[1024];
    
    //Read the file into the string variable
    fgets(response_data/*where to write the data to*/, 1024/*size of the result*/, html_data/*where we are reading the data from*/);
    printf("html data found: %s", response_data);
    
    /// Header
    // Create the first line of the response (the header)
    char http_response[2048] = "HTTP/1.1 200 OK\r\n\n";
    
    /// Response
    // Add the response data to the http_response which currently contains the header line
    strcat(http_response, response_data);
    printf("Created response data: \n%s", http_response);
    
    /// Do the business
    // Create a socket
    int server_socket;
    server_socket = socket(AF_INET/*Internet Domain*/, SOCK_STREAM/*TCP*/, 0/*No Flags*/);
    
    // Define the address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY; // Any address on the local machine
    
    // Bind the address to a port
    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_socket));
    
    // Listen for connections on the socket
    listen(server_socket, 5/*Number of connections allowed in queue*/);
    
    // Placeholder for the client socket
    int client_socket;
    
    // Infinite while loop because we want the server to continue to respond to client requests
    while (1) // While true
    {
        // Accept a connection on the client socket but do not save the client address information
        client_socket = accept(server_socket, NULL, NULL);
        
        // Send some data back to the client
        send(client_socket, http_response, sizeof(http_response), 0/*No Flags*/);
        
        close(client_socket);
    }
    
    return 0;
}







