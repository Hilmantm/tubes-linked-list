//
// Created by Hilman Taris M on 12/25/2021.
//

#ifndef LINKED_LIST_APP_H
#define LINKED_LIST_APP_H

#include <iostream>
#include "event.h"
#include "participant.h"

using namespace std;

#define info(P) (P)->info
#define next(P) (P)->next
#define prev(P) (P)->prev
#define participant(P) (P)->participant
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
const int ADD_PARTICIPANT = 9;
const int REMOVE_PARTICIPANT = 10;
const int SHOW_PARTICIPANTS = 11; // This feature only use for development process
const int SHOW_EVENTS = 12; // This feature only use for development process

void showMenu();

void createEvents(events &events);
adr_event createElmEvent(event event);
void insertEvent(events &events, adr_event adrEvent);
void deleteFirstEvent(events &events, adr_event &adrEvent);
void deleteLastEvent(events &events, adr_event &adrEvent);
void deleteAfterEvent(adr_event adrEventPrec, adr_event &adrEvent);
void showEvents(events events);
void printEvent(event event);
adr_event searchEvent(events events, string eventName);

void createParticipants(participants &participants);
adr_participant createElmParticipant(participant participant);
void insertParticipant(participants &participants, adr_participant adrParticipant);
void showParticipants(participants participants);
void printParticipant(participant participant);

#endif //LINKED_LIST_APP_H
