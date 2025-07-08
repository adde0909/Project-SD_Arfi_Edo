#include <iostream>
#include <string>

using namespace std;

struct Motor {
    string merk;
    string tipe;
    int tahun;
    string keluhan;
    int biaya;
};

struct Node {
    Motor motor;
    Node* next;
};

Node* front = nullptr;
Node* rear = nullptr;
int totalAntrian = 0;
int totalPendapatan = 0;

bool isEmpty() {
    return front == nullptr;
}

void enqueue(Motor m) {
    Node* newNode = new Node;
    newNode->motor = m;
    newNode->next = nullptr;
    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    totalAntrian++;
}

void display() {
    if (isEmpty()) {
        cout << "Antrian kosong." << endl;
        return;
    }
    cout << "No\tMerk\tTipe\tTahun\tKeluhan\t\tBiaya" << endl;
    cout << "--------------------------------------------------" << endl;
    Node* current = front;
    int no = 1;
    while (current != nullptr) {
        cout << no << "\t" << current->motor.merk << "\t" << current->motor.tipe << "\t"
             << current->motor.tahun << "\t" << current->motor.keluhan << "\t" << current->motor.biaya << endl;
        current = current->next;
        no++;
    }
    cout << "--------------------------------------------------" << endl;
    cout << "Total antrian: " << totalAntrian << endl;
    cout << "Total pendapatan: Rp " << totalPendapatan << endl;
}

Node* getNodeAt(int nomor) {
    if (nomor < 1 || nomor > totalAntrian) {
        return nullptr;
    }
    Node* current = front;
    for (int i = 1; i < nomor; i++) {
        current = current->next;
    }
    return current;
}

void edit(int nomor) {
    if (isEmpty()) {
        cout << "Antrian kosong." << endl;
        return;
    }
    Node* node = getNodeAt(nomor);
    if (node == nullptr) {
        cout << "Nomor antrian tidak valid." << endl;
        return;
    }
    cout << "Edit data motor antrian nomor " << nomor << ":" << endl;
    cout << "Merk (sekarang: " << node->motor.merk << "): ";
    getline(cin, node->motor.merk);
    cout << "Tipe (sekarang: " << node->motor.tipe << "): ";
    getline(cin, node->motor.tipe);
    cout << "Tahun (sekarang: " << node->motor.tahun << "): ";
    cin >> node->motor.tahun;
    cin.ignore();
    cout << "Keluhan (sekarang: " << node->motor.keluhan << "): ";
    getline(cin, node->motor.keluhan);
    cout << "Biaya (sekarang: " << node->motor.biaya << "): ";
    cin >> node->motor.biaya;
    cin.ignore();
    cout << "Data berhasil diupdate." << endl;
}

void dequeue() {
    if (isEmpty()) {
        cout << "Antrian kosong." << endl;
        return;
    }
    Node* temp = front;
    cout << "Pembayaran motor merk " << temp->motor.merk << ", tipe " << temp->motor.tipe << endl;
    cout << "Biaya: Rp " << temp->motor.biaya << endl;
    cout << "Masukkan jumlah pembayaran: Rp ";
    int bayar;
    cin >> bayar;
    cin.ignore();
    if (bayar >= temp->motor.biaya) {
        int kembalian = bayar - temp->motor.biaya;
        cout << "Pembayaran berhasil. Kembalian: Rp " << kembalian << endl;
        totalPendapatan += temp->motor.biaya;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        totalAntrian--;
    } else {
        cout << "Pembayaran kurang. Silakan coba lagi." << endl;
    }
}

void menu() {
    cout << "\nPengelolaan Data Bengkel Motor" << endl;
    cout << "1. Tambah antrian motor" << endl;
    cout << "2. Tampilkan antrian motor" << endl;
    cout << "3. Edit antrian motor" << endl;
    cout << "4. Hapus antrian motor (pembayaran)" << endl;
    cout << "5. Keluar" << endl;
    cout << "Pilih menu: ";
}

int main() {
    int pilihan;

    do {
        menu();
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: {
                Motor m;
                cout << "Merk motor: ";
                getline(cin, m.merk);
                cout << "Tipe motor: ";
                getline(cin, m.tipe);
                cout << "Tahun motor: ";
                cin >> m.tahun;
                cin.ignore();
                cout << "Keluhan motor: ";
                getline(cin, m.keluhan);
                cout << "Biaya perbaikan: Rp ";
                cin >> m.biaya;
                cin.ignore();
                enqueue(m);
                cout << "Motor berhasil ditambahkan ke antrian." << endl;
                break;
            }
            case 2:
                display();
                break;
            case 3: {
                if (isEmpty()) {
                    cout << "Antrian kosong." << endl;
                } else {
                    int nomor;
                    cout << "Nomor antrian yang ingin diedit: ";
                    cin >> nomor;
                    cin.ignore();
                    edit(nomor);
                }
                break;
            }
            case 4:
                dequeue();
                break;
            case 5:
                cout << "Terima kasih telah menggunakan program ini." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 5);

    // Clean up remaining nodes
    while (!isEmpty()) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }

    return 0;
}
