#ifndef SOFTWEAR_PHOENIX_PTR_HEADER
#define SOFTWEAR_PHOENIX_PTR_HEADER

#include <mutex>
#include <memory>

namespace softwear {

/// A special type of smart pointer that automatically
/// creates an object when needed and destroys it when no
/// longer needed. After being destroyed it will be recreated
/// when needed again.
///
/// Thus the name phoenix_ptr - It rises again from it's own
/// ashes
///
/// We assume the pointer is needed, when it's converted to
/// a shared_ptr (by cast or by calling lock()); it is no
/// longer needed when all of the shared pointers have been
/// destroyed.
///
/// Thread safe!
template<typename T> class phoenix_ptr {

public:
  /// The type of the element contained
  typedef T element_type;

  typedef std::mutex mutex;
  typedef std::lock_guard<mutex> lock_guard;
  typedef std::weak_ptr<T> weak_ptr;
  typedef std::shared_ptr<T> shared_ptr;

private:
  /// Prevent multiple threads from recreating the element
  /// at the same time
  mutex creatin;

  /// Stores the element if it still exists or nothing.
  weak_ptr store;

public:

  /// Get a weak reference to the object contained.
  /// This never creates an object, but you can use this to
  /// check whether we are currently holding an object.
  weak_ptr weak() {
    return store;
  }

  /// Get the object!
  ///
  /// This will create the object if it has not yet been
  /// created.
  std::shared_ptr<T> lock() {
    shared_ptr r = store.lock();

    // Got a valid ptr
    if (r) return r;

    // Nope; try to create it/wait for another thread to do so
    lock_guard creatin_lock(creatin);

    // Try again. Maybe another thread created the instance in
    // the meantime
    r = store.lock();

    // Nope; create ourselves
    if (!r) {
      r = std::make_shared<T>();
      store = r;
    }

    // At this point we got an instance; either one we created
    // ourselves.
    return r;
  }

  /// Like weak()
  operator weak_ptr() { return weak(); }

  /// Like lock()
  operator shared_ptr() { return lock(); }
};

}

#endif
