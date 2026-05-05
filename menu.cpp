#include <iostream>
#include <sstream>
#include <windows.h>
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
        cout << "Data kosong!";
    } else {
        cout << "Pendapatan :\n";
        for (int i = 0; i < jumlahData; i++) {
            if (listData[i].tipe) {
                cout << listData[i].nama << listData[i].harga << listData[i].jumlah << endl;
            }
        }
        cout << "\n\nPengeluaran: \n";
        for (int i = 0; i < jumlahData; i++) {
            if (!listData[i].tipe) {
                cout << listData[i].nama << listData[i].harga << listData[i].jumlah << endl;
            }
        }
    }

    system("pause");
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
        cout << "Masukkan harga : "; cin >> listData[i].harga; cin.ignore();
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

    system("pause");
    system("cls");
}

// Menu 3
void menu3 () {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    system("cls");

    cout << "Masih dalam uji coba ya...\n";

    system("pause");
    system("cls");
}

// Sub-menu 4 state
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
        if (listData[i].nama.find(namaData) != string::npos) {
            cout << "Nama   : " << listData[i].nama << endl;
            cout << "Harga  : Rp " << listData[i].harga << endl;
            cout << "Jumlah : " << listData[i].jumlah << endl;
            cout << "Tipe   : " << (listData[i].tipe ? "Pendapatan" : "Pengeluaran") << endl;
            cout << "------------------------------------------" << endl;
            found = true;
        }
    }
    if (!found) cout << "Data tidak ditemukan!\n";
    cout << "------------------------------------------\n";
    system("pause");
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
    if (!found) cout << "Data tidak ditemukan!\n";
    cout << "------------------------------------------\n";
    system("pause");
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
    if (!found) cout << "Data tidak ditemukan!\n";
    cout << "------------------------------------------\n";
    system("pause");
}

// Sub-menu 4
// Input
void inputMenu4(bool &ulangMenu4) {
    static bool wpress = false;
    static bool spress = false;
    static bool epress = false;

    if (GetAsyncKeyState('W') && 0x8000)  {
        if (!wpress) {
            menuA--;
            wpress = true;
        }
    } else {
        wpress = false;
    }

    if (GetAsyncKeyState('S') && 0x8000) {
        if (!spress) {
            menuA++;
            spress = true;
        }
    } else {
        spress = false;
    }

    if ((GetAsyncKeyState('E') && 0x8000) || (GetAsyncKeyState(VK_SPACE) && 0x8000)) {
        if (!epress) {
            epress = true;
            if (menuA == 4) {
                ulangMenu4 = false;
            } else {
                switch (menuA) {
                    case 1: carinama(); break;
                    case 2: cariharga(); break;
                    case 3: carijumlah(); break;
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
    oss << "Masukkan int di harga dan jumlah. Kalau enggak nanti bug                         \n\n";
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

    while (ulangMenu4) {
        Sleep(16);
        inputMenu4(ulangMenu4);
        logicMenu4();
        renderMenu4();
    }

    system("cls");
}

// Menu 5
void menu5 () {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    system("cls");

    cout << "Masih dalam uji coba ya...\n";

    system("pause");
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
        if (GetAsyncKeyState('Q') && 0x8000) {
            if (!tekan) {
                tekan = true; keluar = false; ulang = false;
            }
        } else {
            tekan = false;
        }
        if (GetAsyncKeyState('A') && 0x8000){
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
                case 0: menu1(); break;
                case 1: menu2(); break;
                case 2: menu3(); break;
                case 3: menu4(); break;
                case 4: menu5(); break;
                case 5: menu6(); break;
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

// Awoakwoakwaok Ino Pelit Ngasih Main Cuy
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
//aaaaa
