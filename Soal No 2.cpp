#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Peralatan {
    string kode;
    string nama;
    int jumlah;
    string kondisi;
};

// Fungsi untuk menambah data peralatan ke dalam file
void tambahPeralatan(const string &filename) {
    Peralatan alat;
    cout << "Masukkan kode peralatan: ";
    cin >> alat.kode;
    cout << "Masukkan nama peralatan: ";
    cin.ignore();
    getline(cin, alat.nama);
    cout << "Masukkan jumlah: ";
    cin >> alat.jumlah;
    cout << "Masukkan kondisi: ";
    cin.ignore();
    getline(cin, alat.kondisi);

    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << alat.kode << "," << alat.nama << "," << alat.jumlah << "," << alat.kondisi << endl;
        file.close();
        cout << "Data peralatan berhasil ditambahkan.\n";
    } else {
        cout << "Gagal membuka file.\n";
    }
}

// Fungsi untuk membaca data dari file
vector<Peralatan> bacaData(const string &filename) {
    vector<Peralatan> daftarAlat;
    ifstream file(filename);
    if (file.is_open()) {
        Peralatan alat;
        while (getline(file, alat.kode, ',') &&
               getline(file, alat.nama, ',') &&
               file >> alat.jumlah &&
               file.ignore() &&
               getline(file, alat.kondisi)) {
            daftarAlat.push_back(alat);
        }
        file.close();
    }
    return daftarAlat;
}

// Fungsi untuk menampilkan semua data peralatan
void tampilkanPeralatan(const vector<Peralatan> &daftarAlat) {
    if (daftarAlat.empty()) {
        cout << "Tidak ada data peralatan.\n";
        return;
    }

    cout << "Laporan Inventaris Peralatan:\n";
    cout << "Kode\tNama\tJumlah\tKondisi\n";
    for (const auto &alat : daftarAlat) {
        cout << alat.kode << "\t" << alat.nama << "\t" << alat.jumlah << "\t" << alat.kondisi << endl;
    }
}

// Fungsi untuk menghapus data peralatan berdasarkan kode
void hapusPeralatan(const string &filename, const string &kode) {
    vector<Peralatan> daftarAlat = bacaData(filename);
    auto it = remove_if(daftarAlat.begin(), daftarAlat.end(), [&](const Peralatan &alat) {
        return alat.kode == kode;
    });

    if (it == daftarAlat.end()) {
        cout << "Peralatan dengan kode " << kode << " tidak ditemukan.\n";
        return;
    }

    daftarAlat.erase(it, daftarAlat.end());
    ofstream file(filename, ios::trunc);
    for (const auto &alat : daftarAlat) {
        file << alat.kode << "," << alat.nama << "," << alat.jumlah << "," << alat.kondisi << endl;
    }
    file.close();
    cout << "Data peralatan berhasil dihapus.\n";
}

// Fungsi untuk mengubah data peralatan berdasarkan kode
void ubahPeralatan(const string &filename, const string &kode) {
    vector<Peralatan> daftarAlat = bacaData(filename);
    bool ditemukan = false;

    for (auto &alat : daftarAlat) {
        if (alat.kode == kode) {
            cout << "Data lama - Nama: " << alat.nama << ", Jumlah: " << alat.jumlah << ", Kondisi: " << alat.kondisi << endl;
            cout << "Masukkan data baru:\n";
            cout << "Nama peralatan: ";
            cin.ignore();
            getline(cin, alat.nama);
            cout << "Jumlah: ";
            cin >> alat.jumlah;
            cout << "Kondisi: ";
            cin.ignore();
            getline(cin, alat.kondisi);
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Peralatan dengan kode " << kode << " tidak ditemukan.\n";
        return;
    }

    ofstream file(filename, ios::trunc);
    for (const auto &alat : daftarAlat) {
        file << alat.kode << "," << alat.nama << "," << alat.jumlah << "," << alat.kondisi << endl;
    }
    file.close();
    cout << "Data peralatan berhasil diubah.\n";
}

// Fungsi untuk mengurutkan dan menampilkan data peralatan berdasarkan kode
void urutkanPeralatan(vector<Peralatan> &daftarAlat) {
    sort(daftarAlat.begin(), daftarAlat.end(), [](const Peralatan &a, const Peralatan &b) {
        return a.kode < b.kode;
    });
    tampilkanPeralatan(daftarAlat);
}

// Fungsi utama
int main() {
    string filename = "inventaris.txt";
    int pilihan;
    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah Peralatan\n";
        cout << "2. Ubah Peralatan\n";
        cout << "3. Hapus Peralatan\n";
        cout << "4. Tampilkan Peralatan\n";
        cout << "5. Urutkan Peralatan berdasarkan Kode\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahPeralatan(filename);
                break;
            case 2: {
                string kode;
                cout << "Masukkan kode peralatan yang ingin diubah: ";
                cin >> kode;
                ubahPeralatan(filename, kode);
                break;
            }
            case 3: {
                string kode;
                cout << "Masukkan kode peralatan yang ingin dihapus: ";
                cin >> kode;
                hapusPeralatan(filename, kode);
                break;
            }
            case 4: {
                vector<Peralatan> daftarAlat = bacaData(filename);
                tampilkanPeralatan(daftarAlat);
                break;
            }
            case 5: {
                vector<Peralatan> daftarAlat = bacaData(filename);
                urutkanPeralatan(daftarAlat);
                break;
            }
            case 6:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 6);

    return 0;
}