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

