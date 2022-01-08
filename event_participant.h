#ifndef LINKED_LIST_EVENT_PARTICIPANT_H
#define LINKED_LIST_EVENT_PARTICIPANT_H

#include "participant.h"

typedef struct elmEventParticipant *adr_event_participant;

struct elmEventParticipant {
    adr_event_participant next, prev;
    adr_participant info;
};

#endif //LINKED_LIST_EVENT_PARTICIPANT_H
