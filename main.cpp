
#include <iostream>
#include <string>
#include <vector>

#define debug(x) std::cout << #x << " = " << x << "\n";
#define vdebug(a) std::cout << #a << " = "; for(auto x: a) std::cout << x << " "; std::cout << "\n";

using Tokens = std::vector< std::string >; 

class Tokenizer {

    private:
        std::string exp_;
        size_t head;
        Tokens tokens_;

        char peek(auto const &iter)
        {
            return *(iter + 1);
        }

        void skipWhiteSpace(auto &iter)
        {
            bool cond = true;
            while(cond)
            {
                switch(*iter)
                {
                    case '\t':
                        iter++;
                        cond = true;
                        break;
                    case ' ':
                        iter++;
                        cond = true;
                        break;
                    case '\n':
                        iter++;
                        cond = true;
                        break;
                    case '\r':
                        iter++;
                        if(peek(iter) == '\n')
                            iter++;
                        cond = true;
                        break;
                    default:
                        cond = false;
                        break;
                }
            }
        }

        void digit(auto &iter) 
        { 
            auto start = iter;
            while(*iter >= '0' && *iter <= '9')
            {
                iter++;
            }
            tokens_.push_back(std::string(start, iter));
        };

        void syntax(auto &iter) 
        { 
            switch(*iter)
            {
                case '+':
                    iter++;
                    tokens_.push_back("+");
                    break;
                case '-':
                    iter++;
                    tokens_.push_back("-");
                    break;
                case '(':
                    iter++;
                    tokens_.push_back("(");
                    break;
                case ')':
                    iter++;
                    tokens_.push_back(")");
                    break;
            }
        };

    public:
        Tokenizer() = default;
        Tokenizer(const std::string Exp) : exp_{Exp} {};

        Tokens tokenize()
        {
            auto iter = exp_.begin();

            for(;iter != exp_.end();)
            {
               skipWhiteSpace(iter);
               digit(iter); 
               syntax(iter); 
            }

            tokens_.push_back("EOF");
            return tokens_;
        }

        Tokens getTokens(){ return tokens_; }
        void setTokens(Tokens tokens) { tokens_ = tokens; }
        void setExp(std::string Exp) { exp_ = Exp; }
};

class Expression {

private: 

    Tokenizer tokenizer_{};

public:

    Expression() = default;

    int evaluate(std::string str)
    {
        tokenizer_.setExp(str);
        auto tokens_ = tokenizer_.tokenize();

    }

    int evaluate(Tokens tokens_);

    Tokens tokenize(std::string str_)
    {
        tokenizer_.setExp(str_);
        return tokenizer_.tokenize();
    }

};

int main(int argc, char **argv)
{ 
    if(argc <= 1)
    {
        std::exit(1);
    }

    std::string expression(argv[1]);
    Expression e{};
    auto t = e.tokenize( " \n \n ( 99923  +  \n  90293 )   + 30402 " );

    return EXIT_SUCCESS;
}

