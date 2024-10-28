#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

// Struktur Pelanggan dengan nomor antrian dan waktu layanan
struct Pelanggan {
    int nomorAntrian;
    int waktuLayanan; // waktu layanan dalam menit
};

// Kelas Queue untuk operasi antrian
class Queue {
private:
    queue<Pelanggan> q;

public:
    void enqueue(const Pelanggan &p) {
        q.push(p);
    }

    Pelanggan dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue kosong!");
        }
        Pelanggan front = q.front();
        q.pop();
        return front;
    }

    bool isEmpty() const {
        return q.empty();
    }

    int size() const {
        return q.size();
    }
};

// Fungsi untuk menghitung statistik antrian layanan
void simulasiLayanan(int jumlahPelanggan, int jumlahLoket) {
    Queue antrian;
    vector<int> waktuLoket(jumlahLoket, 0);  // waktu layanan per loket
    int totalWaktuTunggu = 0;
    int totalPelangganTerlayani = 0;
    
    // Memasukkan pelanggan ke dalam antrian dengan nomor dan waktu layanan acak
    for (int i = 1; i <= jumlahPelanggan; i++) {
        int waktuLayanan = rand() % 10 + 1; // waktu layanan acak antara 1-10 menit
        antrian.enqueue({i, waktuLayanan});
    }

    // Memproses antrian pelanggan dengan simulasi per menit
    while (!antrian.isEmpty()) {
        for (int i = 0; i < jumlahLoket; i++) {
            if (waktuLoket[i] == 0 && !antrian.isEmpty()) {
                Pelanggan pelanggan = antrian.dequeue();
                waktuLoket[i] = pelanggan.waktuLayanan;
                totalWaktuTunggu += pelanggan.waktuLayanan;
                totalPelangganTerlayani++;
                cout << "Pelanggan #" << pelanggan.nomorAntrian << " dilayani di loket " << i + 1
                     << " dengan waktu layanan " << pelanggan.waktuLayanan << " menit.\n";
            }
        }

        // Mengurangi waktu layanan setiap loket per menit
        for (int i = 0; i < jumlahLoket; i++) {
            if (waktuLoket[i] > 0) {
                waktuLoket[i]--;
            }
        }
    }

    // Menghitung statistik akhir
    double rataRataWaktuTunggu = totalWaktuTunggu / (double)totalPelangganTerlayani;
    cout << "\nStatistik Layanan:\n";
    cout << "Rata-rata waktu tunggu: " << rataRataWaktuTunggu << " menit\n";
    cout << "Total pelanggan terlayani: " << totalPelangganTerlayani << endl;
    cout << "Sisa antrian: " << antrian.size() << endl;
}

int main() {
    srand(time(0)); // Mengatur seed untuk waktu layanan acak
    int jumlahPelanggan, jumlahLoket = 3;

    cout << "Masukkan jumlah pelanggan yang akan dilayani: ";
    cin >> jumlahPelanggan;

    simulasiLayanan(jumlahPelanggan, jumlahLoket);

    return 0;
}