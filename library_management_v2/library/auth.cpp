#include "library.h"

void registerAccount() {
    clearScreen();
    cout << "======================================\n";
    cout << "          DANG KY TAI KHOAN\n";
    cout << "======================================\n\n";

    cout << "  Chon loai tai khoan:\n";
    cout << "    1. Doc gia\n";
    cout << "    2. Thu thu\n";
    cout << "    0. Quay lai\n";
    cout << "  Chon: ";
    int choice; cin >> choice;
    if (choice == 0) return;
    if (choice != 1 && choice != 2) {
        cout << "\n  Lua chon khong hop le!\n";
        pause();
        return;
    }

    cin.ignore();
    User u;
    u.role   = (choice == 1) ? "reader" : "librarian";
    u.status = "active";

    // Sinh ID moi
    int maxId = 0;
    for (auto& usr : gUsers) if (usr.id > maxId) maxId = usr.id;
    u.id = maxId + 1;

    cout << "\n   Thong tin dang ky\n";
    cout << "  Ho ten day du : ";
    getline(cin, u.fullname);
    if (u.fullname.empty()) {
        cout << "\n  Ho ten khong duoc de trong!\n";
        pause();
        return;
    }

    cout << "  Username      : ";
    getline(cin, u.username);
    if (u.username.empty()) {
        cout << "\n  Username khong duoc de trong!\n";
        pause();
        return;
    }
    // Kiem tra username da ton tai chua
    for (auto& usr : gUsers) {
        if (usr.username == u.username) {
            cout << "\n  Username \"" << u.username << "\" da ton tai! Vui long chon ten khac.\n";
            pause();
            return;
        }
    }

    cout << "  Password      : ";
    string pass; getline(cin, pass);
    if (pass.length() < 4) {
        cout << "\n  Password phai co it nhat 4 ky tu!\n";
        pause();
        return;
    }
    cout << "  Nhap lai pass : ";
    string confirm; getline(cin, confirm);
    if (pass != confirm) {
        cout << "\n  Password khong khop!\n";
        pause();
        return;
    }
    u.password = hashPassword(pass);

    cout << "  Email         : ";
    getline(cin, u.email);

    gUsers.push_back(u);
    saveUsers();

    cout << "  DANG KY THANH CONG!\n";
    cout << "  Vai tro  : " << (u.role == "reader" ? "Doc gia" : "Thu thu") << "\n";
    cout << "  Ho ten   : " << u.fullname << "\n";
    cout << "  Username : " << u.username << "\n";
    cout << "  Ban co the dang nhap ngay bay gio.\n";
    pause();
}

// Thuc hien dang nhap (1 lan thu)
bool doLogin() {
    clearScreen();

    cout << "            DANG NHAP\n";
    cout << "  Username: ";
    string username, password;
    cin >> username;
    cout << "  Password: ";
    cin >> password;

    string hashed = hashPassword(password);

    for (auto& u : gUsers) {
        if (u.username == username && u.password == hashed) {
            if (u.status == "locked") {
                cout << "\n  Tai khoan da bi khoa! Lien he Admin.\n";
                pause();
                return false;
            }
            gCurrentUser = &u;
            cout << "\n  Dang nhap thanh cong! Xin chao, " << u.fullname << "!\n";
            pause();
            return true;
        }
    }

    cout << "\n  Sai username hoac password!\n";
    return false;
}

// Menu man hinh chao - tra ve true neu dang nhap ok, false neu thoat
bool login() {
    while (true) {
        clearScreen();
        cout << "      HE THONG QUAN LY THU VIEN\n";
        cout << "  1. Dang nhap\n";
        cout << "  2. Dang ky tai khoan moi\n";
        cout << "  0. Thoat\n";
        cout << "\n  Chon: ";
        int choice; cin >> choice;

        if (choice == 0) return false;

        if (choice == 1) {
            int attempts = 0;
            while (attempts < 3) {
                if (doLogin()) return true;
                attempts++;
                if (attempts < 3) {
                    cout << "  Con " << (3 - attempts) << " lan thu lai.\n";
                    pause();
                }
            }
            cout << "\n  Nhap sai qua 3 lan. Quay lai menu chinh.\n";
            pause();
            continue;
        }

        if (choice == 2) {
            registerAccount();
            continue;
        }

        cout << "\n  Lua chon khong hop le!\n";
        pause();
    }
}

void logout() {
    gCurrentUser = nullptr;
    cout << "\n  Da dang xuat.\n";
}

void changePassword() {
    clearScreen();
    cout << "           DOI MAT KHAU\n";

    string oldPass, newPass, confirmPass;
    cout << "  Mat khau cu    : "; cin >> oldPass;
    cout << "  Mat khau moi   : "; cin >> newPass;
    cout << "  Xac nhan lai   : "; cin >> confirmPass;

    if (hashPassword(oldPass) != gCurrentUser->password) {
        cout << "\n  Mat khau cu khong dung!\n";
        pause();
        return;
    }
    if (newPass != confirmPass) {
        cout << "\n  Mat khau moi khong khop!\n";
        pause();
        return;
    }
    if (newPass.length() < 4) {
        cout << "\n  Mat khau phai co it nhat 4 ky tu!\n";
        pause();
        return;
    }

    for (auto& u : gUsers) {
        if (u.id == gCurrentUser->id) {
            u.password = hashPassword(newPass);
            gCurrentUser->password = u.password;
            break;
        }
    }
    saveUsers();
    cout << "\n  Doi mat khau thanh cong!\n";
    pause();
}
