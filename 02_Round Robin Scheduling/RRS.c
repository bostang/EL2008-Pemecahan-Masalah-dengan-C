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
	arri[maxSize] = EMPTY;
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

void ganttChart(int waktuKedatangan[nProses], int waktuEksekusi[nProses])
{
	// KAMUS LOKAL
	// ALGORITMA
	int antrian[maxSize];
	int telahProses[maxSize];
	int readyqueue[maxSize];
	int waktu = 0; 
	int lastInterrupt = minArray(waktuKedatangan);
	int indexreadyqueue = 0;
	int indexantrian = 0;

	for (int k = 0;k<maxSize;k++)
	{
		readyqueue[k] = EMPTY;
		antrian[k] = EMPTY;
		telahProses[k] = EMPTY;
	}	

		// mencetak Gantt-chart
	printf("Waktu\tAntrian\t\t\tSelesai\n");

	//while(!(isAllEmpty(antrian)) && waktu < timeLimit)
	while((indexreadyqueue < nProses)&& waktu < timeLimit)
	{
		// ada proses yang masuk ke queue
			// ketika ada proses yang masuk ke queue, last harus bergeser
		for (int k = 0;k<nProses;k++)
		{
			if (waktu == waktuKedatangan[k]) // elemen yang datang akan dipindahkan ke antrian index ke-nol
			{
				antrian[indexantrian]= k;
				telahProses[indexantrian] = 0;
				indexantrian++;
			}
		}


	// mengurusi proses yang telah SELESAI 
			// proses yang telah selesai harus dimasukkan ke readyqueue dan dihapus dari antrian
		if (telahProses[0] == (waktuEksekusi[0]))
		{
			readyqueue[indexreadyqueue] = antrian[0];
			removeElement(telahProses,0);
			removeElement(antrian,0);
			indexreadyqueue++;
		}


		// ketika sudah mencapai kuantum waktu atau suatu proses telah selesai dijalankan
		if ((waktu - lastInterrupt >= tKuantum) || (telahProses[0] == waktuEksekusi[0]))
		{
			geserSiklik(antrian, indexantrian );
			geserSiklik(telahProses, indexantrian);
			geserSiklik(waktuEksekusi, indexantrian);
			geserSiklik(waktuKedatangan, indexantrian);

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
						if (k != nProses-1)
						{
							printf(",");
						}
					}
				}
			}
			printf("\n");
			lastInterrupt = waktu;
		}


		// mencetak baris baru dalam Gantt-chart
			// pencetakan baris akan dilakukan apabila ada proses yang selesai, ada proses yang datang, atau waktu telah mencapai kuantum waktu
		if ((indexreadyqueue == nProses) || isInArray(waktu,waktuKedatangan))
		{
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
						if (k != nProses-1)
						{
							printf(",");
						}
					}
				}
			}
			printf("\n");	
		}
		if (telahProses[0] != EMPTY)
		{
			telahProses[0]++;
		}
		waktu++;
	}
}