#include "playlist.h"
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
/*Name: Ayodeji Shote
number: 180004145
Module code: AC21008*/

/* Create a new, empty playlist, storing a pointer to it in the variable 
   provided (e.g. listPtr) */
int createPlaylist(Playlist **listPtr)
{
 if (listPtr == NULL)
        return INVALID_INPUT_PARAMETER;

    if (*listPtr != NULL)
        return INVALID_INPUT_PARAMETER;
    
    (*listPtr) = (Playlist*)myMalloc(sizeof(Playlist));
    if ((*listPtr) == NULL)
        return MEMORY_ALLOCATION_ERROR;
    (*listPtr)->head = NULL;
    (*listPtr)->tail = NULL;
	(*listPtr)->tail = NULL;
    return SUCCESS;
}
/* Add a new MP3 track into the playlist immediately
   BEFORE the current position in the list */
int insertBeforeCurr(Playlist* listPtr, char trackName[], int trackLength)
{
/*
    Checks if the pointer for the mp3 track is null 
*/
    if (listPtr == NULL)
        return INVALID_INPUT_PARAMETER;
    if (trackName == NULL)
        return INVALID_INPUT_PARAMETER;
/*
Input parameters for the mp3 track
*/
 if(strlen(trackName)>49 ||strlen(trackName)<1 || trackLength<=0)
    {
    return INVALID_INPUT_PARAMETER;
    }
else 
    {
    MP3Track *track = (MP3Track*)myMalloc(sizeof(MP3Track));
    /*
    Checks if it failed to allocate memory for a node.
    */
    if (track == NULL)
		return MEMORY_ALLOCATION_ERROR;
    track-> trackLength = trackLength;
    strncpy(track-> trackName, trackName, 49);
    if(listPtr->curr == NULL)
    {
        listPtr->curr = track;
        listPtr->head = track;
        listPtr->tail = track;
    }
    else
    {
        if(listPtr->head == listPtr->curr)
        {
        track->next = listPtr->curr;
        listPtr->curr->prev = track;
        listPtr->head = track;
        
        }
        else
        {
        track->next = listPtr->curr;
        track->prev = listPtr->curr->prev;
		(listPtr->curr->prev)->next= track; 
        listPtr->curr->prev = track;
        }
        
    }
    
    }
return SUCCESS;
}

/* Add a new MP3 track into the playlist immediately
   AFTER the current position in the list */
int insertAfterCurr(Playlist* listPtr, char trackName[], int trackLength)
{
/*
    Checks if the pointer for the mp3 track is null 
*/
    if (listPtr == NULL)
        return INVALID_INPUT_PARAMETER;
    if (trackName == NULL)
        return INVALID_INPUT_PARAMETER;
/*
Input parameters for the mp3 track
*/
 if(strlen(trackName)>49 ||strlen(trackName)<1 || trackLength<=0)
    {
    return INVALID_INPUT_PARAMETER;
    }
else 
    {
    MP3Track *track = (MP3Track*)myMalloc(sizeof(MP3Track));
    /*
    Checks if it failed to allocate memory for a node.
    */
    if (track == NULL)
		return MEMORY_ALLOCATION_ERROR;
    track-> trackLength = trackLength;
    strncpy(track-> trackName, trackName, 49);
    if(listPtr->curr == NULL)
    {
        listPtr->curr = track;
        listPtr->head = track;
        listPtr->tail = track;
    }
    else
    {
        if(listPtr->tail == listPtr->curr)
        {
        track->prev = listPtr->curr;
		listPtr->curr->next= track;
        listPtr->tail->next= track;
        listPtr->tail = track;
        }
        else
        {
        track->prev = listPtr->curr;
        track->next = listPtr->curr->next;
		listPtr->curr->next= track; 
        
        }
        
    }
    
    }
return SUCCESS;
}

/* Skip to the next track in the playlist, i.e. shift 'curr' one
   position forward in the list */
int skipNext(Playlist* listPtr)
{
/*
    Checks if the pointer for the mp3 track is null 
*/
if (listPtr->curr == listPtr->tail)
return INVALID_LIST_OPERATION;
if (listPtr->curr == NULL)
return INVALID_LIST_OPERATION;
if(listPtr->curr->next == NULL)
return INVALID_LIST_OPERATION;
if (listPtr == NULL)
return INVALID_LIST_OPERATION;
listPtr->curr = listPtr->curr->next;
return SUCCESS;

}

/* Skip to the previous track in the playlist, i.e. shift 'curr' one
   position back in the list */
int skipPrev(Playlist* listPtr)
{
if (listPtr->curr == listPtr->head)
return INVALID_LIST_OPERATION;
if (listPtr->curr == NULL)
return INVALID_LIST_OPERATION;
if(listPtr->curr->prev == NULL)
return INVALID_LIST_OPERATION;
if (listPtr == NULL)
return INVALID_LIST_OPERATION;
listPtr->curr = listPtr->curr->prev;
return SUCCESS;
}

