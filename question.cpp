#include<bits/stdc++.h>
using namespace std;

struct item{
	string itemName;
	string personId;
	float itemCost;
	int itemStock;
};

class buyer{
  public:
    string userName;
    vector<item>wishList;
    vector<item>itemList;
    void setPin(string s){
        pin = s;
    }
    
    bool isPin(string s){
        if(s==pin){
            return true;
        }else{
            return false;
        }
    }
  private:
    string pin;
};

class seller{
  public:
    string userName;
    vector<item>products;
    vector<item>soldItems;
    
    void setPin(string s){
        pin = s;
    }
    
    bool isPin(string s){
        if(s==pin){
            return true;
        }else{
            return false;
        }
    }    
  private:
    string pin;
};

class toystore{
    public:
    vector<buyer>buyers;
    vector<seller>sellers;
    //common functions
    bool isManager(){
        cout<<"Enter master key"<<endl;
        string key;
        cin >>key;
        if(key==masterkey){
            return true;
        }
        return false;
    }
    
    void print(){
        int n = sellers.size();
        for(int i=0;i<n;i++){
            int sz = sellers[i].products.size();
            string tag = sellers[i].userName;
            for(int j=0;j<sz;j++){
                if(sellers[i].products[j].itemStock>0){
                    cout<<"Toyname: "<<sellers[i].products[j].itemName
                        <<"Toycost: "<<sellers[i].products[j].itemCost
                        <<"Toyseller: "<<tag<<endl;
                }
            }
        }
    }
    
    bool isValid(string username,string password,string str){
        int k = isUser(username,str);
        if(str=="buyer"){
            if(buyers[k].isPin(password)){
                return true;
            }
        }else{
            if(sellers[k].isPin(password)){
                return true;
            }
        }
        return false;
    }
    
    int isUser(string username,string str){
        if(str=="buyer"){
            int n = buyers.size();
            for(int i=0;i<n;i++){
			    if(buyers[i].userName==username){
				    return i;
			    }
		    }
        }else{
            int n = sellers.size();
            for(int i=0;i<n;i++){
			    if(sellers[i].userName==username){
				    return i;
			    }
		    }
        }
        
        return -1;
    }
    
    void addUser(string username,string str){
        if(str=="buyer"){
            buyer person;
            person.userName=username;
            cout<<"Enter password"<<endl;
            string password;
            cin>> password;
            person.setPin(password);
            buyers.push_back(person);
        }else{
            seller person;
            person.userName=username;
            cout<<"Enter password"<<endl;
            string password;
            cin>> password;
            person.setPin(password);
            sellers.push_back(person);
        }
    }
    
    //buyer functions
    void search(int ind){
        print();
        while(1){
            cout<<"Enter toy name to proceed further or 'exit' to exit"<<endl;
            string answer;
            cin >>answer;
            if(answer != "exit"){
                int seller;
                int number = -1;
                int n = sellers.size();
                for(int i =0;i<n;i++){
                    int x = sellers[i].products.size();
                    for(int j =0;j<x;j++){
                        if(sellers[i].products[j].itemName==answer){
                            seller=i;
                            number=j;
                            break;
                        }
                        if(number!=-1){
                            break;
                        }
                    }
                }
                if(number !=-1){
                    while(1){
                        cout<<"Do you want to buy/wishlist/exit"<<endl;
                        string answer;
                        cin >>answer;
                        if(answer=="buy"){
                            buy(ind,seller,number);
                        }else if(answer=="wishlist"){
                            addToWishList(ind,seller,number);
                        }else if(answer=="exit"){
                            break;
                        }else{
                            cout<<"Invalid command try again"<<endl;
                        }
                    }
                }else{
                    cout<<"No results found for such toy"<<endl;
                }
            }else if(answer == "exit"){
                break;
            }else{
                cout<<"Invalid command try again"<<endl;
            }
        }
    }
    
