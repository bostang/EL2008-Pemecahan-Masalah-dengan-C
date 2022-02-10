# File Type Detector

## Instruksi
Buatlah program yang menerima sebuah file, kemudian menampilkan apakah file sebuah pdf, jpg atau sebuah tidak terdefinisi

## Solusi

Misalkan kita memiliki beberapa file:
  - `kitten.png` yang merupakan file .png
  - `puppy.jfif` yang merupakan file .jpeg
  - `sampel_PDF.pdf` yang merupakan file .pdf
  - `sampel_MP3.mp3` yang merupakan file .mp3 (selain .png, .jpeg, dan .pdf)
  
![Sampel File](https://github.com/bostang/ProblemSolving_C/blob/main/03_File%20Type%20Detector/dll_README/sampelFile.gif )

---
Sekarang kita ingin membuat program C yang bisa mendeteksi jenis file dari file input yang kita berikan:

![Demo](https://github.com/bostang/ProblemSolving_C/blob/main/03_File%20Type%20Detector/dll_README/demo.gif)

---

> sekarang bagaimana kita bisa membedakan antar file?

Kalau kita lihat setiap file secara mentah melalui *text-editor*, kita akan menyadari bahwa setiap file memiliki `angka ajaib` yang berbeda-beda di bagian awal file yang disebut dengan `file signature`. Berdasarkan [Wikipedia](https://en.wikipedia.org/wiki/List_of_file_signatures), kita bisa mengetahui file signature untuk file .png, .pdf, dan .jpeg adalah sebagai berikut:

![File Signature PNG](https://github.com/bostang/ProblemSolving_C/blob/main/03_File%20Type%20Detector/dll_README/png_fileSignature.png)
![File Signature JPG](https://github.com/bostang/ProblemSolving_C/blob/main/03_File%20Type%20Detector/dll_README/jpg_fileSignature.png)
![File Signature PDF](https://github.com/bostang/ProblemSolving_C/blob/main/03_File%20Type%20Detector/dll_README/pdf_fileSignature.png)

Kita akan simpan byte-byte tersebut dalam konstanta array of character:
```
sign_PDF : array[0..4] of character := {0x25,0x50,0x44,0x46,0x2D}
sign_PNG : array[0..7] of character := {0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A}
sign_JPG : array[0..2] of character := {0xFF,0xD8,0xFF}
```

Jadi sekarang yang perlu kita lakukan hanyalah membaca beberapa karakter pertama dari file input lalu membandingkannya apakah sama dengan salah satu dari ketiga konstanta di atas. Untuk mengimplementasikan algoritmanya, kita butuh beberapa variabel sebagai berikut:

| **Variabel**                                        | **Deskripsi**                                                    |
|-----------------------------------------------------|------------------------------------------------------------------|
| `myfile` : SEQFILE of:  (\*) CC : character ; (1) EOF | pointer ke file input                                            |
| `fileIn` : string                                     | nama file yang ingin diketahui jenisnya                          |
| `count` : integer                                     | jumlah karakter yang telah dibaca dari file                      |
| `arrSimpan` : array [0..7] of character               | array yang menyimpan 8 karakter pertama yang kita baca dari file |
| `flag` : boolean                                      | variabel yang menyatakan karakter cocok dengan file signature    |
| `isPDF`, `isPNG`, `isJPG`: boolean                       | flag yang menyatakan bahwa file bertipe PDF, PNG, atau JPG       |
| `CC` : character                                      | karakter yang dibaca dari file                                   |


dan berikut adalah algoritmanya:
```
Program FileTypeDetector
	ALGORITMA UTAMA
input(fileIN)
assign(myfile,fileIN)
open(myfile, CC) { mengakses byte pertama pada file }
if (CC = EOF) then
	output("File Kosong")
else
		{ menyimpan 8 karakter pertama dari file yang kita baca }
	count <- 0
	while (count < 8 && CC != EOF) do
		arrSimpan[count] <- read(myfile,CC) { membaca elemen berikutnya }
		count <- count + 1
	
		{ menentukan jenis file dari karakter yang sudah kita baca }

	count <- 0
	flag <- true
	isPDF <- true
	isPNG <- true
	isJPG <- true

	while (count < 8 and flag) do
		if (not isPNG and not isPDF and not isJPG) then
		{ ketika file gagal di-identifikasi sebagai PNG, PDF, maupun JPG, langsung keluar while loop }
			flag <- false

		if (count <= 2 && isJPG) then { panjang signature JPG adalah 3 karakter }
			if (arrSimpan[count] != sign_JPG[count]) then
				isJPG <- false
		
		if (count <= 4 && isPDF) then { panjang signatire PDF adalah 5 karater } 
			if (arrSimpan[count] != sign_PDF[count]) then
				isPDF <- false

		if (isPNG) then { panjang signature PNG adalah 8 karakter = jumlah iterasi max while loop }
			if (arrSimpan[count] != sign_PNG[count]) then
				output("File bukan PDF, JPG, maupun PNG")
				isPNG <- false

		count <- count + 1

	{ mencetak tipe file berdasarkan flag isPDF/isPNG/isJPG }
	if (isJPG) then
		output('File bertipe JPG.')
	else if (isPNG) then
		output('File bertipe PNG.')
	else if (isPDF) then
		output('File bertipe PDF.')
	else
		output('File bukan JPG, PNG, maupun PDF.')

close(myfile)
```

---
### credit to:

https://tableconvert.com/

https://www.markdownguide.org/cheat-sheet

https://convertio.co/

https://www.incrediblesnaps.com/45-adorable-cute-puppies

https://www.pngmart.com/image/41841
