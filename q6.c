#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Holds the current search bounds for binary search */
struct Range{
        int low;
        int high;
};

/* Binary searches a sorted dictionary for key; returns true if found */
bool binarySearch(char* dictionary[], int n, char* key){
        struct Range r = {0, n-1};
        while(r.low <= r.high){
                int mid = r.low + (r.high - r.low)/2;  /* avoids overflow */
                printf("Remaining search indices %d to %d\n", r.low, r.high);
                printf("Checking word at index %d: %s\n", mid, dictionary[mid]);
                
                int cmp = strcmp(dictionary[mid], key);
                if(cmp == 0) return true;        /* exact match */
                else if(cmp < 0) r.low = mid+1;  /* key is in right half */
                else r.high = mid-1;             /* key is in left half */
        }
        return false;  /* key not found */
}

int main(){
        /* Sorted list of words (must stay sorted for binary search to work) */
        const char* words[] = {"apple","banana","cherry","date","fig","grape","kiwi","mango","orange","peach"};
        int n = sizeof(words)/sizeof(words[0]);

        /* Copy words into a heap-allocated dictionary */
        char** dictionary = malloc(n * sizeof(char*));
        for(int i=0;i<n;i++){
                dictionary[i] = malloc(strlen(words[i])+1);
                strcpy(dictionary[i], words[i]);
        }

        /* Read search term from user and perform binary search */
        char word[50];
        printf("Enter a word to search: ");
        scanf("%49s", word);
        if(binarySearch(dictionary,n,word)) printf("%s found\n", word);
        else printf("%s not found\n", word);

        /* Free all allocated memory */
        for(int i=0;i<n;i++) free(dictionary[i]);
        free(dictionary);
        return 0;
}
