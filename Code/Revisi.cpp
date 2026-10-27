#include <stdio.h>
#include <string.h>

#define MAKS 5 // jika maksimal hanya 5 pelanggan

int main(void)
{
    char nama1[225], nama2[225], nama3[225];
    char nama4[225], nama5[225];
    char nama[225]; 
    char ulang = 'y';
    int jumlah = 0, dilayani = 0;
    int i, j, c, panjang;
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

    printf("\n\n--- PROSES ANTREAN PELAYANAN ---\n");
    printf("Jumlah pelanggan dalam antrean : %d\n", jumlah);

    printf("\n[ANTREAN AKTIF] Menunggu : %d orang\n", jumlah);
    for (j = 0; j < jumlah; j++) {
        switch (j) {
            case 0: strcpy(nama, nama1); break;
            case 1: strcpy(nama, nama2); break;
            case 2: strcpy(nama, nama3); break;
            case 3: strcpy(nama, nama4); break;
            case 4: strcpy(nama, nama5); break;
        }
        printf("   %d. A%03d - %s\n", j + 1, j + 1, nama);
    }

    printf("\nTekan Enter untuk mulai melayani...\n");
    getchar();

    i = 0;

    while (i < jumlah) {
        switch (i) {
            case 0: strcpy(nama, nama1); break;
            case 1: strcpy(nama, nama2); break;
            case 2: strcpy(nama, nama3); break;
            case 3: strcpy(nama, nama4); break;
            case 4: strcpy(nama, nama5); break;
        }

        printf("\n=============================================\n");

        printf("[SEDANG DILAYANI]\n");
        printf("   Nomor : A%03d\n", i + 1);
        printf("   Nama  : %s\n", nama);
        printf("   Status: sedang diproses...\n");

        dilayani++;
        i++;

        printf("   Pelanggan selesai dilayani!\n");

        printf("\n[STATISTIK] Telah dilayani : %d dari %d pelanggan\n", dilayani, jumlah);

        printf("\n[ANTREAN AKTIF] Menunggu : %d orang\n", jumlah - i);
        if (i >= jumlah) {
            printf("   (tidak ada antrean)\n");
        } else {
            for (j = i; j < jumlah; j++) {
                switch (j) {
                    case 0: strcpy(nama, nama1); break;
                    case 1: strcpy(nama, nama2); break;
                    case 2: strcpy(nama, nama3); break;
                    case 3: strcpy(nama, nama4); break;
                    case 4: strcpy(nama, nama5); break;
                }
                printf("   %d. A%03d - %s\n", j - i + 1, j + 1, nama);
            }
        }

        if (i < jumlah) {
            switch (i) {
                case 0: strcpy(nama, nama1); break;
                case 1: strcpy(nama, nama2); break;
                case 2: strcpy(nama, nama3); break;
                case 3: strcpy(nama, nama4); break;
                case 4: strcpy(nama, nama5); break;
            }
            printf("\nNomor berikutnya : A%03d (%s)\n", i + 1, nama);
            printf("Tekan Enter untuk pelanggan berikutnya...\n");
            getchar();
        }
    }

    printf("\n\n=============== RINGKASAN ===============\n");
    printf("Jumlah seluruh pelanggan   : %d\n", jumlah);
    printf("Jumlah yang telah dilayani : %d\n", dilayani);
    printf("Sisa antrean               : %d\n", jumlah - dilayani);
    printf("\nDaftar pelanggan yang telah dilayani:\n");

    for (i = 0; i < dilayani; i++) {
        switch (i) {
            case 0: strcpy(nama, nama1); break;
            case 1: strcpy(nama, nama2); break;
            case 2: strcpy(nama, nama3); break;
            case 3: strcpy(nama, nama4); break;
            case 4: strcpy(nama, nama5); break;
        }
        printf("%d. A%03d - %s\n", i + 1, i + 1, nama);
    }

    printf("\nTerima kasih telah menggunakan layanan kami!\n");

    printf("\nTekan Enter untuk keluar...\n");
    getchar();

    return 0;
}
