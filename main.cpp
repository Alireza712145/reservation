#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <stdexcept>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

class Student;
class Reservation;
class ShoppingCard;

class User {
    int user_id;
    string name ;
    string last_name;
    string hassedPassword;
public:
    User(int _user = 0000000000, string _name ="ali", string _last_name = "fatah",string _hassedPassword = "******")
    :user_id(_user), name(_name), last_name(_last_name), hassedPassword(_hassedPassword){};

    int getuser(){return user_id;}  //get user
    string getname(){return name;} //get name
    string getlastname(){return last_name;}  //get last name
    string gethassedPassword(){return hassedPassword;}  //get hassedPassword

    virtual void print() const;            //const
   // virtual void getType();


};

void User::print()const{
  cout << "User print called." << endl;}

class Admin : public User{

public:
    void print() const;

  //  void getType();
};

void Admin::print()const{}

class Meal{
    int meal_id;
    string name;
    float price;
    enum meal_type{
    a, b ,c
    }meali;
    vector<string> side_items;
    bool isActive;
    enum ReserveDay{
        SATURDAY, SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY
    }reserveday;
    bool _isActive;

public:
    Meal(int _id = 000000, string name2 = "food", float _price = 0000.00,meal_type meal2 = a ,vector<string> _item = {}, bool active2 = false, ReserveDay res3 = ReserveDay(), bool active = false)
    :meal_id(_id), name(name2), price(_price), meali(meal2), side_items(_item), isActive(active2), reserveday(res3), _isActive(active) {};


    int getmeal_id()const {return meal_id;} //get meal id
    string getname()const {return name;} //get name
    float getprice()const {return price;} //get price
    meal_type getmeali()const {return meali;} //get meal_type
    vector<string> getside_item(){return side_items;} // get side_item
    ReserveDay getreserveday(){return reserveday;}  //get reserve day
    bool getactive()const {return isActive;}          // get active

    friend ostream &operator <<(ostream &out,const Meal &me);

    void print (); // f-print

    void update_price(float new_price);

    void add_side_item(string item);

    bool active(){return _isActive;};
    void activate();
    void deactivate();
    void addsideitem(string _set){side_items.push_back(_set);}
    void addprice(float _set){ price = _set; }
};

    ostream &operator <<(ostream &out, const Meal &me){
        out << "meal id=" << me.getmeal_id() << "" << me.getname() << "  " << me.getprice() << " " << me.getactive();
        return out;
    }
    void Meal::print(){
        cout << "meal id=\t" << getmeal_id()
        << "\n name =\t" << getname()
        << "\n price \t" << getprice()
        << "\n activate = \t" << getactive();
    }

    void Meal::update_price(float new_price){
        price = new_price;
    }

    void Meal::add_side_item(string item){
        side_items.push_back(item);
    }

    void Meal::activate(){
        try{isActive = true;} catch(...){cout << "is true";}
        isActive = true;}
    void Meal::deactivate(){
        try{isActive = false;} catch(...){cout << "is false";
        isActive = false;}}



class DiningHall{
    int hall_id, capacity;
    string name, address;
public:
    DiningHall(int _id = 00000, string name2 = "self", int _capacity = 00000, string addres = "........")
    :hall_id(_id), name(name2),capacity(_capacity), address(addres){};

    int gethall_id()const{return hall_id;} //get hall id
    int getcapacity()const{return capacity;} //get capacity
    string getname()const{return name;} //get name
    string getaddress()const{return address;} //get address

    void print();
     friend ostream &operator <<(ostream& os, const DiningHall& hall);
};

    ostream& operator<<(ostream& os, const DiningHall& hall) {
    os << hall.getname() << " (" << hall.getcapacity() << ")";
    return os;
}

void DiningHall::print(){
    cout << "hall id=\t" << gethall_id()
    << "\n name= \t" << getname()
    << "\n capacity =\t" << getcapacity()
    << "\n address=\t" << getaddress();
}

