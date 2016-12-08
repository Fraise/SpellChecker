#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define NODE_SIZE 27

typedef struct TreeNode
{
	struct TreeNode *ptrArray[NODE_SIZE];
	int end;
} treeNode;

void init_treeNode(treeNode *tn)
{
	int i;
	
	for (i = 0; i < NODE_SIZE; i++)
		(*tn).ptrArray[i] = NULL;
}

int char_to_index(char c)
{
	if ((c >= 65) && (c <= 90))
		return c - 65;
	else if ((c >= 97) && (c <= 122))
		return c - 97;
	else if (c == '\'')
		return 26;
	else
		return -1;
}

int check_word_ok(char *word)
{
	int i = 0;
	while (word[i] != '\0')
	{
		if (char_to_index(word[i]) < 0)
			return 0;
			
		i++;
	}
	
	return 1;
}

void remove_punctuation(char *word)
{
	int i = 0;
	while (word[i] != '\0')
	{
		if (char_to_index(word[i]) < 0)
			word[i] = '\0';
			
		i++;
	}
}

void add_word(treeNode *baseNode, char *word)
{
	if (*word != '\0')
	{
		if ((*baseNode).ptrArray[char_to_index(*word)] == NULL)
		{
			(*baseNode).ptrArray[char_to_index(*word)] = calloc(1, sizeof(treeNode));
			add_word((*baseNode).ptrArray[char_to_index(*word)], word + 1);
		}
		else
		{
			add_word((*baseNode).ptrArray[char_to_index(*word)], word + 1);
		}
	}
}

int check_word(treeNode *baseNode, char *word)
{
	//int word_ok;
	if (*word != '\0')
	{
		//printf("checking letter : %c\n", *word);
		if ((*baseNode).ptrArray[char_to_index(*word)] != NULL)
			check_word((*baseNode).ptrArray[char_to_index(*word)], word + 1);
		else
			return 0;
	}
	else
		return 1;
}

void free_tree(treeNode *baseNode)
{
	int i;
	
	for (i = 0; i < NODE_SIZE; i++)
	{
		if ((*baseNode).ptrArray[i] != NULL)
			free_tree((*baseNode).ptrArray[i]);
	}
	
	free(baseNode);
}


int main(int argc, char *argv[])
{
	FILE *dfile, *tfile;
	treeNode *baseNode;
	char *dictionary = NULL, *text = NULL, word[30], c;
	
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
    	fprintf(stdout, "No dictionary file specified, using /usr/share/dict/words.\n");
    	dictionary = "/usr/share/dict/words";
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
		remove_punctuation(word);
		
		//printf("word read : %s, check word : %d\n", word, check_word(baseNode, word));
		
		if (check_word_ok(word))
			if (!check_word(baseNode, word))
				printf("Mistake in word : %s\n", word);
	}
	
	fclose(dfile);
	
	free_tree(baseNode);

	return 0;
}
