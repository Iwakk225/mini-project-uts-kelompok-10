#include <stdio.h>
#include <string.h>

#define MAKS 100

int main(void)
{
    char nama[MAKS][225];
    char correct_nama;
    char ulang;
    int nomor[MAKS];
    int jumlah = 0;
    int dilayani = 0;
    int i;
    int j;
    int c;
    int panjang;

    printf("\n=============================================\n");
    printf("       SISTEM ANTREAN PELAYANAN\n");
    printf("=============================================\n");

    /* ================= MAHASISWA 1: PENDAFTARAN & INPUT ================= */
    printf("\n=== PENDAFTARAN ANTREAN PELANGGAN ===\n");

    do {
        do {
            correct_nama = 'y';

            printf("\nMasukkan nama pelanggan : ");
            scanf(" %50[^\n]", nama[jumlah]);

            /* >>> MAHASISWA 3 <<< : buang sisa input supaya getchar() nanti tidak kelewat */
            while ((c = getchar()) != '\n' && c != EOF) {
            }

            panjang = strlen(nama[jumlah]);

            if (panjang < 3) {
                printf("Nama pelanggan minimal 3 karakter.\n");
                correct_nama = 'n';
            }

            for (i = 0; i < panjang; i++) {
                if (nama[jumlah][i] >= '0' && nama[jumlah][i] <= '9') {
                    printf("Nama pelanggan tidak boleh mengandung angka.\n");
                    correct_nama = 'n';
                    break;
                }
            }
        } while (correct_nama == 'n');

        nomor[jumlah] = jumlah + 1;
        jumlah++;

        printf("\n---------------------------------------------\n");
        printf("\t=== BERHASIL TERDAFTAR ===\n");
        printf("\nNama pelanggan            : %s\n", nama[jumlah - 1]);
        printf("Nomor antrean pelanggan   : A%03d\n\n", nomor[jumlah - 1]);
        printf("---------------------------------------------\n");

        /* >>> MAHASISWA 3 <<< : cegah array penuh */
        if (jumlah == MAKS) {
            printf("Kapasitas antrean penuh (%d).\n", MAKS);
            break;
        }

        printf("Apakah anda ingin mendaftar lagi? (y/n) : ");
        scanf(" %c", &ulang);

        /* >>> MAHASISWA 3 <<< : buang sisa input */
        while ((c = getchar()) != '\n' && c != EOF) {
        }

    } while (ulang == 'y' || ulang == 'Y');

    /* ================= MAHASISWA 2: PROSES ANTREAN ================= */
    printf("\n\n--- PROSES ANTREAN PELAYANAN ---\n");
    printf("Jumlah pelanggan dalam antrean : %d\n", jumlah);

    /* >>> MAHASISWA 3 <<< : tampilkan antrean aktif sebelum mulai */
    printf("\n[ANTREAN AKTIF] Menunggu : %d orang\n", jumlah);
    for (j = 0; j < jumlah; j++) {
        printf("   %d. A%03d - %s\n", j + 1, nomor[j], nama[j]);
    }

    printf("\nTekan Enter untuk mulai melayani...\n");
    getchar();

    i = 0;
    while (i < jumlah)
    {
        printf("\n=============================================\n");

        /* >>> MAHASISWA 3 <<< : tampilkan pelanggan yang sedang dilayani */
        printf("[SEDANG DILAYANI]\n");
        printf("   Nomor : A%03d\n", nomor[i]);
        printf("   Nama  : %s\n", nama[i]);
        printf("   Status: sedang diproses...\n");

        dilayani++;
        i++;

        printf("   Pelanggan selesai dilayani!\n");

        /* >>> MAHASISWA 3 <<< : tampilkan jumlah yang sudah dilayani */
        printf("\n[STATISTIK] Telah dilayani : %d dari %d pelanggan\n", dilayani, jumlah);

        /* >>> MAHASISWA 3 <<< : tampilkan antrean aktif (sisa yang menunggu) */
        printf("\n[ANTREAN AKTIF] Menunggu : %d orang\n", jumlah - i);
        if (i >= jumlah) {
            printf("   (tidak ada antrean)\n");
        } else {
            for (j = i; j < jumlah; j++) {
                printf("   %d. A%03d - %s\n", j - i + 1, nomor[j], nama[j]);
            }
        }

        if (i < jumlah) {
            printf("\nNomor berikutnya : A%03d (%s)\n", nomor[i], nama[i]);
            printf("Tekan Enter untuk pelanggan berikutnya...\n");
            getchar();
        }
    }

    /* ================= MAHASISWA 3: RINGKASAN AKHIR ================= */
    printf("\n\n=============== RINGKASAN ===============\n");
    printf("Jumlah seluruh pelanggan   : %d\n", jumlah);
    printf("Jumlah yang telah dilayani : %d\n", dilayani);
    printf("Sisa antrean               : %d\n", jumlah - dilayani);
    printf("\nDaftar pelanggan yang telah dilayani:\n");

    for (i = 0; i < dilayani; i++)
    {
        printf("%d. A%03d - %s\n", i + 1, nomor[i], nama[i]);
    }

    printf("\nTerima kasih telah menggunakan layanan kami!\n");
    return 0;
}
