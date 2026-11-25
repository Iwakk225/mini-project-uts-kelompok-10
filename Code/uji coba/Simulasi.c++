#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

const string FILE_RIWAYAT = "riwayat_antrean.txt";
const string FILE_LOG = "log_layanan.txt";
const string MENUNGGU = "Menunggu";
const string DILAYANI = "Sedang Dilayani";
const string SELESAI = "Selesai";

const int MAKS_PELANGGAN = 100;
const int MAKS_ANTREAN = 100;

// Deklarasi awal
bool punyaAntreanAktif(const string &id);
void catatLog(int nomor, const string &idPelanggan, const string &status);

// Format nomor: A001
string formatNomor(int n) {
    if (n < 10) return "A00" + to_string(n);
    if (n < 100) return "A0" + to_string(n);
    return "A" + to_string(n);
}

// Baca pilihan menu (-1 jika bukan angka)
int bacaPilihan() {
    int p;
    cout << "Pilihan: ";
    if (!(cin >> p)) {
        if (cin.eof()) return 0;   // input habis
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    return p;
}

// MAHASISWA 1
struct Pelanggan {
    string id;
    string nama;
};

Pelanggan daftarPelanggan[MAKS_PELANGGAN];
Pelanggan *ptrPelanggan = daftarPelanggan;
int jumlahPelanggan = 0;
int urutID = 1;

int nomorAntreanBerikutnya = 1;

string buatIDPelanggan() {
    string nomor = (urutID < 10 ? "0" : "") + to_string(urutID);
    urutID++;
    return "PLG" + nomor;
}

int buatNomorAntrean() {
    return nomorAntreanBerikutnya++;
}

// Cari indeks pelanggan
int cariIndexPelanggan(const string &id) {
    for (int i = 0; i < jumlahPelanggan; i++) {
        if ((ptrPelanggan + i)->id == id) {
            return i;
        }
    }
    return -1;
}

// Ambil nama pelanggan
string cariNamaPelanggan(const string &id) {
    int idx = cariIndexPelanggan(id);
    if (idx == -1) return "(dihapus)";
    return (ptrPelanggan + idx)->nama;
}

// Validasi nama
bool namaValid(const string &nama) {
    int panjang = nama.length();

    if (panjang < 3) {
        cout << "Nama pelanggan minimal 3 karakter.\n";
        return false;
    }

    for (int i = 0; i < panjang; i++) {
        if (nama[i] >= '0' && nama[i] <= '9') {
            cout << "Nama pelanggan tidak boleh mengandung angka.\n";
            return false;
        }
        if (nama[i] == '|') {
            cout << "Nama pelanggan tidak boleh mengandung karakter |.\n";
            return false;
        }
    }
    return true;
}

// Tambah pelanggan
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
        if (!cin) return;
    } while (!namaValid(nama));

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

// Cari by ID
void cariPelangganID() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string id;
    cout << "Masukkan ID pelanggan (contoh PLG01): ";
    getline(cin, id);

    int idx = cariIndexPelanggan(id);
    if (idx == -1) {
        cout << "Pelanggan tidak ditemukan.\n";
        return;
    }

    cout << "\nPelanggan ditemukan.\n";
    cout << "ID    : " << (ptrPelanggan + idx)->id << "\n";
    cout << "Nama  : " << (ptrPelanggan + idx)->nama << "\n";
}

// Ubah nama
void ubahPelanggan() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string id;
    cout << "Masukkan ID pelanggan yang diubah: ";
    getline(cin, id);

    int idx = cariIndexPelanggan(id);
    if (idx == -1) {
        cout << "Pelanggan tidak ditemukan.\n";
        return;
    }

    cout << "Nama saat ini : " << (ptrPelanggan + idx)->nama << "\n";

    string namaBaru;
    do {
        cout << "Nama baru     : ";
        getline(cin, namaBaru);
        if (!cin) return;
    } while (!namaValid(namaBaru));

    (ptrPelanggan + idx)->nama = namaBaru;
    cout << "Data pelanggan berhasil diubah.\n";
}

