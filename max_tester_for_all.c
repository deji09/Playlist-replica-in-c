#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "playlist.h"

/* A function (and global) that can trigger malloc fails on demand. */
int mallocFail = 0;

void* myMalloc(size_t size) {
	if (mallocFail) { return NULL; }
	else { return malloc(size); }
}

// Returns if the playlist is empty
bool isListEmpty(Playlist *listPtr)
{
    // Checks if the list is empty
    if (listPtr->head == NULL && listPtr->tail == NULL && listPtr->curr == NULL)
        return true;
    return false;
}

void displayTrack(Playlist* listPtr) {
    MP3Track *ntp = listPtr->head;
    int counter = 0;
    // if (listPtr->head == NULL)
    // {
    //     printf("The list is already empty.");
    // }
    
    while (ntp!= NULL)
    {
        printf("\n");
        counter++;
        printf("Name: %s\tLength: %d\tCounter Number: %d", ntp->trackName, ntp->trackLength, counter);
        ntp = ntp->next;
    }
    if (ntp == NULL)
    {
        printf("\n");
        printf("We are at the end of the list");
    }

    
}

void displayValid(int valid) {
    printf("\tDisplay Code: ");
    if (valid == SUCCESS) {
        printf("SUCCESS");
    }
    else if (valid == INVALID_INPUT_PARAMETER) {
        printf("INVALID_INPUT_PARAMETER");
    }
    else if (valid == MEMORY_ALLOCATION_ERROR) {
        printf("MEMORY_ALLOCATION_ERROR");
    }
    else if (valid == INVALID_LIST_OPERATION) {
        printf("INVALID_LIST_OPERATION");
    }
    else if (valid == NOT_IMPLEMENTED) {
        printf("NOT_IMPLEMENTED");
    }
    else if (valid == FILE_IO_ERROR) {
        printf("FILE_IO_ERROR");
    }
    else {
        printf("WTF: %d", valid);
    }
    printf("\n");
}

void displayPlaylist(Playlist *listPtr, int valid) {
    if (listPtr == NULL) {
        printf("List is uninitalised\n");
        return;
    }

    // Used to store the current track we're displaying
    MP3Track track;
    // Moves the current track to the head so we can display the entire playlist
    while(skipPrev(listPtr) == SUCCESS) {}
    do {
        if (!isListEmpty(listPtr)) {
        //     // Gets the current track 
            getCurrentTrack(listPtr, &track);
        //     // Displays the current track
            displayTrack(listPtr);
            displayValid(valid);
        }
        printf(" \nvalid");
    } while (skipNext(listPtr) == SUCCESS);
}

int main() {
    // a variable to store an MP3 track popped from the list
	// MP3Track track;

	// a pointer to our doubly-linked list
	Playlist *listPtr = NULL;
    //
    int result;
    MP3Track track;
    result = createPlaylist(&listPtr);
    result = insertAfterCurr(listPtr, "A1", 1);
    result = insertAfterCurr(listPtr, "A2", 2);
    result = insertAfterCurr(listPtr, "A3", 3);
    result = insertAfterCurr(listPtr, "A4", 4);
    result = insertAfterCurr(listPtr, "A5", 5);
    result = insertBeforeCurr(listPtr, "B1", 1);
    result = insertBeforeCurr(listPtr, "B2", 2);
    result = insertBeforeCurr(listPtr, "B3", 3);
    result = insertBeforeCurr(listPtr, "B4", 4);
    result = insertBeforeCurr(listPtr, "B5", 5);
    // printf("name %s",listPtr->curr->trackName);
    // printf(" \nReached 2");
    // result = removeAtCurr(listPtr, &track, 34);
    // result = loadPlaylist(&listPtr, "test_playlist.txt");
    // result = savePlaylist(listPtr, "out.txt");
    result = skipNext(listPtr);
    result = skipPrev(listPtr);
    // result = getCurrentTrack(listPtr, &track);
    // result = clearPlaylist(listPtr);
    // displayTrack(listPtr);
    // printf("\n");
    printf("The result is  %d \t",result);
    displayPlaylist(listPtr, result);
    return 0;
}