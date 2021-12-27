//
// Created by Hilman Taris M on 12/25/2021.
//

#include <iostream>
#include "app.h"

using namespace std;

void showMenu() {
    cout << "=============== MENU ===============" << endl;
    cout << JOIN_EVENT << ". Join event" << endl;
    cout << CANCEL_JOIN_EVENT << ". Batalkan event"<< endl;
    cout << ADD_EVENT << ". Tambahkan event baru" << endl;
    cout << REMOVE_EVENT << ". Hapus event" << endl;
    cout << SHOW_AVAILABLE_EVENTS << ". Tampilkan event yang masih tersedia" << endl;
    cout << SHOW_EVENTS_WITH_PARTICIPANT << ". Tampilkan event beserta peserta" << endl;
    cout << SHOW_PARTICIPANTS_IN_AN_EVENT << ". Tampilkan peserta dari sebuah event" << endl;
    cout << SEARCH_PARTICIPANT_IN_AN_EVENT << ". Cari peserta dari sebuah event" << endl;
    cout << REGISTER_PARTICIPANT << ". Register peserta baru" << endl;
    cout << REMOVE_PARTICIPANT << ". Hapus peserta" << endl;
    cout << SHOW_PARTICIPANTS << ". Tampilkan semua peserta (development)" << endl;
    cout << SHOW_EVENTS << ". Tampilkan semua event (development)" << endl;
    cout << EXIT << ". Keluar" << endl;
    cout << "====================================" << endl;
}

void createEvents(events &events) {
    first(events) = NULL;
    last(events) = NULL;
}

adr_event createElmEvent(event event) {
    // make sure the default jumlah for new event is 0
    if(event.jumlah != 0) {
        event.jumlah = 0;
    }

    adr_event p = new elmEvent;
    info(p) = event;
    next(p) = NULL;
    prev(p) = NULL;
    participant(p) = NULL;
    lastParticipant(p) = NULL;

    return p;
}

void insertEvent(events &events, adr_event adrEvent) {
    if(first(events) == NULL && last(events) == NULL) {
        first(events) = adrEvent;
        last(events) = adrEvent;
        next(adrEvent) = first(events);
        prev(adrEvent) = last(events);
    } else {
        next(adrEvent) = first(events);
        prev(adrEvent) = last(events);
        next(last(events)) = adrEvent;
        last(events) = adrEvent;
        prev(first(events)) = last(events);
    }
}

void deleteFirstEvent(events &events, adr_event &adrEvent) {
    if(first(events) == NULL && last(events) == NULL) {
        cout << "Tidak ada event yang dihapus" << endl;
    } else if(next(first(events)) == first(events)) {
        adrEvent = first(events);
        first(events) = NULL;
        last(events) = NULL;
    } else {
        adrEvent = first(events);
        first(events) = next(first(events));
        next(last(events)) = first(events);
        prev(first(events)) = last(events);
        next(adrEvent) = NULL;
        prev(adrEvent) = NULL;
    }
}

void deleteLastEvent(events &events, adr_event &adrEvent) {
    if(first(events) == NULL && last(events) == NULL) {
        cout << "Tidak ada event yang dihapus" << endl;
    } else if(next(first(events)) == first(events)) {
        adrEvent = first(events);
        first(events) = NULL;
        last(events) = NULL;
    } else {
        adrEvent = last(events);
        last(events) = prev(last(events));
        prev(first(events)) = last(events);
        next(last(events)) = first(events);
        next(adrEvent) = NULL;
        prev(adrEvent) = NULL;
    }
}

void deleteAfterEvent(adr_event adrEventPrec, adr_event &adrEvent) {
    adrEvent = next(adrEventPrec);
    next(adrEventPrec) = next(adrEvent);
    prev(next(adrEvent)) = adrEventPrec;
    prev(adrEvent) = NULL;
    next(adrEvent) = NULL;
}

void deleteEvent(events &events, string eventName, adr_event &deletedEvent) {
    // search the event
    adr_event searchEventData = searchEvent(events, eventName);

    // check event position
    if(searchEventData != NULL) {
        // checking order
        // - if the searchEventData is in first order
        // - if the searchEventData is in last order
        // - if the searchEventData is in middle order
        if(searchEventData == first(events)) {
            deleteFirstEvent(events, deletedEvent);
        } else if(searchEventData == last(events) && next(searchEventData) == first(events)) {
            deleteLastEvent(events, deletedEvent);
        } else {
            deleteAfterEvent(prev(searchEventData), deletedEvent);
        }
    } else {
        cout << "Event yang dicari tidak ada" << endl << endl;
    }
}

