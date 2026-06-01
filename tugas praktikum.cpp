#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

// =====================================
// KELAS TOKO ELEKTRONIK (OOP)
// =====================================
class TokoElektronik {
private:
    array<string, 3> etalase; // enkapsulasi

public:
    // Constructor
    TokoElektronik() {
        etalase[0] = "Laptop ASUS";
        etalase[1] = "Smartphone Samsung";
        etalase[2] = "Headset Logitech";
    }

    // Method mengambil produk
    string ambilProduk(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        }
        catch (const out_of_range&) {
            throw runtime_error(
                "Gagal Mengambil Barang : Rak nomor " +
                to_string(nomorRak) +
                " kosong atau tidak tersedia!"
            );
        }
    }
};

// =====================================
// FUNGSI CRUD FILE
// =====================================

// Menampilkan isi file
void tampilkanBarang() {
    ifstream file("gudang.txt");

    cout << "\n===== DATA GUDANG =====\n";

    string barang;
    int nomor = 1;

    while (getline(file, barang)) {
        cout << nomor++ << ". " << barang << endl;
    }

    if (nomor == 1) {
        cout << "Gudang masih kosong.\n";
    }

    file.close();
}

// CREATE
void tambahBarang() {
    ofstream file("gudang.txt", ios::app);

    string barang;
    cin.ignore();

    cout << "Masukkan nama barang: ";
    getline(cin, barang);

    file << barang << endl;
    file.close();

    cout << "Barang berhasil ditambahkan!\n";
}

// UPDATE
void updateBarang() {
    vector<string> data;
    string barang;

    ifstream file("gudang.txt");

    while (getline(file, barang)) {
        data.push_back(barang);
    }

    file.close();

    if (data.empty()) {
        cout << "Gudang kosong!\n";
        return;
    }

    tampilkanBarang();

    int nomor;
    cout << "Pilih nomor barang yang ingin diubah: ";
    cin >> nomor;

    if (nomor < 1 || nomor > data.size()) {
        cout << "Nomor tidak valid!\n";
        return;
    }

    cin.ignore();
    cout << "Masukkan nama barang baru: ";
    getline(cin, barang);

    data[nomor - 1] = barang;

    ofstream out("gudang.txt");

    for (string item : data) {
        out << item << endl;
    }

    out.close();

    cout << "Data berhasil diperbarui!\n";
}

// DELETE
void hapusBarang() {
    vector<string> data;
    string barang;

    ifstream file("gudang.txt");

    while (getline(file, barang)) {
        data.push_back(barang);
    }

    file.close();

    if (data.empty()) {
        cout << "Gudang kosong!\n";
        return;
    }

    tampilkanBarang();

    int nomor;
    cout << "Pilih nomor barang yang ingin dihapus: ";
    cin >> nomor;

    if (nomor < 1 || nomor > data.size()) {
        cout << "Nomor tidak valid!\n";
        return;
    }

    data.erase(data.begin() + (nomor - 1));

    ofstream out("gudang.txt");

    for (string item : data) {
        out << item << endl;
    }

    out.close();

    cout << "Data berhasil dihapus!\n";
}

// =====================================
// SIMULASI ETALASE
// =====================================
void simulasiEtalase() {
    TokoElektronik toko;

    cout << "\n===== SIMULASI ETALASE =====\n";

    // Skenario 1
    try {
        cout << "\nSkenario 1 (Rak 1)\n";
        cout << "Barang ditemukan: "
             << toko.ambilProduk(1)
             << endl;
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

    // Skenario 2
    try {
        cout << "\nSkenario 2 (Rak 5)\n";
        cout << "Barang ditemukan: "
             << toko.ambilProduk(5)
             << endl;
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
}

// =====================================
// MAIN PROGRAM
// =====================================
int main() {
    int pilihan;

    do {
        cout << "\n================================";
        cout << "\n   TOKO ELEKTRONIK GIBRAN JAYA";
        cout << "\n================================\n";

        tampilkanBarang();

        cout << "\nMENU";
        cout << "\n1. Tambah Barang (Create)";
        cout << "\n2. Lihat Barang (Read)";
        cout << "\n3. Update Barang";
        cout << "\n4. Hapus Barang (Delete)";
        cout << "\n5. Simulasi Etalase";
        cout << "\n0. Keluar";
        cout << "\nPilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tambahBarang();
            break;

        case 2:
            tampilkanBarang();
            break;

        case 3:
            updateBarang();
            break;

        case 4:
            hapusBarang();
            break;

        case 5:
            simulasiEtalase();
            break;

        case 0:
            cout << "Terima kasih telah menggunakan sistem.\n";
            break;

        default:
            cout << "Pilihan tidak tersedia!\n";
        }

    } while (pilihan != 0);

    return 0;
}