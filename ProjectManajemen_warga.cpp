#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// ================== STRUCT ==================
struct Penduduk
{
    string nama;
    int umur;
    string alamat;
    string jenis_kelamin;
    string gol_darah;
};

const int MAX = 100;

// ================== REKURSIF ==================
int totalUmur(Penduduk *data, int n)
{
    if (n == 0)
        return 0;
    return data[n - 1].umur + totalUmur(data, n - 1);
}

// ================== TAMPIL ==================
void tampilkan(Penduduk *data, int n)
{
    system("cls");
    cout << "\n====================================================\n";
    cout << "                  TAMPIL DATA PENDUDUK\n";
    cout << "====================================================\n";

    if (n == 0)
    {
        cout << "[ERROR] Belum ada data untuk dicari.\n";
        return;
    }

    cout << "\n=================================== DATA PENDUDUK ===================================\n";
    cout << left
         << setw(5) << "No"
         << setw(22) << "Nama"
         << setw(6) << "Umur"
         << setw(22) << "Alamat"
         << setw(16) << "Jenis Kelamin"
         << setw(10) << "Gol. Darah" << endl;
    cout << "-------------------------------------------------------------------------------------\n";

    for (int i = 0; i < n; i++)
    {
        cout << left
             << setw(5) << i + 1
             << setw(22) << data[i].nama
             << setw(6) << data[i].umur
             << setw(22) << data[i].alamat
             << setw(16) << data[i].jenis_kelamin
             << setw(10) << data[i].gol_darah << endl;
    }
    cout << "-------------------------------------------------------------------------------------\n";
    cout << "Total data: " << n << " | Total umur: " << totalUmur(data, n) << "\n";
}

