# Algoritma Djikstra 

## Instruksi

Berdasarkan *sourcecode* pada [link berikut](https://github.com/ReynaldoAverill/Tugas7PMC),
modifikasi sehingga program bisa menghitung jarak minimum antar kota dari graf berikut:

![gambar graf](https://github.com/bostang/ProblemSolving_C/blob/main/05_Jarak%20antar%20Kota/dll_README/graf_jarak.png)

Program menerima 4 input, yaitu:
1. **nama file daftar kota**. File ini berisi daftar kota pada graph di atas.
2. **nama file jarak antar kota**. File ini berisi jarak setiap kota yang disusun dalam bentuk matriks segitiga bawah kiri. -1 melambangkan vertex yang tidak terhubung.
3. **titik awal**.
4. **titik tujuan**.
5. **validasi pencarian**.

Program mengeluarkan output berupa daftar nama kota yang harus dilalui serta jarak antar kota

## Solusi

Pertama-tama saya mau berkomentar bahwa [sourcecode](https://github.com/ReynaldoAverill/Tugas7PMC/blob/main/Tugas7kel5.c) masih bisa dibuat lebih bersih lagi. **bagiamana??**

1. Terdapat sebuah fungsi yang didefinisikan tetapi tidak pernah dipanggil, yaitu `printgraph()`
2. pointer ke file `fp_jarak_kota` dan `fp_kota` tidak ditutup setelah diakses
3. terdapat bagian kode yang di-comment untuk di-non-aktifkan sementara $\rightarrow$ seharusnya dihapus bila sudah merupakan *sourcecode* final
4. Penggunaan tanda kurung `{` yang kurang simetris dengan tutup kurung `}`. Misalkan:
```
while (kondisi){
    if (kondisi){
         for (kondisi){
            aksi
        }    
    }
}
```
saya lebih *prefer*:
```
while (kondisi)
{
    if (kondisi)
    {
        for (kondisi)
        {
            aksi
        }    
    }
}
```
5. **line 78 dan 79** pada *original sourcecode* akan tetapi dicetak meskipun file kosong. Seharusnya dilakukan pengecekan apakah file kosong atau tidak
6. antar baris kode pada fungsi main begitu mepet. seharusnya diberikan beberapa spasi untuk memisahkan proses apa yang sedang dilakukan
7. Tidak ada dokumentasi tentang variabel-variabel apa saja yang ada 

---
### Ok... sekarang saatnya bahas kodenya
Agar mampu memodifikasi kode, pertama-tama kita harus memahami algoritma pada program tersebut terlebih dahulu. Saya akan coba jelaskan bagian per bagian dari kode yang pesan interaktif dan nama variabelnya telah saya modifikasi.

Pertama-tama, kita harus mampu membaca isi file kemudian memindahkan isinya ke dalam variabel entah array atau matriks. Pembacaan file dapat menggunakan fungsi `fopen()` yang nilainya kita oper ke sebuah pointer to file.

Sebelum pembacaan isi file daftar kota, kita periksa dulu apakah file kosong atau tidak. Seandainya kosong, proses langsung berhenti.
```
if (fp_kota == NULL)
{
    // PROGRAM BERHENTI
}
```

Untuk pembacaan isi file daftar kota, kita akan baca baris per baris sampai akhir file `EOF`:
```
while (fgets(baris, max_len, fp_kota))
{
    // simpan ke array / matriks
}
```

Baris file daftar kota memuat satu kota di setiap baris. Maka kita akan manfaatkan fungsi `strtok()` dengan delimiter `\n` untuk memecah string baris bacaan menjadi token-token tersebut.
```
    token = strtok(baris,"\n");
    strcpy(nama_kota[n_kota],token);
    n_kota += 1;
```

Kemudian setelah file selesai dibaca, jangan lupa untuk menutup kembali menggunakan fungsi `fclose()`.

Untuk file jarak antar kota, setiap barisnya terdiri dari beberapa token yang dipisahkan oleh `spasi`. Maka `strtok()` akan digunakan secara berulang untuk membaca baris lalu menyalin isinya ke adjacency matrix `graph_kota`. 
```
 while (fgets(baris, max_len, fp_jarak_kota))
    {
        k=0;
        token = strtok(baris," "); // membaca kata pertama sampai bertemu spasi (kata dipisahkan oleh spasi)
        while (token != NULL)
        {
            graph_kota[j][k] = atoi(token); // mengonversi pembacaan ke integer dan menyimpannya pada adjacency matrix
            graph_kota[k][j] = atoi(token); // matriks adjacency sama dengan transposenya
                                                // karena  jarak dari a ke b sama dengan jarak dari b ke a
            if(atoi(token)==-1) // jika tidak terdapat hubungan antara dua kota 
            {
                graph_kota[j][k] = int_max;
                graph_kota[k][j] = int_max;
            }
            k+=1;
            token = strtok(NULL," "); // membaca kata berikutnya
        }
        j+=1;
    }
```
sebagai catatan, `strtok(NULL," ")` digunakan untuk mendapatkan token selanjutnya dari string yang sama. `NULL` digunakan sebagai argumen pertama karena `strtok()` mempertahankan *static pointer* ke string yang di-*pass* sebelumnya.  ([sumber](https://stackoverflow.com/questions/3889992/how-does-strtok-split-the-string-into-tokens-in-c#:~:text=strtok%20replaces%20the%20characters%20in%20the%20second%20argument,gets%20the%20pointer%20from%20the%20static%20variable%20.))


Setelah informasi kota dan jarak antar kota sudah berhasil kita simpan dalam array dan adjacency matrix, sisanya adalah implementasi algoritma Djikstra yang umum tersedia di internet.

---

Berikut saya akan jabarkan cara saya menyalin data jarak dari graf ke dalam bentuk adjacency matrix: 

1. Dari graf di awal, catat nama-nama kota yang ada pada excel. Setelah itu urutkan dengan fitur **sort** pada excel. 
![langkah_1](https://github.com/bostang/ProblemSolving_C/blob/main/05_Jarak%20antar%20Kota/dll_README/01_mengurutkan.png)

2. lalu salin secara transpos agar seolah-olah terbentuk tabel
![langkah_2](https://github.com/bostang/ProblemSolving_C/blob/main/05_Jarak%20antar%20Kota/dll_README/02_pasteTranspose.png)

3. karena kebanyakan kota tidak saling terhubung, maka lebih baik kita isi semua kolom dengan -1 terlebih dahulu.
![langkah_3](https://github.com/bostang/ProblemSolving_C/blob/main/05_Jarak%20antar%20Kota/dll_README/03_minus_satu_semua.png)

4. kemudian ubah diagonal utama menjadi nol semua.
![langkah_4](https://github.com/bostang/ProblemSolving_C/blob/main/05_Jarak%20antar%20Kota/dll_README/04_nol_diagonal.png)

5. hapus separuh diagonal bagian atas
![langkah_5](https://github.com/bostang/ProblemSolving_C/blob/main/05_Jarak%20antar%20Kota/dll_README/05_sorot_diagonal_atas.png)

6. setelah itu mulai lakukan pengisian dengan melihat kota apa aja yang adjacent dengan satu kota. Misalkan kita mau mengisi dari kota bandung
![langkah_6](https://github.com/bostang/ProblemSolving_C/blob/main/05_Jarak%20antar%20Kota/dll_README/06_contoh_pengisian_bandung.png)

![graph_bandung](https://github.com/bostang/ProblemSolving_C/blob/main/05_Jarak%20antar%20Kota/dll_README/07_pengisian_bandung.png)

7. lalu lakukan untuk semua kota lain per kolom ke arah kanan. maka hasilnya seperti ini
![adjacency_matrix_lengkap](https://github.com/bostang/ProblemSolving_C/blob/main/05_Jarak%20antar%20Kota/dll_README/08_verifikasi_jumlah_verteks.png)

8. setelah selesai mengisi, kita bisa verifikasi dengan jumlah *edge* pada graph sebanyak 31.
9. salin hasil pengukuran ke notepad / text editor
![langkah_9](https://github.com/bostang/ProblemSolving_C/blob/main/05_Jarak%20antar%20Kota/dll_README/09_salin_ke_notepad.png)

10. replace setiap tab dengan spasi lalu hapus following tab di akhir setiap baris. Langkah ini sangat penting karena cara kita menggunakan strtok()
![langkah_10](https://github.com/bostang/ProblemSolving_C/blob/main/05_Jarak%20antar%20Kota/dll_README/10_bersihkan_dengan_VSCode.png)

11. Kita sudah selesai dengan pengolahan data kita. Selanjutnya, kita hanya perlu modifikasi `pesan-pesan interaktif` pada program dan mengganti konteks dari jarak antar tanaman menjadi jarak antar kota.

12. Misalkan daftar kota ada dalam file bernama `listkota.txt` dan data jarak antar kota ke dalam `jarakantarkota.txt`. Maka berikut adalah demonstrasi program kita:

![demo_program](https://github.com/bostang/ProblemSolving_C/blob/main/05_Jarak%20antar%20Kota/dll_README/demo_program.gif)
