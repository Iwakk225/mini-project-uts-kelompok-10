#include <stdio.h>
#include <string.h>

#define MAKS 5 // jika maksimal hanya 5 pelanggan

int main(void)
{
    char nama1[225], nama2[225], nama3[225];
    char nama4[225], nama5[225];
    char nama[225];
    char ulang = 'y';
    int jumlah = 0;
    int i, c, panjang;
    int valid;

    printf("\n=============================================\n");
    printf("       SISTEM ANTREAN PELAYANAN\n");
    printf("=============================================\n");

    printf("\n=== PENDAFTARAN ANTREAN PELANGGAN ===\n");

    while (jumlah < MAKS && (ulang == 'y' || ulang == 'Y')) {

        do {
            valid = 1;

            printf("\nMasukkan nama pelanggan : ");

            if (scanf(" %224[^\n]", nama) != 1) {
                printf("Input nama tidak valid.\n");
                return 1;
            }

            while ((c = getchar()) != '\n' && c != EOF) {
            }

            panjang = strlen(nama);

            if (panjang < 3) {
                printf("Nama pelanggan minimal 3 karakter.\n");
                valid = 0;
            }

            for (i = 0; i < panjang; i++) {
                if (nama[i] >= '0' && nama[i] <= '9') {
                    printf("Nama pelanggan tidak boleh mengandung angka.\n");
                    valid = 0;
                    break;
                }
            }

        } while (!valid);

        switch (jumlah) {
            case 0: strcpy(nama1, nama); break;
            case 1: strcpy(nama2, nama); break;
            case 2: strcpy(nama3, nama); break;
            case 3: strcpy(nama4, nama); break;
            case 4: strcpy(nama5, nama); break;
        }

        jumlah++;

        printf("\n---------------------------------------------\n");
        printf("\t=== BERHASIL TERDAFTAR ===\n");
        printf("\nNama pelanggan            : %s\n", nama);
        printf("Nomor antrean pelanggan   : A%03d\n\n", jumlah);
        printf("---------------------------------------------\n");

        if (jumlah == MAKS) {
            printf("Kapasitas antrean penuh (%d).\n", MAKS);
            break;
        }

        printf("Apakah anda ingin mendaftar lagi? (y/n) : ");
        if (scanf(" %c", &ulang) != 1) {
            ulang = 'n';
        }

        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    printf("\nTerima kasih telah mendaftar.\n");

    printf("\nTekan Enter untuk keluar...\n");
    getchar();

    return 0;
}
