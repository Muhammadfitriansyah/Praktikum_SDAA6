#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Sparepart {
    string kodeSparepart;
    string namaSparepart;
    int stok;
    float harga;
    Sparepart* next;  // Pointer to the next node
};

Sparepart* head = nullptr; // Pointer to the head of the list

// Fungsi untuk menambah sparepart
void tambahSparepart() {
    Sparepart* sparepartBaru = new Sparepart;
    
    cout << "Masukkan Kode Sparepart: ";
    cin >> sparepartBaru->kodeSparepart;
    cout << "Masukkan Nama Sparepart: ";
    cin.ignore();
    getline(cin, sparepartBaru->namaSparepart);
    cout << "Masukkan Stok: ";
    cin >> sparepartBaru->stok;
    cout << "Masukkan Harga: ";
    cin >> sparepartBaru->harga;

    sparepartBaru->next = nullptr;

    if (head == nullptr) {
        head = sparepartBaru;
    } else {
        Sparepart* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = sparepartBaru;
    }

    cout << "Sparepart berhasil ditambahkan!" << endl;
}

// Fungsi untuk menampilkan semua sparepart
void tampilkanSpareparts() {
    if (head == nullptr) {
        cout << "Tidak ada sparepart dalam daftar." << endl;
        return;
    }

    Sparepart* temp = head;
    cout << "Daftar Sparepart Motor: " << endl;
    while (temp != nullptr) {
        cout << "Kode: " << temp->kodeSparepart << ", Nama: " << temp->namaSparepart
             << ", Stok: " << temp->stok << ", Harga: Rp" << temp->harga << endl;
        temp = temp->next;
    }
}

// Helper: Convert linked list to vector for searching
vector<Sparepart*> toVector() {
    vector<Sparepart*> spareparts;
    Sparepart* temp = head;
    while (temp != nullptr) {
        spareparts.push_back(temp);
        temp = temp->next;
    }
    return spareparts;
}

// Fibonacci Search for Stok
int fibonacciSearch(int stok) {
    vector<Sparepart*> spareparts = toVector();
    int n = spareparts.size();

    int fib2 = 0;
    int fib1 = 1;
    int fib = fib2 + fib1;

    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib2 + fib1;
    }

    int offset = -1;

    while (fib > 1) {
        int i = min(offset + fib2, n - 1);

        if (spareparts[i]->stok < stok) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        } else if (spareparts[i]->stok > stok) {
            fib = fib2;
            fib1 -= fib2;
            fib2 = fib - fib1;
        } else {
            cout << "Sparepart ditemukan: Kode " << spareparts[i]->kodeSparepart << endl;
            return i;
        }
    }

    if (fib1 && spareparts[offset + 1]->stok == stok) {
        cout << "Sparepart ditemukan: Kode " << spareparts[offset + 1]->kodeSparepart << endl;
        return offset + 1;
    }

    cout << "Stok tidak ditemukan." << endl;
    return -1;
}

// Jump Search for Stok
int jumpSearch(int stok) {
    vector<Sparepart*> spareparts = toVector();
    int n = spareparts.size();
    int step = sqrt(n);
    int prev = 0;

    while (spareparts[min(step, n) - 1]->stok < stok) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            cout << "Stok tidak ditemukan." << endl;
            return -1;
        }
    }

    while (spareparts[prev]->stok < stok) {
        prev++;
        if (prev == min(step, n)) {
            cout << "Stok tidak ditemukan." << endl;
            return -1;
        }
    }

    if (spareparts[prev]->stok == stok) {
        cout << "Sparepart ditemukan: Kode " << spareparts[prev]->kodeSparepart << endl;
        return prev;
    }

    cout << "Stok tidak ditemukan." << endl;
    return -1;
}

// Boyer-Moore for Nama Sparepart
int boyerMooreSearch(const string& nama) {
    vector<Sparepart*> spareparts = toVector();
    int n = spareparts.size();
    vector<int> badChar(256, -1);

    for (int i = 0; i < nama.length(); i++) {
        badChar[nama[i]] = i;
    }

    int s = 0;
    while (s <= (n - nama.length())) {
        int j = nama.length() - 1;

        while (j >= 0 && nama[j] == spareparts[s]->namaSparepart[j]) {
            j--;
        }

        if (j < 0) {
            cout << "Sparepart dengan nama '" << nama << "' ditemukan: Kode " << spareparts[s]->kodeSparepart << endl;
            return s;
        } else {
            s += max(1, j - badChar[spareparts[s]->namaSparepart[j]]);
        }
    }

    cout << "Nama sparepart tidak ditemukan." << endl;
    return -1;
}

