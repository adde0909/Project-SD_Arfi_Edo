//tolong buatkan program sederhana dengan tema "Pengelolaan Data Bengkel Motor" yang didalamnya terdapat linked lis dan queue serta ada 2 struct didalamnya. Program ini didalmnya memiliki menu tambah antrian motor yang ingin diperbaiki yang didalamnya memiliki merk motor, tipe motor, tahun motor, dan keluhan motor; menampilkan antrian motor yang ada, total antriannya dan total pendapatan, serta tampilannya berbentuk tabel yang rapi; mengedit antrian motor ; menghapus antrian motor; dan saat antrian dihapus ada juga program pembayaran perbaikan motor tersebut.
//tolong juga kualifikasi keluhan motor sudah di tentukan harga perbaikannya.
//program sederhana yang mudah dipahami oleh pemula.
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Struct for Motor data
struct Motor {
    string merk;
    string tipe;
    int tahun;
    string keluhan;
    int hargaPerbaikan;
    Motor* next;
};

// Struct for Queue
struct Queue {
    Motor* front;
    Motor* rear;
    int totalAntrian;
    int totalPendapatan;
};

// Function prototypes
//void initQueue(Queue &q);
//bool isEmpty(Queue &q);
//void tambahAntrian(Queue &q);
//void tampilkanAntrian(Queue &q);
//void editAntrian(Queue &q);
//void hapusAntrian(Queue &q);
//int hargaPerbaikan(string keluhan);
//void pembayaran(int harga);


void initQueue(Queue &q) {
    q.front = nullptr;
    q.rear = nullptr;
    q.totalAntrian = 0;
    q.totalPendapatan = 0;
}

bool isEmpty(Queue &q) {
    return q.front == nullptr;
}

void tambahAntrian(Queue &q) {
    Motor* baru = new Motor;
    cout << "Masukkan merk motor: ";
    getline(cin, baru->merk);
    cout << "Masukkan tipe motor: ";
    getline(cin, baru->tipe);
    cout << "Masukkan tahun motor: ";
    cin >> baru->tahun;
    cin.ignore();
    cout << "Masukkan keluhan motor (Ganti Oli, Ganti Ban, Servis Mesin, Ganti Aki): ";
    getline(cin, baru->keluhan);
    baru->hargaPerbaikan = hargaPerbaikan(baru->keluhan);
    baru->next = nullptr;

    if (isEmpty(q)) {
        q.front = baru;
        q.rear = baru;
    } else {
        q.rear->next = baru;
        q.rear = baru;
    }
    q.totalAntrian++;
    cout << "Antrian berhasil ditambahkan.\n";
}

void tampilkanAntrian(Queue &q) {
    if (isEmpty(q)) {
        cout << "Antrian kosong.\n";
        return;
    }
    cout << left << setw(5) << "No" 
         << setw(15) << "Merk" 
         << setw(15) << "Tipe" 
         << setw(10) << "Tahun" 
         << setw(20) << "Keluhan" 
         << setw(15) << "Harga Perbaikan" << endl;
    cout << string(80, '=') << endl;

    Motor* current = q.front;
    int no = 1;
    int totalHarga = 0;
    while(current != nullptr) {
        cout << left << setw(5) << no 
             << setw(15) << current->merk 
             << setw(15) << current->tipe 
             << setw(10) << current->tahun 
             << setw(20) << current->keluhan 
             << "Rp " << current->hargaPerbaikan << endl;
        totalHarga += current->hargaPerbaikan;
        current = current->next;
        no++;
    }
    cout << string(80, '=') << endl;
    cout << "Total Antrian: " << q.totalAntrian << endl;
    cout << "Total Pendapatan: Rp " << totalHarga << endl;
}

void editAntrian(Queue &q) {
    if (isEmpty(q)) {
        cout << "Antrian kosong, tidak bisa diedit.\n";
        return;
    }
    int no;
    cout << "Masukkan nomor antrian yang ingin diedit: ";
    cin >> no;
    cin.ignore();

    if (no < 1 || no > q.totalAntrian) {
        cout << "Nomor antrian tidak valid.\n";
        return;
    }

    Motor* current = q.front;
    for (int i = 1; i < no; i++) {
        current = current->next;
    }

    cout << "Edit merk motor (sekarang: " << current->merk << "): ";
    getline(cin, current->merk);
    cout << "Edit tipe motor (sekarang: " << current->tipe << "): ";
    getline(cin, current->tipe);
    cout << "Edit tahun motor (sekarang: " << current->tahun << "): ";
    cin >> current->tahun;
    cin.ignore();
    cout << "Edit keluhan motor (sekarang: " << current->keluhan << "): ";
    getline(cin, current->keluhan);
    current->hargaPerbaikan = hargaPerbaikan(current->keluhan);

    cout << "Data antrian berhasil diedit.\n";
}

void hapusAntrian(Queue &q) {
    if (isEmpty(q)) {
        cout << "Antrian kosong, tidak bisa dihapus.\n";
        return;
    }
    Motor* temp = q.front;
    cout << "Menghapus antrian motor merk: " << temp->merk << ", tipe: " << temp->tipe << endl;
    pembayaran(temp->hargaPerbaikan);

    q.front = q.front->next;
    delete temp;
    q.totalAntrian--;

    if (q.front == nullptr) {
        q.rear = nullptr;
    }
    cout << "Antrian berhasil dihapus.\n";
}

int hargaPerbaikan(string keluhan) {
    if (keluhan == "Ganti Oli") return 50000;
    else if (keluhan == "Ganti Ban") return 150000;
    else if (keluhan == "Servis Mesin") return 300000;
    else if (keluhan == "Ganti Aki") return 200000;
    else return 0;
}

void pembayaran(int harga) {
    cout << "Total pembayaran: Rp " << harga << endl;
    cout << "Terima kasih atas pembayaran Anda.\n";
}


int main() {
    Queue q;
    initQueue(q);
    int pilihan;

    do {
        cout << "\n=== Pengelolaan Data Bengkel Motor ===\n";
        cout << "1. Tambah Antrian Motor\n";
        cout << "2. Tampilkan Antrian Motor\n";
        cout << "3. Edit Antrian Motor\n";
        cout << "4. Hapus Antrian Motor (Pembayaran)\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch(pilihan) {
            case 1:
                tambahAntrian(q);
                break;
            case 2:
                tampilkanAntrian(q);
                break;
            case 3:
                editAntrian(q);
                break;
            case 4:
                hapusAntrian(q);
                break;
            case 5:
                cout << "Terima kasih telah menggunakan program ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while(pilihan != 5);

    return 0;
}