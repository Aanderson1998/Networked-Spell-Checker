#include "spellChecker.h"

	int main(int argc, char *argv[]) {
	//no arguments passed means use default dictionary and socket
	if (argc == 1) {
		if (!(DICTIONARY = fopen(DEFAULT_DICTIONARY, "r"))) {
			perror("Could not open dictionary");
			exit(EXIT_FAILURE);
		}
	PORT = DEFAULT_SOCKET;
	}
	//have one argument meaning it is a dictionary or socket, figure out which
	else if (argc == 2) {
	char *ptr;
        //check to see if it is a port first. If it does not work
        if (!(PORT = (int) strtol(argv[1], &ptr, 10))) {
            	//assume it's a dictionary
		if (!(DICTIONARY = fopen(argv[1], "r"))) {
                	perror("Unknown dictionary");
                	exit(EXIT_FAILURE);
            		}
            	PORT = DEFAULT_SOCKET;
        	}
    	}
    	//passed specific dictionary and socket
    	else {
        	if (!(DICTIONARY = fopen(argv[1], "r"))) {
            		perror("Could not open dictionary");
            		exit(EXIT_FAILURE);
        	}
        	char *ptr;
        	if (!(PORT = (int) strtol(argv[2], &ptr, 10))) {
            		perror("Could not open socket");
            		exit(EXIT_FAILURE);
        	}
        	//if the port isn't a legal port
        	if (PORT < 1024 || PORT > 65535) {
            		perror("Port entered cannot be used (Must be between 1025 & 65534)");
            		exit(EXIT_FAILURE);
        	}
    	}
	int listenSocket;
    	if ((listenSocket = openListenfd(PORT)) < 0) {
        	perror("Couldn't open listening socket");
        	exit(EXIT_FAILURE);
    	}
	//print listening socket to screen
	printf("Listening Socket: %d\n", PORT);
	//create server struct
	server *server = malloc(sizeof(*server));
	//initialize server
	initServer(server);
	//create worker thread pool
	pthread_t workers[NUM_WORKERS];
	for (int i = 0; i < NUM_WORKERS; i++) {
		pthread_create(&workers[i], NULL, workerThread, (void *)server);
	}
	//create logger thread
	pthread_t logger;
	pthread_create(&logger, NULL, loggerThread, (void *) server);
	//open log file. print error message if problem opening file
	if ((LOG = fopen("log.txt", "w+")) == NULL) {
		printf("Error opening log file");
		exit(0);
	}
	//create socket variable for client connections
    	int socket;
	//welcome message to send to client when connected
	char *str = "Hello you are connected to the spell checker network. Please type in a word to see if it is spelled correctly\nTo disconnect please press escape button \n";
	//connect to client
	while (1) {
		if ((socket = accept(listenSocket, NULL, NULL)) < 1) {
			perror("Unable to connect client");
			break;
		}
	printf("\nClient is connected. Socket descriptor: %d\n", socket);
	//send message that client is connected and can start using spell checker
	send(socket, str, strlen(str), 0);
	//lock job_mutex
	pthread_mutex_lock(&server->job_mutex);
	//check if job queue is full. If it is put a wait on job_not_full condition variable
	while (server->job_count == MAX_BUF_SIZE) {
		pthread_cond_wait(&server->job_not_full, &server->job_mutex);
		}
	//add job to job queue
	insertJob(server, socket);
	//signal job_not_empty condition variable
	pthread_cond_signal(&server->job_not_empty);
	//unlock job_mutex
	pthread_mutex_unlock(&server->job_mutex);
	}
	return 0;
	}


