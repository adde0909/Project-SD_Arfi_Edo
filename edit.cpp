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

pelanggan *front, *tail;

int pendapatan = 0;
int i=0;

void add_pelanggan(pelanggan *&F, pelanggan *&T){
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

    if (F==nullptr){
        F=newPelanggan;
        T=newPelanggan;
    }
    else {
        T->next = newPelanggan;
        T=newPelanggan;
    }
    cout << "Data baru berhasil ditambahkan\n";

}

void print_pelanggan(pelanggan *F, pelanggan *T){

    pelanggan *dummy;
    dummy = new pelanggan;
    dummy = F;
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
        << " | " << setw(16) << dummy -> keluhan << " | " << endl;
        dummy = dummy -> next;
    }
    cout << "---------------------------------------------------------------------------------------------------------------\n";
    cout << "Motor yang harus diservice hari ini sejumlah " << i << " motor" << endl;
    delete dummy;
}

void transaksi_first(pelanggan *&F, pelanggan *&T){
    pelanggan *antrian;
    antrian = new pelanggan;
    antrian = F;
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

        F = F->next;
        delete antrian;
    }
}

void print_pendapatan(){
    cout << "Total pendapatan saat ini = Rp " << pendapatan << endl;
}

void edit_keluhan(pelanggan *&F, pelanggan *&T){
    pelanggan *edit_kel;
    edit_kel = new pelanggan;
    int nomor_urut = 0;

    print_pelanggan(front,tail);

    bali:
    cout << "Keluhan nomor urut berapa yang ingin di edit ? ";cin>>nomor_urut;

    if ((nomor_urut < 1) or (nomor_urut > i)){
        cout << "Nomor Urut tidak ada, Mohon ulangi\n";
        goto bali; 
    }

    pelanggan *dummy;
    dummy = new pelanggan;
    dummy = F;

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
    front = nullptr;
    tail = nullptr;
    int pil=0;
    do{
        system("cls");
        cout << "---------PENGOLAHAN DATA BENGKEL MOTOR---------\n";
        cout << "1. Tambah Data Service Pelanggan Baru\n";
        cout << "2. Cetak Daftar Service Pelanggan\n";
        cout << "3. Pembayaran Service Sesuai Antrian\n";
        cout << "4. Edit keluhan Motor\n";
        cout << "5. Cetak Pendapatan Hari ini\n";
        cout << "0. Keluar\n";
        cout << "-----------------------------------------------\n";
        cout << "Pilih : "; cin >> pil;

        switch (pil)
        {
        case 1:
            add_pelanggan(front,tail);
            break;
        
        case 2:
            if (front==nullptr) cout << "Data service kosong\n";
            else
            print_pelanggan(front,tail);
            break;

        case 3:
            if (front==nullptr) cout << "Data service kosong\n";
            else
            transaksi_first(front,tail);
            break;

        case 4:
            if (front==nullptr) cout << "Data service kosong\n";
            else
            edit_keluhan(front,tail);
            break;

        case 5:
            print_pendapatan();
            break;

        case 0:
            cout << "Terimakasih\n";
            break;
        
        default:
            cout << "Salah pilih menu\n";
            break;
        }
        system("pause");

    }while (pil!=0);

    
    delete front;
    delete tail;

}