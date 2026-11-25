#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// ==================================================
//  MAHASISWA 1 — Data Pelanggan & Pendaftaran
// ==================================================
const int MAX_PLG = 15;
const int MAX_ANT = 15;

int urutPlg = 1; //  untuk nomor ID pelanggan

struct Pelanggan {
    string idPlg;
    string namaPlg;
    string alamatPlg;
    string telpPlg;
};

Pelanggan daftarPlg[MAX_PLG];
int jmlPlg = 0;
int noAntBerikutnya = 1;

Pelanggan *ptrPlg = daftarPlg;

//  FUNGSI PEMBUAT ID: PLG01, PLG02, PLG03...
string buatID() {
    string nomor;
    if (urutPlg < 10) {
        nomor = "0" + to_string(urutPlg);
    } else {
        nomor = to_string(urutPlg);
    }
    urutPlg++;
    return "PLG" + nomor;
}

void inputPlg() {
    if (jmlPlg >= MAX_PLG) {
        cout << " Data pelanggan sudah penuh!\n";
        return;
    }
    cin.ignore();
    ptrPlg[jmlPlg].idPlg = buatID();
    
    cout << "\n--- Input Data Pelanggan ---\n";
    cout << "ID Pelanggan: " << ptrPlg[jmlPlg].idPlg << "\n";
    cout << "Nama Lengkap: ";
    getline(cin, ptrPlg[jmlPlg].namaPlg);
    cout << "Alamat: ";
    getline(cin, ptrPlg[jmlPlg].alamatPlg);
    cout << "No. Telepon: ";
    getline(cin, ptrPlg[jmlPlg].telpPlg);
    
    jmlPlg++;
    cout << " Data pelanggan berhasil ditambahkan!\n";
}

void tampilSemuaPlg() {
    if (jmlPlg == 0) {
        cout << "\n Belum ada data pelanggan.\n";
        return;
    }
    cout << "\n\n============================= DAFTAR SEMUA PELANGGAN =============================\n";
    cout << left
         << setw(5)  << "No"
         << setw(10) << "ID"
         << setw(22) << "Nama"
         << setw(30) << "Alamat"
         << setw(15) << "Telp"
         << "\n";
    cout << "-----------------------------------------------------------------------------------\n";
    for (int i = 0; i < jmlPlg; i++) {
        cout << left
             << setw(5)  << i + 1
             << setw(10) << ptrPlg[i].idPlg
             << setw(22) << ptrPlg[i].namaPlg
             << setw(30) << ptrPlg[i].alamatPlg
             << setw(15) << ptrPlg[i].telpPlg
             << "\n";
    }
    cout << "===================================================================================\n";
}


void cariPlg() {
    cin.ignore();
    string kunci;
    bool ketemu = false;
    cout << "\n--- Cari Data Pelanggan ---\n";
    cout << "Masukkan ID atau Nama: ";
    getline(cin, kunci);
    for (int i = 0; i < jmlPlg; i++) {
        if (ptrPlg[i].idPlg == kunci || ptrPlg[i].namaPlg == kunci) {
            cout << "\n Ditemukan:\n";
            cout << "ID     : " << ptrPlg[i].idPlg << "\n";
            cout << "Nama   : " << ptrPlg[i].namaPlg << "\n";
            cout << "Alamat : " << ptrPlg[i].alamatPlg << "\n";
            cout << "Telp   : " << ptrPlg[i].telpPlg << "\n";
            ketemu = true;
            break;
        }
    }
    if (!ketemu) cout << " Pelanggan tidak ditemukan.\n";
}
// ==================================================
// MAHASISWA 1 — SELESAI
// ==================================================

// ==================================================
// MAHASISWA 2 — Proses & Pengelolaan Antrean
// ==================================================
struct Antrian {
    int noAnt;
    string idPlgAnt;
    string status;
    string layanan;
};

Antrian daftarAnt[MAX_ANT];
int jmlAnt = 0;

Antrian *ptrAnt = daftarAnt;

