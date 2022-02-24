// Program jarakAntarKota
    // memodifikasi kode jarak antar kota untuk mencari jarak antar kota
// KAMUS
    // Konstanta
        // node_max : integer := 50 { jumlah node maksimum }
        // max_len : integer := 255 { ukuran array maksimum }
        // int_max : integer := __INT_MAX__ { menyatakan tak hingga }
    // Variabel
        // nama_file_daftar_kota : string { nama file .txt yang mengandung list daftar kota }
        // fp_kota : pointer to file { pointer ke file yang mengandung list daftar kota }
        // baris : string { baris yang dibaca dari file yang sedang dibuka }
        // token : string { token/potongan string dari baris }
        // n_kota : integer { jumlah kota pada graf }
        // nama_kota : array[0..node_max-1] of string { array berisi daftar nama kota }
        // graph_kota : matrix of integer { adjacency matrix yang menunjukkan jarak antar kota }
        // j, k : integer { variabel untuk while loop }
        // progress : character { pilihan pengguna apakah mau melakukan pencarian lagi atau tidak }
            // ---  variabel untuk implementasi algoritma djikstra ---
        // idx_awal, idx_tujuan : integer
        // jarak_final : array[0..n_kota-1] of integer
        // is_final : boolean
        // list_dilalui : array [0..n_kota-1] of integer
    // Fungsi / Prosedur
        // function idx_process(int n, int jarak_final[n], bool is_final[n]) -> integer
            // Fungsi yang digunakan untuk mencari indeks yang akan diproses pada algoritma dijkstra
// ALGORITMA UTAMA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define node_max 50
#define max_len 255
#define int_max __INT_MAX__

int idx_process(int n, int jarak_final[n], bool is_final[n])
{
    // KAMUS LOKAL
        // Variabel
            // is_found : boolean { }
            // idx_min : integer
            // val_minimum : integer
    // ALGORITMA
    bool is_found=false;
    int idx_min, val_minimum;
    for(int i=0;i<n;i++)
    {
        //Inisiasi nilai minimum awal
        if(!is_final[i]&&!is_found)
        {
            idx_min=i, val_minimum=jarak_final[i];
            is_found=true;
        }
        else if(is_found && !is_final[i] && jarak_final[i]<val_minimum)
        {
            idx_min=i, val_minimum=jarak_final[i];
        }
    }
    if(is_found)
    {
        return idx_min;
    }
    else
    {
        //Jarak minimum ke seluruh vertex telah ditemukan
        return int_max;
    }
}

