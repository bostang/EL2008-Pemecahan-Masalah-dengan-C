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
			// angka 10 dipilih secara sembarang
		// EMPTY : integer := 9999
			// indeks boneka yang menyatakan bahwa elemen pada suatu array kosong
		// timeLimit : integer := 9999
	// Fungsi/Prosedur
		// procedure cetakTimeProcessTable(input waktuEksekusi, waktuKedatangan: array[0..n-1] of integer)
			// mencetak time-process table dari proses yang telah di-input
		// procedure ganttChart(input waktuEksekusi, waktuKedatangan: array [0..n-1] of integer)
			// realisasi algoritma RRS dan mencetaknya dalam bentuk Gantt-chart
		// function isInArray(integer i, array[0..n-1] of integer arri) -> boolean
			// mengembalikan true bila n terdapat di arri
		// procedure cetakAntrian(input antrian: array[0..n-1] of integer)
			// mencetak P{k} dari array of integer yang memiliki elemen k }
		// function isAllEmpty(array[0..maxSize-1] of integer) -> boolean
			// fungsi yang akan mengembalikan nilai true bila semua elemen pada array bernilai EMPTY
		// function swapElement(array[0..maxSize-1] of integer; integer: a, b) -> arr [0..n-1] of integer
			// fungsi untuk menukar 2 elemen pada sebuah array
		// procedure geserSiklik(input arri: array[0..maxSize-1] of integer, x : integer ) 
			// menggeser elemen pada suatu array ke kiri dengan bayangan array tersebut siklik (elemen pertama terhubung langsung)
			// dengan element terakhir. x adalah banyaknya elemen array yang tak kosong.
			// array akan dibuat dipepet ke kiri, artinya tidak ada elemen kosong yang berindeks
			// lebih kecil dari elemen tak kosong. asumsi awal array sudah pepet kiri
		// procedure removeElement(input arri : array[0..maxSize-1] of integer, indexRemove)
			// menghapus elemen dari suatu array of integer dan menggantikannya dengan sebuah
			// nilai yang ditetapkan sebagai EMPTY. Array hasil sedemikian rupa sehingga tidak ada
			// EMPTY di tengah-tengah elemen non-EMPTY
		// function minArray(int arri[0..maxSize-1]) -> integer
			// mencari nilai minimum dari suatu array of integer
		// fungsi countElem(arri : arry [0..maxSize-1] of integer) -> integer
			// menghitung banyaknya elemen dari suatu array yang tidak kosong
		// procedure cetakBaris()
			// mencetak baris dalam gantt-chart pada suatu waktu

// ALGORITMA UTAMA
#include <stdio.h>
#include <stdbool.h>

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
bool isInArray(int i, int arri[]); 
void cetakAntrian(int antrian[]);
void ganttChart(int waktuKedatangan[], int waktuEksekusi[]);
bool isAllEmpty(int arri[]);

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
 
int minArray(int arri[maxSize])
{
	// KAMUS LOKAL
		// Variabel
			// min : integer { nilai minimum sementara }
	// ALGORIMA
	int min = arri[0]; // asumsikan tidak kosong

	for (int k=1;k<maxSize;k++)
	{
		if (arri[k] != EMPTY)
		{
			if (arri[k] < min)
			{
				min = arri[k];
			}
		}
	}
	return min;
}
	
int countElem(int arri[maxSize])
{
	// KAMUS LOKAL
		// count : integer { pencacah }
	// ALGORITMA
	int count = 0;
	for (int k = 0;k<maxSize;k++)
	{
		if(arri[k] != EMPTY)
		{
			count++;
		}
	}
	return count;
}

void swapElement(int arri[maxSize],int a, int b)
{
	// KAMUS LOKAL	
		// Variabel
			// temp : integer { variabel sementara untuk swapping }
	// ALGORITMA
	int temp;
	temp = arri[a];
	arri[a] = arri[b];
	arri[b] = temp;
}

void geserSiklik(int arri[maxSize], int x)
{
	// KAMUS LOKAL
	// ALGORITMA
		// langkah 1 : menggeser secara siklik
	for (int k = 0;k<maxSize-1;k++)
	{
		swapElement(arri,k,k+1);
	}
		// langkah 2 : pepet ke kiri
	swapElement(arri,x-1,maxSize-1);
}

void removeElement(int arri[maxSize], int indexRemove)
{
	// KAMUS LOKAL
	// ALGORITMA 
		// mengapungkan elemen yang mau dihapus ke ujung
	for (int k = indexRemove;k<maxSize;k++)
	{
		swapElement(arri,k,k+1);
	}
		// menghapus elemen yang paling ujung
	arri[maxSize-1] = EMPTY;
}

bool isAllEmpty(int arri[maxSize])
{
	// KAMUS LOKAL
	// ALGORITMA
	for (int k = 0;k<maxSize;k++)
	{
		if(arri[k] != EMPTY)
		{
			return false;
		}
	}
	return true;
}
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

bool isInArray(int i, int arri[maxSize])
{
	// KAMUS LOKAL
	// ALGORITMA
	for (int k = 0;k<maxSize;k++)
	{
		if (arri[k] == i)
		{
			return true;
		}
	}
	return false;
}

void cetakAntrian(int antrian[maxSize])
{
	for (int k = 0;k<nProses;k++)
	{
		if (antrian[k] != EMPTY)
		{
			printf("P%d",antrian[k]);
		}

		if (antrian[k+1] != EMPTY)
		{
			printf(" "); // mencetak spasi bila belum mencapai ujung
		}
	}
}