void tambahAntrean() {
    if (jmlAnt >= MAX_ANT) {
        cout << " Antrean sudah penuh!\n";
        return;
    }
    cin.ignore();
    string idCari;
    cout << "\n--- Tambah Antrean ---\n";
    cout << "Masukkan ID Pelanggan: ";
    getline(cin, idCari);
    
    bool ada = false;
    for (int i = 0; i < jmlPlg; i++) {
        if (ptrPlg[i].idPlg == idCari) { ada = true; break; }
    }
    if (!ada) {
        cout << " ID Pelanggan tidak terdaftar!\n";
        return;
    }
    
    ptrAnt[jmlAnt].noAnt = noAntBerikutnya++;
    ptrAnt[jmlAnt].idPlgAnt = idCari;
    ptrAnt[jmlAnt].status = "Menunggu";
    cout << "Jenis Layanan: ";
    getline(cin, ptrAnt[jmlAnt].layanan);
    
    jmlAnt++;
    cout << " Berhasil! Nomor Antrean: " << ptrAnt[jmlAnt-1].noAnt << "\n";
}

void panggilAntrean() {
    bool dipanggil = false;
    for (int i = 0; i < jmlAnt; i++) {
        if (ptrAnt[i].status == "Menunggu") {
            ptrAnt[i].status = "Dilayani";
            cout << "\n Memanggil Antrean No. " << ptrAnt[i].noAnt << "\n";
            cout << "ID Pelanggan: " << ptrAnt[i].idPlgAnt << "\n";
            cout << "Layanan: " << ptrAnt[i].layanan << "\n";
            dipanggil = true;
            break;
        }
    }
    if (!dipanggil) cout << "\n Tidak ada antrean yang menunggu.\n";
}

void selesaiLayanan() {
    int no;
    cout << "\n--- Selesai Pelayanan ---\n";
    cout << "Nomor Antrean: ";
    cin >> no;
    for (int i = 0; i < jmlAnt; i++) {
        if (ptrAnt[i].noAnt == no && ptrAnt[i].status == "Dilayani") {
            ptrAnt[i].status = "Selesai";
            cout << " Antrean No. " << no << " selesai dilayani!\n";
            return;
        }
    }
    cout << " Nomor antrean tidak ditemukan.\n";
}

void tampilAntreanAktif() {
    cout << "\n=== Daftar Antrean Saat Ini ===\n";
    cout << setw(8) << "No.Ant" << setw(12) << "ID Pelanggan" 
         << setw(12) << "Status" << setw(20) << "Layanan" << "\n";
    cout << string(55, '-') << "\n";
    int aktif = 0;
    for (int i = 0; i < jmlAnt; i++) {
        if (ptrAnt[i].status != "Selesai") {
            cout << setw(8) << ptrAnt[i].noAnt
                 << setw(12) << ptrAnt[i].idPlgAnt
                 << setw(12) << ptrAnt[i].status
                 << setw(20) << ptrAnt[i].layanan << "\n";
            aktif++;
        }
    }
    if (aktif == 0) cout << "Tidak ada antrean aktif.\n";
}
// ==================================================
// MAHASISWA 2 — SELESAI
// ==================================================

// ==================================================
// MAHASISWA 3 — Riwayat & Statistik / File
// ==================================================
void simpanKeFile() {
    ofstream fPlg("data_pelanggan.txt");
    ofstream fAnt("data_antrean.txt");
    if (!fPlg.is_open() || !fAnt.is_open()) {
        cout << " Gagal membuka file!\n";
        return;
    }
    fPlg << jmlPlg << "\n";
    fPlg << urutPlg << "\n";
    for (int i = 0; i < jmlPlg; i++) {
        fPlg << ptrPlg[i].idPlg << "\n";
        fPlg << ptrPlg[i].namaPlg << "\n";
        fPlg << ptrPlg[i].alamatPlg << "\n";
        fPlg << ptrPlg[i].telpPlg << "\n";
    }
    fPlg.close();
    
    fAnt << jmlAnt << "\n";
    fAnt << noAntBerikutnya << "\n";
    for (int i = 0; i < jmlAnt; i++) {
        fAnt << ptrAnt[i].noAnt << "\n";
        fAnt << ptrAnt[i].idPlgAnt << "\n";
        fAnt << ptrAnt[i].status << "\n";
        fAnt << ptrAnt[i].layanan << "\n";
    }
    fAnt.close();
    cout << " Data berhasil disimpan ke file!\n";
}

