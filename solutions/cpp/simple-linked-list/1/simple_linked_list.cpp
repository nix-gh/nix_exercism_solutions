#include "simple_linked_list.h"

#include <memory>

namespace simple_linked_list {

std::size_t List::size() const {
   return m_current_size;
}

void List::push(int entry) {
   m_head = std::make_unique<Element>(entry, std::move(m_head));
   m_current_size++;
}

int List::pop() {
   if(!m_head) {
   }
   auto head = std::move(m_head);
   m_head = std::move(head->m_next);
   m_current_size--;
   return head->m_data;
}

void List::reverse() {
    List reversed;
    while(size()!=0){
        reversed.push(pop());
    }
    *this = std::move(reversed);
}


} // namespace simple_linked_list
