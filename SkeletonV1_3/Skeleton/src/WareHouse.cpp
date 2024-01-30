#include <iostream>
#include <fstream>
#include "../include/WareHouse.h"
#include "../include/Action.h"
using namespace std;
#include <sstream>

WareHouse::WareHouse(const string &configFilePath)
:  isOpen(false), customerCounter(-1), volunteerCounter(-1),orderCounter(-1), 
fake_Customer(new CivilianCustomer(-1,"-1",-1,-1)), fake_Order(new Order(-1,-1,-1)), fake_volunteer(new CollectorVolunteer(-1,"-1",-1))
{Initiatefile(configFilePath);}

//copy constarctor
WareHouse::WareHouse(const WareHouse& other)
: isOpen(other.isOpen), customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter), orderCounter(other.orderCounter),
fake_Customer(other.fake_Customer->clone()), fake_Order(other.fake_Order->clone()), fake_volunteer(other.fake_volunteer->clone()) {
    // Copy action log
    for(BaseAction* act: other.actionsLog) {
        actionsLog.push_back(act->clone());
    }
    // Copy volunteers
    for(Volunteer* vol: other.volunteers) {
        volunteers.push_back(vol->clone());
    }
    // Copy pending orders
    for(Order* order: other.pendingOrders) {
        pendingOrders.push_back(order->clone());
    }
    // Copy inProcess orders
    for(Order* order: other.inProcessOrders) {
        inProcessOrders.push_back(order->clone());
    }
    // Copy completed orders
    for(Order* order: other.completedOrders) {
        completedOrders.push_back(order->clone());
    }
    // Copy customers
    for(Customer* customer: other.customers) {
        customers.push_back(customer->clone());
    }
}
 //move constarctor
WareHouse::WareHouse(const WareHouse&& other) noexcept : 
isOpen(other.isOpen), customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter), orderCounter(other.orderCounter),
fake_Customer(other.fake_Customer), fake_Order(other.fake_Order), fake_volunteer(other.fake_volunteer),actionsLog (other.actionsLog),volunteers(other.volunteers),
pendingOrders(other.pendingOrders), inProcessOrders(other.inProcessOrders), completedOrders(other.completedOrders), customers(other.customers) {
    actionsLog.clear();
    volunteers.clear();
    pendingOrders.clear();
    inProcessOrders.clear();
    completedOrders.clear(); 
    customers.clear();
    fake_volunteer = nullptr;
    fake_Customer  = nullptr;
    fake_Order = nullptr;
}

void WareHouse::Initiatefile(string file){
    string line;
    vector<string> words;
    string word;
    ifstream MyReadFile(file);
    while (getline (MyReadFile, line)) {
        words.clear();     
        istringstream iss(line);
        iss >> word;
        if(word == "customer") {
            for(int i = 0; i < 4; i++) {
                iss >> word;
                words.push_back(word);
            } 
            if (words[1] == "soldier") {
                customers.push_back(new SoldierCustomer(getNewcustomerID(), words[0], stoi(words[2]),stoi(words[3])));
                }
            else {
                customers.push_back(new CivilianCustomer(getNewcustomerID(), words[0], stoi(words[2]),stoi(words[3])));
            }     
        }
        if(word == "volunteer") {
            for(int i = 0; i < 5; i++) {
                iss >> word;
                words.push_back(word);
            } 
            if (words[1] == "collector") {
                volunteers.push_back(new CollectorVolunteer(getNewvolunteerID(), words[0],stoi(words[2])));
                }
            else if(words[1] == "LimitedCollectorVolunteer") {
                volunteers.push_back(new LimitedCollectorVolunteer(getNewvolunteerID(), words[0], stoi(words[2]),stoi(words[3])));
            }
            else if (words[1] == "driver") {
                volunteers.push_back(new DriverVolunteer(getNewvolunteerID(), words[0],stoi(words[2]),stoi(words[3])));
            }
             else if(words[1] == "LimitedDriverVolunteer") {
                volunteers.push_back(new LimitedDriverVolunteer(getNewvolunteerID(), words[0], stoi(words[2]),stoi(words[3]), stoi(words[4])));
            }     
        }
    }
    MyReadFile.close();
}

void WareHouse::start(){
    open();
    cout << "Warehouse is open!" << endl;
    while(isOpen){
        

    }
}

void WareHouse::addOrder(Order* order){
    pendingOrders.push_back(order);
}

void WareHouse::addAction(BaseAction* action){
    actionsLog.push_back(action);
}

void WareHouse::addCustomer(Customer* customer){
    customers.push_back(customer);
}

Customer& WareHouse::getCustomer(int customerId) const {
    for(Customer* c: customers) {
        if(c->getId() == customerId) {
            return *c;
        }
    }
    return *fake_Customer;
}

Volunteer& WareHouse::getVolunteer(int volunteerId) const{
    for(Volunteer* v:volunteers){
        if(v->getId() == volunteerId){ return *v;}}
    return *fake_volunteer;
}

Order& WareHouse::getOrder(int orderId) const{
    for(Order* o:pendingOrders){
        if(o->getId() == orderId){ return *o;}}
    for(Order* o:inProcessOrders){
        if(o->getId() == orderId){ return *o;}}
    for(Order* o:completedOrders){
        if(o->getId() == orderId){ return *o;}}
    return *fake_Order;
}

