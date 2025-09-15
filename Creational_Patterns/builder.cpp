#include <string>
#include <print>
#include <string_view>



class Car {
public:
    void setBrand(std::string_view brand) {m_brand = brand;}
    void setModel(std::string_view model) {m_model = model;}
    void setColor(std::string_view color) {m_color = color;}
    void setYear(const int year) {m_year = year;}
    void hasSunroof(const bool val) {m_has_sunroof = val;}
    void showInfo()const {
        std::println("\n🚗 === VEHICLE INFORMATION ===");
        std::println("Marka: {}",m_brand);
        std::println("Model: {}",m_model);
        std::println("Renk: {}",m_color);
        std::println("Yıl: {}",m_year);
        std::println("Sunroof: {}",m_has_sunroof);
        std::println("=====================");
    }
private:
    std::string m_brand{};
    std::string m_model{};
    std::string m_color{};
    int m_year{};
    bool m_has_sunroof{};

};

class CarBuilder {
private:
    Car car;
public:
    CarBuilder& setBrand(std::string_view brand) {
        car.setBrand(brand);
        return *this;
    }
    CarBuilder& setModel(std::string_view model) {
        car.setModel(model);
        return *this;
    }
    CarBuilder& setColor(std::string_view color) {
        car.setColor(color);
        return *this;
    }
    CarBuilder& setYear(const int year) {
        car.setYear(year);
        return *this;
    }
    CarBuilder& setHasSunroof(const bool val) {
        car.hasSunroof(val);
        return *this;
    }
    Car build() {return car;}
};

int main() {
    CarBuilder builder;
    Car mycar = builder.setBrand("Volvo").setColor("Night Blue").setHasSunroof(true).setModel("XC90").setYear(2022).build();
    mycar.showInfo();
}
