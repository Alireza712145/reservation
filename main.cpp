#include <iostream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

enum MealType { Breakfast, Lunch, Dinner };
enum ReserveDay { Saturday, Sunday, Monday, Tuesday, Wednesday, Thursday, Friday };

class User {
private:
    int userID;
    string name, lastName, hashedPassword;

public:
    User(int id, string n, string ln, string pwd) : userID(id), name(n), lastName(ln), hashedPassword(pwd) {}

    int getUserID() { return userID; }
    string getName() { return name; }
    string getLastName() { return lastName; }
    string getPassword() { return hashedPassword; }

    void setName(string n) { name = n; }
    void setLastName(string ln) { lastName = ln; }
    void setPassword(string pwd) { hashedPassword = pwd; }

    virtual void print() const {
        cout << "User ID: " << userID << "\nName: " << name << " " << lastName << endl;
    }
};
class DiningHall{
private:
    int hall_id;
    string name, address;
    int capacity;
public:
    DiningHall()
    :hall_id(1), name("aboozar"), address("modares2"), capacity(0){}

    void sethall_id(int _hall_id);
    void setname(string _name);
    void setaddress(string _address);
    void setcapacity(int _capacity);

    int gethall_id(){
    return hall_id;}

    string getname (){
    return name;}

    string getaddress(){
    return address;}

    int getcapacity(){
    return capacity;}

    void print();
};
void DiningHall::print(){
    cout << "hall id= \t" << hall_id << endl;
    cout << "name = \t\t" << name << endl;
    cout << "address =\t" << address << endl;
    cout << "capacity =\t" << capacity << endl;
}

void DiningHall::sethall_id(int _hall_id){
    hall_id = _hall_id;}

void DiningHall::setname(string _name){
    name = _name;}

void DiningHall::setaddress(string _address){
    address = _address;}

void DiningHall::setcapacity(int _capacity){
    capacity = _capacity;}
//پایان کلاس سالن غذا خوری
//

class Meal {
private:
    int mealID;
    string name;
    float price;
    bool isActive;
    MealType mealType;
    ReserveDay reserveDay;
    vector<string> sideItems;

public:
    Meal(int id, string n, float p, MealType mt, ReserveDay rd)
    : mealID(id), name(n), price(p), mealType(mt), reserveDay(rd), isActive(true) {}

    void activate() { isActive = true; }
    void deactivate() { isActive = false; }

    void addSideItem(const string& item) { sideItems.push_back(item); }

    void print() const {
        cout << "Meal ID: " << mealID << "\nName: " << name << "\nPrice: " << price;
        cout << "\nType: " << mealType << "\nReserve Day: " << reserveDay << endl;
    }
};

//
enum RStatus { Active, Cancelled };
class Reservation {
private:
    int reservationID;
    DiningHall* dHall;
    Meal* meal;
    RStatus status;
    time_t createdAt;

public:
    Reservation(int id, DiningHall* hall, Meal* m)
    : reservationID(id), dHall(hall), meal(m), status(Active), createdAt(time(nullptr)) {}

    void setStatus(RStatus s) { status = s; }
    RStatus getStatus() const { return status; }

    void print() const {
        cout << "Reservation ID: " << reservationID << "\nStatus: " << status << "\nCreated At: " << createdAt << endl;
        dHall->print();
        meal->print();
    }
};

class Student : public User {
private:
    string studentID, email, phone;
    float balance;
    bool isActive;
    vector<Reservation> reserves;

public:
    Student(int id, string n, string ln, string pwd, string sID, string mail, string ph, float bal)
    : User(id, n, ln, pwd), studentID(sID), email(mail), phone(ph), balance(bal), isActive(true) {}

    void activate() { isActive = true; }
    void deactivate() { isActive = false; }
    bool getIsActive() { return isActive; }

    void addReservation(const Reservation& res) { reserves.push_back(res); }

    void print() const override {
        User::print();
        cout << "Student ID: " << studentID << "\nEmail: " << email << "\nBalance: " << balance << endl;
    }
};
class Storage {
private:
    static Storage* instance;
    vector<Meal> allMeals;
    vector<DiningHall> allDiningHalls;

    Storage() {} // private constructor

public:
    static Storage* getInstance() {
        if (!instance) instance = new Storage();
        return instance;
    }

    void addMeal(const Meal& meal) { allMeals.push_back(meal); }
    void addDiningHall(const DiningHall& hall) { allDiningHalls.push_back(hall); }
};

Storage* Storage::instance = nullptr;

class Panel {
public:
    void showMenu(); // نمایش منو اصلی
    void showStudentInfo(); // نمایش اطلاعات دانشجو
    void checkBalance(); // بررسی موجودی حساب
    void viewReservations(); // نمایش لیست رزروها
    void addReservation(Reservation); // اضافه کردن رزرو
    void addToShoppingCart(); // افزودن به سبد خرید
    void confirmShoppingCart(); // تأیید خرید
    void removeShoppingCartItem(); // حذف آیتم از سبد خرید
    void exit(); // خروج از برنامه
};
class Admin : public User {
public:
    Admin(int id, string n, string ln, string pwd) : User(id, n, ln, pwd) {}

    void activateStudent(Student& s) { s.activate(); }
    void deactivateStudent(Student& s) { s.deactivate(); }
    void viewReservations(const vector<Reservation>& reservations);
};
int main()
{

    return 0;
}