// ================== TAMBAH ==================
void tambahData(Penduduk *data, int &n)
{
    system("cls");
    cout << "\n====================================================\n";
    cout << "                 INPUT DATA PENDUDUK\n";
    cout << "====================================================\n";
    if (n >= MAX)
    {
        cout << "Data sudah penuh (maksimal " << MAX << ")!\n";
        return;
    }

    int jumlah;
    cout << "Jumlah data yang ingin ditambah: ";
    cin >> jumlah;
    cin.ignore();

    if (jumlah <= 0 || n + jumlah > MAX)
    {
        cout << "Jumlah tidak valid atau melebihi kapasitas!\n";
        return;
    }

    for (int i = 0; i < jumlah; i++)
    {
        cout << "\n--- Data ke-" << n + 1 << " ---\n";

        cout << "Nama         : ";
        getline(cin, data[n].nama);

        cout << "Umur         : ";
        while (!(cin >> data[n].umur) || data[n].umur < 0)
        {
            cout << "Input tidak valid. Masukkan umur (angka): ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cin.ignore();

        cout << "Alamat       : ";
        getline(cin, data[n].alamat);

        cout << "Jenis Kelamin: ";
        getline(cin, data[n].jenis_kelamin);

        cout << "Gol. Darah   : ";
        getline(cin, data[n].gol_darah);

        n++;
        cout << "Data berhasil ditambahkan!\n";
    }
}

// ================== HAPUS ==================
void hapus_datawarga(Penduduk *data, int &n)
{
    system("cls");

    if (n == 0)
    {
        cout << "[ERROR] Belum ada data untuk dicari.\n";
        return;
    }

    cout << "\n====================================================\n";
    cout << "                  HAPUS DATA PENDUDUK\n";
    cout << "====================================================\n";

    string cari_nama;
    int cari_umur;

    cout << "Masukkan Nama Warga: ";
    getline(cin, cari_nama);

    cout << "Masukkan Umur Warga: ";
    cin >> cari_umur;
    cin.ignore();

    bool ketemu = false;

    for (int i = 0; i < n; i++)
    {
        if (data[i].nama == cari_nama && data[i].umur == cari_umur)
        {
            for (int j = i; j < n - 1; j++)
            {
                data[j] = data[j + 1];
            }
            n--;
            cout << "[SUKSES] Data Berhasil Di Hapus\n";
            ketemu = true;
            tampilkan(data, n);
            break;
        }
    }
    if (!ketemu)
    {
        cout << "[ERROR] Data Tidak Di Temukan\n";
    }
}

// ================== SEARCH ==================
void cariData(Penduduk *data, int n)
{
    system("cls");
    cout << "\n====================================================\n";
    cout << "                  CARI DATA PENDUDUK\n";
    cout << "====================================================\n";

    if (n == 0)
    {
        cout << "[ERROR] Belum ada data untuk dicari.\n";
        return;
    }

    string cari, ulang;
    do
    {
        cout << "\nMasukkan nama yang dicari: ";
        getline(cin, cari);

        bool found = false;

        // Tampilkan header tabel
        cout << "\n\nHasil Pencarian : ";
        cout << "\n=====================================================================================\n";
        cout << left
             << setw(5) << "No"
             << setw(22) << "Nama"
             << setw(6) << "Umur"
             << setw(22) << "Alamat"
             << setw(16) << "Jenis Kelamin"
             << setw(10) << "Gol. Darah" << endl;
        cout << "---------------------------------------------------------------------------------------\n";

        int count = 0;
        for (int i = 0; i < n; i++)
        {
            // Pencarian case-insensitive (cek substring)
            string namaLower = data[i].nama;
            string cariLower = cari;
            for (char &c : namaLower)
                c = tolower(c);
            for (char &c : cariLower)
                c = tolower(c);

            if (namaLower.find(cariLower) != string::npos)
            {
                found = true;
                count++;
                cout << left
                     << setw(5) << count
                     << setw(22) << data[i].nama
                     << setw(6) << data[i].umur
                     << setw(22) << data[i].alamat
                     << setw(16) << data[i].jenis_kelamin
                     << setw(10) << data[i].gol_darah << endl;
            }
        }

        if (!found)
        {
            cout << "   Data dengan nama \"" << cari << "\" tidak ditemukan.\n";
        }
        else
        {
            cout << "---------------------------------------------------------------------------------------\n";
            cout << "Ditemukan " << count << " data.\n";
        }

        cout << "\nCari lagi? (ya/tidak): ";
        getline(cin, ulang);

    } while (ulang == "ya" || ulang == "YA" || ulang == "Ya");
}

// ================== SORT ==================
void sorting(Penduduk *data, int n)
{
    system("cls");
    cout << "\n====================================================\n";
    cout << "                  URUTKAN DATA PENDUDUK\n";
    cout << "====================================================\n";
    if (n == 0)
    {
        cout << "[ERROR] Belum ada data untuk dicari.\n";
        return;
    }

    int pilihSort;
    cout << "\nUrutkan berdasarkan:\n";
    cout << "1. Umur (ascending)\n";
    cout << "2. Umur (descending)\n";
    cout << "3. Nama (A-Z)\n";
    cout << "Pilih: ";
    cin >> pilihSort;
    cin.ignore();

    // Selection sort
    for (int i = 0; i < n - 1; i++)
    {
        int idx = i;
        for (int j = i + 1; j < n; j++)
        {
            bool kondisi = false;
            if (pilihSort == 1)
                kondisi = data[j].umur < data[idx].umur;
            else if (pilihSort == 2)
                kondisi = data[j].umur > data[idx].umur;
            else if (pilihSort == 3)
                kondisi = data[j].nama < data[idx].nama;

            if (kondisi)
                idx = j;
        }
        if (idx != i)
            swap(data[i], data[idx]);
    }

    cout << "Data berhasil diurutkan!\n";
    tampilkan(data, n);
}

// ================== FILE ==================
void simpanFile(Penduduk *data, int n)
{
    system("cls");
    cout << "\n====================================================\n";
    cout << "                SIMPAN FILE DATA PENDUDUK\n";
    cout << "====================================================\n";
    if (n == 0)
    {
        cout << "[ERROR] Belum ada data untuk dicari.\n";
        return;
    }

    ofstream file("data_penduduk.txt");
    if (!file)
    {
        cout << "Gagal membuka file untuk menyimpan!\n";
        return;
    }

    // Simpan jumlah data di baris pertama supaya bacaFile tahu berapa record
    file << n << "\n";

    for (int i = 0; i < n; i++)
    {
        file << data[i].nama << "\n";
        file << data[i].umur << "\n";
        file << data[i].alamat << "\n";
        file << data[i].jenis_kelamin << "\n";
        file << data[i].gol_darah << "\n";
    }

    file.close();
    cout << "Data berhasil disimpan ke \"data_penduduk.txt\" (" << n << " record).\n";
}

void bacaFile(Penduduk *data, int &n)
{
    system("cls");
    cout << "\n====================================================\n";
    cout << "                 BACA FILE DATA PENDUDUK\n";
    cout << "====================================================\n";
    ifstream file("data_penduduk.txt");

    if (!file)
    {
        cout << "File \"data_penduduk.txt\" tidak ditemukan!\n";
        return;
    }

    // Reset data lama
    n = 0;

    // Baca jumlah record dari baris pertama
    int jumlah;
    file >> jumlah;
    file.ignore();

    if (jumlah <= 0 || jumlah > MAX)
    {
        cout << "Isi file tidak valid atau kosong.\n";
        return;
    }

    for (int i = 0; i < jumlah && i < MAX; i++)
    {
        if (!getline(file, data[n].nama))
            break;
        file >> data[n].umur;
        file.ignore();
        if (!getline(file, data[n].alamat))
            break;
        if (!getline(file, data[n].jenis_kelamin))
            break;
        if (!getline(file, data[n].gol_darah))
            break;
        n++;
    }

    file.close();
    cout << "Berhasil membaca " << n << " data dari file.\n";
}

// ================== MENU ==================
void tampilMenu()
{
    cout << "\n====================================================\n";
    cout << "           SISTEM INFORMASI PENDUDUK\n";
    cout << "====================================================\n";
    cout << "| 1. Tambah Data                                   |\n";
    cout << "| 2. Tampilkan Data                                |\n";
    cout << "| 3. Cari Data                                     |\n";
    cout << "| 4. Urutkan Data (Sorting)                        |\n";
    cout << "| 5. Hapus Data                                    |\n";
    cout << "| 6. Simpan ke File                                |\n";
    cout << "| 7. Baca dari File                                |\n";
    cout << "| 8. Keluar                                        |\n";
    cout << "====================================================\n";
    cout << "Pilih menu: ";
}

// ================== MAIN ==================
int main()
{
    system("cls");
    Penduduk data[MAX];
    string username_daftar, username_pasword;
    int n = 0;
    int pilihan;

    cout << "\n=======================================================\n";
    cout << "                     PEMBUATAN AKUN                   \n";
    cout << "=======================================================\n";

    cout << "\nMasukkan Username: ";
    getline(cin, username_daftar);

    cout << "Masukkan Pasword: ";
    getline(cin, username_pasword);

    bool berhasil = false;

    for (int i = 3; i > 0; i--)
    {
        string username_login, pasword_login;

        cout << "\n=======================================================\n";
        cout << "                      LOGIN AKUN                  \n";
        cout << "=======================================================\n";
        cout << "\nMasukkan Username Anda: ";
        getline(cin, username_login);

        cout << "Masukkan Pasword Anda: ";
        getline(cin, pasword_login);

        if (username_login != username_daftar && pasword_login != username_pasword)
            cout << "Username dan Pasword Anda Tidak Valid!, Sisa Kesempatan " << i - 1 << " Lagi" << endl;
        else if (username_login != username_daftar)
            cout << "username Anda Tidak Sesuai!, Sisa Kesempatan " << i - 1 << " Lagi" << endl;
        else if (pasword_login != username_pasword)
            cout << "Pasword Anda Tidak Sesuai!, Sisa Kesempatan " << i - 1 << " Lagi" << endl;
        else
        {
            cout << "\nLogin Berhasil, Selamat Datang " << username_login << endl;
            berhasil = true;
            break;
        }
    }
    if (!berhasil)
    {
        cout << "\nKesempatan Telah Habis!!, Program Selesai.\n";
        return 0;
    }

    do
    {
        cout << endl;
        cout << "\n====================================================\n";
        cout << "     Selamat datang di Sistem Informasi Penduduk\n";
        cout << "====================================================\n";

        tampilMenu();

        while (!(cin >> pilihan))
        {
            cout << "Input tidak valid. Masukkan angka menu: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cin.ignore();

        cout << "\n";

        switch (pilihan)
        {
        case 1:
            tambahData(data, n);
            break;
        case 2:
            tampilkan(data, n);
            break;
        case 3:
            cariData(data, n);
            break;
        case 4:
            sorting(data, n);
            break;
        case 5:
            hapus_datawarga(data, n);
            break;
        case 6:
            simpanFile(data, n);
            break;
        case 7:
            bacaFile(data, n);
            tampilkan(data, n);
            break;
        case 8:
            cout << "Terima kasih telah menggunakan program ini!\n";
            break;
        default:
            cout << "Pilihan tidak valid! Masukkan angka 1-7.\n";
        }

        if (pilihan != 8)
        {
            cout << "\n[Tekan Enter untuk kembali ke menu...]";
            cin.get();
        }

    } while (pilihan != 8);

    return 0;
}
