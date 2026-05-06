#include <iostream>
#include <sstream>
#include <algorithm>
#include <windows.h>
#include <conio.h>
using namespace std;

// Kode Ini Konsepnya Adalah Pendapatan dan Pengeluaran Sederhana
// Ini Bisa Buat UMKM, Toko, Atau Keuangan Pribadi
// Wajib Menambahkan Komentar Di Setiap Kode Biar Tau Kalo Apa Yang Dibuat Dan Gampang Diubah Sesuai Kebutuhan

struct DataUang{
    string nama;
    int harga;
    int jumlah;
    bool tipe; //true untuk pendapatan, false untuk pengeluaran
};
DataUang listData[100];
int jumlahData = 0;

// Global Ya...
// nama itu Nama Setiap Menu
int menu = 0;
string nama[6] = {"1. Tampil Data","2. Tambah Data","3. Sorting", "4. Cari Data", "5. Laporan Data", "6. Keluar"};
static bool ulang = true;
int jumlah = sizeof(nama) / sizeof(nama[0]);

// Buat Ngilangin Hasil Output
// Wajib di Setiap Menu
// Terutama Setelah cin
void clearStream () {
    cin.clear();
    cin.ignore(100, '\n');
}

// Menu 1
// Tampil Data
void menu1 () {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    system("cls");

    if (jumlahData == 0) {
        cout << "Data kosong!\n";
    } else {
        cout << "Pendapatan:\n";
        for (int i = 0; i < jumlahData; i++) {
            if (listData[i].tipe) {
                cout << "----------\n";
                cout << "Nama : " << listData[i].nama << endl;
                cout << "Biaya : " << listData[i].harga << endl;
                cout << "Jumlah : " << listData[i].jumlah << endl;
            }
        }
        cout << "---------------------\nPengeluaran: \n";
        for (int i = 0; i < jumlahData; i++) {
            if (!listData[i].tipe) {
                cout << "----------\n";
                cout << "Nama : " << listData[i].nama << endl;
                cout << "Biaya : " << listData[i].harga << endl;
                cout << "Jumlah : " << listData[i].jumlah << endl;
            }
        }
    }

    cout << "Ketik apa aja buat gas...";
    _getch();
    system("cls");
}

// Menu 2
// Tambah Data
void menu2 () {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    system("cls");
    
    int jmlh;
    cout << "Masukkan Jumlah Data Yang Ingin Kamu Masukin : ";
    cin >> jmlh; cin.ignore();

    for (int i = jumlahData; i < (jumlahData + jmlh); i++) {
        bool ulangmenu = true;
        static bool tekan = false;
        cout << "Data ke-" << i+1 << endl;
        cout << "Masukkan nama : "; getline(cin, listData[i].nama);
        cout << "Masukkan biaya : "; cin >> listData[i].harga; cin.ignore();
        cout << "Masukkan jumlah : "; cin >> listData[i].jumlah; cin.ignore();
        cout << "Masukkan tipe (Tekan E Untuk Pendapatan, Tekan Q Untuk Pengeluaran) : ";
        
        while (ulangmenu) {
            Sleep(16); // Biar nggak berat di CPU
            if (GetAsyncKeyState('E') & 0x8000) {
                if (!tekan) {
                    listData[i].tipe = true;
                    ulangmenu = false;
                    tekan = true;
                    cout << "Pendapatan\n\n";
                }
            } else if (GetAsyncKeyState('Q') & 0x8000) {
                if (!tekan) {
                    listData[i].tipe = false;
                    ulangmenu = false;
                    tekan = true;
                    cout << "Pengeluaran\n\n";
                }
            } else {
                tekan = false;
            }
        }
    }
    jumlahData += jmlh;

    cout << "Ketik apa aja buat gas...";
    _getch();
    system("cls");
}

// sub-menu 3 state
int menu3A = 1; // menu3A = posisi kursor di halaman 1 (pilih kolom: Nama/Harga/Jumlah)
int menu3B = 1; // menu3B = posisi kursor di halaman 2 (pilih urutan: Ascending/Descending)

