#include <iostream>
#include <string>
#include <iomanip>
//sdddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
using namespace std;
//ASDASDASDASDSADASDASDADASDASDSADAS
struct KTPNode {
    string nama;
    string nik;
    KTPNode* next;
};

class KTPQueue {
private:
    KTPNode* front;
    KTPNode* rear;

public:
    KTPQueue() {
        front = nullptr;
        rear = nullptr;
    }

    ~KTPQueue() {
        while (front != nullptr) {
            KTPNode* temp = front;
            front = front->next;
            delete temp;
        }
    }

    bool nikExists(const string& nik) {
        KTPNode* current = front;
        while (current != nullptr) {
            if (current->nik == nik) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void enqueue(const string& nama, const string& nik) {
        if (nikExists(nik)) {
            cout << "NIK sudah ada. Silakan masukkan NIK yang berbeda." << endl;
            return;
        }
        KTPNode* newNode = new KTPNode{nama, nik, nullptr};
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        cout << "Data KTP berhasil ditambahkan." << endl;
    }

    void printQueue() {
        if (front == nullptr) {
            cout << "Antrian KTP kosong." << endl;
            return;
        }
        cout << "Daftar Antrian Pembuatan KTP Desa" << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "| No | Nama Lengkap              | NIK           |" << endl;
        cout << "-------------------------------------------------" << endl;
        KTPNode* current = front;
        int nomor = 1;
        while (current != nullptr) {
            cout << "| " << setw(2) << nomor << " | " << setw(25) << left << current->nama << " | " << setw(13) << current->nik << " |" << endl;
            current = current->next;
            nomor++;
        }
        cout << "-------------------------------------------------" << endl;
    }

    KTPNode* searchByNIK(const string& nik) {
        KTPNode* current = front;
        while (current != nullptr) {
            if (current->nik == nik) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void editData(const string& nik) {
        if (front == nullptr) {
            cout << "Antrian KTP kosong. Silakan tambahkan data terlebih dahulu." << endl;
            return;
        }
        KTPNode* node = searchByNIK(nik);
        if (node == nullptr) {
            cout << "Data dengan NIK " << nik << " tidak ditemukan." << endl;
            return;
        }
        cout << "Data ditemukan. Silakan masukkan data baru:" << endl;
        cout << "Nama baru: ";cin>>node->nama;
        cout << "NIK baru : ";cin>>node->nik;
        cout << "Data berhasil diperbarui." << endl;
    }

    void deleteData(const string& nik) {
        if (front == nullptr) {
            cout << "Antrian KTP kosong. Tidak ada data yang bisa dihapus." << endl;
            return;
        }
        if (front->nik == nik) {
            KTPNode* temp = front;
            front = front->next;
            if (front == nullptr) {
                rear = nullptr;
            }
            delete temp;
            cout << "Data dengan NIK " << nik << " berhasil dihapus." << endl;
            return;
        }
        KTPNode* current = front;
        while (current->next != nullptr && current->next->nik != nik) {
            current = current->next;
        }
        if (current->next == nullptr) {
            cout << "Data dengan NIK " << nik << " tidak ditemukan." << endl;
            return;
        }
        KTPNode* temp = current->next;
        current->next = temp->next;
        if (temp == rear) {
            rear = current;
        }
        delete temp;
        cout << "Data dengan NIK " << nik << " berhasil dihapus." << endl;
    }
};

int main() {
    KTPQueue queue;
    int pilihan = 0;
    string nik, nama;

    do {
        system("cls");
        cout << "=== Program Antrian Pembuatan KTP Desa ===" << endl;
        cout << "1. Tambah Data Penduduk" << endl;
        cout << "2. Cetak Data Antrian" << endl;
        cout << "3. Edit Data Penduduk" << endl;
        cout << "4. Hapus Data Penduduk" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih menu (1-5): ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                cout << "Masukkan Nama Lengkap: ";
                getline(cin, nama);
                do {
                    cout << "Masukkan NIK: ";
                    getline(cin, nik);
                    if (queue.nikExists(nik)) {
                        cout << "NIK sudah ada. Silakan masukkan NIK yang berbeda." << endl;
                    } else {
                        break;
                    }
                } while (true);
                queue.enqueue(nama, nik);
                system("pause");
                break;
            case 2:
                queue.printQueue();
                system("pause");
                break;
            case 3:
                queue.printQueue();
                cout << "Masukkan NIK data yang ingin diedit: ";
                cin>>nik;
                queue.editData(nik);
                system("pause");
                break;
            case 4:
                queue.printQueue();
                cout << "Masukkan NIK data yang ingin dihapus: ";
                cin>>nik;
                queue.deleteData(nik);
                system("pause");
                break;
            case 5:
                cout << "### TERIMA KASIH TELAH MENGGUNAKAN PROGRAM INI ###" << endl;
                system("pause");
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                system("pause");
        }
        cout << endl;
    } while (pilihan != 5);

    return 0;
}