void showEvents(events events, int showFlag, bool eventData, bool eventParticipant) {
    // can use this function if one of param
    // eventData and eventParticipant
    // is true
    if(eventData || eventParticipant) {
        if(first(events) == NULL && last(events) == NULL) {
            cout << "Tidak ada event tersedia" << endl << endl;
        } else {
            adr_event p = first(events);
            int counter = 1;
            while(next(p) != first(events)) {
                showEventWithFlag(p, showFlag, eventData, eventParticipant, counter);
                counter += 1;
                p = next(p);
            }
            showEventWithFlag(p, showFlag, eventData, eventParticipant, counter);
        }
    } else {
        cout << "Can't use this function because one of parameter "
                "between eventData and eventParticipant should true" << endl;
        return;
    }
}

void showEventWithFlag(adr_event currentEvent, int showFlag, bool eventData, bool eventParticipant, int counter) {
    switch (showFlag) {
        case SHOW_ALL: {
            if(eventData && eventParticipant) {
                cout << "========== Event " << counter << " ==========" << endl;
                printEvent(info(currentEvent));
                showParticipantsInEvent(currentEvent);
            } else if(eventData) {
                cout << "========== Event " << counter << " ==========" << endl;
                printEvent(info(currentEvent));
            } else if(eventParticipant) {
                showParticipantsInEvent(currentEvent);
            }
            break;
        }
        case SHOW_ONLY_AVAILABLE: {
            if(info(currentEvent).jumlah < info(currentEvent).quota_maks) {
                if(eventData && eventParticipant) {
                    cout << "========== Event " << counter << " ==========" << endl;
                    printEvent(info(currentEvent));
                    showParticipantsInEvent(currentEvent);
                } else if(eventData) {
                    cout << "========== Event " << counter << " ==========" << endl;
                    printEvent(info(currentEvent));
                } else if(eventParticipant) {
                    showParticipantsInEvent(currentEvent);
                }
            }
            break;
        }
        case SHOW_ONLY_NOT_AVAILABLE: {
            if(info(currentEvent).jumlah == info(currentEvent).quota_maks) {
                if(eventData && eventParticipant) {
                    cout << "========== Event " << counter << " ==========" << endl;
                    printEvent(info(currentEvent));
                    showParticipantsInEvent(currentEvent);
                } else if(eventData) {
                    cout << "========== Event " << counter << " ==========" << endl;
                    printEvent(info(currentEvent));
                } else if(eventParticipant) {
                    showParticipantsInEvent(currentEvent);
                }
            }
            break;
        }
    }
}

void printEvent(event event) {
    cout << "Nama Event : " << event.nama_event << endl;
    cout << "Jenis Event : " << event.jenis_event << endl;
    cout << "Tanggal Pelaksanaan : " << event.tanggal_pelaksanaan << endl;
    cout << "Tempat Pelaksanaan : " << event.tempat_pelaksanaan << endl;
    cout << "Quota Maks : " << event.quota_maks << endl;
    cout << "Jumlah Peserta : " << event.jumlah << endl;
}

adr_event searchEvent(events events, string eventName) {
    adr_event found = NULL;

    if(first(events) == NULL && last(events) == NULL) {
        cout << "Event yang dicari tidak ada" << endl << endl;
    } else {
        adr_event p = first(events);
        while(next(p) != first(events) && found == NULL) {
            // do this logic here
            if(info(p).nama_event == eventName) {
                found = p;
            }
            p = next(p);
        }
        // do this logic here
        if(found == NULL && info(p).nama_event == eventName) {
            found = p;
        }
    }

    return found;
}

void joinEvent(adr_event adrEvent, adr_event_participant adrEventParticipant) {
    if(info(adrEvent).quota_maks == info(adrEvent).jumlah) {
        cout << "Mohon Maaf, kuota maksimal dari event ini sudah penuh. Anda dapat pilih event lain untuk diikuti" << endl;
    } else {
        if(participant(adrEvent) == NULL && lastParticipant(adrEvent) == NULL) {
            participant(adrEvent) = adrEventParticipant;
            lastParticipant(adrEvent) = adrEventParticipant;
        } else {
            prev(adrEventParticipant) = lastParticipant(adrEvent);
            next(lastParticipant(adrEvent)) = adrEventParticipant;
            lastParticipant(adrEvent) = adrEventParticipant;
        }
        info(adrEvent).jumlah += 1;
    }
}