int main ()
{
    char  nama_file_daftar_kota[max_len]; 
    // Input file nama kota
    printf("Masukkan nama file database nama kota\n>>> ");
    scanf("%s",& nama_file_daftar_kota);
    FILE* fp_kota = fopen( nama_file_daftar_kota,"r");

    // pengecekan apakah file kosong atau tidak
    if (fp_kota == NULL)
    {
        printf("File kosong!\n");
        return 1; // segera terminasi bila file kosong
    }

    // Baca isi file kota
    char baris[max_len];
    char* token;
    int n_kota=0;
    char nama_kota[node_max][max_len];
    while (fgets(baris, max_len, fp_kota))
    {
        token = strtok(baris,"\n");
        strcpy(nama_kota[n_kota],token);
        n_kota += 1;
    }

    // menutup file database setelah diakses
    fclose(fp_kota);

    printf("Pembacaan daftar kota berhasil.\n");
    printf("Terdapat %d kota pada graf\n",n_kota);
    
    // Input graph (berisi jarak masing-masing kota). -1 atau 2147483647=INT_MAX menyatakan tak hingga.
    printf("Silahkan masukkan nama file yang berisi jarak masing-masing kota: ");
    char namafile_graph[max_len];
    scanf("%s",&namafile_graph);

    // File eksternal berbentuk matriks segitiga bawah
    int graph_kota[n_kota][n_kota]; 
    int j=0,k;

    FILE* fp_jarak_kota = fopen(namafile_graph,"r");

    if (fp_jarak_kota == NULL)
    {
        printf("File Kosong!\n");
        return 1;
    }

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
    printf("Pembacaan jarak antar kota berhasil dilakukan.\n\n");
    char progress='y';
    while(progress=='y')
    {
        // Pembacaan vertex awal dan akhir
        int idx_awal, idx_tujuan;
        printf("\nBerikut adalah daftar kota pada graf:\n");
        for(int i=1;i<=n_kota;i++)
        {
            printf("%d. %s\n",i,nama_kota[i-1]);
        }
        printf("\nPilih salah satu kota sebagai posisi awal (Cukup ketik angka saja):\n>>> ");
        scanf(" %d",&idx_awal);
        idx_awal-=1;
        printf("Pilih salah satu kota sebagai tujuan (Cukup ketik angka saja):\n>>> ");
        scanf(" %d",&idx_tujuan);
        idx_tujuan-=1;
        int jarak_final[n_kota]; //Jarak akhir ke masing2 pohon, akan di update terus sesuai jarak yang ditemukan
        bool is_final[n_kota]; //Memberikan keterangan apakah jarak sudah minimum
        int list_dilalui[n_kota][n_kota+1]; //Indeks yang dilalui hingga mencapai tujuan
        int idx_dilalui[n_kota]; //Mencatat jumlah vertex yang dilalui pada list_dilalui
        //Algoritma Dijsktra  
        for(int i=0;i<n_kota;i++){
            //Set jarak menjadi tak hingga pada seluruh vertex selain vertex awal dan
            if(i==idx_awal)
            {
                jarak_final[i]=0;
                is_final[i]=false;
            }
            else
            {
                jarak_final[i]=int_max;
                is_final[i]=false;
            }
            //Set list dilalui menjadi no vertex (dilambangkan dengan int_max)
            for(int j=0;j<=n_kota;j++)
            {
                list_dilalui[i][j]=int_max;
            }
            idx_dilalui[i]=0;
        }
        //Inisiasi jarak awal pada vertex awal
        jarak_final[idx_awal]=0;
        list_dilalui[idx_awal][0]=idx_awal;
        idx_dilalui[idx_awal]+=1;
        int idx_now=idx_awal;
        //Menentukan index yang diproses
        while(idx_now!=int_max)
        {
            is_final[idx_now]=true;
            //printf("idx process = %d\n",idx_now);
            for(int i = 0;i<n_kota;i++)
            {
                //Update nilai saat jarak lebih pendek 
                if(!is_final[i] && (graph_kota[idx_now][i]!=int_max) && 
                (jarak_final[idx_now]+graph_kota[idx_now][i]<jarak_final[i]))
                {
                    jarak_final[i] = jarak_final[idx_now]+graph_kota[idx_now][i];
                    idx_dilalui[i]=idx_dilalui[idx_now]+1;
                    for(int j=0;j<idx_dilalui[i];j++)
                    {
                        if(j==idx_dilalui[i]-1)
                        {
                            list_dilalui[i][j]=i;
                        }
                        else
                        {
                            list_dilalui[i][j]=list_dilalui[idx_now][j];
                        }
                    }
                }
            }
            idx_now = idx_process(n_kota,jarak_final,is_final);
        }
        printf("\nkota yang harus dilalui untuk mencapai %s dengan posisi awal %s adalah: \n",nama_kota[idx_tujuan],nama_kota[idx_awal]);
        for(int i=0;i<idx_dilalui[idx_tujuan];i++)
        {
            if(list_dilalui[idx_tujuan][i]!=int_max)
            {
                printf("%d. %s\n",i+1,nama_kota[list_dilalui[idx_tujuan][i]]);
            }
        }
        printf("\nJarak antara kedua kota tersebut adalah %d meter\n\n",jarak_final[idx_tujuan]);
        
        printf("Apakah ingin mencari jarak antar kota lagi? [y/n]: ");
        scanf(" %c",&progress);
    }
}
