#include <iostream>     //PENGOLAHAN DATA BENGKEL MOTOR
#include <iomanip>
using namespace std;

typedef struct motor_list{
    string merk;
    string tipe;
    string tahun;
}motor;

typedef struct pelanggan_list{
    string nama;
    string no_hp;
    motor jenis_motor;
    string keluhan;
    int biaya;
    pelanggan_list *next;
}pelanggan;

typedef struct stock_list{
    string barang;
    int jml_stock;
    int harga;
    stock_list *next;
}stock;

pelanggan *front_pelanggan, *tail_pelanggan;
stock *front_stock, *tail_stock;

int pendapatan = 0;
int i=0;

void add_pelanggan(pelanggan *&F_Pelanggan, pelanggan *&T_Pelanggan){
    pelanggan *newPelanggan;
    newPelanggan = new pelanggan;
    newPelanggan->next = nullptr;

    cout << "Isi data antrian pelanggan bengkel :\n";
    cin.ignore();
    cout << "Nama Pelanggan : "; getline(cin, newPelanggan->nama);
    cout << "No. HP         : "; cin >> newPelanggan->no_hp;
    cout << "Merk Motor     : "; cin >> newPelanggan->jenis_motor.merk;
    cin.ignore();
    cout << "Tipe Motor     : "; getline(cin, newPelanggan->jenis_motor.tipe);
    cout << "Tahun Keluaran : "; cin >> newPelanggan->jenis_motor.tahun;
    cin.ignore();
    cout << "Keluhan Motor  : "; getline(cin, newPelanggan->keluhan);

    if (F_Pelanggan==nullptr){
        F_Pelanggan=newPelanggan;
        T_Pelanggan=newPelanggan;
    }
    else {
        T_Pelanggan->next = newPelanggan;
        T_Pelanggan=newPelanggan;
    }
    cout << "Data baru berhasil ditambahkan\n";

}

void add_sparepart(stock *&F_Stock, stock *&T_Stock) {
    stock *newStock = new stock;
    newStock->next = nullptr;
    int pilihan;

    cout << "Barang apa berikut ini yg ingin ditambah stocknya :\n";
    cout << "1. Oli 1L" << endl;
    cout << "2. Minyak Rem 300mL" << endl;
    cout << "3. Ban" << endl;
    cout << "4. Busi" << endl;
    cout << "5. Aki" << endl;
    cout << "Pilih barang (1-5): ";
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            newStock->barang = "Oli 1L";
            break;
        case 2:
            newStock->barang = "Minyak Rem 300mL";
            break;
        case 3:
            newStock->barang = "Ban";
            break;
        case 4:
            newStock->barang = "Busi";
            break;
        case 5:
            newStock->barang = "Aki";
            break;
        default:
            cout << "Pilihan tidak valid. Stock tidak ditambahkan.\n";
            delete newStock;
    }

    if (pilihan==1){
        newStock->harga = 60000;
    }
    else if (pilihan==2){
        newStock->harga = 10000;
    }
    else if (pilihan==3){
        newStock->harga = 150000;
    }
    else if (pilihan==4){
        newStock->harga = 25000;
    }
    else if (pilihan==5){
        newStock->harga = 175000;
    }

    cout << "Jumlah stock yang ingin ditambahkan : ";
    cin >> newStock->jml_stock;


    if (F_Stock == nullptr) {
        F_Stock = newStock;
        T_Stock = newStock;
    } else {
        T_Stock->next = newStock;
        T_Stock = newStock;
    }

    cout << "Stock baru berhasil ditambahkan: " << newStock->barang << " sebanyak " << newStock->jml_stock << " unit.\n";
}

void print_sparepart(stock *F_Stock, stock *T_Stock){

    stock *dummy;
    dummy = new stock;
    dummy = F_Stock;
    i = 0;
    
    cout << "Daftar Sparepart Yang Tersedia di Bengkel\n";
    cout << "------------------------------------------------\n";
    cout << "| No |    Nama Barang    | Stock |    Harga    |\n";
    cout << "------------------------------------------------\n";
    while (dummy!=nullptr){
        i++;
        cout << "| " << setw(2) << i << " | " << setw(17) << dummy -> barang << " | " << setw(5) << dummy -> jml_stock << " | " << setw(11)
        << dummy -> harga << " |" << endl;
        dummy = dummy -> next;
    }
    cout << "------------------------------------------------\n";
    delete dummy;
}