// Fungsi untuk update sparepart
void updateSparepart() {
    string kode;
    cout << "Masukkan kode sparepart yang ingin diupdate: ";
    cin >> kode;

    Sparepart* temp = head;
    while (temp != nullptr) {
        if (temp->kodeSparepart == kode) {
            cout << "Masukkan Nama Sparepart Baru: ";
            cin.ignore();
            getline(cin, temp->namaSparepart);
            cout << "Masukkan Stok Baru: ";
            cin >> temp->stok;
            cout << "Masukkan Harga Baru: ";
            cin >> temp->harga;
            cout << "Sparepart berhasil diupdate!" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Sparepart dengan kode tersebut tidak ditemukan." << endl;
}

// Fungsi untuk menghapus sparepart
void hapusSparepart() {
    string kode;
    cout << "Masukkan kode sparepart yang ingin dihapus: ";
    cin >> kode;

    if (head == nullptr) {
        cout << "Daftar kosong, tidak ada yang bisa dihapus." << endl;
        return;
    }

    if (head->kodeSparepart == kode) {
        Sparepart* temp = head;
        head = head->next;
        delete temp;
        cout << "Sparepart berhasil dihapus!" << endl;
        return;
    }

    Sparepart* current = head;
    Sparepart* previous = nullptr;

    while (current != nullptr && current->kodeSparepart != kode) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Sparepart dengan kode tersebut tidak ditemukan." << endl;
        return;
    }

    previous->next = current->next;
    delete current;
    cout << "Sparepart berhasil dihapus!" << endl;
}
void cleanup() {
    while (head != nullptr) {
        Sparepart* temp = head;
        head = head->next;
        delete temp;
    }
}
// Menu program
void menu() {
    int pilihan;
    do {
        cout << "\nMenu Manajemen Penjualan Sparepart Motor:" << endl;
        cout << "1. Tambah Sparepart (Linked List)" << endl;
        cout << "2. Tampilkan Sparepart (Linked List)" << endl;
        cout << "3. Update Sparepart (Linked List)" << endl;
        cout << "4. Hapus Sparepart (Linked List)" << endl;
        cout << "5. Sorting Ascending (Merge Sort)" << endl;
        cout << "6. Sorting Descending (Quick Sort)" << endl;
        cout << "7. Cari Stok (Fibonacci Search)" << endl;
        cout << "8. Cari Stok (Jump Search)" << endl;
        cout << "9. Cari Nama (Boyer-Moore)" << endl;
        cout << "10. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahSparepart();
                break;
            case 2:
                tampilkanSpareparts();
                break;
            case 3:
                updateSparepart();
                break;
            case 4:
                hapusSparepart();
                break;
            case 5:
                mergeSort(&head);
                cout << "Sparepart telah diurutkan secara ascending!" << endl;
                break;
            case 6:
                quickSort(&head);
                cout << "Sparepart telah diurutkan secara descending!" << endl;
                break;
            case 7: {
                int stok;
                cout << "Masukkan stok yang dicari: ";
                cin >> stok;
                fibonacciSearch(stok);
                break;
            }
            case 8: {
                int stok;
                cout << "Masukkan stok yang dicari: ";
                cin >> stok;
                jumpSearch(stok);
                break;
            }
            case 9: {
                string nama;
                cout << "Masukkan nama sparepart yang dicari: ";
                cin.ignore();
                getline(cin, nama);
                boyerMooreSearch(nama);
                break;
            }
            case 10:
                cout << "Terima kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }
    } while (pilihan != 10);
}
// Recursive quicksort function
Sparepart* quickSortRecur(Sparepart* head, Sparepart* end) {
    if (!head || head == end)
        return head;

    Sparepart* newHead = nullptr, *newEnd = nullptr;

    Sparepart* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Sparepart* temp = newHead;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        temp->next = nullptr;

        newHead = quickSortRecur(newHead, temp);

        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}// Helper: Get the tail of the list
Sparepart* getTail(Sparepart* curr) {
    while (curr != nullptr && curr->next != nullptr)
        curr = curr->next;
    return curr;
}
Sparepart* partition(Sparepart* head, Sparepart* end, Sparepart** newHead, Sparepart** newEnd) {
    Sparepart* pivot = end;
    Sparepart *prev = nullptr, *curr = head, *tail = pivot;

    while (curr != pivot) {
        if (curr->harga > pivot->harga) {
            if ((*newHead) == nullptr) {
                (*newHead) = curr;
            }

            prev = curr;
            curr = curr->next;
        } else {
            if (prev) {
                prev->next = curr->next;
            }

            Sparepart* temp = curr->next;
            curr->next = nullptr;
            tail->next = curr;
            tail = curr;
            curr = temp;
        }
    }

    if ((*newHead) == nullptr) {
        (*newHead) = pivot;
    }

    (*newEnd) = tail;

    return pivot;
}
// Merge function for merge sort
Sparepart* merge(Sparepart* left, Sparepart* right) {
    if (!left) return right;
    if (!right) return left;

    Sparepart* result = nullptr;
    if (left->harga <= right->harga) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }
    return result;
}

// Split the list into two halves
void split(Sparepart* source, Sparepart** frontRef, Sparepart** backRef) {
    Sparepart* fast;
    Sparepart* slow;
    slow = source;
    fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}
void quickSort(Sparepart** headRef) {
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
}
void mergeSort(Sparepart** headRef) {
    Sparepart* head = *headRef;
    Sparepart* a;
    Sparepart* b;

    if (head == nullptr || head->next == nullptr) {
        return;
    }

    split(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *headRef = merge(a, b);
}
int main() {
    menu();
    cleanup();
    return 0;
}
