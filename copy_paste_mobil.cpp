#include<iostream>
#include<iomanip>
#include<string>

using namespace std;

typedef struct mobil_list {
    string plat_nomor;
    string merk_mobil;
    int harga_sewa_per_hari;
    string status;
    mobil_list *next;
} mobil;

typedef struct rental_list {
    string id_rental;
    string nama_penyewa;
    string plat_mobil_disewa;
    int lama_sewa;
    int total_biaya;
    rental_list *next;
} rental;

mobil *head_mobil, *tail_mobil;
rental *head_rental, *tail_rental;

int total_pendapatan = 0;

void tambah_mobil(mobil *&H, mobil *&T) {
    mobil* mobil_baru = new mobil;
    cout << "\n===== Tambah Mobil Baru =====\n";
    cout << "Masukkan Plat Nomor      : "; cin.ignore(); getline(cin, mobil_baru->plat_nomor);
    cout << "Masukkan Merk Mobil      : "; getline(cin, mobil_baru->merk_mobil);
    cout << "Masukkan Harga Sewa/hari : "; cin >> mobil_baru->harga_sewa_per_hari;
    mobil_baru->status = "Tersedia";
    mobil_baru->next = NULL;

    if (H == NULL) {
        H = mobil_baru;
        T = mobil_baru;
    } else {
        T->next = mobil_baru;
        T = mobil_baru;
    }
    cout << "Mobil baru berhasil ditambahkan!\n";
}

void cetak_mobil(mobil *H) {
    if (H == NULL) {
        cout << "Belum ada data mobil di dalam sistem.\n";
        return;
    }
    mobil *dummy = H;
    cout << "\n================= DAFTAR SEMUA MOBIL =================\n";
    cout << "--------------------------------------------------------\n";
    cout << setw(4) << "No" << setw(15) << "Plat Nomor" << setw(15) << "Merk Mobil" << setw(15) << "Harga/hari" << setw(12) << "Status" << endl;
    cout << "--------------------------------------------------------\n";
    int i = 0;
    while (dummy != NULL) {
        i++;
        cout << setw(4) << i
             << setw(15) << dummy->plat_nomor
             << setw(15) << dummy->merk_mobil
             << setw(15) << dummy->harga_sewa_per_hari
             << setw(12) << dummy->status << endl;
        dummy = dummy->next;
    }
    cout << "--------------------------------------------------------\n";
}

void tambah_rental(rental *&H_rental, rental *&T_rental, mobil *H_mobil) {
    cout << "\n===== Tambah Transaksi Rental =====\n";
    
    cout << "Daftar mobil yang tersedia untuk disewa:\n";
    mobil *cek_mobil = H_mobil;
    bool ada_mobil_tersedia = false;
    int no = 1;
    while(cek_mobil != NULL){
        if(cek_mobil->status == "Tersedia"){
            cout << " [" << no++ << "] Plat: " << setw(10) << left << cek_mobil->plat_nomor 
                 << " | Merk: " << setw(12) << left << cek_mobil->merk_mobil 
                 << " | Harga: Rp." << cek_mobil->harga_sewa_per_hari << "/hari\n";
            ada_mobil_tersedia = true;
        }
        cek_mobil = cek_mobil->next;
    }

    if(!ada_mobil_tersedia){
        cout << "\nMaaf, tidak ada mobil yang tersedia untuk disewa saat ini.\n";
        return;
    }

    string plat_pilihan;
    cout << "\nMasukkan Plat Nomor mobil yang akan disewa: ";
    cin.ignore();
    getline(cin, plat_pilihan);

    mobil *mobil_dipilih = H_mobil;
    while(mobil_dipilih != NULL && (mobil_dipilih->plat_nomor != plat_pilihan || mobil_dipilih->status != "Tersedia")){
        mobil_dipilih = mobil_dipilih->next;
    }

    if(mobil_dipilih == NULL){
        cout << "Mobil dengan plat nomor tersebut tidak ditemukan atau sedang disewa.\n";
        return;
    }

    rental* rental_baru = new rental;
    cout << "Masukkan ID Rental         : "; getline(cin, rental_baru->id_rental);
    cout << "Masukkan Nama Penyewa      : "; getline(cin, rental_baru->nama_penyewa);
    cout << "Masukkan Lama Sewa (hari)  : "; cin >> rental_baru->lama_sewa;

    rental_baru->plat_mobil_disewa = mobil_dipilih->plat_nomor;
    rental_baru->total_biaya = rental_baru->lama_sewa * mobil_dipilih->harga_sewa_per_hari;
    rental_baru->next = NULL;

    if (H_rental == NULL) {
        H_rental = rental_baru;
        T_rental = rental_baru;
    } else {
        T_rental->next = rental_baru;
        T_rental = rental_baru;
    }

    mobil_dipilih->status = "Disewa";

    cout << "\nRental baru berhasil ditambahkan!\n";
    cout << "Total Biaya Sewa: Rp." << rental_baru->total_biaya << endl;
}