class Reservation{

    int reservation_id;
    DiningHall dHall;
    Meal meal;
    time_t created_at;
    enum status{
        FAILED,
        CANCELLED,
        SUCCESS
    }_status;
    bool RStatus;
public:

    Reservation(int reserv_id = 00000, DiningHall Dining = DiningHall(), Meal mea = Meal(), time_t _create = time(nullptr), status _status2 = FAILED, bool rstatus = false)
    :reservation_id(reserv_id),dHall(Dining),meal(mea),created_at(_create), _status(_status2), RStatus(rstatus){};

    // سازنده
    int getreservation_id()const{return reservation_id;} //get reservation_id
    //Student getstudent() const {return student;} //get student
    DiningHall getdiningHall() const{ return dHall;} //get dHall
    Meal getMeal() const{ return meal;} //get meal
    time_t getcreated() const{return created_at;} //get created_at
    status getstatus() const{ return _status;} //get status
    bool getrstatus()const {return RStatus;}  //get RStatus

    void print() ;           // fprint
    bool Cancel();         // fcancel

     friend ostream &operator <<(ostream& os, const DiningHall& hall);
};

        ostream &operator<<(ostream& os, const Reservation& reserv) {
        os << reserv.getdiningHall() << " (" << reserv.getreservation_id() << ")";
        return os;
    }
    void Reservation::print() {              // fprint
        cout << "reservation id=\t" << getreservation_id()
        <<  "\n time = \t" << getcreated();
    }

    bool Reservation::Cancel(){         //f cancel
        switch (_status) {
            case CANCELLED:
                RStatus = false;
                return false;
            case FAILED:
            case SUCCESS:
                RStatus = true;
                return true;
            default:
                return false;
        }
    }



class Student :public User{

    int user_id;
    string student_id,name,email;
    float balance;
    bool is_active;
    vector <Reservation> reservations ;
    string _phone;
    ShoppingCard* cart;
public:

    Student() {
        cart = new ShoppingCard();
    }

    Student(int _user =0000000000 , string _student = "0000000000", string _name = "ali", string _email = "....@email.com", float _balance = 00000.00, bool _active = false, vector<Reservation> res2 = {}, string phone = "0900000000")
    :user_id(_user),student_id(_student),name(_name),email(_email),balance(_balance),is_active(_active), reservations(res2), _phone(phone){};
    //سازنده
    int getuser_id(){return user_id;}      //get user_id
    string getstudent_id(){return student_id;} //get student_id
    string getname(){return name;}         //get name
    string getemail(){return email;}       //get email
    float getbalance(){return balance;}    //get balance
    bool getis_active(){return is_active;} //get active
    vector<Reservation> getresrvation(){return reservations;} // get reservation
    string getphone(){return _phone;}  //get phone
    ShoppingCard* getshoppingcard()const{return cart;}

    void print();           //const               //تابع print

    void reserve_meal(const Reservation& reseve);
    void reserve_meal(const Meal& meal);          //تابع رزرو غذا
    bool cancel_reservation( Reservation& reservation);  // تابع کنسل رزرو

    void activate (){ is_active =true;
        cout << "is active \n";}

    void deactivate(){is_active = false;
        cout << "is false";}

    bool isActive()
        {return is_active;}

};

    void Student::reserve_meal(const Meal& meal){
      //  if(balance >= meal.getprice() && find(reservations.begin(), reservations.end(), meal) == reservations.end())
        //    int new_reservations = reservations.size() +1;
          //  time_t _created = time(nullptr);
           // string dhall = "self";
            //Reservation new_list_reserv(name, _created, new_reservations, dhall, meal);
            //reservations.push_back(new_list_reserv);  }
        //else { cout << "balance no life="; }
        if (!meal.getactive()) {
        cout << "no active food.\n";
        return;
    }

    if (balance < meal.getprice()) {
        cout << "price no reserved.\n";
        return;
    }

    }

   // bool Student::cancel_reservation( Reservation& reservation){
   //     if(reservation.Cancel() == Reservation::CANCELLED)
   //          {return false;}