adr_event_participant createElmEventParticipant(adr_participant adrParticipant) {
    adr_event_participant adrEventParticipant = new elmEventParticipant;
    info(adrEventParticipant) = adrParticipant;
    next(adrEventParticipant) = NULL;
    prev(adrEventParticipant) = NULL;
    return adrEventParticipant;
}

void createParticipants(participants &participants) {
    first(participants) = NULL;
    last(participants) = NULL;
}

adr_participant createElmParticipant(participant participant) {
    adr_participant newParticipant = new elmParticipant;
    info(newParticipant) = participant;
    next(newParticipant) = NULL;
    prev(newParticipant) = NULL;
    return newParticipant;
}

void insertParticipant(participants &participants, adr_participant adrParticipant) {
    if(first(participants) == NULL && last(participants) == NULL){
        first(participants) = adrParticipant;
        last(participants) = adrParticipant;
    }else{
        prev(adrParticipant) = last(participants);
        next(last(participants)) = adrParticipant;
        last(participants) = adrParticipant;
    }
}

void showParticipants(participants participants) {
    adr_participant adrParticipant;

    if(first(participants) == NULL && last(participants) == NULL){
        cout << "Empty List" << endl;
    }else{
        adrParticipant = first(participants);
        int counter = 1;
        while(adrParticipant != NULL){
            cout << "============= Peserta " << counter << " =============" << endl;
            printParticipant(info(adrParticipant));
            counter += 1;
            adrParticipant = next(adrParticipant);
        }
    }
}

void showParticipantsInEvent(adr_event adrEvent) {
    if(participant(adrEvent) == NULL && lastParticipant(adrEvent) == NULL && info(adrEvent).jumlah == 0) {
        cout << "Tidak memiliki participant" << endl;
    } else {
        adr_event_participant trace = participant(adrEvent);
        int counter = 1;
        while(trace != NULL) {
            cout << "============= Peserta " << counter << " =============" << endl;
            printParticipant(info(info(trace)));
            counter += 1;
            trace = next(trace);
        }
    }
}

void printParticipant(participant participant) {
    cout << "Nomor peserta : " << participant.no_peserta << endl;
    cout << "Nomor tempat duduk : " << participant.no_tempat_duduk << endl;
    cout << "Nama peserta : " << participant.nama_peserta << endl;
    cout << "Email : " << participant.email << endl;
    cout << "Jenis peserta : " << participant.jenis_peserta << endl;
    cout << "Nomor telpon : " << participant.no_telp << endl;
}

adr_participant searchParticipant(participants participants, string participantEmail) {
    adr_participant found = NULL;

    if(first(participants) == NULL && last(participants) == NULL){
        cout << "Empty List" << endl;
    }else{
        adr_participant trace = first(participants);
        while(trace != NULL && found == NULL){
            if(info(trace).email == participantEmail) {
                found = trace;
            }
            trace = next(trace);
        }
    }

    return found;
}

adr_event_participant searchParticipantInEvent(adr_event adrEvent, string participantEmail) {
    adr_event_participant found = NULL;

    if(participant(adrEvent) == NULL && lastParticipant(adrEvent) == NULL) {
        cout << "Tidak ada peserta dalam event ini" << endl;
    } else {
        adr_event_participant trace = participant(adrEvent);
        while(trace != NULL && found == NULL) {
            if(info(info(trace)).email == participantEmail) {
                found = trace;
            }
            trace = next(trace);
        }
    }

    return found;
}

void deleteFirstParticipant(participants &participants, adr_participant &adrParticipant) {
    if(first(participants) == NULL && last(participants) == NULL) {
        cout << "List kosong" << endl;
    } else {
        adrParticipant = first(participants);
        if(first(participants) == last(participants)) {
            first(participants) = NULL;
            last(participants) = NULL;
        } else {
            first(participants) = next(adrParticipant);
            next(adrParticipant) = NULL;
            prev(first(participants)) = NULL;
        }
    }
}

void deleteLastParticipant(participants &participants, adr_participant &adrParticipant) {
    if(first(participants) == NULL && last(participants) == NULL) {
        cout << "List kosong" << endl;
    } else {
        adrParticipant = last(participants);
        if(first(participants) == last(participants)) {
            first(participants) = NULL;
            last(participants) = NULL;
        } else {
            last(participants) = prev(last(participants));
            prev(adrParticipant) = NULL;
            next(last(participants)) = NULL;
        }
    }
}