void cetak_rental(rental *H) {
    if (H == NULL) {
        cout << "Belum ada data rental yang aktif.\n";
        return;
    }
    rental *dummy = H;
    int i = 0;
    cout << "\n====================== DAFTAR RENTAL AKTIF ======================\n";
    cout << "-----------------------------------------------------------------\n";
    cout << setw(4) << "No" << 
            setw(12) << "ID Rental" << 
            setw(18) << "Nama Penyewa" <<
            setw(15) << "Plat Mobil" <<
            setw(10) << "Lama" << 
            setw(12) << "Total Biaya" << endl;
    cout << "-----------------------------------------------------------------\n";
    while (dummy != NULL) {
        i++;
        cout << setw(4) << i
             << setw(12) << dummy->id_rental
             << setw(18) << dummy->nama_penyewa
             << setw(15) << dummy->plat_mobil_disewa
             << setw(8) << dummy->lama_sewa << " hari"
             << setw(12) << dummy->total_biaya << endl;
        dummy = dummy->next;
    }
    cout << "-----------------------------------------------------------------\n";
    cout << "Saat ini ada " << i << " rental yang aktif.\n";
}

void edit_rental(rental *H_rental, mobil *H_mobil) {
    if (H_rental == NULL) {
        cout << "Data rental kosong.\n";
        return;
    }

    cetak_rental(H_rental);
    string id_cari;
    cout << "\nMasukkan ID Rental yang ingin diedit: ";
    cin.ignore();
    getline(cin, id_cari);

    rental *find = H_rental;
    mobil *mobil_terkait = NULL;
    bool ditemukan = false;
    while (find != NULL) {
        if (find->id_rental == id_cari) {
            ditemukan = true;
            
            mobil_terkait = H_mobil;
            while(mobil_terkait != NULL && mobil_terkait->plat_nomor != find->plat_mobil_disewa){
                mobil_terkait = mobil_terkait->next;
            }

            if(mobil_terkait == NULL){
                cout << "Error: Data mobil terkait tidak ditemukan. Tidak bisa mengedit.\n";
                return;
            }

            cout << "\nData ditemukan:\n";
            cout << "ID Rental       : " << find->id_rental << endl;
            cout << "Nama Penyewa    : " << find->nama_penyewa << endl;
            cout << "Lama Sewa (hari): " << find->lama_sewa << endl;

            char ya;
            cout << "\nApakah ingin mengedit data ini? (y/n): ";
            cin >> ya;
            if (ya == 'y' || ya == 'Y') {
                cin.ignore();
                cout << "Nama Penyewa baru      : "; getline(cin, find->nama_penyewa);
                cout << "Lama Sewa baru (hari)  : "; cin >> find->lama_sewa;
                
                find->total_biaya = find->lama_sewa * mobil_terkait->harga_sewa_per_hari;
                cout << "Data berhasil diubah. Total biaya baru: Rp." << find->total_biaya << endl;
            }
            break;
        }
        find = find->next;
    }
    if (!ditemukan) {
        cout << "Rental dengan ID " << id_cari << " tidak ditemukan.\n";
    }
}

