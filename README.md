# Glove Translator BISINDO Berbasis Sensor dan Machine Learning #

## Deskripsi Proyek:
Proyek ini bertujuan mengembangkan perangkat wearable berupa sarung tangan yang berfungsi menerjemahkan Bahasa Isyarat Indonesia (BISINDO). Alat ini dirancang untuk mendeteksi gerakan tangan pengguna dan konversi menjadi teks atau suara secara waktu nyata (real-time). Inisiatif ini diajukan dalam Program Kreativitas Mahasiswa bidang Karsa Cipta (PKM-KC) sebagai solusi untuk mengatasi kesenjangan komunikasi antara penyandang disabilitas pendengaran dan masyarakat umum.

## Mekanisme Sistem:
Perangkat bekerja dengan membaca input fisik dari tangan pengguna melalui serangkaian sensor. Data sensor tersebut diproses oleh mikrokontroler yang menjalankan algoritma Machine Learning untuk mengidentifikasi pola gerakan isyarat yang spesifik. Setelah pola dikenali, sistem akan menampilkan terjemahan dalam bentuk teks pada layar LCD yang terpasang di perangkat.

## Spesifikasi Teknis

## Perangkat Keras
Sistem ini dibangun menggunakan komponen elektronika berikut:

1. **ESP32-S3:** Mikrokontroler utama yang bertugas sebagai unit pemrosesan data sensor dan menjalankan model inferensi.
2. **Sensor Fleksibel (Flex Sensor):** Komponen sensor yang mendeteksi perubahan sudut atau lekukan pada jari tangan.
3. **Accelerometer dan Gyroscope:** Sensor inersia untuk membaca orientasi, rotasi, dan percepatan gerakan tangan.
4. **Layar TFT LCD 3.5 Inci (Resolusi 480x320):** Antarmuka visual untuk menampilkan hasil terjemahan teks kepada lawan bicara.
5. **Baterai 18650:** Sumber daya daya mandiri yang memungkinkan perangkat bersifat portabel.
6. **Battery Shield:** Modul manajemen daya untuk menyuplai tegangan yang stabil ke mikrokontroler dan sensor.

## Perangkat Lunak
1. **Arduino IDE:** Digunakan sebagai lingkungan pengembangan untuk memprogram logika kendali pada ESP32-S3.
2. **Machine Learning:** Implementasi algoritma cerdas untuk klasifikasi pola sinyal sensor menjadi kata atau huruf BISINDO.

## Informasi anggota:
**Institusi: Bina Nusantara University (Kampus Bandung) Program: Computer Science**
**Program: Computer Science**

**Ketua Tim:** Alexandro Julio Caesar Soplantila (NIM: 2802407843)
**Anggota 1:** Michael Irvin Wartju (NIM: 2802410610)
**Anggota 2:** Muhammad Fahry Fauzi (NIM: 2802534222)
**Anggota 3:** Maria Louisa Alfianto (NIM: 2802411046
**Anggota 4:** Farrel Widjaja (NIM: 2802408865)
