# Aryanna Anderson, 3207- Introduction to System Programming and Operating Systems Project 3

output:
	gcc initServer.c logFunctions.c jobFunctions.c findWord.c workerThread.c loggerThread.c openListenfd.c main.c -pthread -o spellCheck
initServer.o: initServer.c spellChecker.h
	gcc -c initServer.c
logFunctions.o: logFunctions.c spellChecker.h
	gcc -c logFunctions.c
jobFunctions.o: jobFunctions.c spellChecker.h
	gcc -c jobFunctions.c 
findWord.o: findWord.c spellChecker.h
	gcc -c findWord.c
workerThread.o: workerThread.c spellChecker.h
	gcc -c workerThread.c
loggerThread.o: loggerThread.c spellChecker.h
	gcc -c loggerThread.c
openListenfd.o: openListenfd.c spellChecker.h
	gcc -c openListenfd.c
main.o: main.c spellChecker.h
	gcc -c main.c
clean:
	rm *.o spellCheck

