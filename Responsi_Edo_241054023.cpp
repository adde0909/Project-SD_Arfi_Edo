#include <iostream>
#include <iomanip>
using namespace std;

typedef struct 
{
    string NIM;
    string nama;
    string tgl_lahir;
    string tmpt_lahir;
    string jurusan;
    string th_masuk;
} rec_mahasiswa;
//UYGOUBIYVGI

typedef rec_mahasiswa larik_mahasiswa[20];

larik_mahasiswa mahasiswa;
int i, n;
char ya;

void input_mahasiswa (larik_mahasiswa &X){
    string nim_mhs;
    int jurusan;

    cout << "Input Data Mahasiswa\n";

    ulang :
    cout << "Masukkan NIM mahasiswa : "; cin >> nim_mhs;

    //cek data
    for ( i = 1; i <= n; i++)
    {
        if(X[i].NIM==nim_mhs){
            cout << "Data Mahasiswa dengan NIM tersebut sudah diinput\n"; goto ulang;
        }
    }

    //valid
    n++;
    X[n].NIM = nim_mhs;
    cin.ignore();
    cout << "Nama Mahasiswa : "; getline(cin, X[n].nama);
    cout << "Tanggal Lahir (DD/MM/YYYY) : "; cin >> X[n].tgl_lahir;
    cin.ignore();
    cout << "Tempat Lahir : "; getline(cin, X[n].tmpt_lahir);

    cout << "Pilih Jurusan : \n1. Informatika \n2. Teknik Industri \n3. Teknik Digital \n4. Teknik Mesin\n"; cin >> jurusan;
    if(jurusan==1) X[n].jurusan= "Informatika";
    else if(jurusan==2) X[n].jurusan = "Teknik Industri";
    else if(jurusan==3) X[n].jurusan = "Teknik Digital";
    else X[n].jurusan= "Teknik Mesin";

    cout << "Tahun Masuk : "; cin >> X[n].th_masuk;
    cout << "Input Data Mahasiswa telah berhasil\n";
}

void print_mahasiswa (larik_mahasiswa X){
    system ("cls");

	cout << "DATA MAHASISWA UNIVERSITAS JOGJA KEMBALI\n";
	cout << "================================================================================================================" << endl;
	cout << "| No  |      NIM     |         Nama         | Tgl Lahir |     Tmpt Lahir      |     Jurusan     |  Tahun Masuk  " << endl;
	cout << "================================================================================================================" << endl;
	for ( i = 1; i <= n; i++ )
        cout << "| " << setw(3) << i <<
        " | " << setw(12) << X[i].NIM <<
        " | " << setw(20) << X[i].nama <<
		" | " << setw(9) << X[i].tgl_lahir <<
		" | " << setw(19) << X[i].tmpt_lahir <<
        " | " << setw(15) << X[i].jurusan <<
        " | " << setw(10) << X[i].th_masuk <<
        " |" << endl;
	cout << "================================================================================================================" << endl;
}

void edit_mahasiswa (larik_mahasiswa &X){
    string edit; 
	int pos;
	int pilih, jurusan;
	bool ada = false;

	do {
		system ("cls");
		print_mahasiswa (X);

		cout << endl;
		cout << "Edit Data Mahasiswa" << endl;
		cout << "Masukkan NIM mahasiswa yang akan di-edit : ";
		cin >> edit;

		//cek data
		for ( i = 1; i <= n; i++ ) {
			if ( X[i].NIM == edit) {
				pos=i;
				ada=true;
			}
		}

		//jika ketemu
		if (ada) {
			cout << "Posisi di record nomor : " << pos<<endl;
            cout << "NIM                    : " << X[pos].NIM<<endl;
			cout << "Nama Mahasiswa         : " << X[pos].nama<<endl;
			cout << "Tanggal Lahir          : " << X[pos].tgl_lahir<<endl;
			cout << "Tempat Lahir           : " << X[pos].tmpt_lahir<<endl;
			cout << "Jurusan                : " << X[pos].jurusan<<endl;
            cout << "Tahun Masuk            : " << X[pos].th_masuk<<endl;
			cout << endl;

			cout << "Edit sesuai opsi di bawah ini : " << endl;
			cout << "1. Nama" << endl;
			cout << "2. Jurusan" << endl;
            cout << "3. Tahun Masuk" <<endl;

			ulang_pilih:
			cout << "Pilih yang ingin di-edit: ";
			cin >> pilih;

			if ( pilih == 1 ) {
				cout<<"Masukkan nama yang baru : ";
				cin>>X[pos].nama;
			}
			else if ( pilih == 2 ) {
				cout << "Masukkan jurusan yang baru :\n1. Informatika \n2. Teknik Industri \n3. Teknik Digital \n4. Teknik Mesin\n"<< endl; 
                cin >> jurusan;
                if(jurusan==1) X[pos].jurusan= "Informatika";
                else if(jurusan==2) X[pos].jurusan = "Teknik Industri";
                else if(jurusan==3) X[pos].jurusan = "Teknik Digital";
                else X[pos].jurusan= "Teknik Mesin";
			}
            else if (pilih == 3) {
                cout << "Masukkan Tahun yang baru : "; cin >> X[pos].th_masuk;
            }
			else {
				cout << "Salah pilih nomor" << endl;
				goto ulang_pilih;
			}
			cout << "Editing sudah dilakukan" << endl;
		}

		else cout << "NIM  " << edit << " tidak ditemukan, editing gagal" << endl;
		cout << "Apakah ingin edit lagi? <y/t>: ";
		cin >> ya;

	} while ( (ya == 'y') || (ya == 'Y') );
}

