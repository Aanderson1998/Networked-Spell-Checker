#include "spellChecker.h"

	int findWord(char *word) {
	//integer variable that holds value of found. 0 if not in dictionary, 1 if in dictionary
	int found = 0;
	//variable to hold words from dictionary to compare them with word client entered
	char dictionaryWord[WORD_SIZE];
	//variable to hold length of word
	size_t length = strlen(word);
	//placing terminating string characters at end of word
	word[length - 2] = '\n';
	word[length - 1] = '\0';
	//searching for word in dictionary
	while(fgets(dictionaryWord, WORD_SIZE, DICTIONARY) != NULL) {
        	//if the word isn't a match, get next word
		if(strcmp(dictionaryWord, word) != 0) {
			continue;
		}else {
			//found word change variable to 1 meaning its found
			found=1;
		}
	}
	//rewind dictionary, so file pointer points to beginning of dictionary file
	rewind(DICTIONARY);
	//return found variable
	return found;
	}

