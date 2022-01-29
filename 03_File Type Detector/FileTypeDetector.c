// Nama    : Bostang Palaguna
// NIM 	   : 13220055
// Tanggal : Sabtu, 29 Januari 2022 ; Minggu, 30 Januari 2022

// Program FileTypeDetector
	// DESKRIPSI PROGRAM
// KAMUS
	// Konstanta
		// sign_PDF : array[0..4] of character := {0x25,0x50,0x44,0x46,0x2D}
		// sign_PNG : array[0..7] of character := {0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A}
		// sign_JPG : array[0..2] of character := {0xFF,0xD8,0xFF}
	// Variabel
		// myfile : SEQFILE of 
			// (*) CC : character
			// (1) EOF
		// fileIn : string 
			// nama file yang ingin diketahui jenisnya
		// count : integer
			// jumlah karakter yang telah dibaca dari file
		// arrSimpan : array [0..7] of character
			// array yang menyimpan 8 karakter pertama yang kita baca dari file
		// flag : boolean
			// variabel yang menyatakan karakter cocok dengan file signature
		// isPDF, isPNG, isJPG : boolean
			// flag yang menyatakan bahwa file bertipe PDF, PNG, atau JPG
		// CC : character
			// karakter yang dibaca dari file
		// retval : integer
			// penyimpanan sementara karakter yang dibaca
// ALGORITMA UTAMA
#include <stdio.h>
#include <stdbool.h>

// deklarasi konstanta
const char sign_PDF[5] = {0x25,0x50,0x44,0x46,0x2D};
const char sign_PNG[8] = {0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A};
const char sign_JPG[3] = {0xFF,0xD8,0xFF};

// deklarasi variabel dan prosedur/fungsi
char fileIN[20];
int count;
char arrSimpan[8];
bool flag;
bool isPNG, isPDF, isJPG;
char CC;
int retval;

FILE *myfile;

int main(int argc, char const *argv[])
{
	// note :
		// argc -> bayaknya argument ketika memanggil program
		// argv -> array berisi argument apa saja yang kita berikan saat memanggil program
	if (argc > 1) // kalau user memberikan nama file melalui command-line argument
	{
		int k = 0;
		while (argv[1][k] != '\0')
		{
			fileIN[k] = argv[1][k];
			k++;
		}
	}
	else
	{
		scanf("%s",&fileIN);
	}
	
	// melakukan pembacaan isi file

	myfile = fopen(fileIN,"rb"); // baca sebagai file biner
	retval = fscanf(myfile,"%c",&CC); // membaca karakter pertama pada file

	if (CC == '\000')
	{
		printf("File Kosong\n");
	}
	else
	{
		// menyimpan 8 karakter pertama dari file yang kita baca
		count = 0;
		while (count < 8 && retval != EOF)
		{
			arrSimpan[count] = CC;
			retval = fscanf(myfile,"%c",&CC); // membaca karakter selanjutnya
			count++;
		}

		// menentukan jenis file dari karakter awal yang sudah kita baca
		count = 0;
		flag = true; isPNG = true; isPDF = true; isJPG = true;

		while(count < 8 && flag)
		{
			if (!isPNG && !isJPG && !isPDF)
			{
				flag = false;
			}

			if(count <= 2 && isJPG)
			{
				if (arrSimpan[count] != sign_JPG[count])
				{
					isJPG = false;	
				}
				
			}

			if(count <= 4 && isPDF)
			{
				if (arrSimpan[count] != sign_PDF[count])
				{
					isPDF = false;
				}
			}

			if(isPNG)
			{
				if (arrSimpan[count] != sign_PNG[count])
				{
					isPNG = false;
				}
			}

			count++;
		}

		// mencetak tipe file berdasarkan flag isPDF, isPNG, isJPG
		if (isJPG)
		{
			printf("File bertipe JPG.\n");
		}
		else if (isPNG)
		{
			printf("File bertipe PNG.\n");
		}
		else if (isPDF)
		{
			printf("File bertipe PDF.\n");
		}
		else
		{
			printf("File tidak bertipe JPG, PNG, maupun PDF.\n");
		}
	}

	fclose(myfile);

	return 0;
}