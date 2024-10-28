#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

struct Buku {
    string ISBN;
    string judul;
    string pengarang;
    int tahunTerbit;
};

const int MAX_BUKU = 100;
Buku* daftarBuku[MAX_BUKU];
int jumlahBuku = 0;

stack<Buku*> riwayatPeminjaman;

queue<Buku*> antrianPeminjaman;

void tambahBuku() {
    if (jumlahBuku >= MAX_BUKU) {
        cout << "Kapasitas perpustakaan penuh!\n";
        return;
    }

    Buku* bukuBaru = new Buku;
    cout << "Masukkan ISBN: ";
    cin >> bukuBaru->ISBN;
    cout << "Masukkan judul buku: ";
    cin.ignore();
    getline(cin, bukuBaru->judul);
    cout << "Masukkan pengarang: ";
    getline(cin, bukuBaru->pengarang);
    cout << "Masukkan tahun terbit: ";
    cin >> bukuBaru->tahunTerbit;

    daftarBuku[jumlahBuku++] = bukuBaru;
    cout << "Buku berhasil ditambahkan.\n";
}

Buku* cariBuku(const string& ISBN) {
    for (int i = 0; i < jumlahBuku; i++) {
        if (daftarBuku[i]->ISBN == ISBN) {
            return daftarBuku[i];
        }
    }
    return nullptr;
}

void tampilkanBuku() {
    if (jumlahBuku == 0) {
        cout << "Tidak ada buku di perpustakaan.\n";
        return;
    }

    cout << "Daftar Buku:\n";
    for (int i = 0; i < jumlahBuku; i++) {
        cout << "ISBN: " << daftarBuku[i]->ISBN
             << ", Judul: " << daftarBuku[i]->judul
             << ", Pengarang: " << daftarBuku[i]->pengarang
             << ", Tahun Terbit: " << daftarBuku[i]->tahunTerbit << endl;
    }
}

void pinjamBuku() {
    string ISBN;
    cout << "Masukkan ISBN buku yang ingin dipinjam: ";
    cin >> ISBN;

    Buku* buku = cariBuku(ISBN);
    if (buku) {
        antrianPeminjaman.push(buku);
        cout << "Buku dengan judul '" << buku->judul << "' ditambahkan ke antrian peminjaman.\n";
    } else {
        cout << "Buku dengan ISBN " << ISBN << " tidak ditemukan.\n";
    }
}

void prosesPeminjaman() {
    if (antrianPeminjaman.empty()) {
        cout << "Tidak ada peminjaman dalam antrian.\n";
        return;
    }

    Buku* bukuDipinjam = antrianPeminjaman.front();
    antrianPeminjaman.pop();
    riwayatPeminjaman.push(bukuDipinjam);
    cout << "Buku dengan judul '" << bukuDipinjam->judul << "' telah dipinjam.\n";
}

void kembalikanBuku() {
    if (riwayatPeminjaman.empty()) {
        cout << "Tidak ada buku yang perlu dikembalikan.\n";
        return;
    }

    Buku* bukuDikembalikan = riwayatPeminjaman.top();
    riwayatPeminjaman.pop();
    cout << "Buku dengan judul '" << bukuDikembalikan->judul << "' telah dikembalikan.\n";
}

void tampilkanRiwayatPeminjaman() {
    if (riwayatPeminjaman.empty()) {
        cout << "Tidak ada riwayat peminjaman.\n";
        return;
    }

    stack<Buku*> tempRiwayat = riwayatPeminjaman;
    cout << "Riwayat Peminjaman:\n";
    while (!tempRiwayat.empty()) {
        Buku* buku = tempRiwayat.top();
        cout << "Judul: " << buku->judul << ", ISBN: " << buku->ISBN << endl;
        tempRiwayat.pop();
    }
}

int main() {
    int pilihan;
    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Cari Buku\n";
        cout << "3. Tampilkan Semua Buku\n";
        cout << "4. Pinjam Buku\n";
        cout << "5. Proses Antrian Peminjaman\n";
        cout << "6. Kembalikan Buku\n";
        cout << "7. Tampilkan Riwayat Peminjaman\n";
        cout << "8. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahBuku();
                break;
            case 2: {
                string ISBN;
                cout << "Masukkan ISBN buku yang dicari: ";
                cin >> ISBN;
                Buku* buku = cariBuku(ISBN);
                if (buku) {
                    cout << "ISBN: " << buku->ISBN
                         << ", Judul: " << buku->judul
                         << ", Pengarang: " << buku->pengarang
                         << ", Tahun Terbit: " << buku->tahunTerbit << endl;
                } else {
                    cout << "Buku tidak ditemukan.\n";
                }
                break;
            }
            case 3:
                tampilkanBuku();
                break;
            case 4:
                pinjamBuku();
                break;
            case 5:
                prosesPeminjaman();
                break;
            case 6:
                kembalikanBuku();
                break;
            case 7:
                tampilkanRiwayatPeminjaman();
                break;
            case 8:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 8);

    for (int i = 0; i < jumlahBuku; i++) {
        delete daftarBuku[i];
    }

    return 0;
}