// Hapus pelanggan
void hapusPelanggan() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string id;
    cout << "Masukkan ID pelanggan yang dihapus: ";
    getline(cin, id);

    int idx = cariIndexPelanggan(id);
    if (idx == -1) {
        cout << "Pelanggan tidak ditemukan.\n";
        return;
    }

    // Tolak jika masih antre
    if (punyaAntreanAktif(id)) {
        cout << "Tidak bisa dihapus: pelanggan masih punya antrean aktif.\n";
        return;
    }

    char yakin;
    cout << "Hapus " << (ptrPelanggan + idx)->nama << "? (y/n): ";
    cin >> yakin;
    if (yakin != 'y' && yakin != 'Y') {
        cout << "Penghapusan dibatalkan.\n";
        return;
    }

    // Geser data ke kiri
    for (int i = idx; i < jumlahPelanggan - 1; i++) {
        *(ptrPelanggan + i) = *(ptrPelanggan + i + 1);
    }
    jumlahPelanggan--;
    cout << "Pelanggan berhasil dihapus.\n";
}

// MAHASISWA 2
struct Antrian {
    int nomor;
    string idPelanggan;
    string status;
};

Antrian daftarAntrean[MAKS_ANTREAN];
Antrian *ptrAntrean = daftarAntrean;
int jumlahAntrean = 0;

// Cari indeks antrean
int cariIndexAntrean(int nomor) {
    for (int i = 0; i < jumlahAntrean; i++) {
        if ((ptrAntrean + i)->nomor == nomor) {
            return i;
        }
    }
    return -1;
}

// Cek antrean aktif
bool punyaAntreanAktif(const string &id) {
    for (int i = 0; i < jumlahAntrean; i++) {
        if ((ptrAntrean + i)->idPelanggan == id &&
            (ptrAntrean + i)->status != SELESAI) {
            return true;
        }
    }
    return false;
}

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
    cout << "\nMasukkan ID pelanggan (contoh PLG01): ";
    getline(cin, id);

    if (cariIndexPelanggan(id) == -1) {
        cout << "ID pelanggan tidak ditemukan.\n";
        return;
    }

    // Cegah antre ganda
    if (punyaAntreanAktif(id)) {
        cout << "Pelanggan tersebut masih punya antrean aktif.\n";
        return;
    }

    (ptrAntrean + jumlahAntrean)->nomor = buatNomorAntrean();
    (ptrAntrean + jumlahAntrean)->idPelanggan = id;
    (ptrAntrean + jumlahAntrean)->status = MENUNGGU;

    cout << "Nomor antrean untuk " << cariNamaPelanggan(id) << ": "
         << formatNomor((ptrAntrean + jumlahAntrean)->nomor) << "\n";

    jumlahAntrean++;
}

void panggilAntrean() {
    // Satu loket saja
    for (int i = 0; i < jumlahAntrean; i++) {
        if ((ptrAntrean + i)->status == DILAYANI) {
            cout << "Antrean " << formatNomor((ptrAntrean + i)->nomor)
                 << " masih dilayani. Selesaikan dulu sebelum memanggil berikutnya.\n";
            return;
        }
    }

    for (int i = 0; i < jumlahAntrean; i++) {
        if ((ptrAntrean + i)->status == MENUNGGU) {
            (ptrAntrean + i)->status = DILAYANI;

            cout << "\nMemanggil antrean nomor "
                 << formatNomor((ptrAntrean + i)->nomor) << "\n";
            cout << "ID Pelanggan : " << (ptrAntrean + i)->idPelanggan << "\n";
            cout << "Nama         : "
                 << cariNamaPelanggan((ptrAntrean + i)->idPelanggan) << "\n";

            catatLog((ptrAntrean + i)->nomor, (ptrAntrean + i)->idPelanggan,
                     (ptrAntrean + i)->status);
            return;
        }
    }

    cout << "Tidak ada antrean yang menunggu.\n";
}

void selesaiLayanan() {
    int nomor;
    cout << "Masukkan nomor antrean yang selesai (angka, contoh 3 untuk A003): ";

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
            cout << "Antrean " << formatNomor(nomor) << " selesai dilayani.\n";

            catatLog((ptrAntrean + i)->nomor, (ptrAntrean + i)->idPelanggan,
                     (ptrAntrean + i)->status);
            return;
        }
    }

    cout << "Antrean tidak ditemukan atau belum dilayani.\n";
}

