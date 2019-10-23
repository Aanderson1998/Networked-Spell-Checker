#include "spellChecker.h"

    int main(int argc, char *argv[]) {
    //no arguments were passed so use default dictionary and default port
    if (argc == 1) {
        if (!(DICTIONARY = fopen(DEFAULT_DICTIONARY, "r"))) {
            perror("Dictionary");
            exit(EXIT_FAILURE);
        }
        PORT = DEFAULT_SOCKET;
    }
    //passed one argument which means it can be either port or dictionary. Must figure out which one and then put other one as default
    else if (argc == 2) {
    char *end;
    //check to see if it is an int, if it is then that is the port. if the first argument isn't an int then it must be the dictionary
        if (!(PORT = (int) strtol(argv[1], &end, 10))) {
            //open dictionary
            if (!(DICTIONARY = fopen(argv[1], "r"))) {
                perror("Unknown dictionary");
                exit(EXIT_FAILURE);
            }
            //use default socket for the port (if dictionary was passed)
            PORT = DEFAULT_SOCKET;
        }
    }
    //had two arguments so one argument is dictionary and other is port
    else {
        if (!(DICTIONARY = fopen(argv[1], "r"))) {
            perror("Unknown dictionary");
            exit(EXIT_FAILURE);
        }
        char *end;
        if (!(PORT = (int) strtol(argv[2], &end, 10))) {
            perror("Issue reading socket");
            exit(EXIT_FAILURE);
        }
        //check to make sure it is legal
        if (PORT < 1024 || PORT > 65535) {
            perror("illegal port");
            exit(EXIT_FAILURE);
    }
    }
    printf("Dictionary in use is %s\n", argv[1]);
    printf("Listening socket is port %d\n", PORT);

    //create a listening socket on the specified port
    int listen_socket;
    if ((listen_socket = open_listenfd(PORT)) < 0) {
        perror("Couldn't open listening socket");
        exit(EXIT_FAILURE);
    }


    int connected_socket;

    char *greeting = "Hello! Type a word to spell-check it.\n";

    //start accepting clients
    while (1) {
        if ((connected_socket = accept(listen_socket, NULL, NULL)) < 1) {
            perror("Can't connect to client");
            break;
        }
        puts("Client connected.");

        //send greeting message to client with instructions
        send(connected_socket, greeting, strlen(greeting), 0);
    }
    }
