#include <iostream>
#include <memory>

// Abstract class
class Shape
{
public:
    virtual ~Shape() = default;
    virtual std::unique_ptr<Shape>clone() = 0;
    virtual void draw() = 0;
};

class Circle : public Shape
{
public:
    Circle(int radius) : m_radius{radius} {}
    std::unique_ptr<Shape> clone() override
    {
        return std::make_unique<Circle>(m_radius);
    }
    void draw() override
    {
        std::cout << "Circle draw (radius : " << m_radius << ")" <<'\n';
    }

    void setRadius(int radius)
    {
        m_radius = radius;
    }
private:
    int m_radius;
};

int main()
{
    std::cout << "Original circle is creating\n";
    Circle org_circle{10};
    org_circle.draw();

    std::cout << "\nClone is creating\n";
    auto cloned{org_circle.clone()};
    cloned->draw();

    if (auto ptr{dynamic_cast<Circle*>(cloned.get())})
    {
        ptr->setRadius(25);
    }
    cloned->draw();

    std::cout << "\nResult:\n";
    std::cout << "Orijinal: ";
    org_circle.draw();
    std::cout << "Clone: ";
    cloned->draw();
}
