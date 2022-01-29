# Round Robin Scheduling Algorithm


## Permasalahan

Kita diperintahkan untuk membuat program yang dapat menjalankan `RRS` (Robin Scheduling Algorithm).

#### Konstanta
Pertama-tama, kita tetapkan perjanjian konstanta dalam program kita:

| **Konstanta**                | **Penjelasan**                                                   |
|------------------------------|------------------------------------------------------------------|
| `maxSize` : integer := 10      | maksimum banyaknya proses yang ada (10 dipilih secara sembarang) |
| `EMPTY` : integer := 9999      | nilai boneka yang menyatakan elemen kosong                       |
| `timeLimit` : integer := 99999 | sembarang nilai untuk mencegah infinite loop seandainya ada BUG  |

 Kita akan menetapkan batasan dari program kita sebagai berikut:
#### Input

| **Input**                                          | **Penjelasan**                              |
|----------------------------------------------------|---------------------------------------------|
| `nProses` : integer                                | banyaknya proses yang akan di-schedule      |
| `waktuKedatangan` : array[0..maxSize-1] of integer | array waktu kedatangan masing-masing proses |
| `waktuEksekusi` : array[0..maxSize-1] of integer   | array waktu eksekusi masing-masing proses   |
| `tKuantum` : integer                               | satuan kuantum waktu                        |

	
Kemudian program akan mengembalikan semacam tabel yang merepresentasikan proses mana yang sedang berlangsung serta queue dari semua proses.
	
#### Output
	1. time-process table yang menyatakan proses, waktu kedatangan, serta waktu eksekusi masing-masing proses
	2. Gantt-chart yang menampilkan antrian serta proses yang telah selesai dalam bentuk tabel

Berikut adalah contoh input-output programnya :
	misalkan kita punya 3 buah input dengan (t_kedatangan, t_eksekusi) masing-masing :
		
	1. P0(200,130)
	2. P1(350,50)
	3. P2(0,250)
		
		
maka program pada console akan tampak seperti sebagai berikut:
	input
	<GAMBAR_INPUT>
	output
	<GAMBAR_OUTPUT>


## Solusi

Kita akan memanfaatkan struktur data berupa queue yang pada C dapat di-implementasikan dengan array dengan ukuran maksimum `maxSize` yang nilainya di-inisiasi dengan `EMPTY`.

Awalnya saya terpikirkan untuk membuat dua buah variabel `first` dan `last` yang menyatakan indeks elemen pertama dan terakhirnya. Tetapi saya mengalami kendala dalam mekanisme penghapusan elemen dari array. Akhirnya saya mencoba kembali dengan implementasi menggunakan array biasa yang dilengkapi beberapa fungsi/prosedur pembantu yang meliputi:

| **Prosedur/Fungsi**       | **Penjelasan**                                          		|
|---------------------------|-------------------------------------------------------------------|
| function `minArray()`       | mencari nilai minimum dari suatu array                  		|
| function `countElem()`      | menghitung banyaknya tak kosong elemen dari suatu array 		|
| procedure `swapElement()`   | prosedur untuk menukar 2 elemen pada sebuah array       		|
| function `isInArray()`      | engembalikan true bila elemen dicari terdapat di array  		|
| procedure `removeElement()` | menghapus elemen dari suatu array                       		|
| procedure `geserSiklik()`   | menggeser elemen pada array seolah-olah array berbentuk lingkaran |

berikut adalah implementasi algoritma dari ke-enam fungsi/prosedur di atas:

1. function minArray()
```
function minArray(int arri[0..maxSize-1]) -> integer
	KAMUS LOKAL
		{ Variabel }
			min : integer { nilai minimum sementara }
	ALGORITMA
	int min = arri[0];

	for (int k = 1 to maxSize-1) do
		if (arri[k] != EMPTY) then
			if (arri[k] < min) then
				min <- arri[k]
	-> min
```

2. function countElem()
```
function countElem(arri : arry [0..maxSize-1] of integer) -> integer
	KAMUS LOKAL
		count : integer { pencacah }
	ALGORITMA
	count <- 0
	for (k = 0 to k = maxSize - 1) do
		if (arri[k] != EMPTY) then
			count <- count + 1
	-> count
```
3. procedure swapElement()
```
procedure swapElement(array[0..maxSize-1] of integer; integer: a, b)
	KAMUS LOKAL
		{ Variabel }
			temp : integer
	ALGORITMA
	temp <- arri[a]
	arri[a] <- arri[b]
	arri[b] <- temp
```