int partition(DataUang arr[], int low, int high, int sortBy, bool ascending) {
    DataUang pivot = arr[high]; // pivot dari paling kanan
    int i = low - 1;

    for(int j = low; j < high; j++){
        bool condition = false;

        // tentukan kondisi perbandingan sesuai kolom yang dipilih
        if(sortBy == 1){            // by nama
           condition = ascending ? (arr[j].nama < pivot.nama) : (arr[j].nama > pivot.nama); 
        } else if(sortBy == 2){     // by harga
           condition = ascending ? (arr[j].harga < pivot.harga) : (arr[j].harga > pivot.harga);
        } else if(sortBy == 3){     // by jumlah
           condition= ascending ? (arr[j].jumlah < pivot.jumlah) : (arr[j].jumlah > pivot.jumlah); 
        }

        if(condition){
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// quick sort rekursif
void quickSort(DataUang arr[], int low, int high, int sortBy, bool ascending){
    if(low < high){
        int pi = partition(arr, low, high, sortBy, ascending);  // posisi pivot
        quickSort(arr, low, pi - 1, sortBy, ascending);         // kiri partisipan
        quickSort(arr, pi + 1, high, sortBy, ascending);        // kanan partisipan
    }
}

// sub-menu 3 input
// ulangMenu3  = kontrol loop menu, false = keluar ke menu utama
// ulangMenu3B = penanda halaman: false = halaman 1 (pilih kolom, true halaman 2 (pilih urutan))
void inputMenu3(bool &ulangMenu3, bool &ulangMenu3B){
    static bool wpress = false;
    static bool spress = false;
    static bool epress = false;

    if(GetAsyncKeyState('W') & 0x8000){
        if(!wpress){
            if(ulangMenu3B) menu3B--;
            else menu3A--;
            wpress = true;
        }
    } else{
        wpress = false;
    }

    if(GetAsyncKeyState('S') & 0x8000){
        if(!spress){
            if(ulangMenu3B) menu3B++;
            else menu3A++;
            spress = true;
        }
    } else{
        spress = false;
    }

    if((GetAsyncKeyState('E') & 0x8000) || (GetAsyncKeyState(VK_SPACE) & 0x8000)) {
        if(!epress){
            epress = true;

            if(ulangMenu3B){
                if(menu3B == 3){
                    ulangMenu3B = false;
                } else {
                    // milih asc atau desc
                    bool ascending = (menu3B == 1);     // 1 = asc, 2 = desc
                    quickSort(listData, 0, jumlahData - 1, menu3A, ascending);
                    ulangMenu3 = false;                 // keluar loop 3
                    ulangMenu3B = false;                // reset state halaman
                    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                    system("cls");
                    cout << "YEYY!! Data berhsail disortir!\n";
                    cout << "Ketik apa aja buat gas...";
                    _getch();
                    system("cls");
                } 
            } else {
                // halaman 1 (pilih kolom)
                if(menu3A == 4){
                    ulangMenu3 = false;     // pilih "kembali" = menu utama
                } else {
                    ulangMenu3B = true;    // pilih kolom = lanjut halaman 2
                    menu3B = 1;             
                }
            }
        }
    } else {
        epress = false;
    }
}

//sub-menu 3 
//logika
void logicMenu3(bool ulangMenu3B){
    if(ulangMenu3B) {
        // halaman 2 ada 3 pilihan (asc, desc, kembali)
        if(menu3B < 1) menu3B = 3;
        else if(menu3B > 3) menu3B = 1; 
    } else {
        // halaman 1 ada 4 pilihan (nama, harga, jumlah, kembali)
        if(menu3A < 1) menu3A = 4;
        else if(menu3A > 4) menu3A = 1;
    }
}

//sub-menu 3
//rendering
void renderMenu3(bool ulangMenu3B){
    ostringstream oss;
    oss << "\033[H";
    oss << "Quick sort                                     \n";
    oss << "Tekan E atau Space untuk konfirmasi            \n";
    oss << "Tekan W/S untuk memilih                        \n\n";

    if(!ulangMenu3B){
        // halaman 1 - tampilkan pilihan kolom 
        oss << "Sortir berdasarka apa?\n\n";
        oss << "1. Nama      " << (menu3A == 1 ? "<-- " : "     ") << "\n";
        oss << "2. Harga     " << (menu3A == 2 ? "<-- " : "     ") << "\n";
        oss << "3. Jumlah    " << (menu3A == 3 ? "<-- " : "     ") << "\n";
        oss << "4. Kembali   " << (menu3A == 4 ? "<-- " : "     ") << "\n";
    } else {
        // halaman 2 tampilkan pilihan urutan, dan kolom yang tadi dipilih
        string kolom = (menu3A == 1) ? "Nama" : (menu3A == 2) ? "Harga" : "Jumlah";
        oss << "Urutan untuk " << kolom << "?\n\n";
        oss << "1. Ascending   " << (menu3B == 1 ? "<-- " : "    ") << "\n";
        oss << "2. Descending  " << (menu3B == 2 ? "<-- " : "    ") << "\n";
        oss << "3. Kembali     " << (menu3B == 3 ? "<-- " : "    ") << "\n";
    }

    cout << oss.str();
}


// Menu 3
//quick sort
void menu3 () {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    system("cls");

    // kalau data kosong langsung balik, ga masuk ke menu
    if(jumlahData == 0) {
    cout << "Data nya kosong weh, ga ada yang bisa disortir!\n";
    cout << "Ketik apa aja buat gas...";
    _getch();
    return;

    }
    
    bool ulangMenu3 = true;     // loop terus selama true
    bool ulangMenu3B = false;   // mulai dari halaman 1 (pilih kolom)
    menu3A = 1;                 // reset kursor halaman 1 ke atas
    menu3B = 1;                 // reset kursor halaman 2 ke atas

    while (ulangMenu3) {
        Sleep(16);
        inputMenu3(ulangMenu3, ulangMenu3B);
        logicMenu3(ulangMenu3B);
        renderMenu3(ulangMenu3B);
    }

    cout << "Ketik apa aja buat gas...";
    _getch();
    system("cls");

}

//Sub-menu 4 state
int menuA = 1;

// Sub-menu 4
// Cari Nama
void carinama() {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    system("cls");
    string namaData;
    cout << "Masukkan nama yang dicari : "; getline(cin, namaData);

    bool found = false;
    cout << "------------------------------------------\n";
    for (int i = 0; i < jumlahData; i++) {
        if (listData[i].nama == namaData) {
            cout << "Nama   : " << listData[i].nama << endl;
            cout << "Harga  : Rp " << listData[i].harga << endl;
            cout << "Jumlah : " << listData[i].jumlah << endl;
            cout << "Tipe   : " << (listData[i].tipe ? "Pendapatan" : "Pengeluaran") << endl;
            cout << "------------------------------------------" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Data tidak ditemukan!\n";
    }
    cout << "------------------------------------------\n";
    cout << "Ketik apa aja buat gas...";
    _getch();
}

// Sub-menu 4
// Cari Harga
void cariharga() {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    system("cls");
    int hargaData;
    cout << "Masukkan harga yang dicari (int) : "; cin >> hargaData; cin.ignore();

    bool found = false;
    cout << "------------------------------------------\n";
    for (int i = 0; i < jumlahData; i++) {
        if (listData[i].harga == hargaData) {
            cout << "Nama   : " << listData[i].nama << endl;
            cout << "Harga  : Rp " << listData[i].harga << endl;
            cout << "Jumlah : " << listData[i].jumlah << endl;
            cout << "Tipe   : " << (listData[i].tipe ? "Pendapatan" : "Pengeluaran") << endl;
            cout << "------------------------------------------" << endl;
            found = true;
        }
    }
    if (!found){
        cout << "Data tidak ditemukan!\n";
    }
    cout << "------------------------------------------\n";
    cout << "Ketik apa aja buat gas...";
    _getch();
}

// Sub-menu 4
// Cari Jumlah
void carijumlah() {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    system("cls");
    int jmlData;
    cout << "Masukkan jumlah yang dicari (int) : "; cin >> jmlData; cin.ignore();

    bool found = false;
    cout << "------------------------------------------\n";
    for (int i = 0; i < jumlahData; i++) {
        if (listData[i].jumlah == jmlData) {
            cout << "Nama   : " << listData[i].nama << endl;
            cout << "Harga  : Rp " << listData[i].harga << endl;
            cout << "Jumlah : " << listData[i].jumlah << endl;
            cout << "Tipe   : " << (listData[i].tipe ? "Pendapatan" : "Pengeluaran") << endl;
            cout << "------------------------------------------" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Data tidak ditemukan!\n";
    }
    cout << "------------------------------------------\n";
    cout << "Ketik apa aja buat gas...";
    _getch();
}

// Sub-menu 4
// Input
void inputMenu4(bool &ulangMenu4) {
    // Static Biar Gak Lupa Jati Diri
    static bool wpress = false;
    static bool spress = false;
    static bool epress = false;

    if (GetAsyncKeyState('W') & 0x8000)  {
        if (!wpress) {
            menuA--;
            wpress = true;
        }
    } else {
        wpress = false;
    }

    if (GetAsyncKeyState('S') & 0x8000) {
        if (!spress) {
            menuA++;
            spress = true;
        }
    } else {
        spress = false;
    }

    if ((GetAsyncKeyState('E') & 0x8000) || (GetAsyncKeyState(VK_SPACE) & 0x8000)) {
        if (!epress) {
            epress = true;
            if (menuA == 4) {
                ulangMenu4 = false;
            } else {
                switch (menuA) {
                    case 1: {
                        carinama(); break;
                    }
                    case 2:{
                        cariharga(); break;
                    }
                    case 3: {
                        carijumlah(); break;
                    }
                }
            }
        }
    } else {
        epress = false;
    }
}

// Sub-menu 4
// Logika
void logicMenu4() {
    if (menuA < 1) {
        menuA = 4;
    } else if (menuA > 4) {
        menuA = 1;
    }
}

//Sub-menu 4
// Rendering
void renderMenu4() {
    ostringstream oss;
    oss << "\033[H";
    oss << "Pilih mau nyariin apa nih?                     \n";
    oss << "Tekan E atau Space untuk konfirmasi                   \n";
    oss << "Tekan W/S untuk memilih                         \n";
    oss << "Plis masukin int di harga dan jumlah. Kalau enggak nanti ngebug asli                         \n\n";
    oss << "1. Nama" << (menuA == 1 ? "   <-- " : "       ") << "                   \n";
    oss << "2. Harga" << (menuA == 2 ? "  <-- " : "       ") << "                   \n";
    oss << "3. Jumlah" << (menuA == 3 ? " <-- " : "       ") << "                   \n";
    oss << "4. Kembali" << (menuA == 4 ? "<-- " : "       ") << "                   \n";
    cout << oss.str();
}


// Menu 4
// Cari Data
void menu4 () {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    system("cls");

    bool ulangMenu4 = true;
    menuA = 1;

    if (jumlahData == 0) {
        ulangMenu4 = false;
        cout << "Kosong woi datanya, isi dulu lah\n";
    } else {
        while (ulangMenu4) {
            Sleep(16);
            inputMenu4(ulangMenu4);
            logicMenu4();
            renderMenu4();
        }
    }

    cout << "Ketik apa aja buat gas...";
    _getch();
    system("cls");
}

// Menu 5
// Laporan Data
void menu5 () {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    system("cls");

    long long totalPendapatan = 0;
    long long totalPengeluaran = 0;

    if (jumlahData == 0) {
        cout << "Woi cik, data masih kosong loh ya!";
    } else {
        for (int i = 0; i < jumlahData; i++) {
            if (listData[i].tipe) {
                totalPendapatan += (long long)listData[i].harga * listData[i].jumlah;
            } else {
                totalPengeluaran += (long long)listData[i].harga * listData[i].jumlah;
            }
      }
    }

    long long labaRugi = totalPendapatan - totalPengeluaran;

    if (jumlahData == 0) {
        cout << " Jangan nyawit mas!\n";
    } else {
        cout << "----------------------\n";
        cout << "Total Pendapatan  : Rp " << totalPendapatan << endl;
        cout << "Total Pengeluaran : Rp " << totalPengeluaran << endl;
        cout << "-----------------------\n";
    
        if (labaRugi > 0) {
            cout << "Hasil: Untung Rp " << labaRugi << endl;
        } else if (labaRugi < 0) {
            cout << "Hasil: Rungkat njir Rp " << -labaRugi << endl;
        } else {
            cout << "Hasil: Yahaha capek doang, Aowaowkaokwaokawk (Rp 0)\n";
        }
    }

    cout << "Ketik apa aja buat gas...";
    _getch();
    system("cls");
}

// Menu 6
void menu6 () {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    system("cls");

    static bool tekan = true;
    bool keluar = true;
    cout << "Yakin pengen keluar? Q untuk keluar, A untuk batal\n" << "Input: ";

    // Input Untuk Keluar
    while (keluar) {
        Sleep(10);
        if (GetAsyncKeyState('Q') & 0x8000) {
            if (!tekan) {
                tekan = true; keluar = false; ulang = false;
            }
        } else {
            tekan = false;
        }
        if (GetAsyncKeyState('A') & 0x8000){
            if (!tekan) {
                tekan = true; keluar = false;
            }
        } else {
            tekan = false;
        }
    }
}

// Dibuat Oleh
// 123250028
// 123250037

// Input Pengguna
void input () {
    // Static Biar Gak Lupa Harga Diri
    static bool wpress = false;
    static bool spress = false;
    static bool enterpress = false;

    // Kode Biar Gak Spam Spam Kayak Chatmu ke Dia
    if (GetAsyncKeyState('W') & 0x8000) {
        if (!wpress) {
            menu--;
            wpress = true;
        }
    } else {
        wpress = false;
    };

    if (GetAsyncKeyState('S') & 0x8000) {
        if (!spress) {
            menu++;
            spress = true;
        }
    } else {
        spress = false;
    }

    if ((GetAsyncKeyState(VK_RETURN) & 0x8000) || (GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState('E') & 0x8000)) {
        if (!enterpress) {
            enterpress = true;
            switch (menu) {
                case 0:{
                    menu1(); break;
                }
                case 1:  {
                    menu2(); break;
                }
                case 2:{
                    menu3(); break;
                }
                case 3: {
                    menu4(); break;
                }
                case 4:{
                    menu5(); break;
                }
                case 5:  {
                    menu6(); break;
                }
            }
        }
    } else {
        enterpress = false;
    }
};

// Logika
void logic () {
    if (menu < 0) {
        menu = 5;
    } else if (menu > 5) {
        menu = 0;
    }
}

// Tampilkan ke Layar
void render () {
    ostringstream oss;
    oss << "\033[H";
    oss << "Tekan E atau Enter atau Space untuk konfirmasi                   \n";
    oss << "Tekan W/S untuk memilih\n";
    for (int i = 0; i < jumlah; i++) {
    oss << nama[i] << (i == menu ? " <-- " : "    ") << "\n";
    }
    oss << "\nPilihan: " << menu+1 << " ";

    cout << oss.str();
}

// Kode Ini Dibuat Oleh Ino dan Jipeh


// Pake Gameloop Biar Kece
int main () {
    while (ulang) {
    Sleep(16);
    input();
    logic();
    render();
    }
    return 0;
}