#include "spellChecker.h"

	int findWord(char *word) {
    	int found = 0;
	//variable to hold words from dictionary to compare them with word client entered
    	char dictionaryWord[WORD_SIZE];
    	//get rid of '\r' first (words in dictionary already have '\n', saving time)
    	size_t len = strlen(word);
    	word[len - 2] = '\n';
    	word[len - 1] = '\0';
    	while(fgets(dictionaryWord, WORD_SIZE, DICTIONARY) != NULL) {
        	//if the word isn't a match, get next word
        	if(strcmp(dictionaryWord, word) != 0) {
            		continue;
        	}
        	else {
            		rewind(DICTIONARY);
            		found=1;
        	}
    	}
    	rewind(DICTIONARY);
    	return found;
	}

