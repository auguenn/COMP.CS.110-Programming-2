#include "queue.hh"
#include <iostream>
using namespace std;

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle){
    this->cycle_=cycle;
}

Queue::~Queue(){
    while ( first_ != nullptr ) {
       Vehicle* item_to_be_released = first_;
       first_ = first_->next;
       delete item_to_be_released;
    }
}
int Queue::get_cycle(){
    return cycle_;
}
bool Queue::get_is_green(){
    return is_green_;
}
void Queue::enqueue(string reg){
    Vehicle* temp = new Vehicle;
        temp->reg_num=reg;
        if(is_green_==false){
            if (last_ == NULL) {
                first_ = last_ = temp;
                return;
            }
            last_->next = temp;
            last_ = temp;
        }
        else{
            cout<<"GREEN: The vehicle "<<temp->reg_num<< " need not stop to wait"<<endl;
        }
}
void Queue::dequeue(){
    if (first_ == NULL)
        return;
    Vehicle* temp = first_;
    first_ = first_->next;
    if (first_ == NULL)
        last_ = NULL;
    delete temp;
}
int Queue::num_in_queue(){
    int count = 0; // Initialize count
    Vehicle* current = first_; // Initialize current
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}
void Queue::toogle_is_green(){
    if(is_green_==false){
        is_green_=true;
    }
    else if(is_green_==true){
        is_green_=false;
    }
}
void Queue::switch_light(){
    toogle_is_green();
    Vehicle *ptr = first_;

    if(get_is_green()==true  && num_in_queue()==0){
        cout<< "GREEN: No vehicles waiting in traffic lights"<<endl;
    }
    else if(get_is_green()==false && num_in_queue()==0){
        cout<< "RED: No vehicles waiting in traffic lights"<<endl;
    }
    else if(is_green_==true && num_in_queue()!=0){
        cout<< "GREEN: Vehicle(s) ";
        if(num_in_queue()<get_cycle()){
            for(int i=0;i<num_in_queue();i++){
                while( ptr !=NULL){
                    cout<<ptr->reg_num<<" ";
                    ptr= ptr->next;
                }
                dequeue();
             }
         }
         else if(num_in_queue()>=get_cycle()){
            for(int i=0;i<get_cycle();i++){
               cout<<ptr->reg_num<<" ";
               ptr= ptr->next;
               dequeue();
             }
         }
         cout<< "can go on "<<endl;
         is_green_=false;
    }
}

void Queue::reset_cycle(unsigned int cycle){
    this->cycle_=cycle;
}

void Queue::print(){
    if(get_is_green()==true){
        cout<< "GREEN: ";
    }
    else if(get_is_green()==false){
        cout<< "RED: ";
    }
    if(first_==nullptr)
        cout<<"No vehicles waiting in traffic lights"<<endl;
    else{
        Vehicle *ptr = first_;
        cout<< "Vehicle(s) ";
        while( ptr !=NULL)
        {
            cout<<ptr->reg_num<<" ";
            ptr= ptr->next;
        }
        cout<< "waiting in traffic lights"<<endl;
    }
}
