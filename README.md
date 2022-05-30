# tubes-pmc
## Tugas Besar EL2008 Kelompok 12 - Minimisasi Logika Dengan Quine-McCluskey/Tabular Method

### Pendahuluan
Quine-McCluskey Method atau metode Tabular merupakan metode minimisasi persamaan logika yang paling umum digunakan dalam membuat algoritma penyederhanaan persamaan logika dan dapat diimplementasikan dengan software (perangkat lunak) secara algoritmik.

Keuntungan utama dari metode ini adalah dapat menerima lebih banyak input daripada K-map dan dapat diimplementasikan dengan software (perangkat lunak) secara algoritmik, sedangkan kelemahannya adalah kompleksitas komputasinya masih tetap tinggi.

Program dibuat dengan aplikasi [CodeBlocks](https://www.codeblocks.org/), yaitu sebuah IDE untuk C/C++. Selain itu, digunakan juga [Visual Studio Code](https://code.visualstudio.com/) sebagai aplikasi koding tambahan.

### Cara Kerja
Misalkan digunakan fungsi logika: 

**F (A, B, C, D) = Σ (0, 1, 2, 3, 5, 7, 8, 10, 12, 13, 15)** 

Program akan menerima input berupa banyak variabel, banyak minterm (termasuk Don’t-Care), dan minterm yang Don’t-Care jika ada. Program ini dapat menerima input variabel sebanyak mungkin, namun semakin banyak variabel yang ada, semakin lama program akan memproses fungsi tersebut. Hal ini disebabkan oleh kompleksitas algoritma yang masih cukup besar.

Program akan menerima input minterm yang sudah termasuk Don’t Care. Jika input minterm tidak sesuai (contohnya minterm tidak berurutan dari kecil sampai besar atau melebihi dua pangkat jumlah variabel), maka program akan memberi pesan peringatan lalu akan menerima input lagi sampai benar.  

Program lalu akan menerima banyak minterm yang Don’t Care. Jika input 0, maka program tidak akan menanyakan minterm yang Don’t Care. Penerimaan minterm akan berulang sampai sesuai dengan jumlah minterm yang ada. Setelah setiap input sudah dilakukan, program lalu akan memproses input-input tersebut untuk melakukan minimisasi logika, Setelah proses tersebut, program akan mengoutput hasil minimisasi. 

Jika jumlah minterm sama dengan dua pangkat jumlah variabel, program akan mengoutput: 

 

Hal ini disebabkan karena fungsi tidak perlu disederhanakan. 

Program akan diterminasi setelah user memencet tombol apa saja pada keyboard. 
