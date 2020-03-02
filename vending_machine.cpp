#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

static string items[4] = {"Water", "Regular Coffee", "Sun Chip", "Chocolate Bar"};

static double prices[4] = {1.5, 2.0, 1.0, 2.5};

int count[4] = {0, 0, 0, 0};

class VendingMachine{
public:
  VendingMachine();
  VendingMachine(int num, string location);
  void setNumber(int num);
  void setName(string location);
  void getNumber();
  void getName();
  string display() const;
  void status() const;
  void displayMenu() const;
  void refill(int first_item, int second_item, int third_item, int fourth_item);
  void selectItem();
  bool payment();
  void displayReceipt();
  void deselect();
  void reset();

  void distotal(); //test the total

private:
  int id;
  string building;
  int stock[4];
  int sold[4];
  double earnings;
  double total;
};

VendingMachine::VendingMachine(){
  id = 0000;
  building = "UNKNOWN";
  for(int i = 0; i < 4; i++){
    stock[i] = 0;
    sold[i] = 0;
  }
  earnings = 0.00;
  total = 0;
}

VendingMachine::VendingMachine(int ID, string location){
  setName(location);
  setNumber(ID);
  for(int i = 0; i < 4; i++){
    stock[i] = 0;
    sold[i] = 0;
  }
  earnings = 0.00;
  total = 0;
}

void VendingMachine::setName(string location){
  building = location;
} 

void VendingMachine::setNumber(int num){
  id = num;
}

string VendingMachine::display() const{
  string a = "Number: ";
  string b = ", Name: ";
  string num = to_string(id);

  return a + num + b + building + "\n";
}

void VendingMachine::reset(){
  for(int i = 0; i < 4; i++){
    stock[i] = 0;
    sold[i] = 0;
    count[i] = 0;
  }
  earnings = 0;
  total = 0;
}

void VendingMachine::refill(int first_item, int second_item, int third_item, int fourth_item){
  stock[0] = first_item;
  stock[1] = second_item;
  stock[2] = third_item;
  stock[3] = fourth_item;
}

void VendingMachine::status()const{
  cout << "Number: " << id << ", Name: " << building << endl
  << "Sold: " << items[0] << ": " << sold[0]
  << " / " << items[1] << ": " << sold[1]
  << " / " << items[2] << ": " << sold[2]
  << " / " << items[3] << ": " << sold[3] << endl
  << "Remaining: Water: " << stock[0]
  << " / Regular Coffee: " << stock[1]
  << " / Sun Chips: " << stock[2]
  << " / Chocolate Bar: " << stock[3] << endl
  << "Total earnings: $" << earnings << endl;
}

void VendingMachine::displayMenu() const{
  cout << "===== Vending Machine Menu =====" << endl
  << "1. Water............$1.50" << endl
  << "2. Regular Coffee...$2.00" << endl
  << "3. Sun Chip.........$1.00" << endl
  << "4. Chocolate Bar....$2.50" << endl;
}

void VendingMachine::selectItem(){
  char con = 'Y';
  int item, amt;

  while(con == 'Y'){
    cout << "Select Item: ";
    cin >> item;
    while(item < 1 || item > 4){
      cout << "Invalid selection. Please try again." << endl << endl;

      cout << "Select Item: ";
      cin >> item;
    }
    cout << "How many do you want to buy? ";
    cin >> amt;
    stock[item-1] -= amt;
    if(stock[item-1] < 0){
      cout << "You selected " << items[item-1] << " (" << amt << ") - Sorry. We don't have enough " << items[item-1] << "." << endl;
      stock[item-1] += amt;
    }else{
      cout << "You selected " << items[item-1] << " (" << amt << ")" << endl;
      sold[item-1] = amt;
      total += prices[item-1]*amt;
    }
    cout << "Continue? (Y/N): ";
    cin >> con;
    cout << endl;

    count[item-1]++;
  }

}

bool VendingMachine::payment(){
  int opt, pin;
  double cash;

  cout << "Payment Option - Debit(1) / Cash(2): ";
  cin >> opt;

  if(opt == 1){
    cout << "Enter PIN: ";
    cin >> pin;
    if(pin == 7777){
      cout << "Valid";
      cout << endl;
      return true;
      
    }
    else{
      reset();
      return false;
    }
  }else if(opt == 2){
    cout << "Enter Money Ammount: $";
    cin >> cash;
    while(cash < total){
      cout << "Not enough money!" << endl
      << "Enter Money Amount: $";
      cin >> cash;
    }
    if(cash >= total){
      cout << "Change: $" << fixed << setprecision(2) << 
      cash-(total+(total*.1));
    }else{
      reset();
      return false;
    }
    cout << endl;
    return true;
  }
  return false;
}