//
  //      reservation.Cancel();
  //  }

    void Student::print()
    {   cout << "user id= \t" << getuser_id()
        << "\n student id= \t" << getstudent_id()
        << "\n name student= \t" << getname()
        << "\n email = \t" << getemail()
        << "\n balance = \t" << getbalance()
        << "\n is active = \t" << getis_active()
        << "\n phone = /t" << getphone();
    }
enum SessionStatus {
    ACTIVE,
    INACTIVE
};

class SessionBase{

    time_t _createdAt;
    time_t _lasttimeLogin;
    SessionStatus _status;

public:
    SessionBase(time_t create = time(nullptr), time_t lasttime = time(nullptr)) : _createdAt(create), _lasttimeLogin(lasttime){};

    virtual void load_session() = 0;
    virtual void save_session() = 0;

    virtual void login(string, string) = 0;
    virtual void logout() = 0;

    time_t getcreatedAt(){return _createdAt;} // get created At
    time_t getlasttimelogin(){return _lasttimeLogin;} //get last time login

};
namespace AdminSession{

    class sessionManager : public SessionBase {


    void func();
    };
}

namespace StudentSession{

    class SessionManager : public SessionBase{

        Student *_currentStudent;
        ShoppingCard *_shopping_cart;
        int _studentID;
        bool _isLoggedIn;

    public:
        //-void load_session() : override
        //-void save_session() : override
            SessionManager(){
            _currentStudent = nullptr;
            _shopping_cart = nullptr;
            _studentID = -1;
            _isLoggedIn = false;
        }
          Student *currentStudent();
          ShoppingCard *shoppingCart();
        int getStudentID() const {return _studentID;}


         void func();
         void login(string username, string password);
         void logout();

    };
    };
/*void SessionManager::login(string username, string password){
    for (Student& s : allStudents) {
        if (s.getname() == username && s.getPassword() == password) {
            _currentStudent = &s;
            _studentID = s.getID();
            cout << "vorod mvafagh." << endl;
            return;
        }
    }
    cout << "username or password false." << endl;

    }

*/
class ShoppingCard{

    vector<Reservation> _reservations;

public:
    ShoppingCard(vector<Reservation> _res):_reservations(_res){};

    void addReservation(Reservation& reservation);
    void removeReservation(int ID);
    void viewShoppingCartItems();
    const vector<Reservation>& getCart();
    void Clear();

    vector<Reservation> getReservation() const{ return _reservations; }  // get vector reservation

    // Transaction confirm()
};

    void ShoppingCard::addReservation(Reservation& reservation){
            _reservations.push_back(reservation);
        }
    void ShoppingCard::viewShoppingCartItems(){
        cout << "Reservation List: \n";
            for( auto& res : _reservations){
                cout << "ID: " << res.getreservation_id() << endl;
                // << "- Detail: " << res.datails << endl;
            }
        }
    void ShoppingCard::Clear(){
            _reservations.clear();
        }


   // void ShoppingCard::removeReservation(int ID){
    //            reservations_shoppingCard.erase(
   //     remove(reservations_shoppingCard.begin(), reservations_shoppingCard.end(), ID),
    //    reservations_shoppingCard.end());
   //     }


class Panel{

public:

    StudentSession::SessionManager* session;


    void Action(int _set);
    void showMenu();
    void showStudentInfo();
    void checkbalance();
    void viewReservations();
    void viewshppingcard();
    void addReservation(Reservation &res);
    void addToShoppingCart();
    void confirmShoppingCart();
    void removeShoppingCartItem();
    void increaseBalance();
    void viewRecentTransactions();
    void cancelReservation(int _canel);

    void exit();


};


