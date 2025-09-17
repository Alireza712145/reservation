#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <stdexcept>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>

using namespace std;

class Student;
class Reservation;
class ShoppingCard;
class Transaction;
class SessionManager;
class Storage;

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
    ReserveDay getSmallityDay() const {
        return SATURDAY;
    }


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

        int gettranscationID()const{return _transactionID;}  //get transaction
        TransactionType gettype()const {return type; }
        TransactionStatus getstatus()const {return status;}
        string gettracking()const{return _trackingCode;}  //get trackingcode
        float getamount()const{return _amount;}  //get amount
        time_t getcreatedAt()const{return _createdAt;}   // get createdAt

} ;

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

        Transaction confirm(float totalamo){
        static int Transactioncount = 1000;
        string trackingcode = "TRK" + to_string(Transactioncount++);

        Transaction t(Transactioncount,RESERVATION_PAYMENT,SUCCESS,trackingcode,totalamo,time(nullptr));
        return t;
        }
        void cancelReservation(int id) {
        for (int i = 0; i < _reservations.size(); ++i) {
        if (_reservations[i].getreservation_id() == id) {
            _reservations.erase(_reservations.begin() + i);
            return;
            }
        }
        }

};

    void ShoppingCard::addReservation(Reservation& reservation){
            _reservations.push_back(reservation);
        }
    void ShoppingCard::viewShoppingCartItems(){
        cout << "Reservation List: \n";
            for( auto& res : _reservations){
                cout << "ID: " << res.getreservation_id() << endl;

            }
        }
    void ShoppingCard::Clear(){
            _reservations.clear();
        }


class Student :public User{

    int user_id;
    string student_id,name,email;
    float balance;
    bool is_active;
    vector <Reservation> reservations ;
    string _phone;
    string password;
    ShoppingCard* cart;
    vector<Transaction> recentTransactions;


public:

    Student(int _user =0000000000 , string _student = "0000000000", string _name = "ali", string _email = "....@email.com", float _balance = 00000.00, bool _active = false, vector<Reservation> res2 = {}, string phone = "0900000000",string _password = " ")
    :user_id(_user),student_id(_student),name(_name),email(_email),balance(_balance),is_active(_active), reservations(res2), _phone(phone),password(_password){};
    //سازنده
    void setPassword(const string& p) {
        std::hash<string> hasher;
        password = to_string(hasher(p));
 }

    int getuser_id(){return user_id;}      //get user_id
    string getstudent_id(){return student_id;} //get student_id
    string getname(){return name;}         //get name
    string getemail(){return email;}       //get email
    float getbalance(){return balance;}    //get balance
    bool getis_active(){return is_active;} //get active
    vector<Reservation> getresrvation(){return reservations;} // get reservation
    string getphone(){return _phone;}  //get phone

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

    bool checkPassword(const string& input) const {
       std::hash<string> hasher;
       return password == to_string(hasher(input));
    }
    void confirmCart();
    vector<Transaction> getRecentTransactions() const { return recentTransactions; }

    void addToCart( Reservation& r);

    ShoppingCard* getshoppingcard() const {
    return cart;
    }
    void increaseBalance(int amount) {
    balance += amount;
    }
    void saveTransactionsToCSV(const string& filename) const;

     void saveReservationsToCSV(const string& filename) const;


};
    void Student::confirmCart(){
        float total = 0;
        vector<Reservation> items = cart->getReservation();
        for (const auto& r : items)
            total += r.getMeal().getprice();

        if (balance < total) return;

        balance -= total;
        Transaction tx = cart->confirm(total);
        recentTransactions.push_back(tx);

        for (const auto& r : items)
            reservations.push_back(r);

        cart->Clear();

    }
    void Student::reserve_meal(const Meal& meal){
        if (!meal.getactive()) {
        cout << "no active food.\n";
        return;
    }

    if (balance < meal.getprice()) {
        cout << "price no reserved.\n";
        return;
    }

    }

     void Student::saveReservationsToCSV(const string& filename) const {
                    ofstream file(filename);
                    for (const auto& r : reservations) {
                        file << r.getreservation_id() << ","
                             << r.getMeal().getmeal_id() << ","
                             << r.getdiningHall().gethall_id() << ","
                             << r.getcreated() << "\n";
                    }
                }
    void Student::print()
    {   cout << "user id= \t" << getuser_id()
        << "\n student id= \t" << getstudent_id()
        << "\n name student= \t" << getname()
        << "\n email = \t" << getemail()
        << "\n balance = \t" << getbalance()
        << "\n is active = \t" << getis_active()
        << "\n phone = /t" << getphone();
    }


    void Student::addToCart( Reservation& r) {
    if (!cart) cart = new ShoppingCard({});
    cart->addReservation(r);
    }

    void Student::saveTransactionsToCSV(const string& filename) const {
        ofstream file(filename);
            for (const auto& tx : recentTransactions) {
                file << tx.gettranscationID() << ","
                     << tx.gettype() << ","
                     << tx.getstatus() << ","
                     << tx.gettracking() << ","
                     << tx.getamount() << ","
                     << tx.getcreatedAt() << "\n";
            }
        }

    void ShoppingCard::removeReservation(int ID){
        for (int i = 0; i < _reservations.size(); ++i) {
        if (_reservations[i].getcreated() == i) {
            _reservations.erase(_reservations.begin() + i);
            return;
                }
            }
        }

    enum SessionStatus {
        ACTIVE,
        INACTIVE
    };

