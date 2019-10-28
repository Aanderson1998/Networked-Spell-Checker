#include "spellChecker.h"

	int findWord(char *word) {
    	int found = 0;
	//variable to hold words from dictionary to compare them with word client entered
    	char dictionaryWord[WORD_SIZE];
    	size_t length = strlen(word);
    	word[length - 2] = '\n';
    	word[length - 1] = '\0';
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

