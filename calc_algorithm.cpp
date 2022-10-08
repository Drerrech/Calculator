#include "calc_algorithm.h"

bool cstm::isdouble(std::string myString)
{
    std::istringstream iss(myString);
    double f;
    iss >> std::noskipws >> f;
    return iss.eof() && !iss.fail();
}


struct cstm::Op
{
    int found = 0;
    size_t pos = std::string::npos;

    void set_pos(size_t pos)
    {
        if (found == 0)
            this->pos = pos;
        found++;
    }
};


float cstm::rec(std::string s)
{
    if (s.empty())
        return 0.f;
    if (isdouble(s))
        return std::stof(s);

    std::unordered_map<char, Op> ops;

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(' || s[i] == ')') ops[s[i]].set_pos(i);
        else if (ops['('].found == ops[')'].found && 0 < i && i < s.size() - 1)
            for (char opi: "+*/")
                if (opi == s[i] || s[i] == '-' && isdigit(s[i - 1]))
                {
                    ops[s[i]].set_pos(i);
                    break;
                }
    }

    if (Op &opt = ops['+']; opt.found > 0)
        return rec(s.substr(0, opt.pos)) + rec(s.substr(opt.pos + 1));

    if (Op &opt = ops['-']; opt.found > 0)
        return rec(s.substr(0, opt.pos)) + rec(s.substr(opt.pos));

    if (Op &opt = ops['*']; opt.found > 0)
        return rec(s.substr(0, opt.pos)) * rec(s.substr(opt.pos + 1));

    if (Op &opt = ops['/']; opt.found > 0)
        return rec(s.substr(0, opt.pos)) / rec(s.substr(opt.pos + 1));

    if (Op &opt = ops['(']; opt.found > 0)
        return rec(s.substr(opt.pos + 1));

    if (Op &opt = ops[')']; opt.found > 0)
        return rec(s.substr(0, opt.pos));
}

double cstm::calcExpr(std::string s)
{
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());

    for (int i = 0; i < s.size() - 1; i++)
        if (s[i] == '-' && !isdigit(s[i + 1]))
        {
            s.insert(i + 1, "1*");
            i += 2;
        }

    return rec(s);
}
