// Nama    : Bostang Palaguna
// NIM 	   : 13220055
// Tanggal : Selasa, 25 Januari 2022 ; Rabu, 26 Januari 2022; Kamis, 27 Januari 2022

// Program roundRobinScheduling (RRS)
	// Program yang mensimulasikan algoritma scheduling : round-robin 
// KAMUS
	// Variabel
		// waktuKedatangan : array[0..maxSize-1] of integer
			// array yang menyimpan informasi waktu kedatangan dari tiap proses
		// waktuEksekusi : array[0..maxSize-1] of integer
			// array yang menyimpan informasi waktu eksekusi dari tiap proses
		// nProses : integer
			// banyaknya proses yang akan di-schedule
		// tKuantum : integer
			// ukuran kuantum waktu
	// Konstanta
		// maxSize : integer := 10
			// maksimum banyaknya proses yang ingin di-schedule
			// angka 100 dipilih secara sembarang
		// EMPTY : integer := 9999
			// indeks boneka yang menyatakan bahwa elemen pada suatu array kosong
	// Fungsi/Prosedur
		// procedure cetakTimeProcessTable(input waktuEksekusi, waktuKedatangan: array[0..n-1] of integer)
			// mencetak time-process table dari proses yang telah di-input
		// procedure ganttChart(input waktuEksekusi, waktuKedatangan: array [0..n-1] of integer)
			// realisasi algoritma RRS dan mencetaknya dalam bentuk Gantt-chart
		// function isInArray(integer i, array[0..n-1] of integer arri) -> boolean
			// mengembalikan true bila n terdapat di arri
		// procedure cetakAntrian(input antrian: array[0..n-1] of integer, x, y : integer)
			// mencetak P{k} dari array of integer yang memiliki elemen k }
// ALGORITMA UTAMA
#include <stdio.h>

	// deklarasi konstanta
const int EMPTY = 9999;
const int timeLimit = 9999;
#define maxSize 13

	// deklarasi variabel dan prosedur
int waktuKedatangan[maxSize];
int waktuEksekusi[maxSize];
int nProses;
int tKuantum;

void cetakTimeProcessTable(int waktuKedatangan[], int waktuEksekusi[]);
int isInArray(int i, int arri[]); 
void cetakAntrian(int antrian[],int x, int y);
void ganttChart(int waktuKedatangan[], int waktuEksekusi[]);

int main()
{
	// inisiasi nilai dari array waktuKedatangan dan waktuEksekusi mejadi nol semua
	for (int k = 0;k<maxSize;k++)
	{
		waktuKedatangan[k] = EMPTY;
		waktuEksekusi[k] = EMPTY;
	}

	// menerima input dari user proses apa aja yang ada serta arriving time dan executing time
	printf("Banyaknya Proses:\n>>> ");
	scanf("%d",&nProses);

	for (int k = 0;k<nProses;k++)
	{
		printf("Waktu kedatangan proses ke-%d:\n>>> ",k);
		scanf("%d",&waktuKedatangan[k]);

		printf("Waktu eksekusi proses ke-%d:\n>>> ",k);
		scanf("%d",&waktuEksekusi[k]);
	}

	printf("tKuantum:\n>>> ");
	scanf("%d",&tKuantum);

	// Mencetak time-process table
	cetakTimeProcessTable(waktuKedatangan,waktuEksekusi);

	// Mencetak Gantt-chart yang menggambarkan waktu, antrian, dan proses yang sedang dijalankan
	ganttChart(waktuKedatangan, waktuEksekusi);

	return 0;
}

// REALISASI FUNGSI/PROSEDUR
void cetakTimeProcessTable(int waktuKedatangan[maxSize], int waktuEksekusi[maxSize])
{
	// KAMUS LOKAL
	// ALGORITMA
	printf("Proses\tWaktu Kedatangan\tWaktu Eksekusi\n");
	for (int k = 0;k<nProses;k++)
	{
		printf("  P%d\t\t%d\t\t      %d\n",k,waktuKedatangan[k],waktuEksekusi[k]);
	}
	printf("\n");
}

int isInArray(int i, int arri[maxSize])
{
	// KAMUS LOKAL
	// ALGORITMA
	for (int k = 0;k<maxSize;k++)
	{
		if (arri[k] == i)
		{
			return 1;
		}
	}
	return 0;
}

