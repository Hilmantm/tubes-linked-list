#ifndef LINKED_LIST_APP_H
#define LINKED_LIST_APP_H

#include <iostream>
#include "event.h"
#include "participant.h"
#include "event_participant.h"

using namespace std;

#define info(P) (P)->info
#define next(P) (P)->next
#define prev(P) (P)->prev
#define participant(P) (P)->participant
#define lastParticipant(P) (P)->lastParticipant
#define first(H) ((H).first)
#define last(H) ((H).last)

const int EXIT = 0;
const int JOIN_EVENT = 1;
const int CANCEL_JOIN_EVENT = 2;
const int ADD_EVENT = 3;
const int REMOVE_EVENT = 4;
const int SHOW_AVAILABLE_EVENTS = 5;
const int SHOW_EVENTS_WITH_PARTICIPANT = 6;
const int SHOW_PARTICIPANTS_IN_AN_EVENT = 7;
const int SEARCH_PARTICIPANT_IN_AN_EVENT = 8;
const int REGISTER_PARTICIPANT = 9;
const int REMOVE_PARTICIPANT = 10;
const int SHOW_PARTICIPANTS = 11; // This feature only use for development process
const int SHOW_EVENTS = 12; // This feature only use for development process

const int SHOW_ALL = 1;
const int SHOW_ONLY_AVAILABLE = 2;
const int SHOW_ONLY_NOT_AVAILABLE = 3;

void showMenu();

void createEvents(events &events);
adr_event createElmEvent(event event);
void insertEvent(events &events, adr_event adrEvent);
void deleteFirstEvent(events &events, adr_event &adrEvent);
void deleteLastEvent(events &events, adr_event &adrEvent);
void deleteAfterEvent(adr_event adrEventPrec, adr_event &adrEvent);
void deleteEvent(events &events, string eventName, adr_event &deletedEvent);
void showEvents(events events, int showFlag = SHOW_ALL, bool eventData = true, bool eventParticipant = false);
void printEvent(event event);
void showEventWithFlag(adr_event currentEvent, int showFlag, bool eventData, bool eventParticipant, int counter);
adr_event searchEvent(events events, string eventName);
void joinEvent(adr_event adrEvent, adr_event_participant adrEventParticipant);
void cancelEvent(adr_event adrEvent, adr_event_participant adrEventParticipant, adr_event_participant &deletedEventParticipant);

adr_event_participant createElmEventParticipant(adr_participant adrParticipant);
void deleteFirstEventParticipant(adr_event adrEvent, adr_event_participant &adrEventParticipant);
void deleteLastEventParticipant(adr_event adrEvent, adr_event_participant &adrEventParticipant);
void deleteAfterEventParticipant(adr_event_participant adrEventParticipantPrec, adr_event_participant &adrEventParticipant);
void deleteEventParticipant(adr_event &adrEvent, adr_event_participant adrEventParticipant, adr_event_participant &deletedEventParticipant);

void createParticipants(participants &participants);
adr_participant createElmParticipant(participant participant);
void insertParticipant(participants &participants, adr_participant adrParticipant);
void deleteFirstParticipant(participants &participants, adr_participant &adrParticipant);
void deleteLastParticipant(participants &participants, adr_participant &adrParticipant);
void deleteAfterParticipant(adr_participant adrParticipantPrec, adr_participant &adrParticipant);
void removeParticipant(participants &participants, string participantEmail, adr_participant &adrParticipant);
void showParticipants(participants participants);
void showParticipantsInEvent(adr_event adrEvent);
void printParticipant(participant participant);
adr_participant searchParticipant(participants participants, string participantEmail);
adr_event_participant searchParticipantInEvent(adr_event adrEvent, string participantEmail);

#endif //LINKED_LIST_APP_H
