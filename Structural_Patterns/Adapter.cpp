#include <iostream>
#include <string>
#include <memory>

class Target {
public:
    virtual ~Target() = default;
    virtual std::string request()const = 0;
};

class Adaptee {
public:
    std::string another_request()const {
        return "dlrow olleH";
    }
};

class ObjectAdapter : public Target {
    std::unique_ptr<Adaptee> m_adaptee;
public:
    explicit ObjectAdapter(std::unique_ptr<Adaptee> adaptee) : m_adaptee(std::move(adaptee)) {
    }
    std::string request() const override {
        std::string req{m_adaptee->another_request()};
        std::reverse(req.begin(), req.end());
        return req;
    }
};

void client(Target &target) {
    std::string str{target.request()};
    std::cout << str << '\n';
}

int main() {
    using namespace std;
    unique_ptr adaptee {make_unique<Adaptee>()};
    ObjectAdapter adapter(std::move(adaptee));
    client(adapter);
}
