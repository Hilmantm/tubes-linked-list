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
                cout << "JOIN EVENT" << endl;
                break;
            }
            case CANCEL_JOIN_EVENT: {
                cout << "CANCEL JOIN EVENT" << endl;
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
                cout << "SHOW AVAILABLE EVENT" << endl;
                break;
            }
            case SHOW_EVENTS_WITH_PARTICIPANT: {
                cout << "SHOW EVENTS WITH PARTICIPANT" << endl;
                break;
            }
            case SHOW_PARTICIPANTS_IN_AN_EVENT: {
                cout << "SHOW PARTICIPANTS IN AN EVENT" << endl;
                break;
            }
            case SEARCH_PARTICIPANT_IN_AN_EVENT: {
                cout << "SHOW PARTICIPANTS IN AN EVENT" << endl;
                break;
            }
            case ADD_PARTICIPANT: {
                int i, jumlah_peserta;
                int no_peserta, no_tempat_duduk;
                string nama_peserta, email, jenis_peserta, no_telp;
                i = 0;

                cout << "Masukkan Jumlah peserta : ";
                cin >> jumlah_peserta;

                while (i < jumlah_peserta){
                    participant new_peserta;
                    cout << "masukkan nomor peserta :";
                    cin >> new_peserta.no_peserta;
                    cout << "masukkan no tempat duduk :";
                    cin >> new_peserta.no_tempat_duduk;
                    cout << "masukkan nama peserta :";
                    cin >> new_peserta.nama_peserta;
                    cout << "masukkan email : ";
                    cin >> new_peserta.email;
                    cout << "masukkan jenis peserta :";
                    cin >> new_peserta.jenis_peserta;
                    cout << "masukkan no telpon :";
                    cin >> new_peserta.no_telp;
                    cout << "====================="<<endl;
                    adr_participant AdrPeserta;
                    AdrPeserta = createElmParticipant(new_peserta);
                    insertParticipant(participantsList, AdrPeserta);
                    i++;
                }
                break;
            }
            case REMOVE_PARTICIPANT: {
                cout << "REMOVE PARTICIPANT" << endl;
                break;
            }
            case SHOW_PARTICIPANTS: {
                showParticipants(participantsList);
                break;
            }
            case SHOW_EVENTS: {
                showEvents(eventList);
                break;
            }
        }
        showMenu();
        cout << "Pilih Menu : "; cin >> choose;
    }

    return 0;
}