void Panel::Action(int choice) {
    switch (choice) {
        case 1:
            checkbalance();
            break;
        case 2:
            addToShoppingCart();
            break;
        case 3:
            viewshppingcard();
            break;
        case 4:
            confirmShoppingCart();
            break;
        case 5:
            viewReservations();
            break;
        case 6:
            showStudentInfo();
            break;
        case 7:
            increaseBalance();
            break;
        case 8:
            removeShoppingCartItem();
            break;
        case 9:
            exit();
            break;
        default:
            cout << "choose no taiid.\n";
    }
}

    void Panel::showMenu() {
        cout << "\n منوی اصلی \n";
        cout << "1. بررسی اعتبار\n";
        cout << "2. رزرو سالن\n";
        cout << "3. مشاهده رزروها\n";
        cout << "4. خروج\n";
        cout << "لطفاً گزینه‌ای را انتخاب کنید: ";
    }
    void Panel::showStudentInfo() {
        Student* student = session->currentStudent();
            if (student != nullptr) {
                cout << "name: " << student->getname() << endl;
                cout << "number student: " << student->getstudent_id() << endl;
                cout << "etebar: " << student->getbalance() << " price" << endl;
            } else {
                cout << "no to student." << endl;
        }
    }

    void Panel::checkbalance(){
    Student *student = session->currentStudent();
         if (student != nullptr) {
                cout << "no price: " << student->getbalance() << " toman" << endl;
            } else {
                cout << "no student." << endl;
            }
        }
    void Panel::viewReservations() {
        vector<Reservation> list = session->currentStudent()->getresrvation();
        cout << "reserv you:\n";
        for (Reservation r : list) {
            cout << "- " << r.getdiningHall() << " in " << r.getcreated() << endl;
        }
    }
    void Panel::viewshppingcard() {
        vector<Reservation> cart = session->currentStudent()->getresrvation();
        cout << "sabad buy:\n";
        for (Reservation r : cart) {
            cout << "- " << r.getdiningHall() << " in " << r.getcreated() << endl;
        }
    }
  /*  void Panel::addToShoppingCart() {
        string hall=" ", time=" ";
        cout << "name hall: ";
        cin >> hall;
        cout << "time reserv: ";
        cin >> time;

        Reservation r((hall),_time(time) );
        session->currentStudent()->addToCart(r);
        cout << "reseerv to sabad ++.\n";
    }
    void Panel::confirmShoppingCart() {
        session->currentStudent()->confirmCart();
        cout << "reserv taiid.\n";
    }
    void Panel::removeShoppingCartItem() {
        int index;
        cout << "number remove: ";
        cin >> index;

        session->currentStudent()->removeItem(index);
        cout << "item remove.\n";
    }*/
    void Panel::increaseBalance() {
        int amount;
        cout << "price ++: ";
        cin >> amount;

        session->currentStudent()->increaseBalance(amount);
        cout << "price ++.\n";
    }
    void Panel::cancelReservation(int id) {
        session->currentStudent()->getShoppingCart()->cancelReservation(id);
        cout << "reserv laghv.\n";
    }
    void Panel::viewRecentTransactions() {
        vector<Transaction> txs = session.currentStudent()->getRecentTransactions();
        cout << "trakonesh:\n";
        for (Transaction t : txs) {
            cout << "- " << t.getType() << ": " << t.getAmount() << " price toman" << t.getDate() << endl;
        }
    }
    void Panel::viewRecentTransactions() {
        auto txs = session.currentStudent()->getRecentTransactions();
        cout << "trakonesh:\n";
        for (auto& t : txs)
            cout << "- " << t.getType() << ": " << t.getAmount() << "price " << t.getDate() << endl;
    }


    void Panel::exit(){
        cout << " exit to system \n "
        exit(0);
    }



enum TransactionType {
    INCREASE_BALANCE,
    RESERVATION_PAYMENT
};

enum TransactionStatus {
    PENDING,
    SUCCESS,
    FAILED
};

class Transaction{

    int _transactionID;
    TransactionType type;
    TransactionStatus status;
    string _trackingCode;
    float _amount;
    time_t _createdAt;

public:

