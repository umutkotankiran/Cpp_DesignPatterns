#include <iostream>
#include <memory>
#include <string_view>
#include <vector>

class Button
{
public:
    virtual ~Button() = default;
    virtual void click() = 0;
    virtual void render() = 0;
};

class TextBox
{
public:
    virtual ~TextBox() = default;
    virtual void render() = 0;
    virtual void type(const char *msg) = 0;
};

class WindowsButton : public Button
{
public:
    virtual void click()override
    {
        std::cout << "Windows button clicked\n";
    }
    virtual void render()override
    {
        std::cout << "Windows button rendered\n";
    }
};

class WindowsTextBox : public TextBox
{
public:
    virtual void render()override
    {
        std::cout << "Windows Textbox rendered\n";
    }

    virtual void type(const char *msg)override
    {
        std::cout << "Windows Textbox type: " << msg << "\n";
    }
};

class LinuxButton : public Button
{
public:
    virtual void click()override
    {
        std::cout << "Linux button clicked\n";
    }
    virtual void render()override
    {
        std::cout << "Linux button rendered\n";
    }
};

class LinuxTextBox : public TextBox
{
public:
    virtual void render()override
    {
        std::cout << "Linux Textbox rendered\n";
    }

    virtual void type(const char *msg)override
    {
        std::cout << "Linux Textbox type: " << msg << "\n";
    }
};

class UIFactory
{
public:
    virtual ~UIFactory() = default;
    virtual std::unique_ptr<Button> create_button() = 0;
    virtual std::unique_ptr<TextBox> create_textbox() = 0;
    virtual std::string get_theme_name() = 0;

};

class WindowsUIFactory : public UIFactory
{
public:
    virtual std::unique_ptr<Button> create_button()override
    {
        return std::make_unique<WindowsButton>();
    }

    virtual std::unique_ptr<TextBox> create_textbox()override
    {
        return std::make_unique<WindowsTextBox>();
    }

    std::string get_theme_name()override
    {
        return "Windows UIFactory";
    }
};

class LinuxUIFactory : public UIFactory
{
public:
    virtual std::unique_ptr<Button> create_button()override
    {
        return std::make_unique<LinuxButton>();
    }

    virtual std::unique_ptr<TextBox> create_textbox()override
    {
        return std::make_unique<LinuxTextBox>();
    }

    std::string get_theme_name()override
    {
        return "LinuxUIFactory";
    }
};


class Application
{
public:
    Application(std::unique_ptr<UIFactory> factory) : m_factory(std::move(factory))
    {
        std::cout << m_factory->get_theme_name() << " is loading\n";
        m_button = m_factory->create_button();
        m_textbox = m_factory->create_textbox();
    }

    void createUI()
    {
        std::cout << "UI is creating\n";
        m_button->render();
        m_textbox->render();
    }

    void UserInteraction()
    {
        std::cout << "User Interaction\n";
        m_textbox->type("Hello world");
        m_button->click();
    }

private:
    std::unique_ptr<UIFactory> m_factory;
    std::unique_ptr<Button> m_button;
    std::unique_ptr<TextBox> m_textbox;
};

std::unique_ptr<UIFactory> createUIForOS(const std::string_view os)
{
    if (os == "Windows" || os == "windows")
        return std::make_unique<WindowsUIFactory>();
    else if (os == "Linux" || os == "linux")
        return std::make_unique<LinuxUIFactory>();
    else
        throw std::runtime_error("Unknown OS");
}

int main()
{
    std::vector<std::string> os {"Linux","Windows"};
    for (auto &s : os)
    {
        auto f{createUIForOS(s)};
        Application a{std::move(f)};
        a.createUI();
        a.UserInteraction();
    }
}