    void buy(int ind,int seller,int number){
        cout<<"Enter the quantity to buy"<<endl;
        int quantity;
        cin>>quantity;
        if(quantity>0){
            if(quantity<= sellers[seller].products[number].itemStock){
                sellers[seller].products[number].itemStock-=quantity;
                item prod;
                prod.itemName=sellers[seller].products[number].itemName;
                prod.personId=buyers[ind].userName;
                prod.itemStock=quantity;
                prod.itemCost=quantity*sellers[seller].products[number].itemCost;
                sellers[seller].soldItems.push_back(prod);
                prod.personId=sellers[seller].userName;
                buyers[ind].itemList.push_back(prod);
                cout<<"Purchase done for "<< prod.itemCost<<endl;
            }else{
                cout<<"Insufficient stock or item out of stock"<<endl;
            }
        }else{
            cout<<"Enter a valid quantity"<<endl;
        }
    }
    
    void addToWishList(int ind,int seller,int number){
        item toy = sellers[seller].products[number];
        buyers[ind].wishList.push_back(toy);
    }
    
    void wishList(int ind){
        while(1){
            int n = buyers[ind].wishList.size();
            for(int i =0;i<n;i++){
                string name = buyers[ind].wishList[i].itemName;
                int cost = buyers[ind].wishList[i].itemCost;
                string tag = buyers[ind].wishList[i].personId;
                cout<<i+1<<"-> "<<"Toyname: "<<name<<" "
                                <<"Toycost: "<<cost<<" "
                                <<"Toyseller: "<<tag<<endl;
            }
            cout<<endl;
            cout<<"Enter 'delete' to delete item or 'exit'"<<endl;
            string answer;
            cin >>answer;
            if(answer=="delete"){
                cout<<"Enter index of item to be deleted"<<endl;
                int x;
                cin>>x;
                if(x>0 && x<=n){
                    buyers[ind].wishList.erase(buyers[ind].wishList.begin()+x-1);
                }else{
                    cout<<"Not a valid index"<<endl;
                }
            }else if(answer=="exit"){
                break;
            }else{
                cout<<"Invalid command try again"<<endl;
            }
        }
    }
    
    void itemsBought(int ind){
        int n = buyers[ind].itemList.size();
        if(n>0){
            for(int i=0;i<n;i++){
                cout<<"Toyname: "<<buyers[ind].itemList[i].itemName
                    <<"Toycost: "<<buyers[ind].itemList[i].itemCost
                    <<"Quantity: "<<buyers[ind].itemList[i].itemStock
                    <<"Toyseller: "<<buyers[ind].itemList[i].personId<<endl;
            }
        }else{
            cout<<"No purchases done yet"<<endl;
        }
    }
    
    //admin functions
    void admin(){
        if(isManager()){
            while(1){
                cout<<"Enter 1 to see all buyers"<<endl;
                cout<<"Enter 2 to see all seller"<<endl;
                cout<<"Enter 3 to see all products"<<endl;
                cout<<"Enter 4 to logout"<<endl;
                int num;
                cin >> num;
                if(num ==1){
                    int n = buyers.size();
                    cout<<"Buyers:"<<endl;
                    for(int i=0;i<n;i++){
                        cout<<i+1<<" "<<buyers[i].userName<<endl;
                    }
                }else if(num ==2){
                    int n = sellers.size();
                    cout<<"Sellers:"<<endl;
                    for(int i=0;i<n;i++){
                        cout<<i+1<<" "<<sellers[i].userName<<endl;
                    }
                }else if(num ==3){
                    print();
                }else if(num ==4){
                    break;
                }else{
                    cout<<"Invalid command pls try again"<<endl;
                }
            }
        }else{
            cout<<"Incorrect masterkey"<<endl;
        }
    }
    
