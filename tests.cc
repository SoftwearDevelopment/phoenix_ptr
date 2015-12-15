#include <atomic>
#include <memory>

#include "softwear/phoenix_ptr.hpp"

#ifdef NDEBUG
#undef NDEBUG
#endif

#ifndef DEBUG
#define DEBUG 1
#endif

#include <assert.h>


struct counterclass {
  /// Counts how often an instance of this class was created
  /// in a thread safe manner
  static std::atomic<int> count;

  counterclass() {
    counterclass::count++;
  }
};

std::atomic<int> counterclass::count{0};

int main() {
  // => test meta check: basic counting works
  counterclass c;
  assert(counterclass::count == 1);

  // => no second instance has been initialiszed
  softwear::phoenix_ptr<counterclass> phc;
  assert(counterclass::count == 1);
  assert(phc.weak().expired() == true);

  {
    // => converting to a shared_ptr allocates
    std::shared_ptr<counterclass> inst = phc;
    assert(counterclass::count == 2);
    assert(phc.weak().expired() == false);

    {
      // => further shared_ptr do not allocate
      std::shared_ptr<counterclass> inst2 = phc;
      assert(counterclass::count == 2);
      assert(phc.weak().expired() == false);

      // => The pointers returned are the same
      assert(inst.get() == inst2.get());
      assert(inst.get() == phc.weak().lock().get());
    }

    // => still valid when just one shared_ptr goes out of scope
    assert(counterclass::count == 2);
    assert(phc.weak().expired() == false);
  }

  // => destroys when all shared_ptrs go out of scope
  assert(counterclass::count == 2);
  assert(phc.weak().expired() == true);

  // => can reallocate and get a new valid instance
  std::shared_ptr<counterclass> inst = phc;
  assert(counterclass::count == 3);
  assert(phc.weak().expired() == false);

  return 0;
}
