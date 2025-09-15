#include <iostream>
#include <memory>

class Animal
{
public:
    virtual ~Animal() = default;
    virtual void make_sound() = 0;
};

class Dog : public Animal
{
public:
    void make_sound() override
    {
        std::cout << "Dog sound\n";
    }
};

class Cat : public Animal
{
public:
    void make_sound() override {
        std::cout << "Cat sound\n";
    }
};

class Bird : public Animal
{
public:
    void make_sound() override
    {
        std::cout << "Bird sound\n";
    }
};

class AnimalFactory
{
public:
    static std::unique_ptr<Animal> createAnimal(std::string_view animal_type)
    {
        if (animal_type == "Dog")
        {
            return std::make_unique<Dog>();
        }
        else if (animal_type == "Cat")
        {
            return std::make_unique<Cat>();
        }
        else if (animal_type == "Bird")
        {
            return std::make_unique<Bird>();
        }
        else
        {
            std::cout << "Unknown animal type: " << animal_type << '\n';
            return nullptr;
        }
    }
};

int main()
{
    std::string animals[]{"Bird","Dog","Cat","Bird","Dog","Dog","test"};
    for (auto &animal : animals)
    {
        if (auto val{AnimalFactory::createAnimal(animal)})
        {
            val->make_sound();
        }
    }
}
