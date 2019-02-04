#include <string>
#include <vector>

class Lexer
{
private:
    int _val;
    std::string _bar;
public:
    Lexer(const std::vector<std::string>& words);
    ~Lexer() {};

    std::vector<std::string>* _words;

    const std::string& bar() const { return _bar; } 
    void bar(const std::string& bar) { _bar = bar; }
};