class SessionBase{

    time_t _createdAt;
    SessionStatus _status;

protected:
       time_t _lasttimeLogin;

public:
    SessionBase(time_t create = time(nullptr), time_t lasttime = time(nullptr)) : _createdAt(create), _lasttimeLogin(lasttime){};



    virtual void load_session() = 0;
    virtual void save_session() = 0;

    virtual void login(string, string) = 0;
    virtual void logout() = 0;

    time_t getcreatedAt(){return _createdAt;}
    time_t getlasttimelogin(){return _lasttimeLogin;}

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
        static SessionManager _instance;

    public:
         static SessionManager& instance();

        void load_session() override {
            ifstream in("student_session.txt");
            string line;
            if (getline(in, line)) {
                stringstream ss(line);
                int id;
                time_t lastLogin;
                char comma;
                ss >> id >> comma >> lastLogin;
                _studentID = id;
                _lasttimeLogin = lastLogin;
            }
        }
        void save_session() override {
            ofstream out("student_session.txt");
            out << _studentID << "," << time(nullptr) << "\n";
        }
            SessionManager(){
            _currentStudent = nullptr;
            _shopping_cart = nullptr;
            _studentID = -1;
            _isLoggedIn = false;
        }
          Student *currentStudent(){return _currentStudent;}
          ShoppingCard *shoppingCart(){return _shopping_cart;}
        int getStudentID() const {return _studentID;}
        bool isLoggedIn()const {return _isLoggedIn;}

        vector<Student> loadStudentsFromCSV(const string& filename) {
            vector<Student> students;
            ifstream file("studentsCsvFile");
            string line;

            while (getline(file, line)) {
                stringstream ss(line);
                string id, name, email, password, phone;
                float balance;
                bool active;

                getline(ss, id, ',');
                getline(ss, name, ',');
                getline(ss, email, ',');
                getline(ss, password, ',');
                ss >> balance; ss.ignore();
                ss >> active; ss.ignore();
                getline(ss, phone, ',');

                Student s(stoi(id), id, name, email, balance, active, {}, phone);
                s.setPassword(password);
                students.push_back(s);
            }

                    return students;
            }
             void func();
             void login(const std::string username,const std::string password)
                {
              auto students = loadStudentsFromCSV("studentsCsvFile.csv");
                for (auto& s : students) {
                    if (s.getname() == username && s.checkPassword(password)) {
                        _currentStudent = new Student(s);
                        _shopping_cart = new ShoppingCard({});
                        _studentID = s.getuser_id();
                        _isLoggedIn = true;
                        cout << "welcome.\n";
                        return;
                    }
         }
            }
         void logout();

    };
};

         void StudentSession::SessionManager::logout(){
             _currentStudent = nullptr;
            _shopping_cart = nullptr;
            _studentID = -1;
            _isLoggedIn = false;
            cout << "exit.\n";
         }


class Storage {
    int _mealIDCounter = 0;
    int _diningHallIDCounter = 0;
    vector<Meal> allMeals;
    vector<DiningHall> allDiningHalls;

    Storage() = default;
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;

public:
    static Storage& instance() {
        static Storage s;
        return s;
    }

    void addMeal(const string& name, float price, bool isActive) {
    auto type = Meal().getmeali();       // مقدار meal_type::a
    auto day = Meal().getSmallityDay();            // مقدار ReserveDay::SMALLITY
    vector<string> items;

    allMeals.emplace_back(++_mealIDCounter, name, price, type, items, isActive, day, isActive);
}

    void addDiningHall(const string& name, const string& address, int capacity) {
        allDiningHalls.emplace_back(++_diningHallIDCounter, name, capacity, address);
    }

    const vector<Meal>& getMeals() const { return allMeals; }
    const vector<DiningHall>& getDiningHalls() const { return allDiningHalls; }

    Meal findMeal(int id) const {
        for (const auto& m : allMeals)
            if (m.getmeal_id() == id) return m;
        return Meal(); // پیش‌فرض
    }

