#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAKS 5                       /* maksimal 5 pelanggan */
#define FILE_RIWAYAT "riwayat_antrean.txt"

/* status antrean: menunggu, sedang dilayani, selesai (Mahasiswa 2) */
enum { MENUNGGU, DILAYANI, SELESAI };
const char *STATUS[] = {"Menunggu", "Sedang dilayani", "Selesai"};

/* ========================================================
   MAHASISWA 1 - DATA PELANGGAN DAN PENDAFTARAN
   ======================================================== */

/* struct Pelanggan: ID dan nama berupa string */
typedef struct {
    char id[10];
    char nama[225];
} Pelanggan;

/* ========================================================
   MAHASISWA 2 - PROSES DAN PENGELOLAAN ANTREAN
   ======================================================== */

/* struct Antrian: menyimpan pointer ke data pelanggan */
typedef struct {
    int nomor;
    int status;
    Pelanggan *pel;
} Antrian;

/* ---------- fungsi bantu umum ---------- */
void bersihkanBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

/* ========================================================
   MAHASISWA 1 - FUNGSI PENDAFTARAN
   ======================================================== */

/* validasi nama: minimal 3 karakter dan tidak boleh ada angka */
int namaValid(const char *s)
{
    if (strlen(s) < 3) {
        printf("Nama pelanggan minimal 3 karakter.\n");
        return 0;
    }
    for (; *s != '\0'; s++) {
        if (isdigit((unsigned char)*s)) {
            printf("Nama pelanggan tidak boleh mengandung angka.\n");
            return 0;
        }
    }
    return 1;
}

/* simpan pelanggan baru ke array, akses memakai pointer, ID otomatis */
Pelanggan *daftarPelanggan(Pelanggan *data, int *jumlah)
{
    Pelanggan *p = data + *jumlah;

    do {
        printf("\nMasukkan nama pelanggan : ");
        scanf(" %224[^\n]", p->nama);
        bersihkanBuffer();
    } while (!namaValid(p->nama));

    snprintf(p->id, sizeof(p->id), "P%03d", *jumlah + 1);
    (*jumlah)++;
    return p;
}

/* ========================================================
   MAHASISWA 2 - FUNGSI ANTREAN
   ======================================================== */

/* tambah antrean: nomor antrean dibuat otomatis, status awal Menunggu */
Antrian *tambahAntrean(Antrian *antrean, int *jumlah, Pelanggan *p)
{
    Antrian *q = antrean + *jumlah;

    q->nomor = *jumlah + 1;
    q->status = MENUNGGU;
    q->pel = p;
    (*jumlah)++;
    return q;
}

/* panggil antrean: Menunggu -> Sedang dilayani (NULL jika tidak ada) */
Antrian *panggilAntrean(Antrian *antrean, int jumlah)
{
    Antrian *q;

    for (q = antrean; q < antrean + jumlah; q++) {
        if (q->status == MENUNGGU) {
            q->status = DILAYANI;
            return q;
        }
    }
    return NULL;
}

/* selesaikan layanan: Sedang dilayani -> Selesai */
void selesaikanLayanan(Antrian *q)
{
    q->status = SELESAI;
}

/* ========================================================
   MAHASISWA 3 - RIWAYAT DAN STATISTIK ANTREAN
   ======================================================== */

/* kosongkan file riwayat di awal program (hapus baris ini jika
   riwayat ingin menumpuk antar sesi) */
void resetRiwayat(void)
{
    FILE *file = fopen(FILE_RIWAYAT, "w");
    if (file != NULL) fclose(file);
}

/* simpan data antrean ke file (mode "a" = tambah di akhir file) */
void simpanRiwayat(const Antrian *q)
{
    FILE *file = fopen(FILE_RIWAYAT, "a");

    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }
    fprintf(file, "%d|%s|%s|%d\n", q->nomor, q->pel->id, q->pel->nama, q->status);
    fclose(file);
}

/* baca riwayat antrean dari file */
void bacaRiwayat(void)
{
    FILE *file = fopen(FILE_RIWAYAT, "r");
    int nomor, status;
    char id[10], nama[225];

    if (file == NULL) {
        printf("Belum ada riwayat.\n");
        return;
    }
    printf("\n--- RIWAYAT ANTREAN (dari file) ---\n");
    while (fscanf(file, "%d|%9[^|]|%224[^|]|%d\n", &nomor, id, nama, &status) == 4)
        printf("A%03d | %-5s | %-20s | %s\n", nomor, id, nama, STATUS[status]);
    fclose(file);
}

/* tampilkan antrean aktif (yang belum selesai) */
void tampilAntreanAktif(const Antrian *antrean, int jumlah)
{
    const Antrian *q;
    int aktif = 0;

    printf("\n[ANTREAN AKTIF]\n");
    for (q = antrean; q < antrean + jumlah; q++) {
        if (q->status != SELESAI) {
            printf("   A%03d - %-20s (%s)\n", q->nomor, q->pel->nama, STATUS[q->status]);
            aktif++;
        }
    }
    if (aktif == 0) printf("   (tidak ada antrean)\n");
}

/* cari antrean berdasarkan nomor antrean (NULL jika tidak ketemu) */
Antrian *cariAntrean(Antrian *antrean, int jumlah, int nomor)
{
    Antrian *q;

    for (q = antrean; q < antrean + jumlah; q++)
        if (q->nomor == nomor)
            return q;
    return NULL;
}