4. function isInArray()
```
function isInArray(integer i, array[0..n-1] of integer arri) -> boolean
	KAMUS LOKAL
	ALGORITMA
	for (k = 0 to k = n-1 ) do
		if (arri[k] = i) then
			-> True
	-> False
```
5. procedure removeElement()
```
procedure removeElement(input arri : array[0..maxSize-1] of integer, indexRemove)
	KAMUS LOKAL
	ALGORITMA
		{ langkah 1 : mengapungkan elemen ke ujung array }
	for (k = indexRemove to k = maxSize-1) do
		swapElement(arri,k,k+1)
		{ langkah 2 : menghapus elemen yang paling ujung }
	arri[maxSize-1] <- EMPTY
```
6. procedure geserSiklik()
```
procedure geserSiklik(input arri: array[0..maxSize-1] of integer, x : integer ) 
	KAMUS LOKAL
	ALGORITMA
		{ langkah 1 : menggeser secara siklik }
	for (int k = 0 to k = maxSize-2) do
		swapElement(arri,k,k+1)
		
		{ langkah 2 : pepet elemen tak kosong ke kiri }
	swapElement(arri,x-1,maxSize-1)
```
---
Karena output kita adalah tabel time-process dan juga Gantt-chart, kita akan implementasikannya masing-masing dalam prosedur `cetakTimeProcessTable()` dan `ganttChart()`. 

Untuk mengimplementasikan `cetakTimeProcessTable()` bisa kita lakukan sebagai berikut:
```
procedure cetakTimeProcessTable(input waktuKedatangan, waktuEksekusi : array [0..n-1] of integer)
	KAMUS LOKAL
	ALGORITMA
	output('Proses \t Waktu Kedatangan \t Waktu Eksekusi\n')
	for (k = 0 to k = n-1) do
		output('P{k} \t waktuKedatangan[k] \t waktuEksekusi[k]')
```

Untuk mengimplementasikan `ganttChart()`, kita juga butuh beberapa prosedur pembantu seperti prosedur `cetakAntrian()` untuk mencetak antrian pada gantt-chart dan juga prosedur `cetakBaris()` untuk mencetak baris dalam gantt-chart pada suatu waktu.

Berikut adalah implementasi masing-masing prosedur pembantu:
1. cetakbaris()
```
procedure cetakBaris(waktu : integer, antrian : array [0..maxSize-1] of integer, readyqueue : array [0..maxSize-1] of integer)
	KAMUS LOKAL
	ALGORITMA
	output(waktu \t)
	cetakAntrian(antrian)
	output(\t)
	if (readyqueue[0] != EMPTY) then
		for (k = 0 to k = nProses-1)
			if (readyqueue[k] != EMPTY) then
				output("P",readyqueue[k])
			if (readyqueue[k+1] != EMPTY) then
				output(", ")
```

2. cetakAntrian()
```
procedure cetakAntrian(input antrian: array[0..n-1] of integer)
	KAMUS LOKAL
	ALGORITMA 
		{ telah dipastikan bahwa setiap elemen array antrian berbeda-beda dan merujuk kepada proses }
	for (k = 0 to k = nProses-1) do
		if (antrian[k] != EMPTY) then
			output(antrian[k])
		if (antrian[k+1] != EMPTY ) then
			output(" ") { mencetak spasi bila belum elemen terujung }
```

Sekarang kita akan membahas bagian tersulit dari program ini, yaitu prosedur pencetakan Gantt-chart sekaligus pengimplementasian algoritma RRS.
`procedure ganttChart(input waktuEksekusi, waktuKedatangan: array [0..n-1] of integer)`

Berikut adalah tabel ringkasan dari variabel lokal yang terdapat pada prosedur `ganttChart()` :

