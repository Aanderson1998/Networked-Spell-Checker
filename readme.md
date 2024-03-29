# Networked Spell-Checker
A multi-threaded spell-checking server implemented over a local network
___
The program is a multithreaded server that performs spell checking on demand for multiple clients

Program can take 0 to 2 arguments. The arguments can be the port number, dictionary file, both, or none. If one or both of the things are not passed as arguments then the default version will be used

Program takes word as input from connected client and checks if the word is in the dictionary file

If it is in the file it is considered to be spelled properly. If not, it's considered to be misspelled.

When clients connect to the server their socket number is placed in job queue

The server has a fixed number of worker threads that can each take a job from the job queue and execute them simultaneously 

The worker threads then write these results to a log queue

There is also one logger thread which takes the contents of the log queue and writes them to a file which can be viewed later after server program is finished

Because multiple worker threads are accessing same job queue and logger thread and worker threads are accessing log queue, synchronization must be implemented using mutex's and condition vairables

Created job and log mutex variables to lock and unlock access to job and log queues. This allows only one thread to access the queues at a time, enabling mutual exclusion so data is not corrupted

Also created four condition variables job_not_full, job_not_empty, log_not_full, and log_not_empty to keep track of slots in queues

If all slots are full in either job or log queue then there is a wait on the job_not_full or log_not_full condition variables. Meaning nothing can be added to queues until these conditions are met (or signaled)

If all slots are empty in either job or log queue then there is a wait on the job_not_empty or job_not_full condition variables. Meaning nothing can be removed from queues until these conditions are met (or signaled)

Adding mutex and condition variables to multithreaded server ensures synchronization and mutual exclusion, which allows for accurate results and data when using program 


## Usage
To use program client must open new terminal and connect to localhost of server. To do this client types in ssh telnet localhost PORT. PORT is the listening socket of the server which displays on the screen of the server program

When client connects the server will send a greeting message and ask for word input. Clients can then begin using the spell checker

To disconnect you must press the escape key on the keyboard and then enter. From there you will get a goodbye message, saying you are done using the spell checker

While you use the spell checker, you type in a word into the prompt and it will respond back with either 'OK' meaning it was spelled correctly, or 'MISSPELLED' meaning it was not spelled correctly

