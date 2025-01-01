#include "symbol_info.h"

class scope_table
{
private:
    int bucket_count;
    int unique_id;
    scope_table *parent_scope = NULL;
    vector<symbol_info *> table;

public:
    void print_scope_table(ofstream &outlog);

    scope_table(int id, scope_table *parent, int bucket)
        :  unique_id(id), parent_scope(parent),bucket_count(bucket)
    {
        table.resize(bucket, nullptr);
    }
    // scope_table(int bucket_count, int unique_id, scope_table *parent_scope);

    scope_table *get_parent_scope()
    {
        return parent_scope;
    }

    void set_parent_scope( scope_table* parent ){
        this->parent_scope = parent;
    }

    int get_unique_id()
    {
        return this->unique_id;
    }

    symbol_info *lookup_in_scope(symbol_info *symbol)
    {
        int iterator = 0;
        int index = hash_function(symbol->getname());
        while (iterator < this->bucket_count)
        {
            if (this->table[index]->getname() == symbol->getname())
            {
                return table[index];
            }
            index = (index + 1) % (this->bucket_count);
            iterator++;
        }

        return nullptr;
    }

    bool insert_in_scope(symbol_info *symbol)
    {

        int index = this->hash_function(symbol->getname());
        cout<<to_string(index)<<" !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << symbol->getname()  <<endl<<endl;
        int iteration_count = 0;

        while (1)
        {
            if (this->table[index] == nullptr)
            {
                this->table[index] = symbol;
                return 1;
            }

            if (this->table[index]->getname() == symbol->getname())
            {
                return 0;
            }

            if (iteration_count > this->bucket_count)
            {
                return 0;
            }

            index = (index + 1) % (this->bucket_count);
            iteration_count++;
        }
    }

    bool delete_from_scope(symbol_info *symbol)
    {
        int index = this->hash_function(symbol->getname());
        int iteration_count = 0;

        while (1)
        {
            if (this->table[index] == nullptr)
            {
                return 0;
            }

            if (this->table[index]->getname() == symbol->getname())
            {
                this->table[index] = nullptr;
                return 1;
            }

            if (iteration_count > this->bucket_count)
            {
                return 0;
            }

            index = (index + 1) % (this->bucket_count);
            iteration_count++;
        }
    }

    int hash_function(string name)
    {
        int total = 0;
        for (int i = 0; i < name.size(); ++i)
        {
            int ascii = static_cast<int>(name[i]);
            total = total + ascii;
        }
        return (total % this->bucket_count);
    }
    // ~scope_table(ofstream &outlog){
    //     outlog<<"Scopetable with ID 2 removed"<<endl;
    // }
};

// you can add more methods if you need

// complete the methods of scope_table class
void scope_table::print_scope_table(ofstream &outlog)
{
    outlog << "ScopeTable # " + to_string(unique_id) << endl;

    for (int i = 0; i < this->bucket_count; i++)
    {
        if ((this->table[i] == NULL) || (this->table[i] == nullptr))
        {
            continue;
        }
        else
        {
            
            if (this->table[i]->get_type() == "func_def")
            {
                outlog << to_string(i) << " -->" << endl
                       << "< " << this->table[i]->getname() << " : ID >" << endl << "Function Definition" << endl;
                outlog << "Return Type: " << this->table[i]->get_ret_type() << endl;
                outlog << "Number of parameter: " << to_string(this->table[i]->get_param_num()) << endl;
                outlog << "Parameter Details: ";
                for (int j = 0 ;   j < this->table[i]->get_param_list().size()   ;     j = j+2  ){
                    outlog << this->table[i]->get_param_list()[j] << " " << this->table[i]->get_param_list()[j+1] << "        ";
                }
                outlog<<endl;
            }

            if (      (this->table[i]->get_type() == "variable")   ||    (this->table[i]->get_type() == "array")  )
            {
                outlog<< to_string(i)  << "-->"  << endl;
                outlog<<  "< " <<  this->table[i]->getname()   << " : ID >" << endl;
                outlog<<    this->table[i]->get_type()    << endl;
                outlog<< "Type: " << this->table[i]->get_var_type() << endl;   


            }

        }


        outlog << endl<< endl<<endl<<endl;
    }
}
