#include "spellChecker.h"

	//function to insert job
        void insertJob(server *server, int socket) {
        //printf("%d\n", socket);
        //insert into client buffer
        jobs[server->job_rear] = socket;
        //increment the job_rear
        server->job_rear = (++server->job_rear) % MAX_BUF_SIZE;
        //increment the job_count
        ++server->job_count;
        }


	//function to remove job
	int remove_job(server *server) {
        int socket = jobs[server->job_front];
        jobs[server->job_front] = 0;
        server->job_front = (++server->job_front) % MAX_BUF_SIZE;
        --server->job_count;
        return socket;
        }