/* hitung pelanggan yang telah dilayani */
int hitungTerlayani(const Antrian *antrean, int jumlah)
{
    const Antrian *q;
    int selesai = 0;

    for (q = antrean; q < antrean + jumlah; q++)
        if (q->status == SELESAI) selesai++;
    return selesai;
}

/* laporan jumlah pelanggan yang telah dilayani */
void laporan(const Antrian *antrean, int jumlah)
{
    const Antrian *q;
    int selesai = hitungTerlayani(antrean, jumlah);

    printf("\n=============== RINGKASAN ===============\n");
    printf("Jumlah seluruh pelanggan   : %d\n", jumlah);
    printf("Jumlah yang telah dilayani : %d\n", selesai);
    printf("Sisa antrean               : %d\n", jumlah - selesai);
    printf("\nDaftar pelanggan yang telah dilayani:\n");
    for (q = antrean; q < antrean + jumlah; q++)
        if (q->status == SELESAI)
            printf("   A%03d - %s\n", q->nomor, q->pel->nama);
}

/* ========================================================
   PROGRAM UTAMA (alur sama seperti kode awal)
   ======================================================== */
int main(void)
{
    Pelanggan data[MAKS];            /* array pelanggan (Mahasiswa 1) */
    Antrian antrean[MAKS];           /* array antrean   (Mahasiswa 2) */
    int jumlahPel = 0, jumlahAntrean = 0;
    int nomor;
    char ulang = 'n', cari;
    char buf[20];
    const char *s;
    Pelanggan *p;
    Antrian *q;

    resetRiwayat();                                          /* M3 */

    printf("\n=============================================\n");
    printf("       SISTEM ANTREAN PELAYANAN\n");
    printf("=============================================\n");

    /* ---------- PENDAFTARAN (Mahasiswa 1 + 2) ---------- */
    printf("\n=== PENDAFTARAN ANTREAN PELANGGAN ===\n");
    do {
        p = daftarPelanggan(data, &jumlahPel);               /* M1 */
        q = tambahAntrean(antrean, &jumlahAntrean, p);       /* M2 */

        printf("\n---------------------------------------------\n");
        printf("\t=== BERHASIL TERDAFTAR ===\n");
        printf("\nID pelanggan              : %s\n", p->id);
        printf("Nama pelanggan            : %s\n", p->nama);
        printf("Nomor antrean pelanggan   : A%03d\n\n", q->nomor);
        printf("---------------------------------------------\n");

        if (jumlahAntrean == MAKS) {
            printf("Kapasitas antrean penuh (%d).\n", MAKS);
            break;
        }
        printf("Apakah anda ingin mendaftar lagi? (y/n) : ");
        scanf(" %c", &ulang);
        bersihkanBuffer();
    } while (ulang == 'y' || ulang == 'Y');

    /* ---------- ANTREAN AKTIF + PENCARIAN (Mahasiswa 3) ---------- */
    printf("\n\n--- PROSES ANTREAN PELAYANAN ---\n");
    printf("Jumlah pelanggan dalam antrean : %d\n", jumlahAntrean);
    tampilAntreanAktif(antrean, jumlahAntrean);              /* M3 */

    printf("\nCari antrean berdasarkan nomor? (y/n) : ");
    scanf(" %c", &cari);
    bersihkanBuffer();
    while (cari == 'y' || cari == 'Y') {
        printf("Masukkan nomor antrean (contoh 1 atau A001) : ");
        scanf("%19s", buf);
        bersihkanBuffer();
        s = buf;
        if (*s == 'A' || *s == 'a') s++;
        if (sscanf(s, "%d", &nomor) == 1) {
            q = cariAntrean(antrean, jumlahAntrean, nomor);  /* M3 */
            if (q != NULL)
                printf("Ditemukan: A%03d - %s (%s)\n",
                       q->nomor, q->pel->nama, STATUS[q->status]);
            else
                printf("Nomor antrean tidak ditemukan.\n");
        } else {
            printf("Input tidak valid.\n");
        }
        printf("Cari lagi? (y/n) : ");
        scanf(" %c", &cari);
        bersihkanBuffer();
    }

    /* ---------- PROSES PELAYANAN (Mahasiswa 2 + 3) ---------- */
    printf("\nTekan Enter untuk mulai melayani...\n");
    getchar();

    while ((q = panggilAntrean(antrean, jumlahAntrean)) != NULL) {   /* M2 */
        printf("\n=============================================\n");
        printf("[SEDANG DILAYANI]\n");
        printf("   Nomor : A%03d\n", q->nomor);
        printf("   Nama  : %s\n", q->pel->nama);
        printf("   Status: %s\n", STATUS[q->status]);

        selesaikanLayanan(q);                                /* M2 */
        simpanRiwayat(q);                                    /* M3 */
        printf("   Pelanggan selesai dilayani! (Status: %s)\n", STATUS[q->status]);

        printf("\n[STATISTIK] Telah dilayani : %d dari %d pelanggan\n",
               hitungTerlayani(antrean, jumlahAntrean), jumlahAntrean);   /* M3 */
        tampilAntreanAktif(antrean, jumlahAntrean);          /* M3 */

        if (hitungTerlayani(antrean, jumlahAntrean) < jumlahAntrean) {
            printf("\nTekan Enter untuk pelanggan berikutnya...\n");
            getchar();
        }
    }

    /* ---------- LAPORAN + RIWAYAT (Mahasiswa 3) ---------- */
    laporan(antrean, jumlahAntrean);                         /* M3 */
    bacaRiwayat();                                           /* M3 */

    printf("\nTerima kasih telah menggunakan layanan kami!\n");
    return 0;
}