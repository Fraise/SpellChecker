#define NODE_SIZE 27

typedef struct TreeNode
{
	struct 	TreeNode *ptrArray[NODE_SIZE];
	int 	end;
} treeNode;

int char_to_index(char c);
int check_word_ok(char *word);
int check_word(treeNode *baseNode, char *word);

void remove_punctuation(char *word);
void add_word(treeNode *baseNode, char *word);
void free_tree(treeNode *baseNode);
