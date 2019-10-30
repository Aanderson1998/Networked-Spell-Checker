#include "spellChecker.h"

	int main(int argc, char *argv[]) {
    	//no arguments passed means use default dictionary and socket
    	if (argc == 1) {
        	if (!(DICTIONARY = fopen(DEFAULT_DICTIONARY, "r"))) {
            		printf("could not open dictionary\n");
            		exit(0);
        	}
        PORT = DEFAULT_SOCKET;
    	}
    	//have one argument meaning it is a dictionary or socket, figure out which
    	else if (argc == 2) {
        char *ptr;
        //if the first argument isn't an int
        if (!(PORT = (int) strtol(argv[1], &ptr, 10))) {
            //assume it's a dictionary
            if (!(DICTIONARY = fopen(argv[1], "r"))) {
                	printf("Could not open dictionary\n");
                	exit(0);
            	}
            PORT = DEFAULT_SOCKET;
        }
	//passed specific dictionary and socket
    	}else {
        	if (!(DICTIONARY = fopen(argv[1], "r"))) {
            		printf("Could not open dictionary\n");
            		exit(0);
        	}
        char *ptr;
        if (!(PORT = (int) strtol(argv[2], ptr, 10))) {
            printf("Could not open socket\n");
            exit(0);
        }
        //check to see if port is legal
        if (PORT < 1024 || PORT > 65535) {
        	perror("Port is not in range (Must be between 1025 & 65534)");
            	exit(0);
        	}
    	}
   	printf("Dictionary:\t%s\n", argv[1]);
    	printf("Socket:\t%d\n", PORT);
    	//open listening socket on the port
    	int listen_socket;
    	if ((listen_socket = openListenfd(PORT)) < 0) {
        	printf("Couldn't open listening socket");
        	exit(0);
    	}
	//create server struct
    	server *server = malloc(sizeof(*server));
    	//initialize the server. Send to initialize server method
    	initServer(server);
    	//create worker thread pool
    	pthread_t workers[MAX_BUF_SIZE];
    	for (int i = 0; i < MAX_BUF_SIZE; i++) {
        pthread_create(&workers[i], NULL, worker_thread, (void *)server);
    	}
    	//create logger thread
    	pthread_t logger;
    	pthread_create(&logger, NULL, logger_thread, (void *) server);
    	//create socket variable for client connections
    	int connected_socket;
    	char *str = "Hello you are connected to the spell checker network. Please type in a word to see if it is spelled correctly.\n";
    	//accepting client jobs
    	while (1) {
        	if ((connected_socket = accept(listen_socket, NULL, NULL)) < 1) {
            		perror("Unable to connect client");
            		break;
        	}
        printf("Client is connected\n");
	//send message that client is connected and can start using spell checker
        send(connected_socket, str, strlen(str), 0);
        //lock job queue
        pthread_mutex_lock(&server->job_mutex);
        //check if job queue is full. Using circular array , so full when read == write && maxed out elements
        while (server->job_front == server->job_rear && server->job_count == MAX_BUF_SIZE) {
            pthread_cond_wait(&server->job_not_full, &server->job_mutex);
        }
        //add client socket to queue
        insertJob(server, connected_socket);
        //signal workers that there is a client needing assistance
        pthread_cond_signal(&server->job_not_empty);
        //unlock job queue
        pthread_mutex_unlock(&server->job_mutex);
    	}
    	return 0;
	}

