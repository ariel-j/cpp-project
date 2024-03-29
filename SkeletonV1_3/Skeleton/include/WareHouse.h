#pragma once
#include <string>
#include <vector>
#include "Order.h"
#include "Customer.h"
#include "Volunteer.h"

class BaseAction;           
class Volunteer;

// Warehouse responsible for Volunteers, Customers Actions, and Orders.


class WareHouse {

    public:
        WareHouse(const string &configFilePath); 
        WareHouse(const WareHouse& other); //copy constarctor
        WareHouse(const WareHouse&& other) noexcept; //move constarctor
        void start();
        void addOrder(Order* order);
        void addAction(BaseAction* action);
        void addCustomer(Customer* customer);
        Customer &getCustomer(int customerId) const;
        Volunteer &getVolunteer(int volunteerId) const;
        Order &getOrder(int orderId) const;
        const vector<BaseAction*> &getActions() const;
        void close();
        void open();
        int getNewcustomerID();
        int getNewvolunteerID();
        int getNewOrderId();
        void Initiatefile(string file);
        vector<Order*>& getPendingOrders();
        vector<Order*>& getInProcessOrders();
        vector<Order*>& getCompletedOrders();
        vector<Customer*>& getCustomers();
        vector<Volunteer*>& getVolunteers();
        int getOrderCounter();
        void deleteVolunteer(Volunteer* vol, int i);            // 'i' - the 'place' in volunteer's vetor where 'vol' is
        void popOrder(int i, vector<Order*>& vec);// 'i' - same^, 'vec' - the vector of the order(pending,inprocess,completed), the method removes the order from the vector.
        void removeOrderByValue(vector<Order*>& vec, Order& value);
        //move assigment
        ~WareHouse(); //distraptor
        WareHouse& operator=(const WareHouse& other); //copy assigment
        WareHouse& operator=(WareHouse&& other) noexcept; //move assigment
              

        
        private:
        bool isOpen;
        vector<BaseAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Customer*> customers;
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
        int orderCounter;
        CollectorVolunteer* fake_volunteer;
        CivilianCustomer* fake_Customer;
        Order* fake_Order;

};