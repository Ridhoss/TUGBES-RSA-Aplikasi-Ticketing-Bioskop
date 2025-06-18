# TUGAS BESAR APLIKASI TICKETING BIOSKOP
## KELOMPOK 6 RSA

### ANGGOTA
1. Raihana Aisha Az-Zahra (241511056)
2. Ridho Sulistyo Saputro (241511059)
3. Salma Arifah Zahra (241511062)

## Spesifikasi Program & Catatan
Program aplikasi ticketing bioskop ini dirancang untuk mengelola sistem penjualan tiket bioskop secara terstruktur menggunakan bahasa C dan memanfaatkan struktur data Tree, Queue, dan Stack. Sistem ini menyediakan antarmuka untuk dua jenis user, yaitu Admin dan User.
Pada sisi Admin, aplikasi menyediakan pengelolaan data bioskop yang mencakup penambahan, pengeditan, dan penghapusan bioskop. Setiap bioskop memiliki beberapa teater yang dapat dikelola secara dinamis. Admin juga dapat mengelola data film yang diputar di setiap teater beserta jadwal tayangnya. Struktur Tree digunakan untuk merepresentasikan hierarki data Bioskop → Teater → Jadwal Film. Selain itu, Admin juga dapat melihat laporan penjualan tiket berdasarkan bioskop tertentu. 
Pada sisi User, aplikasi memungkinkan user untuk melakukan registrasi, login, serta pencarian film berdasarkan bioskop dan teater tertentu. User dapat memilih film, jadwal tayang, dan kursi yang tersedia. Pemilihan kursi dilakukan secara dinamis untuk memastikan tidak ada kursi ganda yang dipesan. Setelah transaksi berhasil, tiket akan disimpan dalam struktur Stack untuk mencatat riwayat transaksi user.  Sistem Queue digunakan untuk mengelola aktivasi e-ticket yang telah dipesan oleh user. Admin akan memproses e-ticket satu per satu dari antrean untuk dikonfirmasi dan diaktifkan, sehingga menghindari konflik atau penyalahgunaan tiket.


## Menjalankan Aplikasi

### Menggunakan VSCode
1. Instalasi MINGW-32 di komputer anda

2. Install Extension
    - C/C++ Extension Pack : Microsoft
    - C/C++ Compile Run : danielpinto8zz6

3. Jika menggunakan VsCode GCC, compile menggunakan :
```bash
gcc main.c -o main.exe
```
Atau bisa menjalankan juga menggunakan : 
```bash
mingw32-make
```

4. Jika sudah berhasil, maka jalankan :
```bash
./main.exe
```

### Menggunakan DevC++
1. Instal Dev C++ Embarcadero versi 6.3 di komputer anda
```bash
https://sourceforge.net/projects/embarcadero-devcpp/
```

2. Buat Project Command Line Baru

3. Import file main.c ke dalam project, import juga folder dan file .c lainnya satu persatu kedalam project

4. Compile Project

5. Jika sudah berhasil, maka jalankan project