    //seller function
    void items(int ind){
        cout<<"Enter 1 to add item"<<endl;
        cout<<"Enter 2 to delete item"<<endl;
        int task;
        cin >>task;
        if(task==1){
            string name;
            cout<<"Enter name of product"<<endl;
            cin>>name;
            if(isItem(name,ind)==-1){
                item prod;
                prod.itemName=name;
                prod.personId=sellers[ind].userName;
                cout<<"Enter quantity of item"<<endl;
                while(1){
                    int quantity;
                    cin >>quantity;
                    if(quantity>=0){
                        prod.itemStock=quantity;
                        break;
                    }else{
                        cout<<"Enter a valid number"<<endl;
                    }
                }
                
                cout<<"Enter selling price"<<endl;
                while(1){
                    int cost;
                    cin >>cost;
                    if(cost>=0){
                        prod.itemCost=cost;
                        break;
                    }else{
                        cout<<"Enter a valid number"<<endl;
                    }
                }
                sellers[ind].products.push_back(prod);
            }else{
                cout<<"product already exists"<<endl; 
            }
        }else if(task==2){
            string name;
            cout<<"Enter name of product"<<endl;
            cin>>name;
            int x = isItem(name,ind);
            if(x!=-1){
                sellers[ind].products.erase(sellers[ind].products.begin()+x);
            }else{
                cout<<"Item doesn't exist"<<endl;
            }
            
        }else{
            cout<<"Invalid command pls try again"<<endl;
        }
    }
    
    int isItem(string name,int ind){
        int n = sellers[ind].products.size();
        for(int i=0;i<n;i++){
            if(sellers[ind].products[i].itemName==name){
                return i;
            }
        }
        
        return -1;
    }
    
    void modifyItem(int ind){
        cout<<"Enter product name"<<endl;
        string name;
        cin >>name;
        int x = isItem(name,ind);
        if(x!=1){
            while(1){
                cout<<"Enter add/remove/exit"<<endl;
                string task;
                cin >>task;
                if(task=="add"){
                    cout<<"Enter quantity"<<endl;
                    int quantity;
                    cin >>quantity;
                    if(quantity>0){
                        sellers[ind].products[x].itemStock +=quantity;
                    }else{
                        cout<<"Enter a valid number"<<endl;
                    }
                }else if(task =="remove"){
                    cout<<"Enter quantity"<<endl;
                    int quantity;
                    cin>>quantity;
                    if(quantity>0){
                        if(sellers[ind].products[x].itemStock>=quantity){
                            sellers[ind].products[x].itemStock -=quantity;
                        }else{
                            sellers[ind].products[x].itemStock=0;
                        }
                    }else{
                        cout<<"Enter a valid number"<<endl;
                    }
                }else if (task=="exit"){
                    break;
                }else{
                    cout<<"Invalid command pls try again"<<endl;
                }
            }
        }else{
            cout<<"Item doesn't exist"<<endl;
        }
    }
    
    void list(int ind){
        int n = sellers[ind].products.size();
        for(int i=0;i<n;i++){
            cout<<"Toyname: "<<sellers[ind].products[i].itemName
                <<"Toycount: "<<sellers[ind].products[i].itemStock<<endl;
        }
    }
    
    void sold(int ind){
        int n = sellers[ind].soldItems.size();
        if(n>0){
            for(int i =0;i<n;i++){
                cout<<"Toyname: "<<sellers[ind].soldItems[i].itemName
                    <<"Toycount: "<<sellers[ind].soldItems[i].itemStock
                    <<"Buyer: "<<sellers[ind].soldItems[i].personId<<endl;
            }
        }else{
            cout<<"No purchases done yet"<<endl;
        }
    }
    
    private:
    string masterkey ="bossisback";
    
    
};

