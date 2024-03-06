#include <iostream>
#include <string>
using namespace std;

const int maxProducts = 10;

class Product
{
protected:
    string name;
    double price;
public:
    Product(string name, double price) : name{ name }, price{ price }
    {
        this->name = name;
        this->price = price;
    }
    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    void setName(string productName) {
        name = productName;
    }

    void setPrice(double productPrice) {
        price = productPrice;
    }
};

class Dish
{
private:
    string name;
    Product* products[maxProducts];
    int productCount;
public:
    Dish() : name(""), productCount(0) {}

    Dish(string name_) : name{ name_ }, productCount(0) {}
    void addProduct(const Product& product) {
        if (productCount < maxProducts)
            products[productCount++] = new Product(product);
        else {
            cout << "Error:\tMax count products in list." << endl;
        }
    }

    void deleteProduct(int index) {
        if (index >= 0 && index < productCount) {
            delete products[index];
            for (int i = index; i < productCount - 1; i++)
            {
                products[i] = products[i + 1];
            }
            productCount--;
        }
    }

    double calculateTotalPriceProducts() const {
        double totalPrice = 0.0;
        for (int i = 0; i < productCount; i++)
        {
            totalPrice += products[i]->getPrice();
        }
        return totalPrice;
    }
    ~Dish() {
        for (size_t i = 0; i < productCount; i++)
        {
            delete products[i];
        }
    }
};

class Beverage
{
private:
    string name;
    Product* fruits[maxProducts];
    int fruitCount;
public:
    Beverage() : name{ "" }, fruitCount(0) {}
    Beverage(string name_) : name{ name_ }, fruitCount(0) {}

    void addFruit(const Product& fruit) {
        if (fruitCount < maxProducts) {
            fruits[fruitCount++] = new Product(fruit);
        }
        else {
            cout << "Error:\tMax count fruits in list." << endl;
        }
    }

    void removeFruit(int index) {
        if (index >= 0 && index <= fruitCount) {
            delete fruits[index];
            for (int i = index; i < fruitCount; i++)
            {
                fruits[i] = fruits[i + 1];
            }
            fruitCount--;
        }
    }

    double calculateTotalPriceFruits() const {
        double totalPrice = 0.0;
        for (size_t i = 0; i < fruitCount; i++)
        {
            totalPrice += fruits[i]->getPrice();
        }
        return totalPrice;
    }

    ~Beverage() {
        for (size_t i = 0; i < fruitCount; i++)
        {
            delete[]fruits[i];
        }
    }
};

class Order
{
private:
    int tableNumber;
    Dish dishes[maxProducts];
    Beverage beverages[maxProducts];
    int dishCount, beverageCount;
public:
    Order(int tableNumber_) : tableNumber(tableNumber_), dishCount(0), beverageCount(0) {}

    void addDish(const Dish& dish) {
        if (dishCount < maxProducts) {
            dishes[dishCount++] = dish;
        }
        else {
            cout << "Error:\tMax count dishes in order." << endl;
        }
    }

    void removeDish(int index) {
        if (index >= 0 && index <= dishCount) {
            for (int i = index; i < dishCount - 1; i++)
            {
                dishes[i] = dishes[i + 1];
            }
            dishCount--;
        }
    }

    void addBeverage(const Beverage& beverage) {
        if (beverageCount < maxProducts) {
            beverages[beverageCount++] = beverage;
        }
        else {
            cout << "Error:\tMax count dishes in order." << endl;
        }
    }

    void removeBeverage(int index) {
        if (index >= 0 && index <= beverageCount) {
            for (int i = index; i < beverageCount - 1; i++)
            {
                beverages[i] = beverages[i + 1];
            }
            beverageCount--;
        }
    }

    double calculateTotalPrice() const {
        double totalPrice = 0.0;
        for (int i = 0; i < dishCount; i++)
        {
            totalPrice += dishes[i].calculateTotalPriceProducts();
        }
        for (int i = 0; i < beverageCount; i++)
        {
            totalPrice += beverages[i].calculateTotalPriceFruits();
        }
        return totalPrice;
    }
};
int main()
{
    Dish dish1("Jonibi");
    dish1.addProduct(Product("Pasta", 5.99));
    dish1.addProduct(Product("Souse", 3.49));

    Dish dish2("Salad");
    dish2.addProduct(Product("Lettuce", 2.99));
    dish2.addProduct(Product("Tomato", 1.49));
    dish2.addProduct(Product("Cucumber", 1.29));

    Beverage beverage1("Orange Juice");
    beverage1.addFruit(Product("Orange", 0.99));
    beverage1.addFruit(Product("Lemon", 0.79));

    Beverage beverage2("Smoothie");
    beverage2.addFruit(Product("Strawberry", 1.49));
    beverage2.addFruit(Product("Banana", 0.89));
    beverage2.addFruit(Product("Milk", 1.29));

    Order order(1);

    order.addDish(dish1);
    order.addDish(dish2);
    order.addBeverage(beverage1);
    order.addBeverage(beverage2);

    double totalOrderPrice = order.calculateTotalPrice();
    cout << "Total order price: $" << totalOrderPrice << endl;

    order.removeDish(0);

    totalOrderPrice = order.calculateTotalPrice();
    cout << "Total order price after removing dish: $" << totalOrderPrice << endl;
}