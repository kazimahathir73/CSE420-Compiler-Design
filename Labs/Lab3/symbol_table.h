#include "scope_table.h"

class symbol_table
{
private:
    scope_table *current_scope;
    int bucket_count;
    int current_scope_id;

public:
    symbol_table(int bucket)
    :bucket_count(bucket), current_scope_id(1)
    {   
        
        scope_table* new_scope_table = new scope_table(this->current_scope_id, nullptr, this->bucket_count);
        this->current_scope = new_scope_table;

    }
   
   
    //~symbol_table();



    void enter_scope(){
        this->current_scope_id++;
        scope_table* temp = this->current_scope;
        scope_table* new_scope_table = new scope_table(this->current_scope_id, temp , this->bucket_count);
        this->current_scope = new_scope_table;
    }
    void exit_scope(ofstream &outlog){
        outlog<<"Scopetable with ID " << to_string(this->current_scope->get_unique_id())   << " removed"<<endl<<endl;
        scope_table* temp = this->current_scope;
        this->current_scope = this->current_scope->get_parent_scope();
        delete temp;
       
    }


    bool insert(symbol_info* symbol){
        return this->current_scope->insert_in_scope(symbol);
    }


    bool insert_into_parent(symbol_info* symbol){
        return this->current_scope->get_parent_scope()->insert_in_scope(symbol);
    }

    bool remove(symbol_info* symbol){
        return this->current_scope->delete_from_scope(symbol);
    }

    symbol_info* lookup(symbol_info* symbol){
        scope_table* temp = this->current_scope;
        symbol_info* returned_pointer = NULL;

        while(  (temp != nullptr)  || (temp != NULL)  ){

            returned_pointer = temp->lookup_in_scope(symbol);
            if ( (returned_pointer != nullptr)  && (returned_pointer != NULL) ){
                break;
            }

            temp = temp->get_parent_scope();
        }
        return returned_pointer;

    }
    
    
    void print_current_scope(ofstream& outlog){
        this->current_scope->print_scope_table(outlog);
    }
    void print_all_scopes(ofstream& outlog);

    int get_id(){
        return this->current_scope_id;
    }

    

};    

// complete the methods of symbol_table class


void symbol_table::print_all_scopes(ofstream& outlog)
{
    outlog<<"################################"<<endl<<endl;
    scope_table *temp = current_scope;
    while (  (temp != NULL)  && (temp !=  nullptr)       )
    {
        temp->print_scope_table(outlog);
        temp = temp->get_parent_scope();
    }
    outlog<<"################################"<<endl<<endl;
}