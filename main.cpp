#include <iostream>
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
            case ADD_EVENT: {
                string tanggal, bulan, tahun;
                event newEvent;
                adr_event newEventElm;

                cout << "Nama event : "; cin >> newEvent.nama_event;
                cout << "Jenis event : "; cin >> newEvent.jenis_event;
                cout << "Tanggal pelaksanaan : "; cin >> tanggal;
                cout << "Bulan pelaksanaan : "; cin >> bulan;
                cout << "Tahun pelaksanaan : "; cin >> tahun;
                newEvent.tanggal_pelaksanaan = tanggal + " " + bulan + " " + tahun;
                cout << "Tempat pelaksanaan : "; cin >> newEvent.tempat_pelaksanaan;
                cout << "Quota Maks : "; cin >> newEvent.quota_maks;
                newEvent.jumlah = 0;

                newEventElm = createElmEvent(newEvent);
                insertEvent(eventList, newEventElm);
                break;
            }
            case REMOVE_EVENT: {
                adr_event removeEvent;
                cout << "REMOVE EVENT" << endl;
                // deleteFirstEvent(eventList, removeEvent);
                deleteLastEvent(eventList, removeEvent);
                break;
            }
            case SHOW_EVENT: {
                showEvents(eventList);
                break;
            }
            case SHOW_PARTICIPANT: {
                cout << "SHOW PARTICIPANT" << endl;
                break;
            }
            case ADD_PESERTA: {
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
            case SHOW_PESERTA: {
                cout << "================"<<endl;
                // showPeserta(participantsList);
                break;
            }
            case SEARCH_EVENT: {
                adr_event P;
                string nama;
                cout << "Masukkan Nama Event";
                cin >> nama;
                P = searchElm(eventList,nama);
                cout << info(P).nama_event << endl;
                break;
            }
        }
        showMenu();
        cout << "Pilih Menu : "; cin >> choose;
    }

    return 0;
}
