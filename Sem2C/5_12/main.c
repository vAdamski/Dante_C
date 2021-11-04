#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char** failed_to_allocate_memory(char** p, char* b, size_t size)
{
    free(b);
    if(size)
        for(size_t i = 0; i < size; i++)
            free(*(p+i));
    free(p);
    return NULL;
}

char** split_words(const char* text)
{
    if (text == NULL)
        return NULL;

    char* buffer = NULL;
    char** result = NULL;
    unsigned int result_size = 0;
    unsigned int buffer_size = 0;

    int trigger = 1;
    while(trigger)
    {
        if(*(text++) == '\0')
            trigger = 0;

        char c = *(text-1);
        if(isalpha(c))
        {
            if(!buffer_size) // edge-case
            {
                char* tmp = NULL;
                if((tmp = realloc(buffer, sizeof(char)*2)) == NULL)
                    return failed_to_allocate_memory(result, buffer, result_size);
                else buffer = tmp;

                buffer_size += 2;
            }
            else
            {
                char* tmp = NULL;
                if((tmp = realloc(buffer, sizeof(char)*(++buffer_size))) == NULL)
                    return failed_to_allocate_memory(result, buffer, result_size);
                else buffer = tmp;
            }

            *(buffer+(buffer_size-2)) = c;
            *(buffer+(buffer_size-1)) = '\0';
        }
        else
        {
            if(!buffer_size)
                continue;
            
            char** tmp = NULL;
            if((tmp = realloc(result, sizeof(char*)*(++result_size))) == NULL)
                return failed_to_allocate_memory(result, buffer, --result_size);
            else result = tmp;

            *(result+result_size-1) = buffer;
            buffer = NULL;
            buffer_size = 0;
        }
    }

    if(result_size)
    {
        char** tmp = NULL;
        if((tmp = realloc(result, sizeof(char*)*(++result_size))) == NULL)
            return failed_to_allocate_memory(result, buffer, --result_size);
        else result = tmp;

        *(result+result_size-1) = NULL;
    }

    return result;
}

int sort_words(char** words)
{
    if(words == NULL)
        return 1;
    
    if(*words==NULL)return 0;
    int changed =1;
    while(changed){
    changed=0;
    for(int i=0;*(words+i+1)!=NULL;i++){
    	if(strcmp(*(words+i),*(words+i+1))>0){
    	char*t=*(words+i);
    	*(words+i)=*(words+i+1);
    	*(words+i+1)=t;
    	changed=1;
    	}
    }
    }

        
    return 0;
}

void destroy(char** words)
{
    char** p = words;

    while(*(p++) != NULL)
        free(*(p-1));

    free(words);
}

int main()
{
    char *buffer=malloc(1000);
    if(buffer==NULL){
    	printf("Failed to allocate memory");
    	return 8;
    }
    printf("Enter text:");
    scanf("%999[^\n]",buffer);

    char** ret = split_words(buffer);
    int ok=0;
    for(int i=0;*(buffer+i)!='\0';i++){
    	if(isalpha(*(buffer+i))){
    		ok=1;
    		break;
    	}
    }
    if(!ok){
    	printf("Nothing to show");
    	free(buffer);
    	return 0;
    }
    if(ret == NULL)
    {
        printf("Failed to allocate memory");
        free(buffer);
        return 8;
    }

    sort_words(ret);
    for(int i=0;*(ret+i)!=NULL;i++){
	    printf("%s\n",*(ret+i));
    }
    	free(buffer);
    destroy(ret);
    return 0;
}
