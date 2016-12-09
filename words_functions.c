#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define NODE_SIZE 27

typedef struct TreeNode
{
	struct 	TreeNode *ptrArray[NODE_SIZE];
	int 	end;
} treeNode;

//Converts a char to an index, ignoring caps
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

//Checks if the word contains any accents. If is does, it is not added to the dictionary
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

//Replaces all puntuation exept ' in read word by \0 to check them without , ; .
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

//Adds a word to the tree and sets the end var to 1 for the last letter
void add_word(treeNode *baseNode, char *word)
{
	if (*word != '\0')
	{
		if ((*baseNode).ptrArray[char_to_index(*word)] == NULL)
		{
			(*baseNode).ptrArray[char_to_index(*word)] = calloc(1, sizeof(treeNode));
			if (*(word + 1) == '\0')
				(*((*baseNode).ptrArray[char_to_index(*word)])).end = 1;
			add_word((*baseNode).ptrArray[char_to_index(*word)], word + 1);
		}
		else
		{
			if (*(word + 1) == '\0')
				(*((*baseNode).ptrArray[char_to_index(*word)])).end = 1;
			add_word((*baseNode).ptrArray[char_to_index(*word)], word + 1);
		}
	}
}

//Checks if a word is in the tree
int check_word(treeNode *baseNode, char *word)
{
	if (*word != '\0')
	{
		if ((*(word + 1) == '\0') && ((*baseNode).ptrArray[char_to_index(*word)] != NULL) && (((*((*baseNode).ptrArray[char_to_index(*word)])).end == 1)))
			return 1;
		else if ((*baseNode).ptrArray[char_to_index(*word)] != NULL)
			return check_word((*baseNode).ptrArray[char_to_index(*word)], word + 1);
		else
			return 0;
	}
	else
		return 0;
}


//Free all callocs used to create the tree
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
