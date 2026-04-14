#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Range{
        int low;
        int high;
};

bool binarySearch(char* dictionary[], int n, char* key){
        struct Range r = {0, n-1};
        while(r.low <= r.high){
                int mid = r.low + (r.high - r.low)/2;
                printf("Checking word at index %d: %s\n", mid, dictionary[mid]);
                printf("Remaining search indices %d to %d\n", r.low, r.high);
                int cmp = strcmp(dictionary[mid], key);
                if(cmp == 0) return true;
                else if(cmp < 0) r.low = mid+1;
                else r.high = mid-1;
        }
        return false;
}

int main(){
        const char* words[] = {"apple","banana","cherry","date","fig","grape","kiwi","mango","orange","peach"};
        int n = sizeof(words)/sizeof(words[0]);
        char** dictionary = malloc(n * sizeof(char*));
        for(int i=0;i<n;i++){
                dictionary[i] = malloc(strlen(words[i])+1);
                strcpy(dictionary[i], words[i]);
        }

        char word[50];
        printf("Enter a word to search: ");
        scanf("%49s", word);
        if(binarySearch(dictionary,n,word)) printf("%s found\n", word);
        else printf("%s not found\n", word);

        for(int i=0;i<n;i++) free(dictionary[i]);
        free(dictionary);
        return 0;
}
