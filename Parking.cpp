
#include<bits/stdc++.h>
using namespace std;
double total_amount=0;

bool validateDuration(double d){
    if(d>=0.5 && d<=10) return true;
    else return false;
}

class Vehicle
{
private:
    string reg_no, ph_no,email;
    int type; // type can be 2 or 4 wheeler
    bool hasCard=false; // If they purchase card make it true
public:
    Vehicle(string, int, string, string);
    ~Vehicle();

    string getReg_no() const{
        return this->reg_no;
    }
    bool getHasCard(){
        return this->hasCard;
    }
    int getType(){
        return this->type;
    }
    void setCard(){
        this->hasCard = true;
    }
};

////////////////////////////////////////////////////////////////////////
vector<Vehicle> users; // stores the objects
map<string, double> parking; // Stores the data of parked Vehicles
 
/////////////////////////////////////////////////////////

Vehicle::Vehicle(string reg_no,int type, string ph_no, string email) :
reg_no(reg_no), type(type), ph_no(ph_no), email(email)
{
}

Vehicle::~Vehicle()
{
}

// This function will take a proper input of email Id
string validateMail(){
    string mail;
    cout<<("Email: ");
    getline(cin, mail);
    const regex pattern(
        "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
  
    // Match the string pattern
    // with regular expression
    while(!regex_match(mail, pattern)){
        cout<<("Please enter correctly: \n");
        getline(cin, mail);
    }
    return mail;
}

// Register a Vehicle 
void registration(){
    string reg_no, ph_no,email;
    int type;

    cout<<"* * * Welcome Parking Billing System * * *\n";
    //Reading customer details 
    cout<<"Please enter the following details:\nRegistration Number: ";
    getline(cin>>ws, reg_no);

    cout<<"Vehicle Type: enter '2' for two wheeler and '4' for 4 wheeler:\n ";
    cin >> type;
    while(type!=2 && type!=4){
        cout<<("Please enter correctly: \n");
        cout<<"Vehicle Type: enter 2 for two wheeler and 4 for 4 wheeler ";
        cin >> type;
    }

    cout<<"Phone Number ";
    getline(cin>>ws, ph_no);

    email = validateMail(); // Above function will take the input

    Vehicle tempObj(reg_no,type,ph_no,email);

    string card;
    cout<<"Registration Successful\n Do you want card for 100rs?:  (yes/no):  ";
    cin >> card;
    if(card.compare("Yes") == 0 || card.compare("yes") ==0){
        tempObj.setCard();
        total_amount += 100; // adds 100 rs to the system;
    }

    users.push_back(tempObj);
}

void park_vehicle(){
    
    string reg_no;
    cout<<"Enter the Registration Number: ";
    cin>>reg_no;

    if(parking.find(reg_no)!=parking.end()){
        cout<<"Vehicle Already Parked: ";
        return;
    }
    for(int i=0; i<users.size(); i++){
        if(reg_no.compare(users[i].getReg_no()) == 0){
            if(users[i].getHasCard()){
                parking[reg_no] = -1;
                cout << "Successfully Parked. \n";
                
            }
            else {
                double duration;
                cout << "Enter the duration (min 0.5 hour/ max 10 hours). \n";
                cin >> duration;
                if(!validateDuration(duration)){
                    cout<<"Enter the total parked duration again: (in hours)\n";
                    cin>>duration;
                }
                parking[reg_no] = duration;
                
            }
            cout<<"Vehicle Successfully Parked. \n";
            return;
        }
    }

    cout << "Registration No. not valid\n";
    
}

void take_out_vehicle(){
    string reg_no;
    cout<<"Enter the Registration Number: ";
    cin >> reg_no;
    
    double current_duration;
    cout<<"Enter the total parked duration: (in hours)\n";
    cin>>current_duration;
    if(!validateDuration(current_duration)){
        cout<<"Enter the total parked duration again: (in hours)\n";
        cin>>current_duration;
    }

    int type;
    double bill =0;
    map<string, double>:: iterator it;
    for (it = parking.begin(); it!=parking.end(); it++)
    {
        if(it->first.compare(reg_no) == 0){
            for(int j=0; j<users.size(); j++){
                if(reg_no.compare(users[j].getReg_no()) == 0){
                    type = users[j].getType();
                    break;
                }
            }
            // If duration is -1 that means it has registered CARD
            if(it->second == -1){
                if(type == 2){
                    bill = 10*ceil(current_duration);
                    cout << "Bill amount = "<<bill<<endl;
                }
                else{
                    bill = 20*ceil(current_duration);
                    cout << "Bill amount = "<<bill<<endl;
                }
            }
            else{
                if(type == 2){
                    if(current_duration < it->second){
                        bill = 15*ceil(it->second);
                        cout << "Bill amount = "<<bill<<endl;
                    }
                    else{
                        bill = 15*ceil(it->second) + 30*(ceil(current_duration-it->second));
                        cout << "Bill amount = "<< bill <<endl;
                    }
                }
                else{
                    if(current_duration < it->second){
                        bill = 25*ceil(it->second);
                        cout << "Bill amount = "<< bill <<endl;
                    }
                    else{
                        bill = 25*ceil(it->second) + 50*ceil(current_duration-it->second);
                        cout << "Bill amount = "<< bill <<endl;
                    }
                }
                // Still Building the logic here.. Need more time to Modify

                // Please.....
            }
            total_amount += bill;
            parking.erase(reg_no);
            return;
        }
    }
    
    cout << "Car is not Parked..\n";
}




int main(){
    int choice = 0;
    while(true){
        cout<<"...\n";
        cout<<"Press 1. to Register a Vehicle"<<endl;
        cout<<"Press 2. Park a Vehicle"<<endl;
        cout<<"Press 3. Take out a Vehicle"<<endl;
        cout<<"Press 4. Print Total Amount"<<endl;
        cout<<"Press 5. to Exit"<<endl;
        cin >> choice;
        while(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize> :: max(),'\n');
            cout <<"\tInvalid Input\n";
            cin >> choice;
        }
        switch (choice)
        {
            case 1:
                registration();
                break;
            
            case 2:
                park_vehicle();
                break;
            case 3:
                take_out_vehicle();
                break;
            case 4:
                cout << "Amount collected= "<<total_amount;
                break;
            case 5:
                cout << "Exit";
                return 0;
            default:
                cout << "Try Again\n"<<endl;
                break;
        }
        
    }

   return 0;
}
