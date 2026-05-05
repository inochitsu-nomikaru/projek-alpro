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
void menu2 () {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    system("cls");
    
    cout << "Masih dalam uji coba ya...\n";

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

// Menu 4
void menu4 () {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    system("cls");

    cout << "Masih dalam uji coba ya...\n";

    system("pause");
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
void renderMenu () {
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
    renderMenu();
    }
    return 0;
}
//aaaaa
