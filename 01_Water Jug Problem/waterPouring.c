// Nama    : Bostang Palaguna
// NIM 	   : 13220055
// Tanggal : Selasa, 18 Januari 2022

// Program waterPouring
	// mendapatkan air sebanyak 4L dari kendi A berkapasitas 3L dan kendi B berkapasitas 5L dengan aksi tertentu
	// Aksi :
		// 1. mengisi penuh suatu kendi
		// 2. mengosongkan suatu kendi
		// 3. memindahkan air dari satu kendi ke kendi lain sampai kendi tujuan sudah penuh atau kendi sumber sudah kosong.
// KAMUS
	// Variabel
		// A, B : integer { banyaknya air yang terdapat di kendi A dan B }
		// opsi : integer { tindakan yang diambil }
		// flag : boolean { jika bernilai 0, maka kita stop program segera }
	// Fungsi/Prosedur
		// procedure fill(input : character x)
			// prosedur untuk mengisi kendi x
		// procedure move(input : x,y character)
			// prosedur untuk memindahkan air dari kendi x ke kendi y
		// procedure empty(input : character x)
			// prosedur untuk mengosongkan kendi x
        // procedure list_opsi()
            // prosedur untuk menampilkan opsi yang bisa dilakukan pengguna
        // procedure opening()
            // menampilkan pesan awal

// ALGORITMA UTAMA
#include <stdio.h>
    // deklarasi variabel dan prosedur
int A,B;
int flag;
int opsi;

void empty(char x);
void fill(char x);
void move(char x, char y);
void list_opsi();
void opening();

    // fungsi utama program
int main()
{
        // inisiasi variabel
	A = 0;
	B = 0;
	flag = 1;

        // menampilkan pesan awal
    opening();
        // menampilkan opsi aksi yang bisa dilakukan
    list_opsi();
    printf("Dapatkanlah air sebesar 4L\n");
    printf("----------------------------\n\n");
        // terus melakukan pemilihan aksi selama B belum sama dengan 4
	while (B != 4 && (flag == 1))
	{
	    printf("A = %d, B = %d\n",A,B);

            // meminta input dari pengguna untuk langkah selanjutnya yang harus dilakukan
		printf("opsi?\n");
		printf(">>> ");
		scanf("%d",&opsi);
		if (opsi == 1)
		{
			fill('A'); // mengisi penuh kendi A
		}

		else if (opsi == 2)
		{
			fill('B'); // mengisi penuh kendi B
		}

		else if (opsi == 3)
		{
			empty('A'); // mengosongkan kendi A
		}

		else if (opsi == 4)
		{
			empty('B'); // mengosongkan kendi B
		}

		else if (opsi == 5)
		{
			move('A','B'); // memindahkan air dari kendi A ke kendi B
		}

		else if (opsi == 6)
		{
			move('B','A'); // memindahkan air dari kendi B ke kendi A
		}
		else if (opsi == 7)
        {
            list_opsi(); // menampilkan kemungkinan opsi
        }
        else if (opsi == 8)
        {
           flag = 0; // keluar program dengan segera
        }
		else
		{
			printf("Opsi tidak sesuai\n");
		}
		printf("\n");
	}
    if (flag == 1) // jika program tidak keluar secara paksa
    {
        printf("A = %d, B = %d\n",A,B); // mencetak nilai akhir A dan B
    }

	return 0;
}

// REALISASI FUNGSI/PROSEDUR
void empty(char x)
{
	if (x == 'A')
		A = 0;
	else if (x == 'B')
		B = 0;
}

void fill(char x)
{
	if (x == 'A')
		A = 3;
	else if (x == 'B')
		B = 5;
}

void move(char x, char y)
{
        // memindahkan air dari A ke B
	if (x == 'A' && y == 'B')
	{
	    if (A != 0 && B != 5) // jika kendi sumber tidak kosong dan kendi tujuan belum penuh
        {
            if (A > (5-B)) // jika B mungkin diisi sampai penuh
            {
                A = A - (5 - B);
                B = 5;
            }
            else // jika A bisa dipindahkan sampai habis
            {
                B = A + B;
                A = 0;
            }
        }
        else
        {
            printf("Aksi tidak dapat dilakukan!\n");
        }
	}

		// memindahkan air dari B ke A
	else if (x == 'B' && y == 'A')
	{
		if (B != 0 && A != 3) // jika kendi sumber tidak kosong dan kendi tujuan belum penuh
        {
            if (B > (3-A)) // jika A mungkin diisi sampai penuh
            {
                B = B - (3-A);
                A = 3;
            }
            else // jika B bisa dipindahkan sampai habis
            {
                A = A + B;
                B = 0;
            }
        }
        else
        {
            printf("Aksi tidak dapat dilakukan!\n");
        }
	}
}

void list_opsi()
{
    printf("pilihan Aksi:\n");
    printf("\t(1) isi penuh A\n");
    printf("\t(2) isi penuh B\n");
    printf("\t(3) kosongkan A\n");
    printf("\t(4) kosongkan B\n");
    printf("\t(5) pindahkan air dari A ke B\n");
    printf("\t(6) pindahkan air dari B ke A\n\n");
    printf("\t(7) tampilkan opsi\n");
    printf("\t(8) keluar\n\n");
}

void opening()
{
    printf("Diberikan 2 buah kendi:\n");
    printf("\tKendi A dengan kapasitas 3L\n");
    printf("\tKendi B dengan kapasitas 5L\n");
    printf("dengan ");
}
