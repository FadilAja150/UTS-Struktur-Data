#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa {
    string NIM;
    string nama;
    float IPK;
};

// Maksimum jumlah mahasiswa
const int MAX_MAHASISWA = 10;
Mahasiswa* dataMahasiswa[MAX_MAHASISWA] = { nullptr };
int jumlahMahasiswa = 0;

// Fungsi untuk menambah data mahasiswa
void tambahMahasiswa() {
    if (jumlahMahasiswa < MAX_MAHASISWA) {
        Mahasiswa* mhs = new Mahasiswa;
        cout << "Masukkan NIM: ";
        cin >> mhs->NIM;
        cout << "Masukkan Nama: ";
        cin.ignore();
        getline(cin, mhs->nama);
        cout << "Masukkan IPK: ";
        cin >> mhs->IPK;

        dataMahasiswa[jumlahMahasiswa] = mhs;
        jumlahMahasiswa++;
        cout << "Data mahasiswa berhasil ditambahkan.\n";
    } else {
        cout << "Data mahasiswa sudah penuh.\n";
    }
}

// Fungsi untuk menghapus data mahasiswa berdasarkan NIM
void hapusMahasiswa() {
    string nim;
    cout << "Masukkan NIM mahasiswa yang ingin dihapus: ";
    cin >> nim;
    bool ditemukan = false;

    for (int i = 0; i < jumlahMahasiswa; i++) {
        if (dataMahasiswa[i] != nullptr && dataMahasiswa[i]->NIM == nim) {
            delete dataMahasiswa[i];
            dataMahasiswa[i] = nullptr;
            for (int j = i; j < jumlahMahasiswa - 1; j++) {
                dataMahasiswa[j] = dataMahasiswa[j + 1];
            }
            dataMahasiswa[jumlahMahasiswa - 1] = nullptr;
            jumlahMahasiswa--;
            ditemukan = true;
            cout << "Data mahasiswa berhasil dihapus.\n";
            break;
        }
    }
    if (!ditemukan) {
        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan.\n";
    }
}

// Fungsi untuk menampilkan data mahasiswa
void tampilkanMahasiswa() {
    if (jumlahMahasiswa == 0) {
        cout << "Belum ada data mahasiswa.\n";
        return;
    }
    cout << "Data Mahasiswa:\n";
    for (int i = 0; i < jumlahMahasiswa; i++) {
        if (dataMahasiswa[i] != nullptr) {
            cout << "NIM: " << dataMahasiswa[i]->NIM
                 << ", Nama: " << dataMahasiswa[i]->nama
                 << ", IPK: " << dataMahasiswa[i]->IPK << endl;
        }
    }
}

// Fungsi untuk mengurutkan data mahasiswa berdasarkan IPK menggunakan Bubble Sort
void urutkanMahasiswaByIPK() {
    for (int i = 0; i < jumlahMahasiswa - 1; i++) {
        for (int j = 0; j < jumlahMahasiswa - i - 1; j++) {
            if (dataMahasiswa[j]->IPK < dataMahasiswa[j + 1]->IPK) {
                Mahasiswa* temp = dataMahasiswa[j];
                dataMahasiswa[j] = dataMahasiswa[j + 1];
                dataMahasiswa[j + 1] = temp;
            }
        }
    }
    cout << "Data mahasiswa berhasil diurutkan berdasarkan IPK (terbesar ke terkecil).\n";
}

// Fungsi utama
int main() {
    int pilihan;
    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah Mahasiswa\n";
        cout << "2. Hapus Mahasiswa\n";
        cout << "3. Tampilkan Mahasiswa\n";
        cout << "4. Urutkan Mahasiswa berdasarkan IPK\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahMahasiswa();
                break;
            case 2:
                hapusMahasiswa();
                break;
            case 3:
                tampilkanMahasiswa();
                break;
            case 4:
                urutkanMahasiswaByIPK();
                break;
            case 5:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);

    // Menghapus data mahasiswa yang tersisa untuk menghindari memory leak
    for (int i = 0; i < jumlahMahasiswa; i++) {
        delete dataMahasiswa[i];
    }
    return 0;
}
