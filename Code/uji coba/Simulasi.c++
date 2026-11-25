#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

const string FILE_RIWAYAT = "riwayat_antrean.txt";
const string MENUNGGU = "Menunggu";
const string DILAYANI = "Sedang Dilayani";
const string SELESAI = "Selesai";

// ==================================================
// MAHASISWA 1 — Data Pelanggan dan Pendaftaran
// ==================================================
const int MAKS_PELANGGAN = 100;
const int MAKS_ANTREAN = 100;

struct Pelanggan {
    string id;
    string nama;
};

Pelanggan daftarPelanggan[MAKS_PELANGGAN];
Pelanggan *ptrPelanggan = daftarPelanggan;
int jumlahPelanggan = 0;
int urutID = 1;

// Nomor antrean dibuat otomatis saat pelanggan masuk antrean.
int nomorAntreanBerikutnya = 1;

string buatIDPelanggan() {
    string nomor = (urutID < 10 ? "0" : "") + to_string(urutID);
    urutID++;
    return "PLG" + nomor;
}

int buatNomorAntrean() {
    return nomorAntreanBerikutnya++;
}

// Mengembalikan nama pelanggan berdasarkan ID (atau "-" jika tidak ada).
string cariNamaPelanggan(const string &id) {
    for (int i = 0; i < jumlahPelanggan; i++) {
        if ((ptrPelanggan + i)->id == id) {
            return (ptrPelanggan + i)->nama;
        }
    }
    return "-";
}

