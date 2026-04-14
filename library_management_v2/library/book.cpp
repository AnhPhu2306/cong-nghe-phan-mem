#include "library.h"

//  QUẢN LÝ SÁCH 

void listBooks() {
    clearScreen();
    cout << "\n";
    cout << "          DANH SACH SACH\n";
    cout << "\n";
    cout << left
         << setw(5)  << "ID"
         << setw(30) << "Ten sach"
         << setw(20) << "Tac gia"
         << setw(15) << "The loai"
         << setw(8)  << "SL"
         << setw(8)  << "Con lai"
         << "Trang thai\n";
    cout << string(90, '-') << "\n";

    for (auto& b : gBooks) {
        string status = (b.available > 0) ? "Con sach" : "Het sach";
        cout << left
             << setw(5)  << b.id
             << setw(30) << b.title.substr(0, 28)
             << setw(20) << b.author.substr(0, 18)
             << setw(15) << b.category.substr(0, 13)
             << setw(8)  << b.quantity
             << setw(8)  << b.available
             << status << "\n";
    }
    cout << "\nTong: " << gBooks.size() << " cuon sach.\n";
    pause();
}

void viewBookDetail(int bookId) {
    for (auto& b : gBooks) {
        if (b.id == bookId) {
            clearScreen();
            cout << "\n";
            cout << "          CHI TIET SACH\n";
            cout << "\n";
            cout << "  ID        : " << b.id        << "\n";
            cout << "  Ten sach  : " << b.title     << "\n";
            cout << "  Tac gia   : " << b.author    << "\n";
            cout << "  NXB       : " << b.publisher << "\n";
            cout << "  Nam xuat ban: " << b.year    << "\n";
            cout << "  The loai  : " << b.category  << "\n";
            cout << "  Vi tri keo: " << b.location  << "\n";
            cout << "  So luong  : " << b.quantity  << "\n";
            cout << "  Con lai   : " << b.available << "\n";
            cout << "  Trang thai: " << (b.available > 0 ? "Con sach" : "Het sach") << "\n";
            pause();
            return;
        }
    }
    cout << "\n  Khong tim thay sach ID " << bookId << "\n";
    pause();
}

void searchBook() {
    clearScreen();
    cout << "\n";
    cout << "           TIM KIEM SACH\n";
    cout << "\n";
    cout << "  1. Tim theo ten sach\n";
    cout << "  2. Tim theo tac gia\n";
    cout << "  3. Tim theo the loai\n";
    cout << "  0. Quay lai\n";
    cout << "  Chon: ";

    int choice; cin >> choice;
    if (choice == 0) return;

    cin.ignore();
    cout << "  Nhap tu khoa: ";
    string keyword;
    getline(cin, keyword);

    // Chuyển thường hóa để tìm không phân biệt hoa thường
    string kw = keyword;
    transform(kw.begin(), kw.end(), kw.begin(), ::tolower);

    cout << "\n--- KET QUA TIM KIEM ---\n";
    cout << left
         << setw(5)  << "ID"
         << setw(30) << "Ten sach"
         << setw(20) << "Tac gia"
         << setw(15) << "The loai"
         << "Con lai\n";
    cout << string(75, '-') << "\n";

    int count = 0;
    for (auto& b : gBooks) {
        string field = "";
        if      (choice == 1) field = b.title;
        else if (choice == 2) field = b.author;
        else if (choice == 3) field = b.category;

        string fieldLower = field;
        transform(fieldLower.begin(), fieldLower.end(), fieldLower.begin(), ::tolower);

        if (fieldLower.find(kw) != string::npos) {
            cout << left
                 << setw(5)  << b.id
                 << setw(30) << b.title.substr(0, 28)
                 << setw(20) << b.author.substr(0, 18)
                 << setw(15) << b.category.substr(0, 13)
                 << b.available << "\n";
            count++;
        }
    }

    if (count == 0) cout << "  Khong tim thay ket qua phu hop.\n";
    else cout << "\n  Tim thay " << count << " sach.\n";

    // Xem chi tiết
    if (count > 0) {
        cout << "\n  Nhap ID sach de xem chi tiet (0 = bo qua): ";
        int id; cin >> id;
        if (id != 0) viewBookDetail(id);
    } else {
        pause();
    }
}

