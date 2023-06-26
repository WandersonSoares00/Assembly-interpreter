#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include "inc/common.hpp"
#include <cmath>

using namespace std;

map <string, unsigned char> instructions{
    {"add",   0x02}, {"mov",  0x0A}, {"goto", 0x09},
    {"jmz",   0x0B}, {"sub",  0x0D}, {"halt", 0xFF}
};

struct posMen   {  int addr; long int value;    };

//  par variável e opcode
map <string, posMen> vars;

// associa um label a um endereço de memória(id)
map <string, int> labels;

bool read_int(unsigned long int& v1, string str){
    stringstream origem(str);
    origem >> v1;
    if (origem.fail())
        return false;
    return true;
}

size_t is_variable(string& line){
    return line.find("ww");
}

bool set_var(string& line_var, int addr, int n){
    long int val;
    
    stringstream origem(line_var);
    origem.ignore(n+2) >> val;

    if (origem.fail())
        return false;
    
    string var = line_var.substr(0, n);
    vars[var] = {addr, val};

    return true;
}


bool is_label(string& line){
    auto ret = line.find(':');
    if ( ret != string::npos && ret == (line.length() - 1) )
        return true;
    return false;
}

void set_label(string& line_label, int id){
    line_label.pop_back();  // rm :
    labels[line_label] = id;
}

bool set_ops(string& line, unsigned long int &oper){
    if (line[0] == 'x' and line[1] == ','){
        string var = line.substr(2);
        //long int value = vars[var];
        if ( vars.count(var) > 0 ){
            struct posMen value = vars[var];
            oper |= (0xFF00 & (value.addr << 8) );
        }
        else
            return false;
    }
    return true;
}

int encode_operand(string& line, unsigned long int &oper){
    //static int ind = 1;
    //if (line.empty())     return;
    int bytes = -1;

    if (line.find("add")==0 or line.find("mov")==0 or line.find("jmz")==0 or line.find("sub")==0){
        oper |= instructions[line.substr(0, 3)];
        line.erase(0, 3);   // desnescessário
        //cout << line << "  " << (0xFF & oper) << "  " << '\n';
        if (set_ops(line, oper))   bytes = 2;
    }
    else if (line.find("halt") == 0 ){
        oper = instructions["halt"];
        bytes = 1;
    }
    else if (line.find("goto") == 0 ){
        oper = instructions["goto"];
        string label = line.substr(4);
        if (labels.count(label) > 0 ){
            int id = labels[label];
            oper |= instructions["goto"];
            oper |= (0xFF00 & (id << 8));
            bytes = 2;
        }
    }

    return bytes;
}

bool encode_var(string& line_var, unsigned long int &buff){
    size_t pos = is_variable(line_var);
    if (pos == string::npos)
        return false;
    string var = line_var.substr(0, pos);
    
    buff = vars[var].value;

    return true;
}

bool encode_byte(string& line_wb, unsigned long int &buff){
    size_t pos = line_wb.find("wb");
    if ( pos != 0 )     // pos == string::npos
        return false;
    int val;
    stringstream origem(line_wb);
    origem.ignore(2) >> val;
    if ( origem.fail() or val > 255 )
        return false;
    
    buff |= ( 0xFF & val);

    return true;
}

void usage (int status) {
    exit (status);
}

int main(int argc, char **argv) {

    if (argc < 2){
        cerr << "Arquivo de entrada não informado como argumento.\n";
        usage (EXIT_FAILURE);
    }

    string out_file("out");
    if (argc >= 3)
        out_file.assign(argv[2]);

    ifstream input  (argv[1], ios::in);
    ofstream output (out_file, ios::binary );

    vector<string> lines;
    string line;
    size_t pos;

    while (getline(input, line)) {
        line.erase( remove_if(line.begin(), line.end(), ::isspace ), line.end() );
        if ( (pos = line.find(';')) != string::npos )
            line.erase(pos);
        lines.push_back(line);
    }
    
    input.close();
    
    int i = 0;
    int row = 0;
    int last_byte = 0;

    //      --- Leitura de variáveis ----
    for (auto& l : lines) {
        ++row;
        if ( l.empty() );
        else if ((pos = is_variable(l)) != string::npos){
            if (!set_var(l, i, pos)){
                cerr << "Erro de sintaxe na linha " << row <<  '\n';
                return EXIT_FAILURE;
            }
            last_byte = i;
            i += 4;
        }
        else if (is_label(l))
            set_label(l, i+1);
        else
            i += 2;
    }
    
    i = 0;
    unsigned long int buff = 0;
    int bytes = 0;

    output.write((char*) &last_byte, 1);

    //      --- 
    for (auto& l : lines) {
        ++row;

        if ( l.empty() );
        else if (encode_byte(l, buff))
            ++bytes;
        else if (encode_var(l, buff))
            bytes += 4;
        else if ((bytes += encode_operand(l, buff)) == -1){
            cerr << "Erro de sintaxe na linha " << row << l << '\n';
            return EXIT_FAILURE;
        }
        
        //cout << bin <1>(buff>>24) <<  ' ' << bin <1>(buff>>16) << ' ';
        //cout << bin <1>(buff>> 8) <<  ' ' << bin <1>(buff) << '\n';

        if (bytes > 0){
            output.write((char*) &buff, bytes);
            buff >>= (8 * bytes);
            bytes = 0;
        }
    }

    return EXIT_SUCCESS;
}




