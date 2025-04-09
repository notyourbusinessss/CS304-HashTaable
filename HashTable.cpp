#include <cstddef>
#include <iostream> 
#include <string> 
#include <stdexcept> 
#include <vector> 


template <typename T> 
class HashTable{ 
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
            size_t hash = 5381; //
            for (char c : key) { 
                hash = ((hash << 5) + hash) + c; 
            } 
            return hash; 
        } 
    
        size_t probe(const std::string& key, bool forInsert = false) const{
            size_t hash = customHash(key)%capacity;
            size_t i = 0;
            size_t index;
            while(true){
                index = (hash + i*i) % capacity;
                if(forInsert){
                    if(!table[index].isOccupied){
                        return index;
                    }
                }else{
                    if(table[index].isOccupied && table[index].key == key){
                        return index;
                    }
                    if(!table[index].isDeleted && !table[index].isOccupied){
                        break;
                    }
                }
            }

            return -1;
        } 
    
        void resize(){
            size_t old = capacity;
            capacity *= 2;
            Entry* oldtable = table;
            table = new Entry[old];
            for(int i = 0 ; i < old ; ++i){
                table[i] = oldtable[i];
            }
        }
    
    public: 
        // Constructor 
        HashTable(size_t initialCapacity = 101){
            table = new Entry[initialCapacity];
            capacity = initialCapacity;
            size = 0;
            loadFactorThreshold = 0.7;
        } 
        
        // Big Five 
        ~HashTable(){                   // Destructor 
            delete[] table;
        }                                       
        HashTable(const HashTable& other)// Copy constructor
        {
            capacity = other.capacity;
            size = other.size;
            loadFactorThreshold = other.loadFactorThreshold;

            table = new Entry[other.capacity];
            for(int i = 0 ; i < capacity ; ++i){
                table[i] = other.table[i];
            }
            
        } 
        HashTable& operator=(const HashTable& other);       // Copy assignment 
        HashTable(HashTable&& other) noexcept;              // Move constructor 
        HashTable& operator=(HashTable&& other) noexcept;   // Move assignment 
    
        // Core methods 
        void insert(const std::string& key, const T& value){
            if((double)size/capacity >= loadFactorThreshold){
                resize();
            }

            size_t index = probe(key,true);

            table[index].key = key;
            table[index].value = value;
            table[index].isOccupied = true;
            table[index].isDeleted = false;

        } 
        T& get(const std::string& key){
            size_t index = probe(key);
            if(index == -1){
                throw std::range_error("key not found");
            }
            return table[index].value;
        } 


        void remove(const std::string& key){
            size_t index = probe(key);
            if(contains(key)){
                table[index].key = NULL;
                table[index].value = NULL;
                table[index].isDeleted = true;
                table[index].isOccupied = false;
            }
        } 
        bool contains(const std::string& key) const{
            size_t index = probe(key);
            if(index == -1){
                return false;
            }else{
                return true;
            }

        } 
    
        size_t getSize() const { 
            return size; 
        } 
        size_t getCapacity() const { 
            return capacity; 
        } 
};

int main(){
    
}