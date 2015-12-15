# phoenix_ptr

A thread safe, header-only implementation of a  smart
pointer that deletes the contained object when not needed at
the moment and recreates the object when needed again.

This is useful when resources are very rarely needed, when
a resource is easy to create and delete, but difficult to
maintain or when you want to defer the initialisation of
a global variable to when it's actually needed.

I wrote this for an application that had two modes (1)
didn't need a database connection (2) had to share
a database connection between multiple threads.
Using phoenix_ptr I could declare the connection in the
containing namespace; in (1) the connection would stay
unallocated, in (2) the first thread would open the
connection and all other threads would reuse it too.

```c++
#include "softwear/phoenix_ptr.hpp"
softwear::phoenix_ptr<my_class> my_phoenix_instance;
```

## Example

See tests.cc for an example.

## Documentation

include/softwear/phoenix_ptr.hpp contains detailed
documentation.

## Testing

Run `make`.

## TODO

* Allow using different types for mutex/lock_guard/weak_ptr/shared_ptr (e.g. the boost ones)
* Allow using an allocator
* Allow using creator/deleter functions
* Allow forwarding parameters
* Allow using some timeout?

# LICENSE

Written by (karo@cupdev.net) Karolin Varner, for Softwear, BV (http://nl.softwear.nl/contact):
You can still buy me a Club Mate. Or a coffee.

Copyright © (c) 2015, Softwear, BV.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
* Neither the name of the Karolin Varner, Softwear, BV nor the
  names of its contributors may be used to endorse or promote products
  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL Softwear, BV BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
