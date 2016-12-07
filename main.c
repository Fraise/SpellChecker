#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define NODE_SIZE 33

typedef struct TreeNode
{
	uint8_t *ptrArray[NODE_SIZE];

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
	else if (c == 'é')
		return 26;
	else if (c == 'è')
		return 27;
	else if (c == 'à')
		return 28;
	else if (c == 'ù')
		return 29;
	else if (c == 'ê')
		return 30;
	else if (c == 'ï')
		return 31;
	else if (c == ''')
		return 32;
	else
		return -1;
}

int main(int argc, char *argv[])
{
	FILE *dfile, *tfile;
	treeNode baseNode
	char *dictionary = NULL, *text = NULL, word[30], c;
	
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
	{
		printf("%s\n", word);
	}
	
	return 0;
}
