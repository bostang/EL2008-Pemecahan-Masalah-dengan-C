# Round Robin Scheduling Algorithm


## Permasalahan

Kita diperintahkan untuk membuat program yang dapat menjalankan `RRS` (Robin Scheduling Algorithm). Kita akan menetapkan batasan dari program kita yaitu:
input `nProses : integer` yang menyatakan banyaknya proses yang akan di-schedule,`waktuKedatangan : array[1..n] of integer`, serta `waktuEksekusi : array[1..n] of integer`. Kemudian program akan mengembalikan semacam tabel yang merepresentasikan proses mana yang sedang berlangsung serta queue dari semua proses.

## Solusi

Kita akan memanfaatkan struktur data berupa queue yang pada C dapat di-implementasikan dengan array serta dua buah variabel `first` dan `last` yang menyatakan indeks elemen pertama dan terakhirnya. Perubahan `first` dan `last` berkorespondensi dengan proses yang dijalankan sekarang telah berubah.

Terdapat 2 kondisi agar terjadi perubahan proses:
	1. waktu suatu proses berjalan sudah mencapai satu time quantum
	2. suatu proses telah selesai dijalankan

Sedangkan terdapat 3 kondisi agar baris baru pada gantt chart dicetak:
	1. waktu suatu proses berjalan sudah mencapai satu time quantum
	2. suatu proses telah selesai dijalankan
	3. terdapat proses baru yang baru masuk ke queue


## Catatan

Terhitung Kamis, 27 Januari 2022 jam 5 17 pagi, saya mohon maaf karena program ini belum selesai sepenuhnya dan masih mengandung banyak bug karena keterbatasan waktu dan kemampuan yang saya punya sekarang untuk menyelesaikan program ini. Jika saya sudah menemukan bugnya, saya akan segera perbaiki programnya. 
