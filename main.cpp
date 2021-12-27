#include <iostream>
#include <stdlib.h>
#include "app.h"

using namespace std;

int main() {

    // Define the events
    events eventList;

    //Define the participans
    participants participantsList;

    // create the event list
    createEvents(eventList);

    // create the participants list
    createParticipants(participantsList);

    showMenu();
    int choose;
    cout << "Pilih Menu : "; cin >> choose;
    while(choose != EXIT) {
        switch(choose) {
            case JOIN_EVENT: {
                string eventName, participantEmail;
                adr_event searchCurrentEvent;
                adr_participant searchCurrentParticipant;
                adr_event_participant newEventParticipant;

                cout << "Nama event yang akan diikuti : "; cin.ignore(); getline(cin, eventName);
                searchCurrentEvent = searchEvent(eventList, eventName);

                if(searchCurrentEvent != NULL) {
                    cout << "Email peserta yang akan diikut sertakan : "; cin >> participantEmail;
                    searchCurrentParticipant = searchParticipant(participantsList, participantEmail);
                    if(searchCurrentParticipant != NULL) {
                        newEventParticipant = createElmEventParticipant(searchCurrentParticipant);
                        joinEvent(searchCurrentEvent, newEventParticipant);
                        cout << "Success invite participant " << participantEmail << " into " << eventName << endl;
                    }
                }
                break;
            }
            case CANCEL_JOIN_EVENT: {
                string eventName, participantEmail, ask;
                adr_event searchCurrentEvent;
                adr_event_participant searchCurrentParticipant, deletedEventParticipant;

                cout << "Nama event yang akan diikuti : "; cin.ignore(); getline(cin, eventName);
                searchCurrentEvent = searchEvent(eventList, eventName);

                if(searchCurrentEvent != NULL) {
                    cout << "Email peserta yang akan dibatalkan : "; cin >> participantEmail;
                    searchCurrentParticipant = searchParticipantInEvent(searchCurrentEvent, participantEmail);
                    if(searchCurrentParticipant != NULL) {
                        cout << "Yakin ingin membatalkan? (Y/N) : "; cin >> ask;
                        if(ask == "Y" || ask == "y") {
                            cancelEvent(searchCurrentEvent, searchCurrentParticipant, deletedEventParticipant);
                            cout << "Success cancel participant " << participantEmail << " from " << eventName << endl;
                        }
                    }
                }
                break;
            }
            case ADD_EVENT: {
                string tanggal, bulan, tahun;
                event newEvent;
                adr_event newEventElm;

                cout << "Nama event : "; cin.ignore(); getline(cin, newEvent.nama_event);
                cout << "Jenis event : "; getline(cin, newEvent.jenis_event);
                cout << "Tanggal pelaksanaan : "; getline(cin, newEvent.tanggal_pelaksanaan);
                cout << "Tempat pelaksanaan : "; getline(cin, newEvent.tempat_pelaksanaan);
                cout << "Quota Maks : "; cin >> newEvent.quota_maks;
                newEvent.jumlah = 0;

                newEventElm = createElmEvent(newEvent);
                insertEvent(eventList, newEventElm);
                break;
            }
            case REMOVE_EVENT: {
                adr_event deletedEvent, searchDeletedEvent;
                string eventName;

                cout << "Masukkan nama event yang ingin dihapus : "; cin.ignore(); getline(cin, eventName);
                cout << "event yang ingin dihapus : " << eventName << endl;
                deleteEvent(eventList, eventName, deletedEvent);

                // confirm delete procedure by search event name again
                searchDeletedEvent = searchEvent(eventList, eventName);

                // if search result is null, delete procedure success
                if(searchDeletedEvent == NULL) {
                    cout << "Success delete " << eventName << endl;
                }
                break;
            }
            case SHOW_AVAILABLE_EVENTS: {
                showEvents(eventList, SHOW_ONLY_AVAILABLE);
                break;
            }
            case SHOW_EVENTS_WITH_PARTICIPANT: {
                showEvents(eventList, SHOW_ALL, true, true);
                break;
            }
            case SHOW_PARTICIPANTS_IN_AN_EVENT: {
                string eventName;
                adr_event searchCurrentEvent;

                cout << "Masukkan nama event : "; cin.ignore(); getline(cin, eventName);

                searchCurrentEvent = searchEvent(eventList, eventName);
                if(searchCurrentEvent != NULL) {
                    showParticipantsInEvent(searchCurrentEvent);
                }
                break;
            }
            case SEARCH_PARTICIPANT_IN_AN_EVENT: {
                string eventName, participantEmail;
                adr_event searchCurrentEvent;
                adr_event_participant searchCurrentEventParticipant;

                cout << "Masukkan nama event : "; cin.ignore(); getline(cin, eventName);

                searchCurrentEvent = searchEvent(eventList, eventName);
                if(searchCurrentEvent != NULL) {
                    cout << "Masukkan email peserta : "; cin >> participantEmail;
                    searchCurrentEventParticipant = searchParticipantInEvent(searchCurrentEvent, participantEmail);
                    if(searchCurrentEventParticipant != NULL) {
                        cout << "Peserta dengan email " << participantEmail << " sudah terdaftar dalam event ini" << endl;
                        printParticipant(info(info(searchCurrentEventParticipant)));
                    }
                }
                break;
            }
            case REGISTER_PARTICIPANT: {
                int totalParticipant;
                participant newParticipant;
                adr_participant newParticipantElm;

                cout << "Masukkan Jumlah peserta : "; cin >> totalParticipant;
                for(int i = 0; i < totalParticipant; i++) {
                    int counter = i + 1;
                    cout << "============= Peserta " << counter << " =============" << endl;
                    cout << "masukkan nomor peserta : "; cin >> newParticipant.no_peserta;
                    cout << "masukkan no tempat duduk : "; cin >> newParticipant.no_tempat_duduk;
                    cout << "masukkan nama peserta : "; cin.ignore(); getline(cin, newParticipant.nama_peserta);
                    cout << "masukkan email : "; cin >> newParticipant.email;
                    cout << "masukkan jenis peserta : "; cin.ignore(); getline(cin, newParticipant.jenis_peserta);
                    cout << "masukkan no telpon : "; cin >> newParticipant.no_telp;
                    newParticipantElm = createElmParticipant(newParticipant);
                    insertParticipant(participantsList, newParticipantElm);
                }
                break;
            }
            case REMOVE_PARTICIPANT: {
                string participantEmail;
                adr_participant deletedParticipant, searchDeletedParticipant;

                cout << "Masukkan email peserta yang akan dihapus : "; cin >> participantEmail;
                removeParticipant(participantsList, participantEmail, deletedParticipant);

                searchDeletedParticipant = searchParticipant(participantsList, participantEmail);
                if(searchDeletedParticipant == NULL) {
                    cout << "Success remove " << participantEmail << endl;
                }
                break;
            }
            case SHOW_PARTICIPANTS: {
                showParticipants(participantsList);
                break;
            }
            case SHOW_EVENTS: {
                showEvents(eventList, SHOW_ALL, true, false);
                break;
            }
        }
        showMenu();
        cout << "Pilih Menu : "; cin >> choose;
    }

    return 0;
}
