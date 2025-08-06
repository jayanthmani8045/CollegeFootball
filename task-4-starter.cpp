#include <string>
#include <iostream>
#include <utility>
#include <climits> // Added for INT_MAX

using namespace std;

class Item {
private:
    string name;
    int quantity;
    float price;

public:
    Item(string name,int quantity,float price) :
            name{move(name)},
            quantity{quantity},
            price{price} {

    }

    string get_name() const {
        return name;
    }

    int get_quantity() const {
        return quantity;
    }

    void set_quantity(int new_quantity) {
        quantity = new_quantity;
    }

    float get_price() const {
        return price;
    }

    bool is_match(const string &other) {
        return name == other;
    }
};

class Inventory {
private:
    Item *items[20];
    float total_money;
    int item_count;

    static void display_data(Item &item) {
        if (item.get_quantity() != 0) {
            cout << "\nItem name: " << item.get_name();
            cout << "\nQuantity: " << item.get_quantity();
            cout << "\nPrice: " << item.get_price();}
    }

public:
    Inventory() :
            items{},
            total_money{0},
            item_count{0} {

    }

    void add_item() {
        string name;
        int quantity;
        float price;

        cin.ignore();
        cout << "\nEnter item name: ";
        cin >> name;
        cout << "Enter quantity: ";
        cin >> quantity;
        cout << "Enter price: ";
        cin >> price;

        items[item_count] = new Item(name, quantity, price);
        item_count++;
    }

    void sell_item() {
        list_items(); // see list before selling
        if (item_count != 0) {
            string item_to_check;
            cin.ignore();
            cout << "\nEnter item name: ";
            cin >> item_to_check;

            for (int i = 0; i < item_count; i++) {
                if (items[i]->is_match(item_to_check)) {
                    remove_item(i);
                    return;
                }
            }
            cout << "\nThis item is not in your Inventory";
        }
        else {
            cout<<"\nNo item in the inventory";
        }
    }

    void remove_item(int item_index) {
        int input_quantity;
        Item *item = items[item_index];
        cout << "\nEnter number of items to sell: ";
        cin >> input_quantity;

        int quantity = item->get_quantity();
        if (input_quantity <= quantity) {
            float price = item->get_price();
            float money_earned = price * input_quantity;
            item->set_quantity(quantity - input_quantity);
            cout << "\nItems sold";
            cout << "\nMoney received: " << money_earned;
            total_money += money_earned;
            
            // modification to remove the item
            if (item->get_quantity() ==0) {
                cout<<"\nQuantity: "<<0<<" \t Removed item from the inventory";
                for (int i = item_count; i < item_count-1; i++) {
                    items[i] = items[i+1];
                }
                item_count--;
            }
            
        } else {
            cout << "\nCannot sell more items than you have.";
        }
    }

    void list_items() {
        if (item_count == 0) {
            cout << "\nInventory empty.";
            return;
        }

        for (int i = 0; i < item_count; i++) {
            display_data(*items[i]);
            cout << "\n";
        }
    }
};

// no need to modify anything here
int main() {
    int choice;
    Inventory inventory_system;
    cout << "Welcome to the inventory!";

    while (1) {
        cout << "\n\nMENU\n"
                  << "1. Add new item\n"
                  << "2. Sell item\n"
                  << "3. List items\n"
                  << "4. Exit\n\n"
                  << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                inventory_system.add_item();
                break;

            case 2:
                inventory_system.sell_item();
                break;

            case 3:
                inventory_system.list_items();
                break;

            case 4:
                exit(0);

            default:
                cout << "\nInvalid choice entered";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                break;
        }
    }
}