| **Variabel Lokal**                                   | **Penjelasan**                                                                        |
|------------------------------------------------------|---------------------------------------------------------------------------------------|
| `kondisiGeser` : boolean                             | flag agar antrian tidak digeser ketika baru saja ada elemen yang dihapus              |
| `antrian` : array [0..n-1] of integer                | array atrian proses                                                                   |
| `telahProses` : array[0..n-1] of integer             | lama waktu yang telah berlangsung untuk masing-masing proses                          |
| `waktu` : integer                                    |                                                                                       |
| `lastInterrupt` : integer                            | waktu terakhir kali mencapai kuantum atau ada proses yang telah selesai               |
| `readyqueue` : array [0..n-1] of integer             | array yang menyatakan proses yang telah selesai dijalankan                            |
| `indexreadyqueue` : integer                          | index pada array readyqueue yang akan digunakan juga ketika pencetakan elemen antrian |
| `indexantrian` : integer                             | jumlah elemen pada array antrian                                                      |
| `tempwaktuEksekusi` : array[0..maxSize-1] of integer | array waktu eksekusi masing-masing proses (yang ikut digeser bersama dengan antrian)  |

---
#### penjelasan prosedur ganttChart()

Kita akan terus mencetak baris pada gantt-chart sampai semua proses telah selsai dijalankan
```
while(indexreadyqueue < nProses and waktu < timeLimit) do
	...
```
> Kapan kita harus mencetak baris baru?

1. Kalau `waktu` sudah mencapai *time quantum*, maka kita akan geser siklik antrian serta mencetak baris baru pada *Gantt-Chart*.
2. Jika waktu belum mencapai *time quantum* tetapi sudah ada proses yang  selesai, maka kita akan hapus dia dari `antrian` serta cetak baris baru pula. 
3. Bila ada proses yang masuk ke `antrian`.

Berikut adalah implementasi dari prosedur `ganttChart()`
```
procedure ganttChart(input waktuEksekusi, waktuKedatangan: array [0..n-1] of integer)
	ALGORITMA
	waktu <- 0
	lastInterrupt <- minArray(waktuKedatangan)
	indexreadyqueue <- 0
	indexantrian <- 0
	kondisiGeser <- true
	for (k = 0 to k = n-1) do
		readyqueue[k] <- EMPTY
		telahProses[k] <- EMPTY
		antrian[k] <- EMPTY

		{ mencetak header gantt-chart }
	output('Waktu \t Antrian \t selesai')

		{ mencetak baris gantt-chart sekaligus menjalankan algoritma RRS }
	while(indexreadyqueue < nProses and waktu < timeLimit) do { terus lakukan sampai semua proses telah dijalankan }

		{ mengurusi proses yang telah SELESAI dijalankan }
			{ proses yang telah selesai harus dimasukkan ke readyqueue dan dihapus dari antrian }
		if (telahProses[0] != EMPTY and telahProses[0] >= (tempwaktuEksekusi[0])) then
			kondisiGeser <- false
			readyqueue[indexreadyqueue] = antrian[0]
			removeElement(telahProses,0)
			removeElement(antrian,0)
			indexreadyqueue <- indexreadyqueue + 1
			cetakBaris(waktu, antrian, readyqueue)
			
			lastInterrupt <- waktu

		{ ketika sudah mencapai kuantum waktu atau suatu proses telah selesai dijalankan, maka lastInterrupt akan diupdate }

		if (waktu - lastInterrupt >= tKuantum ) then
			
			if (kondisiGeser) then
				geserSiklik(antrian, countElem(antrian))
				geserSiklik(telahProses, countElem(telahProses))
				geserSiklik(tempwaktuEksekusi,countElem(tempwaktuEksekusi))

			if (kondisiGeser and !(isInArray(waktu, waktuKedatangan))) then { tidak dilakukan ketika ada proses yang datang pada waktu tersebut }
			
				cetakBaris(waktu, antrian, readyqueue)
			
			kondisiGeser <- true
			lastInterrupt <- waktu

		{ Ada proses yang masuk ke queue }
			{ ketika ada proses yang masuk ke queue, last harus bergeser }
		for (k = 0 to k = nProses-1) do
			if (waktu = waktuKedatangan[k]) then
				antrian[indexantrian] = k
				telahProses[indexantrian] = 0
				indexantrian <- indexantrian + 1
	
		for (k = 0 to k = nProses-1) do
			if (antrian[k] != EMPTY) then
				tempwaktuEksekusi[k] <- waktuEksekusi[antrian[k]]

		{ mencetak baris baru dalam gantt-chart saat ada proses yang datang }
		if isInArray(waktu, waktuKedatangan) then
			cetakBaris(waktu, antrian, readyqueue)

		if (telahProses[0] != EMPTY) then
			telahProses[0] <- telahProses[0] + 1

		waktu <- waktu + 1
```

---
### credit to:

https://tableconvert.com/

https://www.markdownguide.org/cheat-sheet
