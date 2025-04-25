# Tugas 4 - Struktur Data dan Algoritma

**Nama Mahasiswa:** Ikram Al Ghiffari  
**NPM:** 2308107010071
## Penjelasan Tugas

Tugas ini mengimplementasikan dan menganalisis performa 6 algoritma sorting:
1. Bubble Sort
2. Selection Sort
3. Insertion Sort
4. Merge Sort
5. Quick Sort
6. Shell Sort

Algoritma diuji dengan dua jenis data (angka dan kata) pada 8 ukuran dataset berbeda:
- 10,000
- 50,000
- 100,000
- 250,000
- 500,000
- 1,000,000
- 1,500,000
- 2,000,000

## Struktur Proyek

- `sorting.h`: Berisi implementasi dari 6 algoritma sorting beserta fungsi pendukung
- `main.c`: Program utama untuk menjalankan eksperimen dan menghasilkan data performa
- `integer_sorting_results.csv`: Hasil eksperimen untuk data angka
- `string_sorting_results.csv`: Hasil eksperimen untuk data kata
- `Laporan_Tugas4_SDA.pdf`: Laporan hasil analisis dan kesimpulan

## Cara Menjalankan Program

1. Kompilasi program dengan perintah:
   ```
   gcc main.c -o sorting
   ```

2. Jalankan program:
   ```
   ./sorting
   ```

3. Program secara otomatis akan:
    - Membangkitkan data acak (angka dan kata)
    - Menjalankan eksperimen untuk setiap algoritma sorting
    - Menyimpan hasil performa dalam file CSV

4. Hasil eksperimen dapat dilihat di file CSV, yang kemudian digunakan untuk analisis dalam laporan.
5. Untuk Grafik perbandingan bisa dilihat di index.html tinggal jalankan saja.