void bacaDariFile() {
    ifstream fPlg("data_pelanggan.txt");
    ifstream fAnt("data_antrean.txt");
    if (!fPlg.is_open() || !fAnt.is_open()) {
        cout << "  File data belum tersedia. Dimulai dari awal.\n";
        return;
    }
    fPlg >> jmlPlg;
    fPlg >> urutPlg;
    fPlg.ignore();
    for (int i = 0; i < jmlPlg; i++) {
        getline(fPlg, ptrPlg[i].idPlg);
        getline(fPlg, ptrPlg[i].namaPlg);
        getline(fPlg, ptrPlg[i].alamatPlg);
        getline(fPlg, ptrPlg[i].telpPlg);
    }
    fPlg.close();
    
    fAnt >> jmlAnt;
    fAnt >> noAntBerikutnya;
    fAnt.ignore();
    for (int i = 0; i < jmlAnt; i++) {
        fAnt >> ptrAnt[i].noAnt;
        fAnt.ignore();
        getline(fAnt, ptrAnt[i].idPlgAnt);
        getline(fAnt, ptrAnt[i].status);
        getline(fAnt, ptrAnt[i].layanan);
    }
    fAnt.close();
    cout << " Data dimuat dari file!\n";
}

void cariRiwayat() {
    int dicari;
    cout << "\n--- Cari Riwayat Antrean ---\n";
    cout << "Nomor Antrean: ";
    cin >> dicari;
    for (int i = 0; i < jmlAnt; i++) {
        if (ptrAnt[i].noAnt == dicari) {
            cout << "\n Ditemukan:\n";
            cout << "No. Antrean: " << ptrAnt[i].noAnt << "\n";
            cout << "ID Pelanggan: " << ptrAnt[i].idPlgAnt << "\n";
            cout << "Status     : " << ptrAnt[i].status << "\n";
            cout << "Layanan    : " << ptrAnt[i].layanan << "\n";
            return;
        }
    }
    cout << " Riwayat tidak ditemukan.\n";
}

void laporanStatistik() {
    int selesai = 0, menunggu = 0, dilayani = 0;
    for (int i = 0; i < jmlAnt; i++) {
        if (ptrAnt[i].status == "Selesai") selesai++;
        else if (ptrAnt[i].status == "Menunggu") menunggu++;
        else if (ptrAnt[i].status == "Dilayani") dilayani++;
    }
    cout << "\n========== LAPORAN STATISTIK ==========\n";
    cout << "Total Pelanggan Terdaftar: " << jmlPlg << "\n";
    cout << "Total Antrean Dibuat     : " << jmlAnt << "\n";
    cout << "Sedang Menunggu          : " << menunggu << "\n";
    cout << "Sedang Dilayani          : " << dilayani << "\n";
    cout << "Selesai Dilayani         : " << selesai << "\n";
    cout << "========================================\n";
}

void menuUtama() {
    cout << "\n\n===== SISTEM ANTRIAN PELAYANAN =====\n";
    cout << " 1. Tambah Data Pelanggan\n";
    cout << " 2. Tampil Semua Pelanggan\n";
    cout << " 3. Cari Data Pelanggan\n";
    cout << " 4. Tambah Antrean\n";
    cout << " 5. Panggil Antrean Berikutnya\n";
    cout << " 6. Selesai Pelayanan\n";
    cout << " 7. Tampil Antrean Aktif\n";
    cout << " 8. Simpan Data ke File\n";
    cout << " 9. Baca Data dari File\n";
    cout << "10. Cari Riwayat Antrean\n";
    cout << "11. Laporan Statistik\n";
    cout << " 0. Keluar\n";
    cout << "Pilihan Anda: ";
}
// ==================================================
//  MAHASISWA 3 — SELESAI
// ==================================================

int main() {
    // Baca data yang pernah disimpan tanpa menghapus file.
    bacaDariFile();
    
    int pilihan;
    do {
        menuUtama();
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << " Masukkan angka yang valid!\n";
            continue;
        }
        switch (pilihan) {
            case 1: inputPlg(); break;
            case 2: tampilSemuaPlg(); break;
            case 3: cariPlg(); break;
            case 4: tambahAntrean(); break;
            case 5: panggilAntrean(); break;
            case 6: selesaiLayanan(); break;
            case 7: tampilAntreanAktif(); break;
            case 8: simpanKeFile(); break;
            case 9: bacaDariFile(); break;
            case 10: cariRiwayat(); break;
            case 11: laporanStatistik(); break;
            case 0: cout << "\n Terima kasih!\n"; break;
            default: cout << " Pilihan tidak tersedia!\n";
        }
    } while (pilihan != 0);
    return 0;
}