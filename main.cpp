//
//  main.cpp
//  Project
//
//  Created by Charley on 3/18/24.
//

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <unordered_map>


using namespace std;

//reads the input file and makes it a string
string inpFile()
{
    string str;
    ifstream input("input_scode.txt");
    if(input.is_open())
    {
        while(getline(input, str)){
            return str;
        }
        input.close();
    }
    return "No File";
}


size_t position = 0;
string str = inpFile();

string keyword()
{
    size_t start = position;
    vector<string> key = {"while", "if", "else", "then"};
    while(position < str.size() && isalnum(str[position]))
    {
        ++position;
    }
    string token = str.substr(start, position-start);
    for(int i = 0; i < key.size(); i++)
    {
        if(key[i] == token)
        {
            return("KEYWORD     " + token);
        }
    }
    return "IDENTIFIER  " + token;
}
   
string numbers()
{
    size_t start = position;
    while(position < str.size() && (isdigit(str[position]) || str[position] == '.'))
    {
        ++position;
    }
    string token = str.substr(start, position - start);
    return "REAL        " + token;
}

string separator()
{
    vector<char> seps = {'(', ')', '[', ']', ';', '{','}'};
    char current  = str[position];
    string sep = "SEPARATOR   ";
    while(position < str.size() && (str[position] == '(' || str[position] ==')'||str[position] == '['||
          str[position] == ']' || str[position] == ';' || str[position] == '{'|| str[position] == '}'))
    {
        ++position;
    }
    for(int j = 0; j < str.size(); j++)
    {
        if(seps[j] == current)
        {
            sep.push_back(current);
        }
    }
    return sep;
}
    
string oper()
{
    vector<char> symbols = {'=', '<', '>', '+', '*', '/'};
    char current  = str[position];
    string op = "OPERATOR    ";
    while(position < str.size() && (str[position] == '=' || str[position] =='<'||str[position] == '>'||
                                str[position] == '+' || str[position] == '*' || str[position] == '/'))
    {
        ++position;
    }
    for(int j = 0; j < str.size(); j++)
    {
        if(symbols[j] == current)
        {
            op.push_back(current);
        }
    }
    return op;
    
}
    
void Lexer()
{
    vector<string> tok;
    while(position < str.size())
    {
        char current = str[position];
        if(isspace(current))
        {
            position++;
        }
        else if(isalpha(current))
        {
            tok.push_back(keyword());
        }
        else if (isdigit(current) || current == '.')
        {
            tok.push_back(numbers());
        }
        else if(current == '(' || current ==')'||current == '['|| current == ']' || current == ';' || current == '{' || current == '}')
        {
            tok.push_back(separator());
        }
        else if(current == '=' || current =='<'||current == '>'|| current == '+' || current == '*' ||current == '/')
        {
            tok.push_back(oper());
        }
    }
    
    ofstream out;
    out.open("output.txt");
    out << "Token:      Lexeme:" << endl;
    for(int i = 0; i < tok.size(); i++)
    {
        out << tok[i] << endl;
    }
    out.close();
}


int main()
{
    Lexer();
}
