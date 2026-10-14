#include <stdio.h>
#include <string.h>

#define MAKS 100

int main(void)
{
    char nama[MAKS][25];
    char correct_nama;
    char ulang;
    int nomor[MAKS];  
    int jumlah = 0;
    int dilayani = 0;
    int i;
    int panjang;

    printf("\n=============================================\n");
    printf("       SISTEM ANTREAN PELAYANAN\n");
    printf("=============================================\n");

    printf("\n=== PENDAFTARAN ANTREAN PELANGGAN ===\n");

    do {
        do {
            correct_nama = 'y';

            printf("\nMasukkan nama pelanggan : ");
            scanf(" %[^\n]", nama[jumlah]);

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

        printf("Apakah anda ingin mendaftar lagi? (y/n) : ");
        scanf(" %c", &ulang);

    } while (ulang == 'y' || ulang == 'Y');


    printf("\n\n--- PROSES ANTREAN PELAYANAN ---\n");
    printf("Jumlah pelanggan dalam antrean : %d\n", jumlah);
    printf("Tekan Enter untuk mulai melayani...\n");
    getchar();

    i = 0;
    while (i < jumlah)
    {
        printf("\n---------------------------------------------\n");
        printf("Nomor antrean berikutnya : A%03d\n", nomor[i]);
        printf("Nama pelanggan dilayani  : %s\n", nama[i]);
        printf("Sedang diproses...\n");
        printf("Pelanggan %s selesai dilayani!\n", nama[i]);
        printf("---------------------------------------------\n");

        dilayani++;
        i++;

        if (i < jumlah) {
            printf("Tekan Enter untuk pelanggan berikutnya...\n");
            getchar();
        }
    }

 
    printf("\n\n=============== RINGKASAN ===============\n");
    printf("Jumlah seluruh pelanggan   : %d\n", jumlah);
    printf("Jumlah yang telah dilayani : %d\n", dilayani);
    printf("\nDaftar pelanggan yang telah dilayani:\n");

    for (i = 0; i < dilayani; i++)
    {
        printf("%d. A%03d - %s\n", i + 1, nomor[i], nama[i]);  
    }

    printf("\nTerima kasih telah menggunakan layanan kami.\n");
    return 0;
}
