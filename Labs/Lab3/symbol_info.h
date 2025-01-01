#include<bits/stdc++.h>
using namespace std;

class symbol_info
{
private:
    string name;
    string type;


    string ret_type;
    int param_num;
    vector<string> param_list;
    string var_type;

public:
    symbol_info(string name, string type)
    {
        this->name = name;
        this->type = type;
        
    }
    string getname()
    {
        return name;
    }
    string get_type()
    {
        return type;
    }
    string get_ret_type(){
        return this->ret_type;
    }
   
    int get_param_num(){
        return this->param_num;
    }

    string get_var_type(){
        return this->var_type;
    }

    vector<string> get_param_list(){
        return this->param_list;
    }

    void set_name(string name)
    {
        this->name = name;
    }
    void set_type(string type)
    {
        this->type = type;
    }

    void set_param_list(vector<string> list){
        this->param_list = list;
    }

    void set_ret_type(string ret){
        this->ret_type = ret;
    }


    void set_param_num(int num){
        this->param_num = num;
    }

    void set_var_type(string type){
        this->var_type = type;
    }

    ~symbol_info()
    {
        // Write necessary code to deallocate memory, if necessary
    }
};