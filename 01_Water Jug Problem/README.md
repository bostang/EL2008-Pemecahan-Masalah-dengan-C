# Water Jug Problem / Water Pouring Puzzles

## Permasalahan
Diberikan 2 buah kendi air `A` dan `B` yang masing-masing memiliki kapasitas 3 liter dan 5 liter. Terdapat tiga buah aksi yang bisa kita lakukan terhadap masing-masing kendi:
	
	1. mengisi penuh suatu kendi
	2. mengosongkan suatu kendi
	3. memindahkan air dari satu kendi ke kendi lain sampai kendi tujuan sudah penuh atau kendi sumber sudah kosong.

Dari ketiga langkah yang bisa dilakukan tersebut, kita ingin mendapatkan air sebanyak 4 liter.

Buatlah program `interaktif` C yang mengharuskan user untuk mendapatkan air 4 liter tersebut.


## Solusi 

Jelas disini kita membutuhkan setidaknya 2 buah variabel bertipe data integer untuk menyimpan informasi banyaknya air yang ada di kendi A dan B.

```
A : integer
B : integer
```

kemudian kita membutuhkan variabel lain bertipe data integer untuk menyatakan opsi yang dipilih user

`opsi : integer`

Setidaknya terdapat 6 buah opsi agar permasalahan kita dapat terselesaikan, yaitu:

	1. Mengisi penuh kendi A
	2. Mengisi penuh kendi B
	3. Mengosongkan kendi A
	4. Mengosongkan kendi B
	5. Memindahkan air dari kendi A ke kendi B
	6. Memindahkan air dari kendi B ke kendi A

Untuk  mengosongkan kendi dapat dengan mudah kita lakukan dengan cara sebagai berikut:

```
procedure empty(x)
	if x = 'A' then
		A = 0
	else if x = 'B' then
		B = 0
```

Begitu juga untuk mengisi penuh kendi dapat dengan mudah kita lakukan dengan cara sebagai berikut:

```
procedure fill(input : character x)
	if x = 'A' then
		A <- 3
	else if x = 'B' then
		B <- 5
```

Yang sekarang menjadi tantangan adalah membuat prosedur untuk memindahkan air dari satu kendi ke kendi yang lain. Sekarang kita fokus ke prosedur pemindahan air dari kendi A (e liter) ke kendi B (5 liter). Pertama-tama kita harus pastikan bahwa kendi sumber air (dalam hal ini kendi A) tidaklah kosong serta kendi tujuan (dalam hal ini kendi B) belum penuh. Setelah sudah kita pastikan, pemindahan ini dapat terjadi dengan dua kemungkinan. yaitu:
	
	1. air dipindahkan dari A ke B sampai B penuh
	2. air dipindahkan dari A ke B sampai A kosong

Kemungkinan pertama tercapai saat kondisi air di A masih lebih banyak dari air yang dibutuhkan untuk membuat B penuh. Sedangkan kemungkinan kedua tercapai saat kondisi air di A tidak mencukupi untuk membuat B penuh. Berikut adalah algoritmanya:

```
if A !=0 and B != 5 then
	if  A > (5-B)  then
		A <- A - (5-B)
		B <- 5
	else
		B <- B + A
		A <- 0
else
	output("Aksi tidak bisa dilakukan")
```

Pemindahan air dari tangki B ke A dapat kita lakukan dengan serupa.
```
if B != 0 and A != 3 then
	if B > 3-A then
		B <- B - (3-A)
		A <- 3
	else
		A <- A + B
		B <- 0
```

Secara algoritma kita sudah selesai. Sekarang saatnya menambahkan beberapa hal lain. Kita akan menambahkan dua opsi tambahan agar program kita lebih interaktif. Pertama, kita akan tambahkan opsi untuk menampilkan semua kemungkinan opsi. Kedua, kita akan tambahkan opsi untuk keluar paksa dari program. Maka variabel integer `opsi` memiliki 2 kemungkinan nilai tambahan:

	7. tampilkan pilihan opsi 
	8. keluar

---

Berikut adalah tabel ringkasan variabel dan prosedur yang terdapat untuk solusi permasalahan ini:

### Variabel

	| Variabel | Penjelasan                                   |
	|----------|----------------------------------------------|
	| A, B     | banyaknya air yang terdapat di kendi A dan B |
	| opsi     | tindakan yang diambil                        |	
		
### Prosedur

	| Prosedur                    | Penjelasan                                                   |
	|-----------------------------|--------------------------------------------------------------|
	| fill(input : character x)   | mengisi kendi                                                |
	| move(input : x,y character) | memindahkan kendi                                            |
	| empty(input : character x)  | prosedur untuk mengosongkan kendi x                          |
	| list_opsi()                 | prosedur untuk menampilkan opsi yang bisa dilakukan pengguna |
	| opening()                   | menampilkan pesan awal                                       |


---
### credit to:

https://tableconvert.com/

https://www.markdownguide.org/cheat-sheet
