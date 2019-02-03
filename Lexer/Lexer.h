#include <string>

class Lexer
{
private:
    int _val;
    std::string _bar;
public:
    Lexer() {};
    ~Lexer() {};

    const std::string& bar() const { return _bar; } 
    void bar(const std::string& bar) { _bar = bar; }
};
