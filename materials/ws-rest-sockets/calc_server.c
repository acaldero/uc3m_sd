   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <unistd.h>
   #include <netinet/in.h>

   #define PORT 8080
   #define BUF_SIZE 4096

   double get_param ( const char *request, const char *name )
   {
         char pattern[1024];
         snprintf(pattern, sizeof(pattern), "%s=", name);

         char *pos = strstr(request, pattern);
         if (!pos) return 0;

         return atof(pos + strlen(pattern));
   }

   void send_response ( int client, int status, const char *status_text, const char *body )
   {
         char response[1024];

         snprintf(response, sizeof(response),
                  "HTTP/1.1 %d %s\r\n"
                  "Content-Type: application/json\r\n"
                  "Content-Length: %zu\r\n"
                  "Connection: close\r\n"
                  "\r\n"
                  "%s",
                  status, status_text, strlen(body), body);

         write(client, response, strlen(response));
   }

   void handle_client ( int client )
   {
         char buffer[BUF_SIZE] = {0};
         char body[1024];

         // read request
         read(client, buffer, sizeof(buffer) - 1);
         double a = get_param(buffer, "a");
         double b = get_param(buffer, "b");

         // send reply
         if (strncmp(buffer, "GET /add", 8) == 0) {
             snprintf(body, sizeof(body), "{\"result\": %.6f}\n", a + b);
             send_response(client, 200, "OK", body);
         }
         else if (strncmp(buffer, "GET /sub", 8) == 0) {
             snprintf(body, sizeof(body), "{\"result\": %.6f}\n", a - b);
             send_response(client, 200, "OK", body);
         }
         else if (strncmp(buffer, "GET /mul", 8) == 0) {
             snprintf(body, sizeof(body), "{\"result\": %.6f}\n", a * b);
             send_response(client, 200, "OK", body);
         }
         else if (strncmp(buffer, "GET /div", 8) == 0) {
             if (b == 0) {
                 send_response(client, 400, "Bad Request", "{\"error\":\"division by zero\"}\n");
             } else {
                 snprintf(body, sizeof(body), "{\"result\": %.6f}\n", a / b);
                 send_response(client, 200, "OK", body);
             }
         }
         else {
             send_response(client, 404, "Not Found", "{\"error\":\"unknown endpoint\"}\n");
         }

         // close client
         close(client);
   }

   int main ( int argc, char *argv[] )
   {
         int ret, opt ;
         int server_fd, client ;
         struct sockaddr_in address ;

         server_fd = socket(AF_INET, SOCK_STREAM, 0);
         if (server_fd < 0) {
             perror("socket");
             return -1;
         }

         // reuse socket
         opt = 1;
         setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

         // bind
         memset(&address, 0, sizeof(address)) ;
         address.sin_family      = AF_INET ;
         address.sin_addr.s_addr = INADDR_ANY ;
         address.sin_port        = htons(PORT) ;

         ret = bind(server_fd, (struct sockaddr *)&address, sizeof(address)) ;
         if (ret < 0) {
             perror("bind") ;
             close(server_fd) ;
             return -1 ;
         }

         // listen
         ret = listen(server_fd, 10) ;
         if (ret < 0) {
             perror("listen") ;
             close(server_fd) ;
             return -1 ;
         }

         printf("Calculator REST service running on http://localhost:%d\n", PORT);

         while (1)
         {
             // accept
             client = accept(server_fd, NULL, NULL);
             if (client < 0) {
                 perror("accept");
                 continue;
             }

             // do-work
             handle_client(client);
         }

         close(server_fd);
         return 0;
   }
