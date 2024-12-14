#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

class Product {
protected:
    string name;
    double price;

public:
    Product(const string& name, double price) : name(name), price(price) {}

    virtual string getName() const { return name; }
    virtual double getPrice() const { return price; }

    virtual void setPrice(double newPrice) { price = newPrice; }

    virtual double getFinalPrice() const = 0;

    virtual ~Product() {}
};

class Discountable {
public:
    virtual double applyDiscount(double price) const = 0;
    virtual ~Discountable() {}
};

class Book : public Product, public Discountable {
public:
    Book(const string& name, double price) : Product(name, price) {}

    double applyDiscount(double price) const override {
        return price * 0.9;
    }

    double getFinalPrice() const override {
        return applyDiscount(price);
    }
};

class Pen : public Product, public Discountable {
public:
    Pen(const string& name, double price) : Product(name, price) {}

    double applyDiscount(double price) const override {
        return (price > 5.0) ? price - 5.0 : price;
    }

    double getFinalPrice() const override {
        return applyDiscount(price);
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    vector<Product*> products;
    int choice;

    do {
        cout << "\nМеню:\n"
             << "1. Додати предмет\n"
             << "2. Переглянути предмети\n"
             << "3. Вийти\n"
             << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Виберіть тип предмета:\n"
                     << "1. Книга\n"
                     << "2. Ручка\n"
                     << "Ваш вибір: ";
                int type;
                cin >> type;

                if (type == 1) {
                    cout << "Введіть назву книги: ";
                    string bookName;
                    cin.ignore();
                    getline(cin, bookName);

                    cout << "Введіть ціну книги: ";
                    double bookPrice;
                    cin >> bookPrice;

                    products.push_back(new Book(bookName, bookPrice));
                    cout << "Книга успішно додана!\n";
                } else if (type == 2) {
                    cout << "Введіть назву ручки: ";
                    string penName;
                    cin.ignore();
                    getline(cin, penName);

                    cout << "Введіть ціну ручки: ";
                    double penPrice;
                    cin >> penPrice;

                    products.push_back(new Pen(penName, penPrice));
                    cout << "Ручка успішно додана!\n";
                } else {
                    cout << "Невірний вибір типу предмета.\n";
                }
                break;
            }

            case 2: {
                if (products.empty()) {
                    cout << "Список предметів порожній.\n";
                } else {
                    cout << "\nСписок предметів:\n";
                    for (const auto& product : products) {
                        cout << "Товар: " << product->getName()
                             << ", Базова ціна: " << product->getPrice() << " грн"
                             << ", Кінцева ціна: " << product->getFinalPrice() << " грн\n";
                    }
                }
                break;
            }

            case 3:
                cout << "Вихід із програми\n";
                break;

            default:
                cout << "Невірний вибір\n";
        }
    } while (choice != 3);

    for (auto& product : products) {
        delete product;
    }

    return 0;
}
