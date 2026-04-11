#include "library.h"
#include <sys/stat.h>

// ===================== BIẾN TOÀN CỤC =====================
vector<User>       gUsers;
vector<Book>       gBooks;
vector<BorrowSlip> gBorrows;
vector<Fine>       gFines;
User*              gCurrentUser = nullptr;

// ===================== KHỞI TẠO DỮ LIỆU MẶC ĐỊNH =====================
// Tạo tài khoản admin mặc định nếu chưa có file dữ liệu

void initDefaultData() {
    // Kiểm tra file users đã có chưa
    ifstream f(DATA_USERS);
    if (f.is_open()) { f.close(); return; }  // đã có, không cần tạo

    // Tạo thư mục data
    #ifdef _WIN32
        system("mkdir data 2>nul");
    #else
        mkdir("data", 0777);
    #endif

    // Tạo tài khoản mặc định
    User admin;
    admin.id       = 1;
    admin.username = "admin";
    admin.password = hashPassword("admin123");
    admin.role     = "admin";
    admin.status   = "active";
    admin.fullname = "Quan Tri Vien";
    admin.email    = "admin@library.com";
    gUsers.push_back(admin);

    User lib;
    lib.id       = 2;
    lib.username = "thuthu";
    lib.password = hashPassword("thu123");
    lib.role     = "librarian";
    lib.status   = "active";
    lib.fullname = "Thu Thu Nguyen";
    lib.email    = "thuthu@library.com";
    gUsers.push_back(lib);

    User reader;
    reader.id       = 3;
    reader.username = "docgia1";
    reader.password = hashPassword("doc123");
    reader.role     = "reader";
    reader.status   = "active";
    reader.fullname = "Nguyen Van A";
    reader.email    = "docgia1@gmail.com";
    gUsers.push_back(reader);

    // Tạo vài sách mẫu
    Book b1 = {1, "Lap Trinh C++ Co Ban", "Bjarne Stroustrup", "NXB KHKT", 2020,
               "Lap trinh", 5, 5, "A1-01"};
    Book b2 = {2, "Co So Du Lieu", "Ramez Elmasri", "NXB GD", 2018,
               "CSDL", 3, 3, "A1-02"};
    Book b3 = {3, "Giai Tich 1", "Nguyen Dinh Tri", "NXB DHQG", 2019,
               "Toan hoc", 4, 4, "B2-01"};
    Book b4 = {4, "Tri Tue Nhan Tao", "Stuart Russell", "NXB KHKT", 2021,
               "AI", 2, 2, "A2-01"};
    Book b5 = {5, "Cau Truc Du Lieu & Giai Thuat", "Thomas Cormen", "NXB DHQG", 2017,
               "Lap trinh", 3, 3, "A1-03"};
    gBooks = {b1, b2, b3, b4, b5};

    saveAllData();

    cout << "  === DU LIEU MAN KHOI TAO ===\n";
    cout << "  Tai khoan mac dinh:\n";
    cout << "    Admin    : admin / admin123\n";
    cout << "    Thu thu  : thuthu / thu123\n";
    cout << "    Doc gia  : docgia1 / doc123\n";
    cout << "  ============================\n\n";
    pause();
}

// ===================== MAIN =====================
int main() {
    // Khởi tạo dữ liệu nếu lần đầu chạy
    initDefaultData();

    // Tải dữ liệu từ file
    loadAllData();

    // Vong lap chinh - login() tu xu ly menu dang nhap/dang ky/thoat
    while (true) {
        bool loggedIn = login();
        if (!loggedIn) break;  // nguoi dung chon Thoat

        // Dieu huong theo role
        if (gCurrentUser->role == "reader") {
            menuReader();
        } else if (gCurrentUser->role == "librarian") {
            menuLibrarian();
        } else if (gCurrentUser->role == "admin") {
            menuAdmin();
        }
        // Sau khi logout, vong lap quay lai menu dang nhap
    }

    saveAllData();
    cout << "\n  === Hen gap lai! ===\n\n";
    return 0;
}
