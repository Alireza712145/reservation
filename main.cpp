#include <iostream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;


class Student{

private:

    int user_id;

    string student_id, name, email;

    float balance;

    bool is_active;

public:

    Student(int user_id = 123456789, string student_id = "4050608495", string name = "ali", string email = "example@gmail.com", float balance = 78.5, bool is_active = false)
    :user_id (user_id), student_id (student_id), name (name), email (email), balance (balance), is_active (is_active){}

    void setuser_id(int User_id);
    void setstudent_id(string Student_id_);
    void setname(string _name);
    void setemail(string _email);
    void setbalance(float _balance);
    void setis_active(bool _is_active);
    int getuser_id(){
        return user_id;
    }
    string getstudent_id(){
        return student_id;
    }
    string getname(){
        return name;
    }
    string getemail(){
        return email;
    }
    float getbalance(){
        return balance;
    }
    bool getis_active(){
        return is_active;
    }
    void print();

    bool cancel_reservation(int reservation_id){

        return true;
    }
};

void Student::print(){
    cout << "user_id =\t" << getuser_id() << endl;
    cout << "student_id =\t" << getstudent_id() << endl;
    cout << "name =\t" << getname() << endl;
    cout << "email ='t" << getemail() << endl;
    cout << "balance ='t" << getbalance() << endl;
    cout << "is_active =\t" << getis_active();
}
void Student::setuser_id(int User_id){
        user_id = User_id;
    }
void Student::setstudent_id(string Student_id_){
        student_id = Student_id_;}
void Student::setname(string _name){
        name = _name;}
void Student::setemail(string _email){
        email = _email;}
void Student::setbalance(float _balance){
        balance = _balance;}
void Student::setis_active(bool _is_active){
        is_active  = _is_active;}
// پایان کلاس student
//

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

class Meal{
private:
    int meal_id;
    string name;
    float price;
    enum meal_type{
    Breakfast, Lunch, Dinner};
    meal_type Meal_type;
    vector<string> side_items;

public:
    Meal()
    :meal_id(0), name("salad"), price(14500), Meal_type(Dinner){}
    void setmeal_id(int _meal_id);
    void setname(string _name);
    void setprice(float _price);
    void setmeal_type(meal_type _Meal_type);

    int getmeal_id(){
    return meal_id;}

    string getname(){
    return name;}

    float getprice(){
    return price;}

    meal_type getmeal_type(){
    return Meal_type;}

    void add_side_item(const string &item);

    void print();

    void updatePrice(float new_price);

};

void Meal::updatePrice(float new_price) {
        price = new_price;
    }

void Meal::setmeal_id(int _meal_id){
        meal_id = _meal_id;}
void Meal::setname(string _name){
        name = _name;}
void Meal::setprice(float _price){
    price = _price;}
void Meal::setmeal_type(meal_type _Meal_type){
    Meal_type = _Meal_type;}

void Meal::print(){
    cout << "meal_type=\t" << Meal_type <<endl;
    cout << "name =\t" << name << endl;
    cout << "meal id=\t" << meal_id << endl;
    cout << "price =\t" << price << endl;
}

void Meal::add_side_item(const string &item){
    side_items.push_back(item);
}
//
//پایان کلاس رزرو غذا
class Reservation{

private:

    int reservation_id;
    Student student;
    DiningHall dHall;
    Meal meal;
    enum Status { Active,cancelled };
    time_t created_at;
    Status status;

public:

    Reservation()
    :reservation_id (0), student(Student()), dHall(DiningHall()), meal (Meal()),status (Active), created_at(time(nullptr)){}

    void setreservation_id ( int Reservation_id );
    void setStudent (const Student &_student);
    void setDiningHall ( const DiningHall &_dHall);
    void setMeal (const Meal &_meal);
    void setstatus ( Status _status );
    void setcreated_at ( time_t _created_at );

    int getreservation_id(){
        return reservation_id;
    }
    Student getStudent(){
        return student;
    }
    DiningHall getDiningHall(){
        return dHall;
    }
    Meal getMeal(){
        return meal;
    }
    Status getstatus (){
        return status;
    }
    time_t getcreated_at(){
        return created_at;
    }
    void print();

    bool cancel();

    void reserve_meal(Meal meal){
    }
};

void Reservation::print(){
    cout << "reservation= \t" << getreservation_id() <<endl;
    cout << "status= \t" << getstatus() << endl;
    cout << "time reserve= \t" << getcreated_at() << endl;
    student.print();
    dHall.print();
    meal.print();
}

bool Reservation::cancel(){
    if(status == cancelled)
        {cout << true; }
    else if(status == Active)
        {cout << false;}
}

void Reservation::setreservation_id ( int Reservation_id ){
        reservation_id = Reservation_id;}
void Reservation::setStudent (const Student &_student){
        student = _student;}
void Reservation::setDiningHall ( const DiningHall &_dHall ){
        dHall = _dHall;}
void Reservation::setMeal (const Meal &_meal){
        meal = _meal;}
void Reservation::setstatus ( Status _status ){
        status = _status;}
void Reservation::setcreated_at ( time_t _created_at ){
        created_at = _created_at;}
// پایان کلاس رزرو
//

int main()
{

    return 0;
}
