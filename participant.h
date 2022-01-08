#ifndef LINKED_LIST_PARTICIPANT_H
#define LINKED_LIST_PARTICIPANT_H

#include <iostream>
#include "event.h"

using namespace std;

typedef struct elmParticipant *adr_participant;

struct participant {
    int no_peserta, no_tempat_duduk;
    string nama_peserta, email, jenis_peserta, no_telp;
};

struct elmParticipant {
    participant info;
    adr_participant next, prev;
};

struct participants{
    adr_participant first, last;
};

#endif //LINKED_LIST_PARTICIPANT_H
