
#include <stdio.h>
#include <string.h>

#define MAKS 5

char *pilihNama(int index, char *n1, char *n2, char *n3,
                char *n4, char *n5)
{
    switch (index) {
        case 0: return n1;
        case 1: return n2;
        case 2: return n3;
        case 3: return n4;
        case 4: return n5;
        default: return "";
    }
}

int main(void)
{
    char nama1[225], nama2[225], nama3[225];
    char nama4[225], nama5[225];
    char *nama;
    char ulang = 'y';
    int jumlah = 0, dilayani = 0;
    int i, j, c, panjang;
    int valid;

    printf("=============================================\n");
    printf("       SISTEM ANTREAN PELAYANAN\n");
    printf("=============================================\n");

    printf("\n=== PENDAFTARAN PELANGGAN ===\n");

    while (jumlah < MAKS && (ulang == 'y' || ulang == 'Y')) {
        nama = pilihNama(jumlah, nama1, nama2, nama3, nama4, nama5);

        do {
            valid = 1;

            printf("\nMasukkan nama pelanggan: ");

            if (scanf(" %224[^\n]", nama) != 1) {
                printf("Input nama tidak valid.\n");
                return 1;
            }

            while ((c = getchar()) != '\n' && c != EOF) {
            }

            panjang = strlen(nama);

            if (panjang < 3) {
                printf("Nama minimal 3 karakter.\n");
                valid = 0;
            }

            for (i = 0; i < panjang; i++) {
                if (nama[i] >= '0' && nama[i] <= '9') {
                    printf("Nama tidak boleh mengandung angka.\n");
                    valid = 0;
                    break;
                }
            }

        } while (!valid);

        jumlah++;

        printf("\nBerhasil terdaftar!\n");
        printf("Nama          : %s\n", nama);
        printf("Nomor antrean : A%03d\n", jumlah);

        if (jumlah == MAKS) {
            printf("Kapasitas antrean penuh.\n");
            break;
        }

        printf("Daftar lagi? (y/n): ");
        scanf(" %c", &ulang);

        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    printf("\n=== PROSES ANTREAN ===\n");
    printf("Jumlah pelanggan: %d\n", jumlah);

    printf("\n[ANTREAN AKTIF]\n");
    for (j = 0; j < jumlah; j++) {
        nama = pilihNama(j, nama1, nama2, nama3, nama4, nama5);
        printf("%d. A%03d - %s\n", j + 1, j + 1, nama);
    }

    printf("\nTekan Enter untuk mulai melayani...");
    getchar();

    i = 0;

    while (i < jumlah) {
        nama = pilihNama(i, nama1, nama2, nama3, nama4, nama5);

        printf("\n=============================================\n");
        printf("[SEDANG DILAYANI]\n");
        printf("Nomor  : A%03d\n", i + 1);
        printf("Nama   : %s\n", nama);
        printf("Status : sedang diproses...\n");

        dilayani++;
        i++;

        printf("Pelanggan selesai dilayani!\n");
        printf("[STATISTIK] Telah dilayani: %d dari %d\n",
               dilayani, jumlah);

        printf("\n[ANTREAN AKTIF] Menunggu: %d orang\n",
               jumlah - i);

        if (i >= jumlah) {
            printf("(Tidak ada antrean)\n");
        } else {
            for (j = i; j < jumlah; j++) {
                nama = pilihNama(j, nama1, nama2, nama3, nama4, nama5);
                printf("%d. A%03d - %s\n",
                       j - i + 1, j + 1, nama);
            }

            printf("Tekan Enter untuk pelanggan berikutnya...");
            getchar();
        }
    }

    printf("\n=============== RINGKASAN ===============\n");
    printf("Jumlah seluruh pelanggan   : %d\n", jumlah);
    printf("Jumlah yang telah dilayani : %d\n", dilayani);
    printf("Sisa antrean                : %d\n", jumlah - dilayani);

    printf("\nDaftar pelanggan yang dilayani:\n");

    for (i = 0; i < dilayani; i++) {
        nama = pilihNama(i, nama1, nama2, nama3, nama4, nama5);
        printf("%d. A%03d - %s\n", i + 1, i + 1, nama);
    }

    printf("\nTerima kasih telah menggunakan layanan kami!\n");

    return 0;
}