void deleteAfterParticipant(adr_participant adrParticipantPrec, adr_participant &adrParticipant) {
    adrParticipant = next(adrParticipantPrec);
    next(adrParticipantPrec) = next(adrParticipant);
    prev(next(adrParticipant)) = adrParticipantPrec;
    prev(adrParticipant) = NULL;
    next(adrParticipant) = NULL;
}

void removeParticipant(participants &participants, string participantEmail, adr_participant &adrParticipant) {
    // search the participant
    adr_participant searchParticipantData = searchParticipant(participants, participantEmail);

    // check participant position
    if(searchParticipantData != NULL) {
        // checking order
        // - if the searchParticipantData is in first order
        // - if the searchParticipantData is in last order
        // - if the searchParticipantData is in middle order
        if(searchParticipantData == first(participants)) {
            deleteFirstParticipant(participants, adrParticipant);
        } else if(searchParticipantData == last(participants)) {
            deleteLastParticipant(participants, adrParticipant);
        } else {
            deleteAfterParticipant(prev(searchParticipantData), adrParticipant);
        }
    } else {
        cout << "Peserta yang dicari tidak ada" << endl << endl;
    }
}

void cancelEvent(adr_event adrEvent, adr_event_participant adrEventParticipant, adr_event_participant &deletedEventParticipant) {
    if(participant(adrEvent) == NULL && lastParticipant(adrEvent) == NULL) {
        cout << "Tidak ada data peserta" << endl;
    } else {
        deleteEventParticipant(adrEvent, adrEventParticipant, deletedEventParticipant);
        info(adrEvent).jumlah -= 1;
    }
}

void deleteFirstEventParticipant(adr_event adrEvent, adr_event_participant &adrEventParticipant) {
    if(participant(adrEvent) == NULL && lastParticipant(adrEvent) == NULL) {
        cout << "Tidak ada peserta" << endl;
    } else {
        adrEventParticipant = participant(adrEvent);
        if(participant(adrEvent) == lastParticipant(adrEvent)) {
            participant(adrEvent) = NULL;
            lastParticipant(adrEvent) = NULL;
        } else {
            participant(adrEvent) = next(adrEventParticipant);
            next(adrEventParticipant) = NULL;
            prev(participant(adrEvent)) = NULL;
        }
    }
}

void deleteLastEventParticipant(adr_event adrEvent, adr_event_participant &adrEventParticipant) {
    if(participant(adrEvent) == NULL && lastParticipant(adrEvent) == NULL) {
        cout << "Tidak ada peserta" << endl;
    } else {
        adrEventParticipant = lastParticipant(adrEvent);
        if(participant(adrEvent) == lastParticipant(adrEvent)) {
            participant(adrEvent) = NULL;
            lastParticipant(adrEvent) = NULL;
        } else {
            lastParticipant(adrEvent) = prev(lastParticipant(adrEvent));
            prev(adrEventParticipant) = NULL;
            next(lastParticipant(adrEvent)) = NULL;
        }
    }
}

void deleteAfterEventParticipant(adr_event_participant adrEventParticipantPrec, adr_event_participant &adrEventParticipant) {
    adrEventParticipant = next(adrEventParticipantPrec);
    next(adrEventParticipantPrec) = next(adrEventParticipant);
    prev(next(adrEventParticipant)) = adrEventParticipantPrec;
    prev(adrEventParticipant) = NULL;
    next(adrEventParticipant) = NULL;
}

void deleteEventParticipant(adr_event &adrEvent, adr_event_participant adrEventParticipant, adr_event_participant &deletedEventParticipant) {

    // check participant position
    if(adrEventParticipant != NULL) {
        // checking order
        // - if the searchParticipantData is in first order
        // - if the searchParticipantData is in last order
        // - if the searchParticipantData is in middle order
        if(adrEventParticipant == participant(adrEvent)) {
            deleteFirstEventParticipant(adrEvent, deletedEventParticipant);
        } else if(adrEventParticipant == lastParticipant(adrEvent)) {
            deleteLastEventParticipant(adrEvent, deletedEventParticipant);
        } else {
            deleteAfterEventParticipant(prev(adrEventParticipant), deletedEventParticipant);
        }
    } else {
        cout << "Peserta yang dicari tidak ada" << endl << endl;
    }
}