void selesaikan_rental(rental *&H_rental, mobil *H_mobil) {
    if(H_rental == NULL){
        cout << "Tidak ada rental aktif yang bisa diselesaikan.\n";
        return;
    }
    
    rental* del_rental = H_rental;
    int pembayaran, kembalian;
    
    cout << "\n===== Penyelesaian dan Pembayaran Rental =====\n";
    cout << "Berikut adalah data rental yang akan diselesaikan (antrian pertama):\n";
    cout << "ID Rental       : " << del_rental->id_rental << endl;
    cout << "Nama Penyewa    : " << del_rental->nama_penyewa << endl;
    cout << "Plat Mobil      : " << del_rental->plat_mobil_disewa << endl;
    cout << "----------------------------------------------\n";
    cout << "TOTAL TAGIHAN   : Rp." << del_rental->total_biaya << endl;
    cout << "----------------------------------------------\n";
    
    char ya;
    cout << "Lanjutkan ke pembayaran? (y/t): "; cin >> ya;
    if (ya == 'Y' || ya == 'y') {
        
        bayar_ulang:
        cout << "Tagihan sebesar Rp." << del_rental->total_biaya << ". Masukkan uang pembayaran : Rp."; 
        cin >> pembayaran;

        if (pembayaran < del_rental->total_biaya) {
            cout << "Uang tidak cukup! Silakan lakukan pembayaran ulang.\n";
            goto bayar_ulang;
        } 
        
        if (pembayaran > del_rental->total_biaya) {
            kembalian = pembayaran - del_rental->total_biaya;
            cout << "Kembalian Anda : Rp." << kembalian << endl;
        } else {
            cout << "Uang pas, terima kasih!\n";
        }

        total_pendapatan += del_rental->total_biaya;

        string plat_kembali = del_rental->plat_mobil_disewa;
        mobil* mobil_dikembalikan = H_mobil;
        while(mobil_dikembalikan != NULL && mobil_dikembalikan->plat_nomor != plat_kembali){
            mobil_dikembalikan = mobil_dikembalikan->next;
        }
        if(mobil_dikembalikan != NULL){
            mobil_dikembalikan->status = "Tersedia";
            cout << "Status mobil " << plat_kembali << " telah dikembalikan menjadi Tersedia.\n";
        }

        H_rental = del_rental->next;
        delete del_rental;
        cout << "Rental telah berhasil diselesaikan!\n";

    } else {
        cout << "Proses pembayaran dibatalkan.\n";
    }
}

void hapus_rental(rental *&H_rental, mobil *H_mobil) {
    if (H_rental == NULL) {
        cout << "\nTidak ada data rental yang aktif untuk dihapus.\n";
        return;
    }
    cetak_rental(H_rental);
    string id_hapus;
    cout << "\nMasukkan ID Rental yang akan dibatalkan/dihapus: ";
    cin.ignore();
    getline(cin, id_hapus);
    rental *current = H_rental;
    rental *previous = NULL;
    while (current != NULL && current->id_rental != id_hapus) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) {
        cout << "\nData rental dengan ID '" << id_hapus << "' tidak ditemukan.\n";
        return;
    }

    string plat_mobil_batal = current->plat_mobil_disewa;

    if (previous == NULL) { 
        H_rental = current->next;
    } else { 
        previous->next = current->next;
    }
    delete current; 

    mobil* mobil_update = H_mobil;
    while(mobil_update != NULL && mobil_update->plat_nomor != plat_mobil_batal){
        mobil_update = mobil_update->next;
    }
    if(mobil_update != NULL){
        mobil_update->status = "Tersedia";
    }

    cout << "\nData rental dengan ID '" << id_hapus << "' berhasil dihapus.\n";
    cout << "Status mobil dengan plat " << plat_mobil_batal << " telah dikembalikan menjadi 'Tersedia'.\n";
}

int main() {
    int pilih = 0;
    do {
        system("cls");
        cout << "====================================\n";
        cout << "   Sistem Manajemen Rental Mobil\n";
        cout << "====================================\n";
        cout << "MENU UTAMA:\n";
        cout << "1. Tambah Rental Baru\n";
        cout << "2. Selesaikan Rental & Pembayaran\n";
        cout << "3. Lihat Daftar Rental Aktif\n";
        cout << "4. Edit Data Rental\n";
        cout << "5. Hapus Data Rental\n";
        cout << "------------------------------------\n";
        cout << "MENU MANAJEMEN MOBIL:\n";
        cout << "6. Tambah Mobil Baru\n";
        cout << "7. Lihat Daftar Semua Mobil\n";
        cout << "------------------------------------\n";
        cout << "LAPORAN:\n";
        cout << "8. Lihat Total Pendapatan\n";
        cout << "0. Keluar\n";
        cout << "====================================\n";
        cout << "Pilih Menu : "; cin >> pilih;

        switch (pilih) {
            case 1: tambah_rental(head_rental, tail_rental, head_mobil); break;
            case 2: selesaikan_rental(head_rental, head_mobil); break;
            case 3: cetak_rental(head_rental); break;
            case 4: edit_rental(head_rental, head_mobil); break;
            case 5: hapus_rental(head_rental, head_mobil); break;
            case 6: tambah_mobil(head_mobil, tail_mobil); break;
            case 7: cetak_mobil(head_mobil); break;
            case 8: cout << "\nTotal Pendapatan Rental saat ini adalah: Rp." << total_pendapatan << endl; break;
            case 0: cout << "\nTerima kasih telah menggunakan sistem ini.\n"; break;
            default: cout << "\nPilihan tidak valid. Silakan coba lagi.\n"; break;
        }
        system("pause");
    } while (pilih != 0);
    
    return 0;
}