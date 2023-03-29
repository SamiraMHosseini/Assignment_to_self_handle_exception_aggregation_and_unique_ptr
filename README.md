# Understanding unique_ptr reassignment and its impact on dynamically allocated objects

In this code, in each step, we are re-assigning a new value to the object variable. The previous value of object will be destroyed and its associated memory will be deallocated, because std::unique_ptr is a unique ownership smart pointer. This means that a std::unique_ptr can only have one owner and ownership can only be transferred by moving the pointer.

When object is reassigned to a new value, the previous std::unique_ptr object is destroyed, which in turn will destroy the object that it was managing. This ensures that the memory associated with the previous object is properly deallocated and prevents any potential memory leaks.

# std::unique_ptr
std::unique_ptr is a type of smart pointer that implements unique ownership semantics. 
This means that a std::unique_ptr instance manages a dynamically allocated object and is the sole owner of that object. 
As a result, only one std::unique_ptr instance can manage a given object at any given time.

When you reassign the value of object in each step of the code, you are changing the ownership of the managed object. 
The previous value of object is destroyed and its associated memory is deallocated, because the std::unique_ptr has a move constructor, which allows you to transfer ownership of the managed object from one std::unique_ptr instance to another.

Here's what happens in each step of the code:

In the first step, you initialize object with the value returned by make_object(Type::Base_Type). 
This creates a new std::unique_ptr instance that manages a Base object.

In the second step, you reassign object with the value returned by make_object(Type::Derived1_Type). This creates a new std::unique_ptr instance that manages a Derived1 object. The previous std::unique_ptr instance is destroyed, which in turn destroys the Base object that it was managing and deallocates the associated memory.

In the third step, you reassign object with the value returned by make_object(Type::Derived2_Type). This creates a new std::unique_ptr instance that manages a Derived2 object. The previous std::unique_ptr instance is destroyed, which in turn destroys the Derived1 object that it was managing and deallocates the associated memory.
In this way, std::unique_ptr ensures that dynamically allocated objects are properly destroyed and their associated memory is deallocated when they are no longer needed, without the need for manual memory management.
# Notes 
If you had defined three different std::unique_ptr variables, each of them would manage a different dynamically allocated object and each of these objects would be properly destroyed and their associated memory would be deallocated when the corresponding std::unique_ptr variable goes out of scope at the end of the main function