void VendingMachine::displayReceipt(){
  if(count[0] > 0){
    cout << items[0] << ": " << prices[0] << " X " << sold[0] << " = " << fixed << setprecision(2) << "$" << prices[0]*sold[0] << endl;
  }
  if(count[1] > 0){
    cout << items[1] << ": " << prices[1] << " X " << sold[1] << " = " << fixed << setprecision(2) << "$" << prices[1]*sold[1] << endl;
  }
  if(count[2] > 0){
    cout << items[2] << ": " << prices[2] << " X " << sold[2] << " = " << fixed << setprecision(2) << "$" << prices[2]*sold[2] << endl;
  }
  if(count[3] > 0){
    cout << items[3] << ": " << prices[3] << " X " << sold[3] << " = " << fixed << setprecision(2) << "$" << prices[3]*sold[3] << endl;
  }

  double tax = (total*0.1);

  cout << "Subtotal: $" << fixed << setprecision(2) << total << endl;
  cout << "Tax (10.0%): $" << fixed << setprecision(2) << tax << endl;
  cout << "Total: $" << fixed << setprecision(2) << total + tax << endl;

  earnings += (total + tax);
  for(int i = 0; i < 4; i++)
    count[i] = 0;
}

void VendingMachine::deselect(){
  cout << "You de-selected" << endl;
  if(count[0] > 0){
    cout << "\t" << items[0] << " (" << sold[0] << ")"<< endl;
    count[0] = 0;
    stock[0] += sold[0];
    total = 0;
    sold[0] = 0;
  }
  if(count[1] > 0){
    cout << "\t" << items[1] << " (" << sold[1] << ")" << endl;
    count[1] = 0;
    stock[1] += sold[1];
    total = 0;
    sold[1] = 0;
  }
  if(count[2] > 0){
    cout << "\t" << items[2] << " (" << sold[2] << ")" << endl;
    count[2] = 0;
    stock[2] += sold[2];
    total = 0;
    sold[2] = 0;
  }
  if(count[3] > 0){
    cout << "\t" << items[3] << " (" << sold[3] << ")" << endl;
    count[3] = 0;
    stock[3] += sold[3];
    total = 0;
    sold[3] = 0;
  }
  
}

int main() {
cout << "===== Welcome to CSUMB Vending Machine =====\n";

VendingMachine machine1;
cout << machine1.display(); // Display the ID and name of machine1.

VendingMachine machine2 (200, "Library"); 
cout << machine2.display();

cout << "\n===== Updated machine1 Info =====\n"; 
machine1.setNumber(100); 
machine1.setName("BIT117");
cout << machine1.display();

cout << "\n===== machine1 Status (1) =====\n";
machine1.status(); // status() function displays current status of the machine.

machine1.refill(5, 7, 3, 10); // A machine’s admin can refill the items.

cout << "\n===== machine1 Status (2) =====\n"; 
machine1.status();

cout << endl; 
machine1.displayMenu();

cout << endl; 
machine1.selectItem();
// A user can select item(s). 

cout << "\n===== machine1 Payment (1) =====\n";
if(machine1.payment() == true) {// Pay with a debit card or cash. 32. 
  cout << "\n===== Receipt (1) =====\n";
  machine1.displayReceipt();
}
else{// Note that if a user entered incorrect payment information, all selections should be deselected.
  cout << "Invalid payment. All selections are cancelled.\n";
}

cout << "\n===== machine1 Status (3) =====\n";
machine1.status();

cout << endl;
machine1.selectItem();

cout << endl;
machine1.deselect( ); // A user can de-select items.

cout << endl;
machine1.selectItem();

cout << "\n===== machine1 Payment (2) =====\n";
if(machine1.payment()){
  cout << "\n===== Receipt (2) =====\n";
  machine1.displayReceipt();
}

cout << "\n===== machine1 Status (4) =====\n";
machine1.status();

machine1.reset(); // An admin resets the machine to the initial 
// status, except the ID and name of the machine. 
cout << "\n===== machine1 Status (5) =====\n";
machine1.status();

cout << "\n===== Thank you! =====\n";
  return 0;

}
