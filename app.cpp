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
    cout << ADD_PARTICIPANT << ". Tambahkan peserta baru" << endl;
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

void showEvents(events events) {
    if(first(events) == NULL && last(events) == NULL) {
        cout << "Tidak ada event tersedia" << endl << endl;
    } else {
        adr_event p = first(events);
        int counter = 1;
        while(next(p) != first(events)) {
            cout << "========== Event " << counter << " ==========" << endl;
            event temp = info(p);
            printEvent(temp);
            counter += 1;
            p = next(p);
        }
        cout << "========== Event " << counter << " ==========" << endl;
        printEvent(info(p));
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
        while(adrParticipant != NULL){
            printParticipant(info(adrParticipant));
            cout << endl;
            adrParticipant = next(adrParticipant);
        }
    }
    cout << endl;
}

void printParticipant(participant participant) {
    cout << "Nomor peserta :" << participant.no_peserta << endl;
    cout << "Nomor tempat duduk :" << participant.no_tempat_duduk << endl;
    cout << "Nama peserta :" << participant.nama_peserta << endl;
    cout << "Email :" << participant.email << endl;
    cout << "Jenis peserta :" << participant.jenis_peserta << endl;
    cout << "Nomor telpon :" << participant.no_telp << endl;
}