// MAHASISWA 3
void simpanKeFile() {
    ofstream file(FILE_RIWAYAT);

    if (!file.is_open()) {
        cout << "File gagal dibuka.\n";
        return;
    }

    // Pelanggan
    file << "Jumlah Pelanggan|" << jumlahPelanggan << "\n";
    file << "ID Berikutnya|" << urutID << "\n";
    file << "ID|Nama\n";
    for (int i = 0; i < jumlahPelanggan; i++) {
        file << (ptrPelanggan + i)->id << "|"
             << (ptrPelanggan + i)->nama << "\n";
    }

    file << "\n";

    // Antrean
    file << "Jumlah Antrean|" << jumlahAntrean << "\n";
    file << "Nomor Berikutnya|" << nomorAntreanBerikutnya << "\n";
    file << "Nomor|ID Pelanggan|Status\n";
    for (int i = 0; i < jumlahAntrean; i++) {
        file << (ptrAntrean + i)->nomor << "|"
             << (ptrAntrean + i)->idPelanggan << "|"
             << (ptrAntrean + i)->status << "\n";
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

    string label;
    int jp, uid, ja, nb;

    // Bagian pelanggan
    getline(file, label, '|');
    if (label != "Jumlah Pelanggan") {
        cout << "Format file riwayat tidak valid.\n";
        return;
    }
    file >> jp;
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    getline(file, label, '|');
    file >> uid;
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    file.ignore(numeric_limits<streamsize>::max(), '\n');   // baris judul

    if (!file || jp < 0 || jp > MAKS_PELANGGAN || uid < 1) {
        cout << "Format file riwayat tidak valid.\n";
        return;
    }

    Pelanggan tmpP[MAKS_PELANGGAN];
    for (int i = 0; i < jp; i++) {
        getline(file, tmpP[i].id, '|');
        getline(file, tmpP[i].nama);
    }

    file.ignore(numeric_limits<streamsize>::max(), '\n');   // baris kosong

    // Bagian antrean
    getline(file, label, '|');
    if (label != "Jumlah Antrean") {
        cout << "Format file riwayat tidak valid.\n";
        return;
    }
    file >> ja;
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    getline(file, label, '|');
    file >> nb;
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    file.ignore(numeric_limits<streamsize>::max(), '\n');   // baris judul

    if (!file || ja < 0 || ja > MAKS_ANTREAN || nb < 1) {
        cout << "Format file riwayat tidak valid.\n";
        return;
    }

    Antrian tmpA[MAKS_ANTREAN];
    for (int i = 0; i < ja; i++) {
        file >> tmpA[i].nomor;
        file.ignore(1);   // lewati tanda |
        getline(file, tmpA[i].idPelanggan, '|');
        getline(file, tmpA[i].status);

        if (tmpA[i].status != MENUNGGU && tmpA[i].status != DILAYANI &&
            tmpA[i].status != SELESAI) {
            cout << "Format file riwayat tidak valid (status salah).\n";
            return;
        }
    }

    if (!file) {
        cout << "Format file riwayat tidak valid.\n";
        return;
    }

    // Pindahkan ke program
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

// Catat log (fstream)
void catatLog(int nomor, const string &idPelanggan, const string &status) {
    fstream log(FILE_LOG.c_str(), ios::out | ios::app);

    if (!log.is_open()) {
        cout << "(Log layanan gagal dibuka.)\n";
        return;
    }

    log << formatNomor(nomor) << " | " << idPelanggan << " | "
        << cariNamaPelanggan(idPelanggan) << " | " << status << "\n";
    log.close();
}

// Tampil antrean (semua = true termasuk yang selesai)
void tampilAntrean(bool semua) {
    cout << (semua ? "\n===== SELURUH ANTREAN =====\n" : "\n===== ANTREAN AKTIF =====\n");
    cout << left
         << setw(10) << "Nomor"
         << setw(12) << "ID"
         << setw(20) << "Nama"
         << "Status\n";
    cout << "------------------------------------------------------\n";

    int jumlah = 0;

    for (int i = 0; i < jumlahAntrean; i++) {
        if (semua || (ptrAntrean + i)->status != SELESAI) {
            cout << left
                 << setw(10) << formatNomor((ptrAntrean + i)->nomor)
                 << setw(12) << (ptrAntrean + i)->idPelanggan
                 << setw(20) << cariNamaPelanggan((ptrAntrean + i)->idPelanggan)
                 << (ptrAntrean + i)->status << "\n";
            jumlah++;
        }
    }

    if (jumlah == 0) {
        cout << "Tidak ada antrean.\n";
    }
}

void cariRiwayat() {
    int nomor;
    cout << "Masukkan nomor antrean yang dicari (angka, contoh 3 untuk A003): ";

    if (!(cin >> nomor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nomor antrean harus berupa angka.\n";
        return;
    }

    int idx = cariIndexAntrean(nomor);
    if (idx == -1) {
        cout << "Riwayat antrean tidak ditemukan.\n";
        return;
    }

    cout << "\nRiwayat antrean ditemukan.\n";
    cout << "Nomor antrean : " << formatNomor((ptrAntrean + idx)->nomor) << "\n";
    cout << "ID pelanggan  : " << (ptrAntrean + idx)->idPelanggan << "\n";
    cout << "Nama          : "
         << cariNamaPelanggan((ptrAntrean + idx)->idPelanggan) << "\n";
    cout << "Status        : " << (ptrAntrean + idx)->status << "\n";
}

// Laporan
void laporan() {
    int menunggu = 0;
    int dilayani = 0;
    int selesai = 0;

    for (int i = 0; i < jumlahAntrean; i++) {
        if ((ptrAntrean + i)->status == MENUNGGU) {
            menunggu++;
        } else if ((ptrAntrean + i)->status == DILAYANI) {
            dilayani++;
        } else {
            selesai++;
        }
    }

    cout << "\n========== LAPORAN ANTREAN ==========\n";
    cout << "Jumlah pelanggan terdaftar    : " << jumlahPelanggan << "\n";
    cout << "Jumlah seluruh antrean        : " << jumlahAntrean << "\n";
    cout << "Menunggu                      : " << menunggu << "\n";
    cout << "Sedang dilayani               : " << dilayani << "\n";
    cout << "Pelanggan yang telah dilayani : " << selesai << "\n";

    cout << "\nDaftar pelanggan yang telah dilayani:\n";
    int no = 1;
    for (int i = 0; i < jumlahAntrean; i++) {
        if ((ptrAntrean + i)->status == SELESAI) {
            cout << no << ". " << formatNomor((ptrAntrean + i)->nomor) << " - "
                 << cariNamaPelanggan((ptrAntrean + i)->idPelanggan) << "\n";
            no++;
        }
    }
    if (no == 1) {
        cout << "(belum ada)\n";
    }
}

// MENU
void menuTampil() {
    cout << "\n--- Tampilkan Data ---\n";
    cout << "1. Data pelanggan\n";
    cout << "2. Seluruh data antrean\n";
    cout << "3. Antrean aktif\n";
    cout << "0. Kembali\n";

    switch (bacaPilihan()) {
        case 1: tampilPelanggan(); break;
        case 2: tampilAntrean(true); break;
        case 3: tampilAntrean(false); break;
        case 0: break;
        default: cout << "Pilihan tidak valid.\n";
    }
}

void menuCari() {
    cout << "\n--- Cari Data ---\n";
    cout << "1. Pelanggan berdasarkan ID\n";
    cout << "2. Antrean berdasarkan nomor\n";
    cout << "0. Kembali\n";

    switch (bacaPilihan()) {
        case 1: cariPelangganID(); break;
        case 2: cariRiwayat(); break;
        case 0: break;
        default: cout << "Pilihan tidak valid.\n";
    }
}

void menuTransaksi() {
    cout << "\n--- Proses Transaksi Antrean ---\n";
    cout << "1. Tambah antrean\n";
    cout << "2. Panggil antrean berikutnya\n";
    cout << "3. Selesaikan pelayanan\n";
    cout << "0. Kembali\n";

    switch (bacaPilihan()) {
        case 1: tambahAntrean(); break;
        case 2: panggilAntrean(); break;
        case 3: selesaiLayanan(); break;
        case 0: break;
        default: cout << "Pilihan tidak valid.\n";
    }
}

void menuUtama() {
    cout << "\n===== SISTEM SIMULASI ANTRIAN =====\n";
    cout << "1. Tambah Data (daftar pelanggan baru)\n";
    cout << "2. Tampilkan Data\n";
    cout << "3. Cari Data\n";
    cout << "4. Ubah Data\n";
    cout << "5. Hapus Data\n";
    cout << "6. Proses Transaksi (tambah / panggil / selesai)\n";
    cout << "7. Simpan Data\n";
    cout << "8. Baca Data\n";
    cout << "9. Laporan\n";
    cout << "0. Keluar\n";
}

int main() {
    int pilihan;

    // Baca data awal
    bacaDariFile();

    do {
        menuUtama();
        pilihan = bacaPilihan();

        switch (pilihan) {
            case 1: inputPelanggan(); break;
            case 2: menuTampil(); break;
            case 3: menuCari(); break;
            case 4: ubahPelanggan(); break;
            case 5: hapusPelanggan(); break;
            case 6: menuTransaksi(); break;
            case 7: simpanKeFile(); break;
            case 8: bacaDariFile(); break;
            case 9: laporan(); break;
            case 0:
                simpanKeFile();   // auto simpan
                cout << "Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    return 0;
}