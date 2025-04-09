#pragma once 
#include <iostream> 
#include <string> 
#include <stdexcept> 
#include <vector> 
 
template <typename T> 
class HashTable { 
    private: 
            struct Entry { 
                std::string key; 
                T value; 
                bool isOccupied; 
                bool isDeleted; 
        
                Entry() : key(""), value(), isOccupied(false), isDeleted(false) {} 
            }; 
    
        Entry* table; 
        size_t capacity; 
        size_t size; 
        double loadFactorThreshold; 
    
        size_t customHash(const std::string& key) const { 
            size_t hash = 5381; 
            for (char c : key) { 
                hash = ((hash << 5) + hash) + c; 
            } 
            return hash; 
        } 
    
        size_t probe(const std::string& key, bool forInsert = false) const; 
    
        void resize(){
            size_t old = capacity;
            capacity *= 2;
            Entry* oldtable = table;
            table = new Entry[]
            for(int i = 0 ; i < oldcapacity ; ++i){
                table[i] = oldtable[i];
            }
        }
    
    public: 
        // Constructor 
        HashTable(size_t initialCapacity = 101){
            Entry* = new Entry[initialCapacity];
            capacity = initialCapacity;
            size = 0;
        } 
        
        // Big Five 
        ~HashTable(){                   // Destructor 
            delete[] table;
        }                                       
        HashTable(const HashTable& other)// Copy constructor
        {
            capacity = other.capacity;
            size = other.size;
            table = new Entry[other.capacity];
            for(int i = 0 ; i < capacity ; ++i){
                table[i] = other.table[i];
            }
            
        } 
        HashTable& operator=(const HashTable& other);       // Copy assignment 
        HashTable(HashTable&& other) noexcept;              // Move constructor 
        HashTable& operator=(HashTable&& other) noexcept;   // Move assignment 
    
        // Core methods 
        void insert(const std::string& key, const T& value); 
        T& get(const std::string& key); 
        void remove(const std::string& key); 
        bool contains(const std::string& key) const; 
    
        size_t getSize() const { 
            return size; 
        } 
        size_t getCapacity() const { 
            return capacity; 
        } 
}; 