void addBook() {
    clearScreen();
    cout << "\n";
    cout << "            THEM SACH MOI\n";
    cout << "\n\n";

    cin.ignore();
    Book b;

    // Sinh ID mới
    int maxId = 0;
    for (auto& bk : gBooks) if (bk.id > maxId) maxId = bk.id;
    b.id = maxId + 1;

    cout << "  Ten sach     : "; getline(cin, b.title);
    cout << "  Tac gia      : "; getline(cin, b.author);
    cout << "  NXB          : "; getline(cin, b.publisher);
    cout << "  Nam xuat ban : "; cin >> b.year;
    cin.ignore();
    cout << "  The loai     : "; getline(cin, b.category);
    cout << "  So luong     : "; cin >> b.quantity;
    cin.ignore();
    cout << "  Vi tri keo   : "; getline(cin, b.location);

    b.available = b.quantity;

    gBooks.push_back(b);
    saveBooks();

    cout << "\n  Them sach thanh cong! ID = " << b.id << "\n";
    pause();
}

void updateBook() {
    clearScreen();
    cout << "\n";
    cout << "         CAP NHAT THONG TIN SACH\n";
    cout << "\n\n";

    cout << "  Nhap ID sach can sua: ";
    int id; cin >> id;

    Book* found = nullptr;
    for (auto& b : gBooks) {
        if (b.id == id) { found = &b; break; }
    }

    if (!found) {
        cout << "\n  Khong tim thay sach!\n";
        pause();
        return;
    }

    cout << "  Sach hien tai: " << found->title << "\n\n";
    cin.ignore();

    cout << "  Ten moi (Enter = giu nguyen): ";
    string input;
    getline(cin, input);
    if (!input.empty()) found->title = input;

    cout << "  Tac gia moi  : ";
    getline(cin, input);
    if (!input.empty()) found->author = input;

    cout << "  NXB moi      : ";
    getline(cin, input);
    if (!input.empty()) found->publisher = input;

    cout << "  The loai moi : ";
    getline(cin, input);
    if (!input.empty()) found->category = input;

    cout << "  Vi tri moi   : ";
    getline(cin, input);
    if (!input.empty()) found->location = input;

    cout << "  So luong them (0 = khong doi): ";
    int addQty; cin >> addQty;
    if (addQty > 0) {
        found->quantity  += addQty;
        found->available += addQty;
    }

    saveBooks();
    cout << "\n  Cap nhat thanh cong!\n";
    pause();
}

void deleteBook() {
    clearScreen();
    cout << "\n";
    cout << "             XOA SACH\n";
    cout << "\n\n";

    cout << "  Nhap ID sach can xoa: ";
    int id; cin >> id;

    for (int i = 0; i < (int)gBooks.size(); i++) {
        if (gBooks[i].id == id) {
            // Kiểm tra sách đang được mượn
            if (gBooks[i].available < gBooks[i].quantity) {
                cout << "\n  Sach dang duoc muon, khong the xoa!\n";
                pause();
                return;
            }
            cout << "  Xac nhan xoa sach \"" << gBooks[i].title << "\"? (y/n): ";
            char c; cin >> c;
            if (c == 'y' || c == 'Y') {
                gBooks.erase(gBooks.begin() + i);
                saveBooks();
                cout << "\n  Da xoa sach!\n";
            } else {
                cout << "\n  Huy bo.\n";
            }
            pause();
            return;
        }
    }
    cout << "\n  Khong tim thay sach ID " << id << "\n";
    pause();
}

void manageBook() {
    int choice;
    do {
        clearScreen();
        cout << "\n";
        cout << "          QUAN LY SACH\n";
        cout << "\n";
        cout << "  1. Xem danh sach sach\n";
        cout << "  2. Tim kiem sach\n";
        cout << "  3. Them sach moi\n";
        cout << "  4. Sua thong tin sach\n";
        cout << "  5. Xoa sach\n";
        cout << "  0. Quay lai\n";
        cout << "  Chon: ";
        cin >> choice;

        switch (choice) {
            case 1: listBooks();   break;
            case 2: searchBook();  break;
            case 3: addBook();     break;
            case 4: updateBook();  break;
            case 5: deleteBook();  break;
        }
    } while (choice != 0);
}