void delete_mahasiswa (larik_mahasiswa &X) {
	
	int hapus;

	do{
		ulang:
		system ("cls");
		
		print_mahasiswa (X);

		cout << "Masukkan No. data yang akan dihapus : ";
		cin >> hapus;

		//validasi
		if ( (hapus < 1) || (hapus > n) ) {
			cout<<"Nomor record tidak valid" << endl;
			goto ulang;
			}

		//sudah valid
		cout << "Yakin akan dihapus <y/t>? ";
		cin >> ya;
		if ( (ya == 'y') || (ya =='Y') ) {
			cout << "Data telah dihapus" << endl;
			for ( i = hapus; i < n; i++ ) X[i] = X[i+1];

			n--;
			}
		else cout << "Data tidak jadi di hapus" << endl;
		cout << "Apakah ingin hapus data lagi <y/t>? ";
		cin >> ya;
	} while ((ya == 'y') || (ya == 'Y'));
}


void search_mahasiswa (larik_mahasiswa X) {

	system ("cls");
	string cari; 
	bool ada= false;
	
	cout << "Search Data Mahasiswa " << endl;
	cout << "Masukkan NIM yang akan dicek : ";
	cin >> cari;

	//Cek
	for ( i = 1; i <= n; i++ ) {
		if (X[i].NIM == cari) {
            ada=true;
			cout << "NIM             : " << cari << endl;
			cout << "Nama Mahasiswa  : " << X[i].nama << endl;
			cout << "Tanggal Lahir   : " << X[i].tgl_lahir << endl;
			cout << "Tempat Lahir    : " << X[i].tmpt_lahir << endl;
			cout << "Jurusan         : " << X[i].jurusan << endl;
            cout << "Tahun Masuk     : " << X[i].th_masuk << endl; }
		}
	if (! ada) cout << "NIM " << cari << " tidak ditemukan" << endl;
	}

int main(){
    int pilih = 0;

    do{
        system("cls");
        cout << "DATA MAHASISWA UNIVERSITAS JOGJA KEMBALI\n";
        cout << "1. Input Data Mahasiswa\n";
        cout << "2. Print Data Mahasiswa\n";
        cout << "3. Edit Data Mahasiswa\n";
        cout << "4. Delete Data Mahasiswa\n";
        cout << "5. Search Data Mahasiswa\n"; 
        cout << "0. Selesai\n";
        cout << "Pilih menu: "; cin >> pilih;

        switch (pilih)
        {
        case 1:
            if (n == 20)
            {
                cout << "Data Mahasiswa telah penuh\n";
            }
            else input_mahasiswa(mahasiswa);
            break;
        
        case 2:
            if (n == 0)
            {
                cout << "Data Mahasiswa masih kosong\n";
            }
            else print_mahasiswa(mahasiswa);
            break;

        case 3:
            if (n == 0)
            {
                cout << "Data Mahasiswa masih kosong\n";
            }
            else edit_mahasiswa(mahasiswa);
            break;

        case 4:
            if (n == 0)
            {
                cout << "Data Mahasiswa masih kosong\n";
            }
           else delete_mahasiswa(mahasiswa);
            break;

        case 5:
            if (n == 0)
            {
                cout << "Data Mahasiswa masih kosong\n";
            }
           else search_mahasiswa(mahasiswa);
            break;

        case 0:
            cout << "Terimakasih\n";
            break;

        default:
            cout << "Menu salah, tolong ulangi\n";
            break;
        }
        system("pause");
    }while(pilih!=0);
}