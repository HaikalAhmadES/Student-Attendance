#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Mahasiswa {
public:
    string nama;
    string nim;
    string jurusan;
    string kehadiran;

    Mahasiswa(string nama, string nim, string jurusan, string kehadiran){
    Mahasiswa::nama = nama; 
    Mahasiswa::nim = nim;
    Mahasiswa::jurusan = jurusan;
    Mahasiswa::kehadiran = kehadiran;
    }

    string stringify() { 
        return nama + ";" + nim + ";" + jurusan + ";" + kehadiran; 
        }
};

class db {
public:
    ifstream in;
    ofstream out;
    string fileName;

    db(const char* fileName){
        this->fileName = fileName;
    }

    void save(Mahasiswa data) {
        out.open(fileName, ios::app);
        if (!out.is_open()){ 
            cout << "Error: File tidak terbuka" << endl; 
            return; 
        }
        out << data.stringify() << endl;
        out.close();
    }

    void showAll() {
        in.open(fileName);
        if (!in.is_open()){ 
            cout << "Error: File tidak bisa dibuka" << endl; 
            return; 
        }
        cout << "-----------------------------" << endl;
        cout << left << setw(5) << "No." << setw(25) << "Nama" << setw(15) << "NIM" << setw(20) << "Jurusan" << setw(10) << "Kehadiran" << endl;
        cout << "-----------------------------" << endl;
        string line; 
        int index = 1;
        while (getline(in, line)) {
            stringstream ss(line);
            string nama, nim, jurusan, kehadiran;
            getline(ss, nama, ';');
            getline(ss, nim, ';');
            getline(ss, jurusan, ';');
            getline(ss, kehadiran, ';');
            if (nama.length() > 24) nama = nama.substr(0, 24) + "...";
            cout << left << setw(5) << index++ << setw(25) << nama << setw(15) << nim << setw(20) << jurusan << setw(10) << kehadiran << endl;
        }
        in.close();
    }

    void clearData() {
        out.open(fileName, ios::trunc);
        if (!out.is_open()){ 
            cout << "Error: File tidak terbuka" << endl; 
            return; 
        }
        cout << "Data dihapus!" << endl;
        out.close();
    }
};

string inputNIM() {
    string nim;
    while (true) {
        cout << "NIM (angka): "; cin >> nim;
        if (nim.find_first_not_of("0123456789") == string::npos) break;
        else cout << "NIM harus angka, coba lagi." << endl;
    }
    return nim;
}

int main() {
    db database("data.txt");
    int pilihan;
    while (true) {
    cout << "========== MENU ==========" << endl;
        cout << "1. Tampilkan semua data mahasiswa" << endl;
        cout << "2. Masukkan data mahasiswa baru" << endl;
        cout << "3. Hapus semua data mahasiswa" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih opsi: ";
        cin >> pilihan;

        if (cin.fail() || pilihan < 1 || pilihan > 4){ 
            cin.clear(); 
            cin.ignore(1000, '\n');
            cout << "Pilihan salah, ulangi!\n"; 
            continue;; 
        }

        if (pilihan == 1) database.showAll();
        else if (pilihan == 2) {
            string nama, nim, jurusan, kehadiran;
            cout << "Nama: "; getline(cin >> ws, nama);
            nim = inputNIM();
            cout << "Jurusan: "; getline(cin >> ws, jurusan);
            cout << "Kehadiran: "; cin >> kehadiran;
            Mahasiswa mhs(nama, nim, jurusan, kehadiran);
            database.save(mhs);
        }
        else if (pilihan == 3) database.clearData();
        else if (pilihan == 4) break;
    }
    return 0;
}
