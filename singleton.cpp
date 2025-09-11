#include <iostream>
#include <memory>

class Printer {
private:
    static std::unique_ptr<Printer> instance;
    Printer() {
        std::cout << "Printer Created!\n";
    }

public:
    Printer(const Printer&) = delete;
    Printer& operator=(const Printer&) = delete;

    static Printer& getInstance() {
        if (!instance) {
            instance = std::unique_ptr<Printer>(new Printer());
        }
        return *instance;
    }
    
    void print(const std::string& text) {
        std::cout << "Printing: " << text << std::endl;
    }
};

std::unique_ptr<Printer> Printer::instance = nullptr;

int main() {
    Printer& printer1 = Printer::getInstance();
    printer1.print("First Message!");
    
    Printer& printer2 = Printer::getInstance();
    printer2.print("Second Message");
    
    if (&printer1 == &printer2) {
        std::cout << "They are same printer object\n";
    }
    
    return 0;
}