int main(){
    toystore store;
    while(1){
        cout<<"Enter 1 to proceed as consumer"<<endl;
        cout<<"Enter 2 to proceed as manager"<<endl;
        cout<<"Enter 3 to proceed as seller"<<endl;
        cout<<"Enter 4 to Exit"<<endl;
        int num;
        cin >> num;
        if(num==1){
            while(1){
                cout<< "Enter SignIn/SignUp/Exit"<<endl;
      			string answer;
      			cin>>answer;
      			
                if(answer == "SignUp"){
      				cout<<"Enter User name"<<endl;
      				string username;
      				cin >> username;
      				int k = store.isUser(username,"buyer");
      				if(k==-1){
      					store.addUser(username,"buyer");
      					cout<<"Account created please Proceed to SignIn"<<endl;
      				}else{
      					cout<<"Account already exist,pls use SignIn"<<endl;
      				}
      			}else if(answer=="SignIn"){
      			    cout<<"Enter User name"<<endl;
      				string username;
      				cin >> username;
      				int k = store.isUser(username,"buyer");
      				if(k!=-1){
      				    cout<<"Enter password"<<endl;
      				    string password;
      				    cin >>password;
      				    if(store.isValid(username,password,"buyer")){
      				        while(1){
      				            cout<<"Enter 1 to search items"<<endl;
      				            cout<<"Enter 2 to look into wishlist"<<endl;
      				            cout<<"Enter 3 to see items bought"<<endl;
      				            cout<<"Enter 4 to logout"<<endl;
      				            int task;
      				            cin >>task;
      				            if(task==1){
      				                store.search(k);
      				            }else if(task ==2){
      				                store.wishList(k);
      				            }else if(task==3){
      				                store.itemsBought(k);
      				            }
      				            else if(task==4){
      				                break;
      				            }else{
      				                cout<<"Invalid commmand try again"<<endl;
      				            }
      				        }
      				    }
      				}else{
      				    cout<<"Account doesn't exist,pls use SignUp"<<endl;
      				}
      			}else if(answer=="Exit"){
      			    break;
      			}else{
      			    cout<<"Invalid command try again"<<endl;
      			}
            }
        }else if(num==2){
            store.admin();
        }else if(num==3){
            while(1){
                cout<< "Enter SignIn/SignUp/Exit"<<endl;
      			string answer;
      			cin>>answer;
      			if(answer=="SignUp"){
      			    cout<<"Enter User name"<<endl;
      				string username;
      				cin >> username;
      				int k = store.isUser(username,"seller");
      				if(k==-1){
      					store.addUser(username,"seller");
      					cout<<"Account created please Proceed to SignIn"<<endl;
      				}else{
      					cout<<"Account already exist,pls use SignIn"<<endl;
      				} 
      			}else if(answer == "SignIn"){
      			    cout<<"Enter User name"<<endl;
      				string username;
      				cin >> username;
      				int k = store.isUser(username,"seller");
      				if(k!=-1){
      				    cout<<"Enter password"<<endl;
      				    string password;
      				    cin >>password;
      				    if(store.isValid(username,password,"seller")){
      				        while(1){
      				            cout<<"Enter 1 to add/delete item"<<endl;
      				            cout<<"Enter 2 to modify existing item"<<endl;
      				            cout<<"Enter 3 to see to remaining products"<<endl;
      				            cout<<"Enter 4 to see sold items"<<endl;
      				            cout<<"Enter 5 to logout"<<endl;
      				            int task;
      				            cin >>task;
      				            if(task==1){
      				                store.items(k);  
      				            }else if(task==2){
      				                store.modifyItem(k);
      				            }else if(task ==3){
      				                store.list(k);
      				            }else if(task ==4){
      				                store.sold(k);
      				            }else if(task==5){
      				                break;
      				            }else{
      				                cout<<"Invalid commmand try again"<<endl;
      				            }
      				        }
      				    }
      				}else{
      				    cout<<"Account doesn't exist,pls use SignUp"<<endl;
      				}
      			}else if(answer == "Exit"){
      			    break;
      			}else{
      			    cout<<"Invalid command please try again"<<endl;
      			}
            }
        }else if(num==4){
            break;
        }else{
            cout<<"Invalid command"<<endl;
        }
    }
    return 0;
}

