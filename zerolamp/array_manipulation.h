#ifndef ZB_ARRAY_MANIPULATION_H
#define ZB_ARRAY_MANIPULATION_H

#include <stack>

template <typename T>
class ArrayManipulationAlgorithm {

public:

  virtual void step(T* array) = 0;

  virtual bool is_completed() = 0;

  virtual ~ArrayManipulationAlgorithm() {}

};

template <typename T>
class FisherYatesShuffleAlgorithm : public ArrayManipulationAlgorithm<T> {

private:
  int array_size;
  int i;
  bool completed;

public:
  FisherYatesShuffleAlgorithm(int array_size) : array_size(array_size), i(array_size - 1), completed(array_size <= 1) {}

  void step(T* array) {

    assert(!completed);
    assert(i > 0);

    int j = random(0, i + 1);

    std::swap(array[i], array[j]);

    i--;

    if (i == 0) {
      completed = true;
    }

  }

  bool is_completed() {
    return completed;
  }

};

template <typename T>
class BubbleSortAlgorithm : public ArrayManipulationAlgorithm<T> {

private:
  int array_size;
  int i = 0;
  int j = 0;
  bool completed;

public:
  BubbleSortAlgorithm(int array_size) : array_size(array_size), completed(array_size <= 1) {}

  void step(T* array) {

    // bubble sort:
    // for (int i = 0; i < array_size - 1; i++) {
    //   for (int j = 0; j < array_size - 1 - i; j++) {
    //     if (array[j] > array[j + 1]) {
    //       std::swap(array[j], array[j+1]);
    //     }
    //   }
    // }

    assert(!completed);

    if (i >= array_size - 1) {
      completed = true;
      return;
    }

    if (j >= array_size - 1 - i) {
      // inner loop finished execution
      i++;
      j = 0;
      if (i >= array_size - 1) {
        completed = true;
        return;
      }
    }

    if (array[j] > array[j + 1]) {
      std::swap(array[j], array[j+1]);
    }

    j++;

  }

  bool is_completed() {
    return completed;
  }

};

template <typename T>
class InsertionSortAlgorithm : public ArrayManipulationAlgorithm<T> {

private:
  int array_size;
  int i = 1;
  int j = 0;
  T key;
  bool at_the_beginning_of_outer_loop = true;
  bool completed;

public:
  InsertionSortAlgorithm(int array_size) : array_size(array_size), completed(array_size <= 1) {}

  void step(T* array) {

    // insertion sort:
    /*
    for (int i = 1; i < n; i++) {
      int key = arr[i];
      int j = i - 1;
      while (j >= 0 && arr[j] > key) {
        arr[j + 1] = arr[j];
        j = j - 1;
      }
      arr[j + 1] = key;
    }
    */

    assert(!completed);

    if (i >= array_size) {
      completed = true;
      return;
    }

    if (at_the_beginning_of_outer_loop) {
      key = array[i];
      j = i - 1;
      at_the_beginning_of_outer_loop = false;
    }

    if (j >= 0 && array[j] > key) {
      // while loop condition met
      // run body of the while loop
      array[j + 1]  = array[j];
      j--;
    }
    else {
      array[j + 1] = key;
      i++;
      if (i >= array_size) {
        completed = true;
        return;
      }
      at_the_beginning_of_outer_loop = true;
    }

  }
  
  bool is_completed() {
    return completed;
  }

};

template <typename T>
class SelectionSortAlgorithm : public ArrayManipulationAlgorithm<T> {

private:
  int array_size;
  int i = 0;
  bool completed;

public:
  SelectionSortAlgorithm(int array_size) : array_size(array_size), completed(array_size <= 1) {}

  void step(T* array) {

    // selection sort:
    /*
      for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
          if (arr[j] < arr[min_index]) {
            min_index = j;
          }
        }
        std::swap(arr[i], arr[min_index]);
      }
    */

    assert(!completed);
    assert(i <= array_size - 1);

    if (i == array_size - 1) {
      completed = true;
      return;
    }

    int min_index = i;

    for (int j = i + 1; j < array_size; j++) {
      if (array[j] < array[min_index]) {
        min_index = j;
      }
    }

    std::swap(array[i], array[min_index]);
    i++;

    if (i == array_size - 1) {
      completed = true;
    }

  }
  
