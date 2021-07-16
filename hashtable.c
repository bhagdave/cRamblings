#include <string.h>
#include <stdlib.h>
#define HASHSIZE 101


struct node {
	struct node *next;
	char *name;
	char *defn;
};

static struct node *hashtab[HASHSIZE];

/* hash: form hash value for string */
unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* get: look for s in hashtab */
struct node *get(char *s)
{
	struct node *newnode;

	for (newnode = hashtab[hash(s)]; newnode != NULL; newnode = newnode->next)
		if (strcmp(s, newnode->name) == 0)
			return newnode;
	return NULL;
}

/* put: put (name, defn) in hashtab */
struct node *put(char *name, char *defn)
{
	struct node *newnode;
	unsigned hashval;

	if ((newnode == get(name)) == NULL) { /* not found */
			newnode = (struct node *) malloc(sizeof(*newnode));
			if (newnode == NULL || (newnode->name = strdup(name)) == NULL)
				return NULL;
			hashval = hash(name);
			newnode->next = hashtab[hashval];
			hashtab[hashval] = newnode;
			} else /* already there */
				free((void *) newnode->defn);
	if ((newnode->defn = strdup(defn)) == NULL)
		return NULL;
	return newnode;
}

int main()
{
	struct node *starter;
	struct node *found;

	starter = put("one", "The Number one");
	starter = put("two", "The number tow");
	starter = put("two", "The number 2");
	starter = put("three", "Three is the magic number");
	starter = put("four", "Four is a mess");
	starter = put("five", "Fiv why?");
	starter = put("tciwwo", "There were six");
	starter = put("six", "I am the real six");
	starter = put("seven", "The magnificient seven");
	starter = put("eight", "The rowdy eight");
	starter = put("nine", "NinetyNine");
	starter = put("ten", "Ten thats round");
	starter = put("eleven", "Eleven - What an age");
	starter = put("twelve", "Twelve is a dozen");
	starter = put("thirteen", "Bakers Dozen");

	found = get("two");

	printf("Found.%s\n", found->defn);

	return 0;
}
