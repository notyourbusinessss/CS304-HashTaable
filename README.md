# Generic Hash Table in C++

## Overview

This project implements a **generic hash table** in C++ using **open addressing** with customizable hashing and collision resolution strategies. The hash table is built using a class template `HashTable<T>`, where `T` represents any user-defined type for the values. It uses `std::string` for keys.

The hash table is implemented from scratch — including the hash function, collision resolution, and resizing logic. It also adheres to modern C++ principles by implementing the **Rule of Five** for proper resource management.

---

## Features

- Templated class: `HashTable<T>`
- Custom dynamic array-based implementation
- Custom hash function (based on djb2)
- Open addressing with quadratic probing
- Automatic resizing based on load factor
- Support for insertion, deletion, retrieval, and existence check
- Proper memory management (Rule of Five)
- Demonstrated with practical use cases

---

## Core Data Structure

### `Entry<T>` Struct

The hash table internally uses an array of `Entry<T>` objects. This struct is used to represent a **single slot** in the hash table. Each slot contains:

```cpp
template <typename T>
struct Entry {
    std::string key;     // The key for the entry (used for hashing and lookup)
    T value;             // The value associated with the key
    bool isOccupied;     // Indicates if this slot is currently used
    bool isDeleted;      // Indicates if this slot was deleted (important for open addressing)

    Entry() : key(""), value(), isOccupied(false), isDeleted(false) {}
};
```

**Usage Explanation:**

- When you insert a key-value pair, the `Entry` struct stores both values.
- `isOccupied = true` means that this slot contains a valid value.
- `isDeleted = true` is used for lazy deletion. When a key is deleted, the entry is marked deleted but not removed — this helps maintain the integrity of probe chains.
- During probing, the hash table checks these flags to determine whether to continue searching or stop.

---

## Hash Table Internal Layout

Internally, the class stores:

```cpp
Entry<T>* table;          // Dynamic array of entries
size_t capacity;          // Total number of available slots
size_t size;              // Current number of key-value pairs
double loadFactorThreshold; // When exceeded, triggers resizing
```

Each slot in the `table` array is an `Entry<T>` object. When the number of elements exceeds `capacity * loadFactorThreshold`, the table resizes and rehashes all entries into a larger array.

---

## Hash Function

The table uses a custom hash function based on the `djb2` algorithm:

```cpp
size_t customHash(const std::string& key) const {
    size_t hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}
```

This function provides good distribution for string keys and is fast to compute.

---

## Collision Resolution: Quadratic Probing

When multiple keys hash to the same index (a collision), the table uses quadratic probing to resolve it:

```cpp
index = (hash + i^2) % capacity;
```

This spreads out collisions more evenly than linear probing and avoids clustering.

---

## Insert Operation

1. Compute the hash of the key.
2. Use probing to find the first available or matching slot.
3. If the key already exists, update the value.
4. If inserting a new key:
   - Mark the entry as occupied.
   - Store the key and value.
   - Increment the size.
5. Resize the table if needed.

---

## Get Operation

1. Compute the hash of the key.
2. Use probing to find the slot where the key exists.
3. If found, return a reference to the value.
4. If not found, throw an exception.

---

## Remove Operation

1. Probe to find the key.
2. If found, mark `isDeleted = true`, `isOccupied = false`.
3. Do not remove the data physically — this maintains probe chain consistency.

---

## Resize Operation

When the load factor exceeds the threshold:
1. Allocate a new array of larger size.
2. Rehash all occupied and non-deleted entries into the new array.
3. Replace the old table with the new one.

---

## Rule of Five

To properly manage dynamic memory, the hash table implements:

- **Destructor**: Frees allocated memory.
- **Copy Constructor**: Creates a deep copy.
- **Copy Assignment Operator**: Frees existing memory and copies the data.
- **Move Constructor**: Transfers ownership of resources.
- **Move Assignment Operator**: Transfers ownership during assignment.

---

## Public API

```cpp
// Constructor & Destructor
HashTable(size_t initialCapacity = 101);
~HashTable();

// Rule of Five
HashTable(const HashTable& other);
HashTable& operator=(const HashTable& other);
HashTable(HashTable&& other) noexcept;
HashTable& operator=(HashTable&& other) noexcept;

// Core functionality
void insert(const std::string& key, const T& value);
T& get(const std::string& key);
void remove(const std::string& key);
bool contains(const std::string& key) const;

// Info
size_t getSize() const;
size_t getCapacity() const;
```

---

## Testing & Use Cases

Tests should cover:

- Basic insert and get
- Duplicate key updates
- Deletion and reinsertion
- Collision handling
- Load factor and resizing
- Custom data types

### Applications

**Two Sum**: Uses `HashTable<int>` to map value → index.  
**Group Anagrams**: Uses `HashTable<std::vector<std::string>>` with sorted word as key.

---

## How to Compile

```sh
g++ -std=c++11 main.cpp -o hashtable
./hashtable
```

---

## License

For educational use only.
