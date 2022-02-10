// Nama    : Bostang Palaguna
// NIM 	   : 13220055
// Tanggal : Kamis, 10 Februari 2022

// Program absensiKurang
	// Program yang menerima nama, nim, dan persentase kehadiran dalams suatu kelas yang berisi n mahasiswa
	// kemudian menampilkan ke layar nama dan NIM mahasiswa yang memiliki kehadiran kurang dari 80%.
// KAMUS
	// Konstanta
		// maxSize : integer := 30 { ukuran maksimum dari array }
	// Tipe Data Bentukan
		// type mhs : < nama : string ,
		//				nim  : integer,
		//				persentase_kehadiran : real>
	// Variabel
		// n : integer { jumlah mahasiswa }
		// kelas : array of mhs { array yang menyimpan data dengan tipe data struct mahasiswa }
	
// ALGORITMA UTAMA
#include <stdio.h>

#define maxSize 30

// mendeklarasikan struct mhs dengan properti : nama, nim, persentase_kehadiran
struct mhs
{
	char nama[maxSize];
	int nim;
	double persentase_kehadiran;
};

int n;

struct mhs kelas[maxSize];

int main()
{
	// Menerima input data mahasiswa
	printf("Masukkan jumlah mahasiswa\n>>> ");
	scanf("%d",&n);
	for (int k = 0;k<n;k++)
	{
		printf("Data Mahasiswa ke-%d\n",k+1);

		printf("Nama : ");
		scanf("%s",&kelas[k].nama);

		printf("NIM :");
		scanf("%d",&kelas[k].nim);

		printf("Persentasi kehadiran: ");
		scanf("%lf",&kelas[k].persentase_kehadiran);

		printf("\n");
	}

	// Mencetak nama data mahasiswa yang memiliki presensi kurang dari 80% 
	printf("Berikut adalah mahasiswa yang memiliki presensi kurang dari 80%:\n");
	for (int k = 0;k<n;k++)
	{
		if (kelas[k].persentase_kehadiran<0.8)
		{
			printf("%s\t\t%d\n",kelas[k].nama,kelas[k].nim);
		}
	}

	return 0;
}