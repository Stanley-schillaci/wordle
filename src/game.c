#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <err.h>
#include <time.h>

#include "utils/alloc.h"


int is_in_string(char c, char *res, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (c == res[i])
            return 1;
    }
    return 0;
}

char *check_word(char *str, char *guess, size_t len)
{

    char *res = xmalloc(sizeof(char) * len + 1);

    for (size_t i = 0; i < len; i++)
    {
        if (str[i] == guess[i])
            res[i] = 'V';
        else if (is_in_string(str[i], guess, len))
            res[i] = 'R';
        else
            res[i] = 'F';
    }
    res[len] = '\0';

    return res;
}


char *getword(void) 
{
    char *line = malloc(100), *linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if(line == NULL)
        return NULL;

    for(;;) 
    {
        c = fgetc(stdin);
        if(c == EOF || c == '\n')
            break;

        if(--len == 0) 
        {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);

            if(linen == NULL) 
            {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}

char *get_random_word(char *filename)
{
    srand(time(NULL));
    size_t r = (rand() % 7103) + 1;
    printf("random : %zu\n", r);

    if (!filename)
        return NULL;


    FILE *f = fopen(filename, "r");
    if (!f)
        return NULL;
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    size_t index = 0;

    while (getline(&line_buf, &line_buf_size, f) != - 1)
    {
        if (index == r)
            return line_buf;
        index++;
    }
    return NULL;
}


void play_game(size_t len)
{
    int round = 1;
    char *guess = get_random_word("data/words5.txt");
    guess[len] = '\0';
    //printf("guess word : %s\n", guess);

    while (1)
    {
        printf("=========================\nRound %i\n", round);
        char *word = getword();
        if (word == NULL)
            errx(1, "[play_game] Cannot read word from terminal\n");

        if (strlen(word) != len)
        {
            printf("you word is %s and its a %lu len | you need a %lu len", word, strlen(word), len);
            printf("Votre mot est invalide\n");
            continue;
        }
        if (!strcmp(word, "sstop"))
        {
            free(word);
            free(guess);
            return;
        }
        if (!strcmp(word, guess))
        {
            printf("Vous avez trouve le mot en %i tentatives\n", round);
            free(word);
            free(guess);
            return;
        }
        else 
        {
            char *check = check_word(word, guess, len);
            printf("%s\n",check);
            free(check);
            free(word);
        }
        round++;
    }
}


























