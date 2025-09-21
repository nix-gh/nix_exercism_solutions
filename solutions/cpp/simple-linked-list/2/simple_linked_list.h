#pragma once

#include <cstddef>
#include <memory>

namespace simple_linked_list {

class List {
   public:
   List() = default;
   ~List() = default;
   
   List(const List&) = delete;
   List& operator=(const List&) = delete;
   List(List&&) = default;
   List& operator=(List&&) = default;

   std::size_t size() const;
   void push(int entry);
   int pop();
   void reverse();

   private:
   struct Element {
      Element(int data)
      : m_data{ data } {};
      Element(int data, std::unique_ptr<Element> next)
      : m_data{ data }
      , m_next(std::move(next)){};
      int m_data{};
      std::unique_ptr<Element> m_next{};
   };

   std::unique_ptr<Element> m_head{};
   std::size_t m_current_size{ 0 };
};

} // namespace simple_linked_list
