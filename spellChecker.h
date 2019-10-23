//libraries used throughout program
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <pthread.h>


//constant for default socket port
#define DEFAULT_SOCKET 3999
//constant for default dictionary
#define DEFAULT_DICTIONARY "dictionary.txt"
//constant for maximum word size
#define WORD_SIZE 128
//constant for maximum buffer size
#define MAX_BUF_SIZE 5


// global variable. file pointer to dictionary file
FILE *DICTIONARY;
//global variable. file pointer to log file
FILE *LOG;
//global integer variable for port that users connect to to us spellcheck
int PORT;
//global integer array to hold clients
int jobs[MAX_BUF_SIZE];
//global pointer array to hold client logged data
char *logs[MAX_BUF_SIZE];


//struct for server
typedef struct {
char **log_buf;
int *job_buf;
int job_len;
int log_len;
int job_count;
int log_count;
int job_front;
int job_rear;
int log_front;
int log_rear;
pthread_mutex_t job_mutex;
pthread_mutex_t log_mutex;
pthread_cond_t job_not_empty;
pthread_cond_t job_not_full;
pthread_cond_t log_not_empty;
pthread_cond_t log_not_full;
}server;


//function prototypes
void server_init(server *server, int job_len, int log_len);
void server_deinit(server *server);
void server_insert_log(server *server, char *item);
void server_insert_job(server *server, int item);
int server_remove_log(server *server, char **server_buf);
int server_remove_job(server *server);
int open_listenfd(int port);
