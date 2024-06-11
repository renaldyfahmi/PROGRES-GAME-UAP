#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <limits>
#include <ncurses/ncurses.h>

using namespace std;

class Pengguna {
public:
    string namaPengguna;
    string kataSandi;

    Pengguna(string nama, string sandi) : namaPengguna(nama), kataSandi(sandi) {}
};

class Film {
public:
    string judul;
    string jadwal;

    Film(string judul, string jadwal) : judul(judul), jadwal(jadwal) {}
};

class Pemesanan {
public:
    string namaPengguna;
    string judulFilm;
    string jadwal;
    int nomorKursi;
    string kodeKonfirmasi;

    Pemesanan(string nama, string jFilm, string jw, int kursi, string kKonfirmasi)
        : namaPengguna(nama), judulFilm(jFilm), jadwal(jw), nomorKursi(kursi), kodeKonfirmasi(kKonfirmasi) {}
};

vector<Pengguna> pengguna;
vector<Film> film;
list<Pemesanan> pemesanan;
unordered_map<string, vector<int>> kursiTersedia = {
    {"Film1", {1, 2, 3, 4, 5}},
    {"Film2", {1, 2, 3, 4, 5}}
};

bool daftarPengguna(const string &namaPengguna, const string &kataSandi) {
    for (const auto &p : pengguna) {
        if (p.namaPengguna == namaPengguna) {
            printw("Nama pengguna sudah ada!\n");
            return false;
        }
    }
    pengguna.emplace_back(namaPengguna, kataSandi);
    printw("Pendaftaran berhasil!\n");
    return true;
}

bool masukPengguna(const string &namaPengguna, const string &kataSandi) {
    for (const auto &p : pengguna) {
        if (p.namaPengguna == namaPengguna && p.kataSandi == kataSandi) {
            printw("Login berhasil!\n");
            return true;
        }
    }
    printw("Nama pengguna atau kata sandi salah!\n");
    return false;
}

void tampilkanFilm() {
    printw("Film dan jadwal yang tersedia:\n");
    for (const auto &f : film) {
        printw("Judul: %s, Jadwal: %s\n", f.judul.c_str(), f.jadwal.c_str());
    }
}
