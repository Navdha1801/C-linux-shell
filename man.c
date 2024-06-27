#include "headers.h"

void parsehtml(const char *str, size_t l) {

    int Tag = 0;  
    size_t start = 0;      

    for (size_t i = 0; i < l; i++) {
        if (str[i] == '<') {
            Tag = 1;
        } else if (str[i] == '>') {
            Tag = 0;
            start = i + 1;
        } else if (Tag==0) {
            putchar(str[i]);
        }
    }
    putchar('\n');
}
size_t write_callback(char *ptr, size_t size, size_t member, void *userdata) {
    parsehtml(ptr, size * member);
    return size * member;
}

void fetchManPage(const char *command, int append, char *filename, char *token) {
    struct addrinfo hint, *res, *rp;
    memset(&hint, 0, sizeof(struct addrinfo));
    hint.ai_family = AF_UNSPEC;
    hint.ai_socktype = SOCK_STREAM;

    if (getaddrinfo("man.he.net", NULL, &hint, &res) != 0) {
        fprintf(stderr, "getaddrinfo: DNS resolution failed\n");
        return;
    }

    char ipstr[INET6_ADDRSTRLEN];
    void *addr;

    for (rp = res; rp != NULL; rp = rp->ai_next) {
        if (rp->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
            addr = &(ipv4->sin_addr);
            inet_ntop(rp->ai_family, addr, ipstr, sizeof(ipstr));
            break;
        }
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    if (inet_pton(AF_INET, ipstr, &(server_addr.sin_addr)) <= 0) {
        perror("inet_pton");
        close(sockfd);
        return;
    }

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        close(sockfd);
        return;
    }

    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error initializing libcurl\n");
        return;
    }

    char command_url[100000];
    snprintf(command_url, sizeof(command_url), "http://%s:%d/?topic=%s&section=all", ipstr, 80, command);

    curl_easy_setopt(curl, CURLOPT_URL, command_url);

    // Configure CURLOPT_WRITEFUNCTION and CURLOPT_WRITEDATA based on the append flag
     FILE *outputFile = NULL;
    if (append == 0) {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);  // Output to terminal
    } else {
        //FILE *outputFile = NULL;
        if (strcmp(token, ">>") == 0) {
            // Append mode
            outputFile = fopen(filename, "a");
        } else {
            // Overwrite mode
            outputFile = fopen(filename, "w");
        }

        if (outputFile == NULL) {
            fprintf(stderr, "Error opening file: %s\n", filename);
            curl_easy_cleanup(curl);
            close(sockfd);
            return;
        }

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);  // Disable default write function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, outputFile);  // Output to file
    }

    CURLcode curl_res = curl_easy_perform(curl);
    if (curl_res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curl_res));
    }

    // Cleanup
    curl_easy_cleanup(curl);
    if (append == 1) {
        fclose(outputFile);  // Close the file if opened in append mode
    }
    close(sockfd);
}