  bool is_completed() {
    return completed;
  }

};

template <typename T>
class MergeSortAlgorithm : public ArrayManipulationAlgorithm<T> {

private:
  enum class AlgoState {
    OUTER_LOOP,
    INNER_LOOP,
    MERGE_LOOP_1,
    MERGE_LOOP_2,
    MERGE_LOOP_3
  };

  int array_size;
  T* temp;
  int size = 1;
  int left;
  int mid;
  int right;
  int i;
  int j;
  int k;

  AlgoState state = AlgoState::OUTER_LOOP;
  bool completed;

public:
  MergeSortAlgorithm(int array_size) : array_size(array_size), completed(array_size <= 1) {
    temp = new T[array_size];
  }

  void step(T* array) {

    // merge sort pseudocode with labels
    /*

    int size = 1;

    // --------------------------------
    // label: AlgoState::OUTER_LOOP
    // --------------------------------
    for (; size < array_size; size *= 2) {

      // create a copy of the array
      std::copy(array, array + array_size, temp);

      int left = 0;

      // --------------------------------
      // label: AlgoState::INNER_LOOP
      // --------------------------------
      for (; left < array_size; left += 2 * size) {
        
        int mid = left + size;
        if (mid > array_size) {
          mid = array_size;
        }

        int right = left + 2 * size;
        if (right > array_size) {
          right = array_size;
        }
        
        int i = left; // starting index for left subarray
        int j = mid; // starting index for right subarray
        int k = left; // starting index to store sorted elements

        // --------------------------------
        // label: AlgoState::MERGE_LOOP_1
        // --------------------------------
        // merge sorted array fragments
        while (i < mid && j < right) {
          if (temp[i] <= temp[j]) {
            array[k++] = temp[i++];
          }
          else {
            array[k++] = temp[j++];
          }
        }

        // --------------------------------
        // label: AlgoState::MERGE_LOOP_2
        // --------------------------------
        // copy remaining elements of the left subarray, if any
        while (i < mid) {
          array[k++] = temp[i++];
        }

        // --------------------------------
        // label: AlgoState::MERGE_LOOP_3
        // --------------------------------
        // copy remaining elements of the right subarray, if any
        while (j < right) {
          array[k++] = temp[j++];
        }

      }
    }
    */

    assert(!completed);

    while (true) {
      switch (state) {

        case AlgoState::OUTER_LOOP:

          if (size >= array_size) {
            completed = true;
            return;
          }

          // create a copy of the array
          std::copy(array, array + array_size, temp);

          left = 0;

          state = AlgoState::INNER_LOOP;

          break;

        case AlgoState::INNER_LOOP:

          if (left >= array_size) {
            // condition of the inner loop not satisfied
            size <<= 1;
            state = AlgoState::OUTER_LOOP;
          }
          else {
            // run the body of the inner loop
            mid = left + size;
            if (mid > array_size) {
              mid = array_size;
            }

            right = left + 2 * size;
            if (right > array_size) {
              right = array_size;
            }
            
            i = left; // starting index for left subarray
            j = mid; // starting index for right subarray
            k = left; // starting index to store sorted elements

            state = AlgoState::MERGE_LOOP_1;
          }

          break;

        case AlgoState::MERGE_LOOP_1:

          if (i < mid && j < right) {
            // run the body of the loop

            if (temp[i] <= temp[j]) {
              array[k++] = temp[i++];
            }
            else {
              array[k++] = temp[j++];
            }

            return; // since we changed an array element, the current step has ended

          }
          else {
            // the condition of the loop doesn't hold
            // go to the next loop
            state = AlgoState::MERGE_LOOP_2;
          }

          break;

        case AlgoState::MERGE_LOOP_2:

          if (i < mid) {
            // run the body of the loop
            array[k++] = temp[i++];
            return; // since we changed an array element, the current step has ended
          }
          else {
            state = AlgoState::MERGE_LOOP_3;
          }

          break;

        case AlgoState::MERGE_LOOP_3:

          if (j < right) {
            // run the body of the loop
            array[k++] = temp[j++];
            return; // since we changed an array element, the current step has ended
          }
          else {
            // the loop finished executing
            left += size << 1;
            state = AlgoState::INNER_LOOP;
          }

          break;

        default:
          assert(false);
          break;

      }
    }

  }
  