    Transaction(int _trans = 000000,TransactionType _type = INCREASE_BALANCE,TransactionStatus _status = PENDING, string _track = "track", float amount = 0.00, time_t created = time(nullptr))
    :_transactionID(_trans),type(_type),status(_status),_trackingCode(_track), _amount(amount),_createdAt(created){};

    int gettranscationID(){return _transactionID;}  //get transaction
    TransactionType gettype()const {return type; }
    TransactionStatus getstatus()const {return status;}
    string gettracking(){return _trackingCode;}  //get trackingcode
    float getamount(){return _amount;}  //get amount
    time_t getcreatedAt(){return _createdAt;}   // get createdAt

} ;
/*
class Storage {
private:
    int _mealIDCounter = 0;
    int _diningHallIDCounter = 0;
    vector<Meal> allMeals;
    vector<DiningHall> allDiningHalls;

    // جلوگیری از ایجاد نمونه‌های اضافی
    Storage() = default;
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;

public:
    static Storage& instance() {
        static Storage storageInstance;
        return storageInstance;
    }

  //  void addMeal(const string& name, float price, bool isActive) {
  //      allMeals.emplace_back(++_mealIDCounter, name, price, isActive);
   // }
void addMeal(const string& name, float price, bool isActive) {
    allMeals.emplace_back(
        ++_mealIDCounter,  // meal_id
        name,              // name
        price,             // price
        {},                // side_items (خالی)
        isActive,          // isActive
        Meal(),            // استفاده از سازنده پیش‌فرض برای ReserveDay
        isActive           // _isActive
    );
}
    void addDiningHall(const string& name, const string& address, int capacity) {
        allDiningHalls.emplace_back(++_diningHallIDCounter, name, address, capacity);
    }

    void printMeals() const {
        cout << "Meals List:\n";
        for (const auto& meal : allMeals) {
            cout << "ID: " << meal.getmeal_id() << ", Name: " << meal.getname()
                      << ", Price: " << meal.getprice() << ", Active: " << (meal.getactive() ? "Yes" : "No") << endl;
        }
    }

    void printDiningHalls() const {
        cout << "Dining Halls List:\n";
        for (const auto& hall : allDiningHalls) {
            cout << "ID: " << hall.gethall_id() << ", Name: " << hall.getname()
                      << ", Address: " << hall.getaddress() << ", Capacity: " << hall.getcapacity() << endl;
        }
    }
};
*/



//StudentSession::SessionManager::func() {}
//StudentSession::SessionManager::func() {}

*/
int main()
{

Meal meal1(1, "Kebab", 45000.0);


    DiningHall hall1(1, "Main Hall", 200, "Campus A");

     if (hall1.getcapacity() <= 0) {
        cout << "Dining hall is full. Cannot reserve." << endl;
        return 0;
    }


    Student student1(1, "Ali");

    if (!meal1.getactive()) {
        cout << "Meal is not active. Cannot reserve." << endl;
    return 0;
    }


    Reservation r1(
        1,
        hall1,
        meal1,
        time(nullptr),
        r1.getstatus(),
        false
    );


                // نمایش اطلاعات رزرو
    cout << "Student " << student1.getname()
         << " reserved meal \" " << r1.getMeal().getname()
         << "\" in hall \"" << r1.getdiningHall().getname()
         << "\" [Reservation ID: " << r1.getreservation_id() << "]"
         << ", Status: " << (r1.getstatus() == r1.getstatus() ? "Failed" : "Success")
         << endl;




//  Storage& storage = Storage::instance();

  //  storage.addMeal("Pizza", 10.5, true);
  //  storage.addMeal("Burger", 8.0, false);
  //  storage.addDiningHall("Main Hall", "123 Street", 100);
 //   storage.addDiningHall("VIP Hall", "456 Avenue", 50);

  //  storage.printMeals();
  //  storage.printDiningHalls();

    return 0;
}
