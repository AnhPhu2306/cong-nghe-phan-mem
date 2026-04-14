#include "library.h"

//  CÁC HÀM TIỆN ÍCH 

// Lấy ngày hiện tại dạng "dd/mm/yyyy"
string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buf[20];
    snprintf(buf, sizeof(buf), "%02d/%02d/%04d",
        ltm->tm_mday,
        ltm->tm_mon + 1,
        ltm->tm_year + 1900);
    return string(buf);
}

// Chuyển "dd/mm/yyyy" → số ngày (tính từ epoch đơn giản)
// Trả về số ngày tính từ 01/01/2000
int dateToDay(string date) {
    int d, m, y;
    sscanf(date.c_str(), "%d/%d/%d", &d, &m, &y);
    // Công thức đơn giản tính số ngày
    int days = y * 365 + m * 30 + d;
    return days;
}

// Tính số ngày giữa 2 ngày (date2 - date1)
int daysBetween(string date1, string date2) {
    return dateToDay(date2) - dateToDay(date1);
}

// Cộng thêm n ngày vào date (định dạng dd/mm/yyyy)
string addDays(string date, int days) {
    int d, m, y;
    sscanf(date.c_str(), "%d/%d/%d", &d, &m, &y);

    // Mảng số ngày trong tháng
    int daysInMonth[] = {0, 31,28,31,30,31,30,31,31,30,31,30,31};

    d += days;
    // Xử lý tràn tháng
    while (d > daysInMonth[m]) {
        d -= daysInMonth[m];
        m++;
        if (m > 12) { m = 1; y++; }
    }

    char buf[20];
    snprintf(buf, sizeof(buf), "%02d/%02d/%04d", d, m, y);
    return string(buf);
}

// Hash password đơn giản (cộng tổng ASCII + xáo trộn)
string hashPassword(string password) {
    string hashed = "";
    int key = 37;
    for (char c : password) {
        int code = (int)c + key;
        hashed += to_string(code) + "-";
        key = code % 97;
    }
    return hashed;
}

// Xóa màn hình
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Dừng chờ người dùng nhấn Enter
void pause() {
    cout << "\n  Nhan Enter de tiep tuc...";
    cin.ignore();
    cin.get();
}

// Tạo ID mới (max + 1)
int generateId(int maxId) {
    return maxId + 1;
}
