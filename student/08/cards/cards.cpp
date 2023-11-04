#include "cards.hh"

// TODO: Implement the methods here

Cards::Cards():
  top_(nullptr)
{

}


Card_data *Cards::get_topmost()
{
  return top_;
}


void Cards::add(int id)
{
  // create new cards
  Card_data *card = new Card_data{id, top_};
  top_ = card;
}


void Cards::print_from_top_to_bottom(std::ostream &s)
{
  Card_data *current = top_;

  uint i = 1;

  while(current != nullptr)

    {
      s << i++ << ": " << current->data << std::endl;
      current = current->next;
    }
}


bool Cards::remove(int &id)
{
  // structure is empty
  if(top_ == nullptr)
    return false;

  Card_data *ptr = top_;
  top_ = top_->next;

  id = ptr->data;

  delete ptr;

  return true;

}


bool Cards::bottom_to_top()
{
  if(top_ == nullptr)
    return false;

  // fetch last item
  Card_data *bottom = top_;
  Card_data *previous = bottom;
  while(bottom->next != nullptr)
    {
      previous = bottom;
      bottom = bottom->next;
    }
  bottom->next = top_;
  top_ = bottom;
  previous->next = nullptr;
  return true;

}


bool Cards::top_to_bottom()
{
  if(top_ == nullptr)
    return false;

  if(top_->next == nullptr)
    return false;

  Card_data *first_top = top_;
  Card_data *bottom = top_;
  top_ = top_->next;

  // find bottom
  while(bottom->next != nullptr)
    bottom = bottom->next;

  bottom->next = first_top;
  first_top->next = nullptr;
  return true;
}


void Cards::print_from_bottom_to_top(std::ostream &s)
{
  recursive_print(top_, s);
}

Cards::~Cards()
{
  // loop through cards and deallocate memory
  Card_data *ptr = top_;
  while(ptr != nullptr)
    {
      top_ = top_->next;
      delete ptr;
      ptr = top_;
    }
}

int Cards::recursive_print(Card_data *top, std::ostream &s)
{
  // use tail recursion
  // trivial case
  if(top == nullptr)

    return 1;
  int index = recursive_print(top->next, s);
  s << index << ": " << top->data << std::endl;

  return index + 1;

}
