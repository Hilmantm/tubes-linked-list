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
const int ADD_EVENT = 1;
const int REMOVE_EVENT = 2;
const int SHOW_EVENT = 3;
const int SHOW_PARTICIPANT = 4;
const int ADD_PESERTA = 5;
const int SHOW_PESERTA = 6;
const int SEARCH_EVENT = 7;

void showMenu();

void createEvents(events &events);
adr_event createElmEvent(event event);
void insertEvent(events &events, adr_event adrEvent);
void deleteFirstEvent(events &events, adr_event &adrEvent);
void deleteLastEvent(events &events, adr_event &adrEvent);

#endif //LINKED_LIST_APP_H
