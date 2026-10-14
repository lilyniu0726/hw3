#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */

  //Constructor declaration
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap() = default;

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> heap_vec;
  int m_;
  PComparator c_;
  void swap(int i, int j);

};

//Constructor definition
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) : m_(m), c_(c) {};

// Add implementation of member functions here
template <typename T, typename PComparator>
void Heap<T,PComparator>::swap(int i, int j){
  T val = heap_vec[j];
  heap_vec[j] = heap_vec[i];
  heap_vec[i] = val;
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
  if(heap_vec.empty()){
    heap_vec.push_back(item);
    return;
  }
  heap_vec.push_back(item);
  int item_ind = heap_vec.size() - 1;
  while(item_ind > 0){
    int parent_ind = (item_ind - 1)/m_;
    if(c_(heap_vec[item_ind], heap_vec[parent_ind])){
      swap(item_ind, parent_ind);
      item_ind = parent_ind;
    }
    else{
      break;
    }
  }
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw(std::underflow_error("Empty Heap!"));
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return heap_vec[0];

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw(std::underflow_error("Empty Heap!"));
  }
  swap(0, heap_vec.size()-1);
  heap_vec.pop_back();
  int root_ind = 0;
  while(root_ind < int(heap_vec.size())){
    int first = root_ind*m_ + 1;
    if(first >= int(heap_vec.size())){
      break;
    }
    int best = first;
    for(int j = 1; j < m_ && first + j < int(heap_vec.size()); j++){
      if(c_(heap_vec[first+j], heap_vec[best])){
        best = first+j;
      }
    }

    // The parent already has at least as much priority as its best child.
    if (!c_(heap_vec[best], heap_vec[root_ind])) {
      break;
    }
    swap(best, root_ind);
    root_ind = best;
    }
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
  return heap_vec.empty();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const{
  return heap_vec.size();
}

#endif