void transaksi_sparepart(stock *&F_Stock, stock *&T_Stock){
    stock *sparepart;
    sparepart = new stock;
    int bayar, kembalian, jumlah, harga;
    int no_urut = 0;

    print_sparepart(front_stock,tail_stock);

    kembali:
    cout << "Sparepart apa yg ingin Anda beli (Masukkan no.urut) ? ";cin>>no_urut;

    if ((no_urut < 1) or (no_urut > i)){
        cout << "Nomor Urut tidak ada, Mohon ulangi\n";
        goto kembali; 
    }

    stock *dummy;
    dummy = new stock;
    dummy = F_Stock;

    int ii=0;
    while (dummy != NULL){
        ii++;
        if(ii == no_urut){
           sparepart = dummy;
           
           cout << "Harga sparepart " << sparepart->barang << " = " << sparepart->harga << endl;

           back :
           cout << "Berapa " << sparepart->barang << " yang ingin Anda beli ? "; cin >> jumlah;
           if (sparepart->jml_stock < jumlah){
            cout << "Maaf stock tidak tersedia, Mohon ulangi\n"; goto back;
           }
           else {

               harga = sparepart->harga * jumlah;
               cout << "Total harga yang perlu dibayarkan = " << harga << endl;
               
               balek :
               cout << "Masukkan uang nominal : "; cin >> bayar;
               if (bayar < harga){
                    cout << "Uang Anda kurang, mohon ulangi\n"; goto balek;
               }
               else {
                    kembalian = bayar - harga;
                    cout << "Terimakasih telah membeli di bengkel kami!\n";
                    cout << "Kembalian = " << kembalian << endl;
               
                    pendapatan = pendapatan + harga;
               
                    sparepart->jml_stock = sparepart->jml_stock - jumlah;
               }
            }
        }
        dummy = dummy->next;
    }

}


void print_pelanggan(pelanggan *F_Pelanggan, pelanggan *T_Pelanggan){

    pelanggan *dummy;
    dummy = new pelanggan;
    dummy = F_Pelanggan;
    i = 0;
    
    cout << "Daftar Data Antrian di Bengkel Service Motor\n";
    cout << "---------------------------------------------------------------------------------------------------------------\n";
    cout << "|    |                      |              |                        Motor                  |                  |\n";
    cout << "| No |    Nama Pelanggan    |     No HP    |-----------------------------------------------|      Keluhan     |\n";
    cout << "|    |                      |              |      Merk      |       Tipe       |   Tahun   |                  |\n";
    cout << "---------------------------------------------------------------------------------------------------------------\n";
    while (dummy!=nullptr){
        i++;
        cout << "| " << setw(2) << i << " | " << setw(20) << dummy -> nama << " | " << setw(12) << dummy -> no_hp << " | " << setw(14)
        << dummy -> jenis_motor.merk << " | " << setw(16) << dummy -> jenis_motor.tipe << " | " << setw(9) << dummy -> jenis_motor.tahun 
        << " | " << setw(16) << dummy -> keluhan << " |" << endl;
        dummy = dummy -> next;
    }
    cout << "---------------------------------------------------------------------------------------------------------------\n";
    cout << "Motor yang harus diservice hari ini sejumlah " << i << " motor" << endl;
    delete dummy;
}

void transaksi_first(pelanggan *&F_Pelanggan, pelanggan *&T_Pelanggan){
    pelanggan *antrian;
    antrian = new pelanggan;
    antrian = F_Pelanggan;
    int pembayaran, kembalian;
    int jml=0;

    cout << "Lakukan transaksi untuk antrian :\n";
    cout << "Nama Pelanggan : " << antrian->nama << endl;
    cout << "No. HP         : " << antrian->no_hp << endl;
    cout << "Merk Motor     : " << antrian->jenis_motor.merk << endl;
    cout << "Tipe Motor     : " << antrian->jenis_motor.tipe << endl;
    cout << "Tahun Keluaran : " << antrian->jenis_motor.tahun << endl;
    cout << "Keluhan Motor  : " << antrian->keluhan << endl;
    cout << "Total biaya perbaikan  : ";cin >> jml;
    ulang :
    cout << "Masukkan nominal uang  : ";
    cin >> pembayaran;

    if (pembayaran < jml){
        cout << "Uangnya kurang! Mohon diulangi\n"; goto ulang;
    }
    else {
        kembalian = pembayaran - jml;
        cout << "Terimakasih telah service di bengkel kami!\n";
        cout << "Kembalian = " << kembalian << endl;

        pendapatan = pendapatan + jml;

        F_Pelanggan = F_Pelanggan->next;
        delete antrian;
    }
}

