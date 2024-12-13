#ifndef ZB_ARRAY_MANIPULATION_H
#define ZB_ARRAY_MANIPULATION_H

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

#endif