void cetakBaris(int waktu, int antrian[maxSize], int readyqueue[maxSize] )
{
	// KAMUS LOKAL
	// ALGORTIMA
	printf("%d\t",waktu);
	cetakAntrian(antrian);
	printf("\t\t\t");
	if (readyqueue[0] != EMPTY) // jika sudah ada proses yang selesai
	{
		for (int k = 0;k<nProses;k++)
		{
			if (readyqueue[k] != EMPTY)
			{
				printf("P%d",readyqueue[k]);
				if (readyqueue[k+1] != EMPTY)
				{
					printf(",");
				}
			}
		}
	}
	printf("\n");		
}	

void ganttChart(int waktuKedatangan[nProses], int waktuEksekusi[nProses])
{
	// KAMUS LOKAL
		// Variabel
			// antrian : array [0..maxSize-1] of integer
				// array atrian proses
			// telahProses : array[0..maxSize-1] of integer
				// lama waktu yang telah berlangsung untuk masing-masing proses
			// waktu : integer
			// lastInterrupt: integer
				// terakhir kali baris tabel gantt-Chart dicetak
			// readyqueue : array [0..mazSize-1] of integer
				// array yang menyatakan proses yang telah selesai dijalankan
			// indexreadyqueue : integer
				// jumlah elemen yang sudah ada pada array readyqueue
			// first : integer
				// indeks yang merujuk ke elemen pertama pada queue -> proses yang sedang dijalankan
			// last : integer
				//  indeks yang merujuk ke elemen terakhir pada queue -> proses yang terakhir dijalankan
			// indexantrian : integer
				// jumlah elemen pada array antrian
			// tempwaktuEksekusi : array[0..maxSize-1] of integer
				// array waktu eksekusi masing-masing proses (yang ikut digeser bersama dengan antrian)
			// kondisiGeser : boolean
				// flag agar antrian tidak digeser ketika baru saja ada elemen yang dihapus
			// : boolean
				// flag agar tidak mencetak suatu baris dua kali pada waktu yang sama
				// kasus yang mungkin yaitu saat pada suatu waktu ada elemen yang masuk dan ada elemen yang dihapuskan

	// ALGORITMA
		// deklarasi dan inisiasi variabel lokal
	bool kondisiGeser = true;
	int antrian[maxSize];
	int telahProses[maxSize];
	int readyqueue[maxSize];
	int waktu = 0; 
	int lastInterrupt = minArray(waktuKedatangan);
	int indexreadyqueue = 0;
	int indexantrian = 0;
	int tempwaktuEksekusi[maxSize];

	for (int k = 0;k<maxSize;k++)
	{
		readyqueue[k] = EMPTY;
		antrian[k] = EMPTY;
		telahProses[k] = EMPTY;
		tempwaktuEksekusi[k] = EMPTY;
	}	

		// mencetak header Gantt-chart
	printf("Waktu\tAntrian\t\t\tSelesai\n");

		// mencetak baris Gantt-chart sekaligus menjalankan algoritma
	while((indexreadyqueue < nProses)&& waktu < timeLimit)
	{
		
	// mengurusi proses yang telah SELESAI 
		// proses yang telah selesai harus dimasukkan ke readyqueue dan dihapus dari antrian
		if ((telahProses[0] != EMPTY) && (telahProses[0] >= (tempwaktuEksekusi[0])))
		{
			kondisiGeser = false;
			readyqueue[indexreadyqueue] = antrian[0];
			removeElement(telahProses,0);
			removeElement(antrian,0);
			indexreadyqueue++;
		}

		// ketika sudah mencapai kuantum waktu atau suatu proses telah selesai dijalankan
		if ((waktu - lastInterrupt >= tKuantum) || ((telahProses[0] >= tempwaktuEksekusi[0]) && (telahProses[0] != EMPTY)))
		{
			if (kondisiGeser)
			{
				geserSiklik(antrian, countElem(antrian));
				geserSiklik(telahProses, countElem(telahProses));
				geserSiklik(tempwaktuEksekusi, countElem(tempwaktuEksekusi));
			}

			kondisiGeser = true;

			if (!(isInArray(waktu, waktuKedatangan))) // tidak dilakukan ketika ada proses yang datang agar 
			{											// pada waktu tersebut tidak dicetak dua kali
				cetakBaris(waktu, antrian, readyqueue);			
			}

			lastInterrupt = waktu;
		}

		// ada proses yang masuk ke queue
		for (int k = 0;k<nProses;k++)
		{
			if (waktu == waktuKedatangan[k])
			{
				antrian[indexantrian- indexreadyqueue]= k;
				telahProses[indexantrian-indexreadyqueue] = 0;
				indexantrian++;
			}
		}

		for (int k = 0;k<nProses;k++)
		{
			if (antrian[k] != EMPTY)
			{
				tempwaktuEksekusi[k] = waktuEksekusi[antrian[k]];
			}
		}

		// mencetak baris baru dalam Gantt-chart
			// pencetakan baris akan dilakukan apabila ada proses yang selesai, ada proses yang datang, atau waktu telah mencapai kuantum waktu
		if ((indexreadyqueue == nProses) || isInArray(waktu,waktuKedatangan))
		{
			cetakBaris(waktu, antrian, readyqueue);
		}
		if (telahProses[0] != EMPTY)
		{
			telahProses[0]++;
		}
		waktu++;
	}
}