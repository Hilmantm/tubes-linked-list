//
// Created by Hilman Taris M on 12/25/2021.
//

#ifndef LINKED_LIST_EVENT_H
#define LINKED_LIST_EVENT_H

#include <iostream>
#include "participant.h"
#include "event_participant.h"

using namespace std;

typedef struct elmEvent *adr_event;

struct event {
    string nama_event, jenis_event, tanggal_pelaksanaan, tempat_pelaksanaan;
    int quota_maks, jumlah;
};

struct elmEvent {
    event info;
    adr_event_participant participant;
    adr_event_participant lastParticipant;
    adr_event prev, next;
};

struct events{
    adr_event first, last;
};

#endif //LINKED_LIST_EVENT_H