/* Get the data for the current track in the playlist */
int getCurrentTrack(Playlist* listPtr, MP3Track *pTrack)
{
if (listPtr->curr == NULL)
    return INVALID_LIST_OPERATION;
    
if (pTrack == NULL)
    return INVALID_LIST_OPERATION;

pTrack->trackLength = listPtr->curr->trackLength;
strncpy(pTrack-> trackName, listPtr->curr->trackName, 49);
/*
This segment of cod is to prove that it prints the current track
*/
printf("The current track is \n");
printf("\nName: %s\tLength: %d", pTrack->trackName, pTrack->trackLength);
return SUCCESS;   
// return NOT_IMPLEMENTED;
    
}

/* Remove the MP3 track from the current position in the list. The track data should be copied into 
   the variable provided (*pTrack) for confirmation. The variable ‘moveForward’ is used to suggest 
   what happens to the ‘curr’ pointer in the list after the track is removed. If ‘moveForward’ is set 
   to 1 then the ‘curr’ pointer should be set to point to the next track in the list, immediately 
   after the one which has just been removed. Otherwise, ‘curr’ should be set to point to the previous 
   track in the list, immediately prior to the one which has just been removed. */
int removeAtCurr(Playlist* listPtr, MP3Track *pTrack, int moveForward)
{
if (listPtr->curr == NULL)
    return INVALID_LIST_OPERATION;
if (pTrack == NULL)
    return INVALID_LIST_OPERATION;
if (moveForward == NULL)
    return INVALID_LIST_OPERATION;
if (listPtr->head == NULL)
    return INVALID_LIST_OPERATION;

    pTrack = listPtr->curr;
    pTrack->trackLength = listPtr->curr->trackLength;
    strncpy(pTrack-> trackName, listPtr->curr->trackName, 49);
if(listPtr->head->next == NULL)
{
    listPtr->curr = NULL;  
    listPtr->tail = NULL; 
    listPtr->head = NULL;
    free(pTrack); 
    return;
}
if(moveForward == 1)
{   printf("\n");
    //  printf("Name: %s \tLength: %d", pTrack->trackName, pTrack->trackLength);
    if(listPtr->curr == listPtr->tail)
    {
        
        listPtr->tail = pTrack->prev;
        listPtr->tail->next = NULL;
        listPtr->curr = listPtr->tail;
        free(pTrack);
    }
    else if (listPtr->curr == listPtr->head )
    {
        listPtr->head = pTrack->next;
        listPtr->head->prev= NULL;
        listPtr->curr = listPtr->head;
        free(pTrack);
    }
    else
    {
        pTrack->prev->next = pTrack->next;
        pTrack->next->prev = pTrack->prev;
        listPtr->curr=listPtr->curr->next;
        free(pTrack); 
    }
    
    
    // printf(" This area was not reached ");
}
if (moveForward !=1 || moveForward == 0)
{
    if(listPtr->curr == listPtr->tail)
    {
        listPtr->tail = pTrack->prev;
        listPtr->tail->next = NULL;
        listPtr->curr = listPtr->tail;
        free(pTrack);
    }
    else if (listPtr->curr == listPtr->head )
    {
        listPtr->head = pTrack->next;
        listPtr->head->prev= NULL;
        listPtr->curr = listPtr->head;
        free(pTrack);
    }
    else
    {
        pTrack->next->prev = pTrack->prev;
        pTrack->prev->next = pTrack->next;
        listPtr->curr=listPtr->curr->prev;
        free(pTrack); 
    }
}

return SUCCESS;
}

/* Empty the entire contents of the playlist, freeing up any memory that it currently uses */
int clearPlaylist(Playlist* listPtr)
{
if (listPtr == NULL)
return INVALID_LIST_OPERATION;
if (listPtr->curr == NULL)
return INVALID_INPUT_PARAMETER;
MP3Track pTrack;
int counter = 0;
while (listPtr->curr !=NULL)
{
    removeAtCurr( listPtr, &pTrack, 1);
    counter++;
}
if (listPtr->curr == NULL)
{
    printf(" \nThe list is empty");
}


}

/* save details of all of the tracks in the playlist into the given file */
int savePlaylist(Playlist *listPtr, char filename[])
{
return NOT_IMPLEMENTED;
}

/* This function is similar to 'createPlaylist'. It should create a new, empty playlist BUT
   then also load the details of a playlist from the given file (a list of track names and 
   track lengths); insert these as new MP3 tracks into your playlist, and store a pointer to 
   the newly created playlist into the variable provided (e.g. listPtr)  */
int loadPlaylist(Playlist **listPtr, char filename[])
{
return NOT_IMPLEMENTED;
}