  bool is_completed() {
    return completed;
  }

  ~MergeSortAlgorithm() {
    delete[] temp;
  }

};

template <typename T>
class QuickSortAlgorithm : public ArrayManipulationAlgorithm<T> {

private:
  enum class AlgoState {
    OUTER_LOOP,
    PARTITION_LOOP,
    RECURSION
  };

  struct StackFrame {
    int low;
    int high;

    StackFrame(int low, int high) : low(low), high(high) {}
    StackFrame() {}
  };

  std::stack<StackFrame> stack;
  StackFrame current;
  AlgoState state = AlgoState::OUTER_LOOP;
  int pivot_value;
  int pivot_position;
  int i;
  int j;

  int array_size;
  bool completed;

public:
  QuickSortAlgorithm(int array_size) : array_size(array_size), completed(array_size <= 1) {
    stack.push(
      StackFrame(0, array_size - 1)
    );
  }

  void step(T* array) {

    // quicksort:
    /*
      std::stack<StackFrame> stack;
      stack.push(StackFrame(0, array_size - 1));

      // --------------------------------
      // label: AlgoState::OUTER_LOOP
      // --------------------------------
      while (!stack.empty()) {

        StackFrame current = stack.top();
        stack.pop();

        // partition array
        int pivot_value = array[current.high]; // let the last element be the pivot
        int i = current.low - 1;
        int j = current.low;

        // --------------------------------
        // label: AlgoState::PARTITION_LOOP
        // --------------------------------
        for (; j < current.high; j++) {
          if (array[j] < pivot_value) {
            i++;
            std::swap(array[i], array[j]);
          }
        }

        int pivot_position = i + 1;
        
        std::swap(array[i + 1], array[current.high]);

        // --------------------------------
        // label: AlgoState::RECURSION
        // --------------------------------
        // push sub-arrays onto the stack
        if (current.low < pivot_position - 1) {
          stack.push(StackFrame(current.low, pivot_position - 1));
        }

        if (pivot_position + 1 < current.high) {
          stack.push(StackFrame(pivot_position + 1, current.high));
        }
      }
    */

    assert(!completed);
    
    while (true) {

      switch (state) {

        case AlgoState::OUTER_LOOP:

          if (stack.empty()) {
            completed = true;
            return;
          }

          current = stack.top();
          stack.pop();

          pivot_value = array[current.high]; // let the last element be the pivot
          i = current.low - 1;
          j = current.low;

          state = AlgoState::PARTITION_LOOP;

          break;

        case AlgoState::PARTITION_LOOP:

          if (j < current.high) {
            // run body of the loop

            j++;

            if (array[j - 1] < pivot_value) {
              i++;
              std::swap(array[i], array[j - 1]);
              return; // since we changed an array element, the current step has ended
            }

          }
          else {
            // loop condition became false
            pivot_position = i + 1;
  
            std::swap(array[i + 1], array[current.high]);

            state = AlgoState::RECURSION;

            return; // since we changed an array element, the current step has ended
          }

          break;

        case AlgoState::RECURSION:

          if (current.low < pivot_position - 1) {
            stack.push(StackFrame(current.low, pivot_position - 1));
          }

          if (pivot_position + 1 < current.high) {
            stack.push(StackFrame(pivot_position + 1, current.high));
          }

          state = AlgoState::OUTER_LOOP;

          break;

        default:
          assert(false);
          break;

      }

    }

  }
  
  bool is_completed() {
    return completed;
  }

};

#endif