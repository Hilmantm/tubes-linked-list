//
// Created by Hilman Taris M on 12/25/2021.
//

#include <iostream>
#include "app.h"

using namespace std;

void showMenu() {
    cout << "=============== MENU ===============" << endl;
    cout << ADD_EVENT << ". Tambahkan event baru" << endl;
    cout << REMOVE_EVENT << ". Hapus event" << endl;
    cout << SHOW_EVENT << ". Tampilkan semua event" << endl;
    cout << SHOW_PARTICIPANT << ". Tampilkan peserta dari sebuah event" << endl;
    cout << ADD_PESERTA << ". Tambahkan Data Pesera" << endl;
    cout << SHOW_PESERTA << ". Tampilkan data peserta" << endl;
    cout << SEARCH_EVENT << ". Mencari EVENT"<< endl;
    cout << EXIT << ". Keluar" << endl;
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

