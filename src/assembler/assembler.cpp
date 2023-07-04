#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include "consts.hpp"
#include <cmath>

using namespace std;

unsigned char instructions[4][7] = {
    {ADDX, MOVX, JMZX, SUBX, MULX, DIVX, LDRX},
    {ADDY, MOVY, JMZY, SUBY, MULY, DIVY, LDRY},
    {   0,    0,    0,    0,    0,    0,    0},
    {ADDXY, SUBXY, MULXY, DIVXY, 0,   0,    0}
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

bool set_jump(string label, unsigned long int &buff){
    //cout << label << "\n";
    if (labels.count(label) > 0 ){
        int id = labels[label];
        buff |= (0xFF00 & (id << 8));
        return true;
    }
    else
        return false;
}

int get_reg(string& line){
    if (line[0] == 'x' and line[1] == ',')
        return 0;
    if (line[0] == 'y' and line[1] == ',')
        return 1;
    
    return -1;
}

bool set_ops(string& line, unsigned long int &oper){
    string var = line.substr(2);    // rm "[origem],"
    //long int value = vars[var];
    if ( vars.count(var) > 0 ){
        struct posMen value = vars[var];
        oper |= (0xFF00 & (value.addr << 8) );
    }
    else{
        cerr << "Variável " << var << " não identificada.\n";
        return false;
    }
    return true;
}

int encode_operand(string& line, unsigned long int &oper){
    //static int ind = 1;
    //if (line.empty())     return;
    int bytes = -1, reg;
    
    if (line.find("add")==0){
        line = line.substr(3);
        if (line == "x,y"){
            oper |= instructions[3][0];
            bytes = 1;  }
        else if ((reg = get_reg(line)) == -1)  cerr << "Registrador não definido\n";

        else{
            if (reg == 0 and line[2] == 'y') 
                {oper |= instructions[3][0]; bytes = 1;}
            else{
                oper |= instructions[reg][0];
                if (set_ops(line, oper))        bytes = 2;
            }
        }
    }
    else if (line.find("mov")==0){
        line = line.substr(3);
        if ((reg = get_reg(line)) == -1)  cerr << "Registrador não definido\n";
        else{
            oper |= instructions[reg][1];
            if (set_ops(line, oper))        bytes = 2;
        }
    }
    else if (line.find("sub")==0){
        line = line.substr(3);
        if (line == "x,y"){
            oper |= instructions[3][1]; 
            bytes = 1;}
        else if ((reg = get_reg(line)) == -1)  cerr << "Registrador não definido\n";

        else{
            oper |= instructions[reg][3];
            if (set_ops(line, oper))        bytes = 2;
        }
    }
    else if (line.find("mul")==0){
        line = line.substr(3);
        if (line == "x,y"){
            oper |= instructions[3][2];
            bytes = 1;    }
        else if ((reg = get_reg(line)) == -1)  cerr << "Registrador não definido\n";

        else{
            oper |= instructions[reg][4];
            if (set_ops(line, oper))        bytes = 2;
        }
    }
    else if (line.find("div")==0){
        line = line.substr(3);
        if (line == "x,y"){
            oper |= instructions[3][3];
            bytes = 1;}
        else if ((reg = get_reg(line)) == -1)  cerr << "Registrador não definido\n";

        else{
            oper |= instructions[reg][5];
            if (set_ops(line, oper))        bytes = 2;
        }
    }
    else if (line.find("ldr")==0){
        line = line.substr(3);
        if ((reg = get_reg(line)) == -1)  cerr << "Registrador não definido\n";
        else{
            oper |= instructions[reg][6];
            if (set_ops(line, oper))        bytes = 2;
        }
    }
    else if (line.find("jmz")==0){
        line = line.substr(3);
        if ((reg = get_reg(line)) == -1)  cerr << "Registrador não definido\n";
        else{
            oper |= instructions[reg][2];
            if (set_jump(line.substr(2), oper))     bytes = 2;
            else    cerr << "Não foi possível identificar o rótulo associado a " << line << '\n';
        }
    }
    else if (line.find("halt") == 0 ){
        oper = HALT;
        bytes = 1;
    }
    else if (line.find("goto") == 0 ){
        oper |= GOTO;
        line = line.substr(4);
        if (set_jump(line, oper))
            bytes = 2;
        else
            cerr << "Não foi possível identificar o rótulo associado a " << line << '\n';
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
    
    int i = 1;
    int row = 0;
    
    //      --- Leitura de variáveis ----
    for (auto& l : lines) {
        ++row;
        if ( l.empty() );
        else if ((pos = is_variable(l)) != string::npos){
            if (!set_var(l, (i/4), pos)){       // assegure a que não terá truncamento
                cerr << "Erro de sintaxe na linha " << row <<  '\n';
                return EXIT_FAILURE;
            }
            i += 4;
        }
        else if (is_label(l)){
            labels[l.substr(0, l.length() - 1)] = i;
        }
        else if (l.find("wb") == 0 or l.substr(3) == "x,y")
            ++i;
        else
            i += 2;
    }

    i = 0;
    row = 0;
    unsigned long int buff = 0;
    int bytes = 0;

    //      --- 
    for (auto& l : lines) {
        ++row;

        if (l.empty() or is_label(l));
        else if (encode_byte(l, buff))
            bytes = 1;
        else if (encode_var(l, buff))
            bytes = 4;
        else if ((bytes += encode_operand(l, buff)) == -1){
            cerr << "Erro de sintaxe na linha " << row << '\n';
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