void inputPelanggan() {
    if (jumlahPelanggan >= MAKS_PELANGGAN) {
        cout << "Data pelanggan sudah penuh!\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n--- Pendaftaran Pelanggan ---\n";

    string nama;
    do {
        cout << "Nama         : ";
        getline(cin, nama);
        if (nama.empty()) {
            cout << "Nama tidak boleh kosong.\n";
        }
    } while (nama.empty());

    (ptrPelanggan + jumlahPelanggan)->id = buatIDPelanggan();
    (ptrPelanggan + jumlahPelanggan)->nama = nama;

    cout << "ID Pelanggan : " << (ptrPelanggan + jumlahPelanggan)->id << "\n";
    jumlahPelanggan++;
    cout << "Pelanggan berhasil didaftarkan.\n";
}

void tampilPelanggan() {
    cout << "\n===== DATA PELANGGAN =====\n";
    cout << left << setw(12) << "ID" << "Nama\n";
    cout << "------------------------------------------\n";

    if (jumlahPelanggan == 0) {
        cout << "Belum ada pelanggan yang terdaftar.\n";
        return;
    }

    for (int i = 0; i < jumlahPelanggan; i++) {
        cout << left << setw(12) << (ptrPelanggan + i)->id
             << (ptrPelanggan + i)->nama << "\n";
    }
    cout << "Total pelanggan: " << jumlahPelanggan << "\n";
}

// ==================================================
// MAHASISWA 2 — Proses dan Pengelolaan Antrean
// ==================================================
struct Antrian {
    int nomor;
    string idPelanggan;
    string status;
};

Antrian daftarAntrean[MAKS_ANTREAN];
Antrian *ptrAntrean = daftarAntrean;
int jumlahAntrean = 0;

void tambahAntrean() {
    if (jumlahAntrean >= MAKS_ANTREAN) {
        cout << "Data antrean sudah penuh!\n";
        return;
    }

    if (jumlahPelanggan == 0) {
        cout << "Belum ada pelanggan yang terdaftar.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string id;
    cout << "\nMasukkan ID pelanggan: ";
    getline(cin, id);

    bool ditemukan = false;
    for (int i = 0; i < jumlahPelanggan; i++) {
        if ((ptrPelanggan + i)->id == id) {
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "ID pelanggan tidak ditemukan.\n";
        return;
    }

    // Cegah pelanggan yang sama mengantre dua kali sekaligus.
    for (int i = 0; i < jumlahAntrean; i++) {
        if ((ptrAntrean + i)->idPelanggan == id &&
            (ptrAntrean + i)->status != SELESAI) {
            cout << "Pelanggan tersebut masih punya antrean aktif (nomor "
                 << (ptrAntrean + i)->nomor << ").\n";
            return;
        }
    }

    (ptrAntrean + jumlahAntrean)->nomor = buatNomorAntrean();
    (ptrAntrean + jumlahAntrean)->idPelanggan = id;
    (ptrAntrean + jumlahAntrean)->status = MENUNGGU;

    cout << "Nomor antrean untuk " << cariNamaPelanggan(id) << ": "
         << (ptrAntrean + jumlahAntrean)->nomor << "\n";

    jumlahAntrean++;
}

void panggilAntrean() {
    for (int i = 0; i < jumlahAntrean; i++) {
        if ((ptrAntrean + i)->status == MENUNGGU) {
            (ptrAntrean + i)->status = DILAYANI;

            cout << "\nMemanggil antrean nomor " << (ptrAntrean + i)->nomor << "\n";
            cout << "ID Pelanggan : " << (ptrAntrean + i)->idPelanggan << "\n";
            cout << "Nama         : "
                 << cariNamaPelanggan((ptrAntrean + i)->idPelanggan) << "\n";
            return;
        }
    }

    cout << "Tidak ada antrean yang menunggu.\n";
}

void selesaiLayanan() {
    int nomor;
    cout << "Masukkan nomor antrean yang selesai: ";

    if (!(cin >> nomor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nomor antrean harus berupa angka.\n";
        return;
    }

    for (int i = 0; i < jumlahAntrean; i++) {
        if ((ptrAntrean + i)->nomor == nomor &&
            (ptrAntrean + i)->status == DILAYANI) {
            (ptrAntrean + i)->status = SELESAI;
            cout << "Antrean " << nomor << " selesai dilayani.\n";
            return;
        }
    }

    cout << "Antrean tidak ditemukan atau belum dilayani.\n";
}

// ==================================================
// MAHASISWA 3 — Riwayat dan Statistik Antrean
// ==================================================
void simpanKeFile() {
    ofstream file(FILE_RIWAYAT);

    if (!file.is_open()) {
        cout << "File gagal dibuka.\n";
        return;
    }

    // Bagian pelanggan
    file << jumlahPelanggan << "\n";
    file << urutID << "\n";
    for (int i = 0; i < jumlahPelanggan; i++) {
        file << (ptrPelanggan + i)->id << "\n";
        file << (ptrPelanggan + i)->nama << "\n";
    }

    // Bagian antrean
    file << jumlahAntrean << "\n";
    file << nomorAntreanBerikutnya << "\n";
    for (int i = 0; i < jumlahAntrean; i++) {
        file << (ptrAntrean + i)->nomor << "\n";
        file << (ptrAntrean + i)->idPelanggan << "\n";
        file << (ptrAntrean + i)->status << "\n";
    }

    file.close();
    cout << "Data pelanggan dan riwayat antrean berhasil disimpan.\n";
}

void bacaDariFile() {
    ifstream file(FILE_RIWAYAT);

    if (!file.is_open()) {
        cout << "File riwayat belum tersedia.\n";
        return;
    }

    int jp, uid, ja, nb;

    file >> jp >> uid;
    file.ignore(numeric_limits<streamsize>::max(), '\n');
    if (!file || jp < 0 || jp > MAKS_PELANGGAN || uid < 1) {
        cout << "Format file riwayat tidak valid.\n";
        return;
    }

    Pelanggan tmpP[MAKS_PELANGGAN];
    for (int i = 0; i < jp; i++) {
        getline(file, tmpP[i].id);
        getline(file, tmpP[i].nama);
    }

    file >> ja >> nb;
    file.ignore(numeric_limits<streamsize>::max(), '\n');
    if (!file || ja < 0 || ja > MAKS_ANTREAN || nb < 1) {
        cout << "Format file riwayat tidak valid.\n";
        return;
    }

    Antrian tmpA[MAKS_ANTREAN];
    for (int i = 0; i < ja; i++) {
        file >> tmpA[i].nomor;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, tmpA[i].idPelanggan);
        getline(file, tmpA[i].status);
    }

    if (!file) {
        cout << "Format file riwayat tidak valid.\n";
        return;
    }

    // Data valid seluruhnya, baru dipindahkan ke data program.
    jumlahPelanggan = jp;
    urutID = uid;
    for (int i = 0; i < jp; i++) *(ptrPelanggan + i) = tmpP[i];

    jumlahAntrean = ja;
    nomorAntreanBerikutnya = nb;
    for (int i = 0; i < ja; i++) *(ptrAntrean + i) = tmpA[i];

    file.close();
    cout << "Data berhasil dibaca dari file ("
         << jumlahPelanggan << " pelanggan, "
         << jumlahAntrean << " antrean).\n";
}

void tampilAntreanAktif() {
    cout << "\n===== ANTREAN AKTIF =====\n";
    cout << left
         << setw(10) << "Nomor"
         << setw(12) << "ID"
         << setw(20) << "Nama"
         << "Status\n";
    cout << "------------------------------------------------------\n";

    int aktif = 0;

    for (int i = 0; i < jumlahAntrean; i++) {
        if ((ptrAntrean + i)->status != SELESAI) {
            cout << left
                 << setw(10) << (ptrAntrean + i)->nomor
                 << setw(12) << (ptrAntrean + i)->idPelanggan
                 << setw(20) << cariNamaPelanggan((ptrAntrean + i)->idPelanggan)
                 << (ptrAntrean + i)->status << "\n";
            aktif++;
        }
    }

    if (aktif == 0) {
        cout << "Tidak ada antrean aktif.\n";
    }
}

void cariRiwayat() {
    int nomor;
    cout << "Masukkan nomor antrean yang dicari: ";

    if (!(cin >> nomor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nomor antrean harus berupa angka.\n";
        return;
    }

    for (int i = 0; i < jumlahAntrean; i++) {
        if ((ptrAntrean + i)->nomor == nomor) {
            cout << "\nRiwayat antrean ditemukan.\n";
            cout << "Nomor antrean : " << (ptrAntrean + i)->nomor << "\n";
            cout << "ID pelanggan  : " << (ptrAntrean + i)->idPelanggan << "\n";
            cout << "Nama          : "
                 << cariNamaPelanggan((ptrAntrean + i)->idPelanggan) << "\n";
            cout << "Status        : " << (ptrAntrean + i)->status << "\n";
            return;
        }
    }

    cout << "Riwayat antrean tidak ditemukan.\n";
}

void laporanPelangganDilayani() {
    int jumlahDilayani = 0;

    for (int i = 0; i < jumlahAntrean; i++) {
        if ((ptrAntrean + i)->status == SELESAI) {
            jumlahDilayani++;
        }
    }

    cout << "\nJumlah pelanggan yang telah dilayani: "
         << jumlahDilayani << "\n";
}

// ==================================================
// MENU UTAMA
// ==================================================
void menuUtama() {
    cout << "\n===== SISTEM SIMULASI ANTRIAN =====\n";
    cout << "1.  Daftar pelanggan baru\n";
    cout << "2.  Tambah antrean\n";
    cout << "3.  Panggil antrean\n";
    cout << "4.  Selesaikan pelayanan\n";
    cout << "5.  Tampilkan antrean aktif\n";
    cout << "6.  Simpan data ke file\n";
    cout << "7.  Baca data dari file\n";
    cout << "8.  Cari riwayat antrean\n";
    cout << "9.  Laporan pelanggan dilayani\n";
    cout << "10. Tampilkan data pelanggan\n";
    cout << "0.  Keluar\n";
    cout << "Pilihan: ";
}

int main() {
    int pilihan;

    // Membaca data yang tersimpan saat program dijalankan.
    bacaDariFile();

    do {
        menuUtama();

        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukkan pilihan berupa angka.\n";
            pilihan = -1;
            continue;
        }

        switch (pilihan) {
            case 1:  inputPelanggan(); break;
            case 2:  tambahAntrean(); break;
            case 3:  panggilAntrean(); break;
            case 4:  selesaiLayanan(); break;
            case 5:  tampilAntreanAktif(); break;
            case 6:  simpanKeFile(); break;
            case 7:  bacaDariFile(); break;
            case 8:  cariRiwayat(); break;
            case 9:  laporanPelangganDilayani(); break;
            case 10: tampilPelanggan(); break;
            case 0:
                simpanKeFile();   // simpan otomatis saat keluar
                cout << "Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak tersedia.\n";
        }

    } while (pilihan != 0);

    return 0;
}