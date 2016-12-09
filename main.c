#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#include "words_functions.h"

#define RED "\x1B[31m"
#define RESET "\x1B[0m"

int main(int argc, char *argv[])
{
	FILE *dfile, *tfile;
	treeNode *baseNode;
	char *dictionary = NULL, *text = NULL, word[30], punc_word[30], c;
	
	baseNode = calloc(1, sizeof(treeNode));
	
	while ((c = getopt (argc, argv, "d:")) != -1)
	{
		switch (c)
		{
			case 'd':
				dictionary = optarg;
				break;
			case '?':
				fprintf(stderr, "Usage: %s [-d dictionary] file\n", argv[0]);
				return 1;
			default:
				fprintf(stderr, "Usage: %s [-d dictionary] file\n", argv[0]);
				return 1;
		}
	}
	
	if ((optind >= argc))
	{
        fprintf(stderr, "Usage: %s [-d dictionary] file\n", argv[0]);
        return 1;
    }
    
    if (dictionary == NULL)
    {
    	if (access("/usr/share/dict/words", R_OK) == 0)
    	{
			fprintf(stdout, "No dictionary file specified, using /usr/share/dict/words.\n\n");
			dictionary = "/usr/share/dict/words";
    	}
    	else
    	{
    		fprintf(stderr, "Can't access default dictionary file, you must supply you own. Usage: %s [-d dictionary] file\n", argv[0]);
    		return 1;
    	}
    }
    
    text = argv[argc - 1];
    
    dfile = fopen(dictionary, "r");

	while (fscanf(dfile, "%s", word) != EOF)
		if (check_word_ok(word))
			add_word(baseNode, word);

	fclose(dfile);
	
	tfile = fopen(text, "r");
	
	while (fscanf(tfile, "%s", word) != EOF)
	{
		memcpy(punc_word, word, 30);
		remove_punctuation(word);
		
		if (check_word_ok(word))
		{
			if (!check_word(baseNode, word))
				printf(RED "%s " RESET, punc_word);
			else
				printf("%s ", punc_word);
		}
	}
	
	fclose(tfile);
	
	printf("\n\n");
	
	free_tree(baseNode);

	return 0;
}
