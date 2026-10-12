#include <stdio.h>
#include <string.h>


int main(void)
{
    char nama[25];
    char correct_nama;
    char ulang;
    int nomor = 0;
    int i;
    int panjang;

    printf("\n=== PENDAFTARAN ANTREAN PELANGGAN ===\n");

    do {
        do {
            correct_nama = 'y';

            printf("\nMasukkan nama pelanggan : ");
            scanf(" %[^\n]", nama);

            panjang = strlen(nama);

            if (panjang < 3) {
                printf("Nama pelanggan minimal 3 karakter.\n");
                correct_nama = 'n';
            }

            for (i = 0; i < panjang; i++) {
                if (nama[i] >= '0' && nama[i] <= '9') {
                    printf("Nama pelanggan tidak boleh mengandung angka.\n");
                    correct_nama = 'n';
                    break;
                }
            }
        } while (correct_nama == 'n');
    

        nomor = nomor + 1;
        printf("\n---------------------------------------------\n");
        printf("\t=== BERHASIL TERDAFTAR ===\n");
        printf("\nNama pelanggan            : %s\n", nama);    
        printf("Nomor antrean pelanggan   : A%03d\n\n", nomor);
        printf("---------------------------------------------\n");

        printf("Apakah anda ingin mendaftar lagi? (y/n) : ");
        scanf(" %c", &ulang);

    } while (ulang == 'y' || ulang == 'Y');  
    
    printf("\nTerima kasih telah mendaftar.\n");
    return 0;
}
