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
void tambahFilm(const string &judul, const string &jadwal) {
    film.emplace_back(judul, jadwal);
}

bool perbaruiJadwalFilm(const string &judul, const string &jadwalBaru) {
    for (auto &f : film) {
        if (f.judul == judul) {
            f.jadwal = jadwalBaru;
            printw("Jadwal film %s berhasil diperbarui!\n", judul.c_str());
            return true;
        }
    }
    printw("Film tidak ditemukan!\n");
    return false;
}

void tampilkanTiket(const Pemesanan &pemesanan) {
    printw("\n--- Tiket Bioskop ---\n");
    printw("Nama Pengguna: %s\n", pemesanan.namaPengguna.c_str());
    printw("Judul Film: %s\n", pemesanan.judulFilm.c_str());
    printw("Jadwal: %s\n", pemesanan.jadwal.c_str());
    printw("Nomor Kursi: %d\n", pemesanan.nomorKursi);
    printw("Kode Konfirmasi: %s\n", pemesanan.kodeKonfirmasi.c_str());
    printw("Harga Tiket: Rp 30,000\n");
    printw("Barcode: ||| ||| ||| ||| |||\n");
    printw("\n----------------------\n");
}

bool pesanTiket(const string &namaPengguna, const string &judulFilm, const string &jadwal, int nomorKursi) {
    for (auto &k : kursiTersedia) {
        if (k.first == judulFilm) {
            auto &kursi = k.second;
            auto it = find(kursi.begin(), kursi.end(), nomorKursi);
            if (it != kursi.end()) {
                kursi.erase(it);
                string kodeKonfirmasi = "KONF" + to_string(pemesanan.size() + 1);
                Pemesanan pemesananBaru(namaPengguna, judulFilm, jadwal, nomorKursi, kodeKonfirmasi);
                pemesanan.push_back(pemesananBaru);
                printw("Pemesanan berhasil! Kode Konfirmasi: %s\n", kodeKonfirmasi.c_str());
                tampilkanTiket(pemesananBaru);
                return true;
            }
        }
    }
    printw("Kursi tidak tersedia!\n");
    return false;
}

bool filmTersedia(const string &judul, const string &jadwal) {
    for (const auto &f : film) {
        if (f.judul == judul && f.jadwal == jadwal) {
            return true;
        }
    }
    return false;
}

void inputString(string &input, const char* prompt) {
    printw("%s", prompt);
    refresh();
    char str[100];
    getstr(str);
    input = str;
}