void print_pendapatan(){
    cout << "Total pendapatan saat ini = Rp " << pendapatan << endl;
}

void edit_keluhan(pelanggan *&F_Pelanggan, pelanggan *&T_Pelanggan){
    pelanggan *edit_kel;
    edit_kel = new pelanggan;
    int nomor_urut = 0;

    print_pelanggan(front_pelanggan,tail_pelanggan);

    bali:
    cout << "Keluhan nomor urut berapa yang ingin di edit ? ";cin>>nomor_urut;

    if ((nomor_urut < 1) or (nomor_urut > i)){
        cout << "Nomor Urut tidak ada, Mohon ulangi\n";
        goto bali; 
    }

    pelanggan *dummy;
    dummy = new pelanggan;
    dummy = F_Pelanggan;

    int ii=0;
    while (dummy != NULL){
        ii++;
        if(ii == nomor_urut){
           edit_kel = dummy;
           
           cout << "Nama Pelanggan : " << edit_kel->nama << endl;
           cout << "No. HP         : " << edit_kel->no_hp << endl;
           cout << "Merk Motor     : " << edit_kel->jenis_motor.merk << endl;
           cout << "Tipe Motor     : " << edit_kel->jenis_motor.tipe << endl;
           cout << "Tahun Keluaran : " << edit_kel->jenis_motor.tahun << endl;
           cout << "Keluhan Motor  : " << edit_kel->keluhan << endl;
           cin.ignore();
           cout << "Tambahkan/Ubah Keluhan yang ada : ";getline(cin,edit_kel->keluhan);
           cout << "Keluhan berhasil diubah !!!"<<endl;
        }
        dummy = dummy->next;
    }

}

int main(){
    front_pelanggan = nullptr;
    tail_pelanggan = nullptr;
    front_stock = nullptr;
    tail_stock = nullptr;
    int pil=0;
    do{
        system("cls");
        cout << "---------PENGOLAHAN DATA BENGKEL MOTOR---------\n";
        cout << "1. Tambah Data Service Pelanggan Baru\n";
        cout << "2. Cetak Daftar Service Pelanggan\n";
        cout << "3. Pembayaran Service Sesuai Antrian\n";
        cout << "4. Edit keluhan Motor\n";
        cout << "5. Cetak Pendapatan Hari ini\n";
        cout << "                      6. Tambah Stock Sparepart\n";
        cout << "                      7. Print Stock Sparepart\n";
        cout << "                      8. Beli Sparepart Saja\n";
        cout << "0. Keluar\n";
        cout << "-----------------------------------------------\n";
        cout << "Pilih : "; cin >> pil;

        switch (pil)
        {
        case 1:
            add_pelanggan(front_pelanggan,tail_pelanggan);
            break;
        
        case 2:
            if (front_pelanggan==nullptr) cout << "Data service kosong\n";
            else
            print_pelanggan(front_pelanggan,tail_pelanggan);
            break;

        case 3:
            if (front_pelanggan==nullptr) cout << "Data service kosong\n";
            else
            transaksi_first(front_pelanggan,tail_pelanggan);
            break;

        case 4:
            if (front_pelanggan==nullptr) cout << "Data service kosong\n";
            else
            edit_keluhan(front_pelanggan,tail_pelanggan);
            break;

        case 5:
            print_pendapatan();
            break;

        case 6:
            add_sparepart(front_stock,tail_stock);
            break;

        case 7:
            if (front_stock==nullptr) cout << "Data stock kosong\n";
            else
            print_sparepart(front_stock,tail_stock);
            break;

        case 8:
            if (front_stock==nullptr) cout << "Data stock kosong\n";
            else
            transaksi_sparepart(front_stock,tail_stock);
            break;

        case 0:
            cout << endl;
            cout << "###TERIMAKASIH TELAH MENGGUNAKAN PROGRAM INI !!!###\n";
            cout << endl;
            break;
        
        default:
            cout << "Salah pilih menu\n";
            break;
        }
        system("pause");

    }while (pil!=0);

    
    delete front_pelanggan;
    delete tail_pelanggan;
    delete front_stock;
    delete tail_stock;

}