const vector<BaseAction*>& WareHouse::getActions() const {
    return actionsLog;
}
// Changes isOpen status and exit the loop and finishes the program(free all memory as well)
void WareHouse::close() {
    isOpen=false;
    delete this;
}

int WareHouse::getNewcustomerID() {
    customerCounter++;
    return customerCounter;
}

int WareHouse::getNewvolunteerID() {
    volunteerCounter++;
    return volunteerCounter;
}

int WareHouse::getNewOrderId(){
    orderCounter++;
    return orderCounter;
}

vector<Order*>& WareHouse::getPendingOrders(){
    return pendingOrders;
}

vector<Order*>& WareHouse::getInProcessOrders(){
    return inProcessOrders;
}

vector<Order*>& WareHouse::getCompletedOrders(){
    return completedOrders;
}

vector<Customer*>& WareHouse::getCustomers(){
    return customers;
}
vector<Volunteer*>& WareHouse::getVolunteers(){
    return volunteers;
}

int WareHouse::getOrderCounter(){
    return orderCounter;
}


// Copy assingment
void WareHouse::operator=(const WareHouse &other){
    if(&other != this) {
        isOpen = other.isOpen;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        orderCounter = other.orderCounter;
        fake_volunteer = other.fake_volunteer->clone();
        fake_Customer = other.fake_Customer->clone();
        fake_Order = other.fake_Order->clone();
        // Clear action log
        for(BaseAction* a:actionsLog){delete(a);}
        actionsLog.clear();
        // Copy action log
        for(BaseAction* act: other.actionsLog) {
            actionsLog.push_back(act->clone());
        }
        // Copy volunteers
        for(Volunteer* v:volunteers){delete(v);}
        volunteers.clear();
        for(Volunteer* vol: other.volunteers) {
            volunteers.push_back(vol->clone());
        }
        // Copy pending orders
        for(Order* o:pendingOrders){delete(o);}
        pendingOrders.clear();
        for(Order* order: other.pendingOrders) {
            pendingOrders.push_back(order->clone());
        }
        // Copy inProcess orders
        for(Order* o:inProcessOrders){delete(o);}
        inProcessOrders.clear();
        for(Order* order: other.inProcessOrders) {
            inProcessOrders.push_back(order->clone());
        }
        // Copy completed orders
        for(Order* o:completedOrders){delete(o);}
        completedOrders.clear(); 
        for(Order* order: other.completedOrders) {
            completedOrders.push_back(order->clone());
        }
        // Copy customers
        for(Customer* c:customers){delete(c);}
        customers.clear();
        for(Customer* customer: other.customers) {
            customers.push_back(customer->clone());
        }
        
       
    }

}
//move assigment
WareHouse& WareHouse::operator=(WareHouse&& other) noexcept {
    if(&other != this) {
        // Primitive varibles
        isOpen = other.isOpen;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        orderCounter = other.orderCounter;

        // Objects
        delete fake_volunteer;
        delete fake_Customer;
        delete fake_Order;
        fake_volunteer = other.fake_volunteer;
        fake_Customer = other.fake_Customer;
        fake_Order = other.fake_Order;
        other.fake_volunteer = nullptr;
        other.fake_Customer = nullptr;
        other.fake_Order = nullptr;

        // Vectors
        for(BaseAction* a:actionsLog){delete(a);} // Delete myself
        actionsLog.clear(); // Clear myself
        actionsLog = other.actionsLog; // Assingment
        other.actionsLog.clear(); //nullptr the other

        for(Order* o:pendingOrders){delete(o);} 
        pendingOrders.clear();
        pendingOrders = other.pendingOrders;
        other.pendingOrders.clear();

        for(Order* o:inProcessOrders){delete(o);} // Delete myself
        inProcessOrders.clear();// Clear myself
        inProcessOrders = other.inProcessOrders;// Assingment
        other.inProcessOrders.clear(); //nullptr the other

        for(Order* o:completedOrders){delete(o);}
        completedOrders.clear();
        completedOrders = other.completedOrders;
        other.completedOrders.clear();
        
        for(Volunteer* v:volunteers){delete(v);} // Delete myself
        volunteers.clear();// Clear myself
        volunteers = other.volunteers;// Assingment
        other.volunteers.clear(); //nullptr the other
        
        for(Customer* c:customers){delete(c);} // Delete myself
        customers.clear();// Clear myself
        customers = other.customers;// Assingment
        other.customers.clear(); //nullptr the other            
    }
} 

WareHouse::~WareHouse() {
    for(Order* o:pendingOrders) {
        if(o != nullptr) {delete(o);}} 

    for(Order* o:inProcessOrders){
        if(o != nullptr) {delete(o);}} 

    for(Order* o:completedOrders){
        if(o != nullptr) {delete(o);}} 

    for(Volunteer* v:volunteers){
        if(v != nullptr) {delete(v);}} 

    for(Customer* c:customers){
        if(c != nullptr) {delete(c);}} 

    for(BaseAction* a:actionsLog){
        if(a != nullptr) {delete(a);}} 
    // Default delete     
    delete(this);   
}

int main(int argc, char** argv) {
    cout << "Entering main:" << endl;
    string configurationFile = argv[1];
    cout << configurationFile << endl;
    WareHouse wareHouse(configurationFile);
    wareHouse.start();
    return 0;
}