void cetakAntrian(int antrian[maxSize],int x, int y)
{	
	// KAMUS LOKAL
		// Variabel
			// index : integer
	// ALGORITMA

		// x -> menyatakan posisi awal dari elemen ber-indeks 0 dari array antrian
		// y -> menyatakan banyaknya elemen di akhir cetakAntrian yang tidak diikutkan

	for (int k = 0;k<(nProses-y);k++)
	//for (int k = 0;k<nProses;k++)
	{
		if (nProses != y)
		{
			int index = (k+x) % (nProses-y);

			if (antrian[index] != EMPTY)
			{
				printf("P%d",antrian[index]);

			}

			if (k != nProses-1) // mencetak spasi untuk elemen bukan terakhir
			{
				printf(" ");
			}
		}
		
	}
	// x sebagai offset, misalkan kita ingin mencetak elemen dengan index 2,3,4,0, dan 1. maka n = 5 dan x = 2
	// y sebagai jumlah elemen antrian yang tidak perlu dicetak lagi

	/* contoh :
			misalkan antrian = {1,3,2,0,4} untuk y = 1 :
		 untuk x = 0 -> akan tercetak : P1 P3 P2 P0 {P4}
		 untuk x = 1 -> akan tercetak : P3 P2 P0 {P4} P1
		 untuk x = 2 -> akan tercetak : P2 P0 {P4} P1 P3 
		 	note : {} -> tidak dicetak
	*/

}

//void ganttChart(int waktuKedatangan[nProses], int waktuEksekusi[nProses])
void ganttChart(int waktuKedatangan[maxSize], int waktuEksekusi[maxSize])
{
	// KAMUS LOKAL
		// Variabel
			// antrian : array [0..n-1] of integer
				// array atrian proses
			// telahProses : array[0..n-1] of integer
				// lama waktu yang telah berlangsung untuk masing-masing proses
			// waktu : integer
			// lastInterrupt: integer { terakhir kali tabel ganttChart dicetak }
			// readyqueue : array [0..n-1] of integer
				// array yang menyatakan proses yang telah selesai dijalankan
			// indexreadyqueue : integer
				// index pada array readyqueue yang akan digunakan juga ketika pencetakan elemen antrian
			// first : integer
				// indeks yang merujuk ke elemen pertama pada queue -> proses yang sedang dijalankan
			// last : integer
				//  indeks yang merujuk ke elemen terakhir pada queue -> proses yang terakhir dijalankan
			// indexantrian : integer
	// ALGORITMA
		// Inisiasi nilai variabel
	int first = 0;
	int last = nProses-1;
	int antrian[maxSize];
	int telahProses[maxSize];
	int readyqueue[maxSize];
	int waktu = 0; 
	int lastInterrupt = 0;
	int indexreadyqueue = 0;
	int indexantrian = 0;

	for (int k = 0;k<nProses;k++)
	{
		readyqueue[k] = EMPTY;
		antrian[k] = EMPTY;
		telahProses[k] = EMPTY;
	}

		// mencetak Gantt-chart
	printf("Waktu\tAntrian\t\t\tSelesai\n");

	while (indexreadyqueue < nProses && waktu < timeLimit) // terus lakukan sampai semua proses telah dijalankan
	{
		// ada proses yang masuk ke queue
		for (int k = 0;k<nProses;k++)
		{
			if (waktu == waktuKedatangan[k])
			{
				antrian[indexantrian]= k;
				telahProses[indexantrian] = 0;
				indexantrian++;
			}
		}

		// mengubah first ke index elemen yang akan diproses
			// perubahan terjadi ketika sudah mencapai kuantum waktu atau suatu proses telah selesai dijalankan
		if ((waktu - lastInterrupt >= tKuantum) || (telahProses[first] == waktuEksekusi[first]))
		{
			first = (first+1) % (nProses-indexreadyqueue);
			last =  (last+1) % (nProses-indexreadyqueue);
			lastInterrupt = waktu;
		}

		// mengurusi proses yang telah SELESAI dijalankan
		if (telahProses[first] == (waktuEksekusi[first]))
		{
				readyqueue[indexreadyqueue] = antrian[first];
				indexreadyqueue++;
		}

		// mencetak baris baru dalam Gantt-chart
			// pencetakan baris akan dilakukan apabila ada proses yang selesai, ada proses yang datang, atau waktu telah mencapai kuantum waktu
		if ((waktu - lastInterrupt >= tKuantum) || (indexreadyqueue == nProses) || (isInArray(waktu,waktuKedatangan) == 1))
		{
			printf("%d\t",waktu);
			cetakAntrian(antrian,first,indexreadyqueue);
			printf("\t\t\t");
			
			if (readyqueue[0] != EMPTY) // jika sudah ada proses yang selesai
			{
				for (int k = 0;k<nProses;k++)
				{
					if (readyqueue[k] != EMPTY)
					{
						printf("P%d",readyqueue[k]);
						if (k != nProses-1)
						{
							printf(",");
						}
					}
				}
			}
			printf("\n");	
		}
		telahProses[first]++;
		waktu++;
	}
}