    DiningHall findHall(int id) const {
        for (const auto& h : allDiningHalls)
            if (h.gethall_id() == id) return h;
        return DiningHall();
    }
    //ذخیره غذاها
    void saveMealsToCSV(const string& filename) {
        ofstream file(filename);
        for (const auto& meal : allMeals) {
            file << meal.getmeal_id() << ","
                 << meal.getname() << ","
                 << meal.getprice() << ","
                 << meal.getactive() << "\n";
            }
        }
        //ذخیره سالن غذا خوری
    void saveDiningHallsToCSV(const string& filename) {
        ofstream file(filename);
        for (const auto& hall : allDiningHalls) {
            file << hall.gethall_id() << ","
                 << hall.getname() << ","
                 << hall.getcapacity() << ","
                 << hall.getaddress() << "\n";
            }
        }

                    void loadMealsFromCSV(const string& filename) {
            ifstream file(filename);
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                int id;
                string name;
                float price;
                bool active;

                ss >> id; ss.ignore();
                getline(ss, name, ',');
                ss >> price; ss.ignore();
                ss >> active;

                auto type = Meal().getmeali();         // مقدار پیش‌فرض
                auto day = Meal().getSmallityDay();    // مقدار پیش‌فرض
                vector<string> items;

                allMeals.emplace_back(id, name, price, type, items, active, day, active);
            }
        }
            void loadDiningHallsFromCSV(const string& filename) {
                ifstream file(filename);
                string line;
                while (getline(file, line)) {
                    stringstream ss(line);
                    int id, capacity;
                    string name, address;

                    ss >> id; ss.ignore();
                    getline(ss, name, ',');
                    ss >> capacity; ss.ignore();
                    getline(ss, address);

                    allDiningHalls.emplace_back(id, name, capacity, address);
                }
            }


};


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
    void run();
    void exit();


};

    void Panel::run() {
        int choice;
        do {
            showMenu();
            cin >> choice;
            Action(choice);
        } while (choice != 0);
    }

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
        auto s = session->currentStudent();
    if (s) cout << s->getname() << " | " << s->getstudent_id() << " | " << s->getbalance() << " toman\n";
    }

    void Panel::checkbalance(){
        auto s = session->currentStudent();
        if (s) cout << "price: " << s->getbalance() << " toman\n";
        }
    void Panel::viewReservations() {
        for (auto& r : session->currentStudent()->getresrvation())
        cout << "- " << r.getdiningHall().getname() << " | " << r.getcreated() << "\n";
    }
    void Panel::viewshppingcard() {
       for (auto& r : session->currentStudent()->getshoppingcard()->getReservation())
        cout << "- " << r.getdiningHall().getname() << " | " << r.getcreated() << "\n";
    }
    void Panel::addToShoppingCart() {
        int hallID, mealID;
        cin >> hallID >> mealID;
        auto hall = Storage::instance().findHall(hallID);
        auto meal = Storage::instance().findMeal(mealID);
        if (!meal.getactive()) return;


        Reservation r;
        session->currentStudent()->addToCart(r);
    }
    void Panel::confirmShoppingCart() {
        session->currentStudent()->confirmCart();
    }
    void Panel::removeShoppingCartItem() {
       int id; cin >> id;
    session->currentStudent()->getshoppingcard()->removeReservation(id);

    }
    void Panel::increaseBalance() {
        int amount;
        cout << "price ++: ";
        cin >> amount;

        session->currentStudent()->increaseBalance(amount);
        cout << "price ++.\n";
    }
    void Panel::cancelReservation(int id) {
        session->currentStudent()->getshoppingcard()->cancelReservation(id);
        cout << "reserv laghv.\n";
    }
    void Panel::viewRecentTransactions() {
        vector<Transaction> txs = session->currentStudent()->getRecentTransactions();
        cout << "trakonesh:\n";
        for (Transaction t : txs) {
            cout << "- " << t.gettype() << ": " << t.getamount() << " price toman" << t.getcreatedAt() << endl;
        }
    }

    void Panel::exit(){
        cout << " exit to system \n ";
        exit();
    }


int main()
{
    StudentSession::SessionManager::instance().load_session();   // برای دانشجو

   // AdminSession::SessionManager::instance().load_session();  // برای ادمین

    Storage::instance().loadMealsFromCSV("meals.csv");
    Storage::instance().loadDiningHallsFromCSV("dining_halls.csv");


    int userType;
    cout << "به سامانه رزرو غذا خوش آمدید!\n";
    cout << "نوع کاربر را انتخاب کنید:\n";
    cout << "1. دانشجو\n";
    cout << "2. ادمین\n";
    cout << "گزینه: ";
    cin >> userType;

    if (userType == 1) {

        StudentSession::SessionManager::instance().load_session();


        Panel studentPanel;
        studentPanel.run();


        StudentSession::SessionManager::instance().save_session();
    }
    else {
        cout << "chosse false.\n";
    }

    return 0;
}
