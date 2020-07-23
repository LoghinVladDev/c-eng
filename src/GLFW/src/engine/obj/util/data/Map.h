
//
// Created by loghin on 7/22/20.
//

#ifndef ENG1_MAP_H
#define ENG1_MAP_H

#include "Array.h"
#include "Pair.h"
#include "String.h"
#include <types.h>

namespace engine {

    constexpr static uint8 DEFAULT_TABLE_SIZE = UINT8_MAX;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-reserved-identifier"
    template <class K>
    struct _INTERNAL_KEY_HASH {
        uint32 operator()(const K& key) const {
            return reinterpret_cast<uint32>(key) % DEFAULT_TABLE_SIZE;
        }
    };

    template <>
    struct _INTERNAL_KEY_HASH<engine::String> {
        uint32 operator()(const engine::String& key) const {
            return key.length() % DEFAULT_TABLE_SIZE;
        }
    };

    template <class T>
    struct _INTERNAL_KEY_HASH<engine::Array<T>> {
        uint32 operator()(const engine::Array<T>& key) const {

        }
    };
#pragma clang diagnostic pop

    template <class K, class V, class F = _INTERNAL_KEY_HASH<K>>
    class HashMap {
    public:
        using MapEntry = NonConstexprPair<K*, V*>;

        class HashNode {
            friend class HashMap;
        private:
            K _key;
            V _value;
            HashNode* _next;

        public:
            HashNode() = delete;
            HashNode(const K& key, const V& value) : _key(key), _value(value), _next(nullptr) {

            }

            K& getKey() noexcept {
                return this->_key;
            }

            V& getValue() noexcept {
                return this->_value;
            }

            void setValue(const V& value) noexcept {
                this->_value = value;
            }
        };

    public:
        HashMap() noexcept {
            this->_table = new HashNode * [DEFAULT_TABLE_SIZE];
        }

        ~HashMap() noexcept {
            for(std::size_t i = 0; i < DEFAULT_TABLE_SIZE; i++) {
                HashNode* entry = this->_table[i];
                while(entry != nullptr) {
                    HashNode* previous = entry;
                    entry = entry->_next;
                    delete previous;
                }
                this->_table[i] = nullptr;
            }
            delete [] this->_table;
        }

        bool get(const K& key, V& value) noexcept {
            uint32 hashValue = this->_hashFunction(key);
            HashNode *entry = this->_table[hashValue];

            while(entry != nullptr) {
                if(entry->_key == key) {
                    value = entry->_value;
                    return true;
                }
                entry = entry->_next;
            }

            return false;
        }

        const V* get(const K& key) noexcept {
            uint32 hashValue = this->_hashFunction(key);
            HashNode *entry = this->_table[hashValue];

            while(entry != nullptr) {
                if(entry->_key == key)
                    return &(entry->_value);

                entry = entry->_next;
            }

            return nullptr;
        }

        const V* operator[] (const K& key) const noexcept {
            uint32 hashValue = this->_hashFunction(key);
            HashNode* entry = this->_table[hashValue];

            while(entry != nullptr) {
                if(entry->_key == key)
                    return &(entry->_value);

                entry = entry->_next;
            }

            return nullptr;
        }

        bool contains(const K& key) noexcept {
            uint32 hashValue = this->_hashFunction(key);
            HashNode *entry = this->_table[hashValue];

            while(entry != nullptr) {
                if(entry->_key == key)
                    return true;
                entry = entry->_next;
            }

            return false;
        }

        void put(const K& key, const V& value) noexcept {
            uint32 hashValue = this->_hashFunction(key);
            HashNode* previous = nullptr;
            HashNode* entry = this->_table[hashValue];

            while( entry != nullptr && entry->_key != key ) {
                previous = entry;
                entry = entry->_next;
            }

            if( entry == nullptr ) {
                entry = new HashNode (key, value);
                if ( previous == nullptr )
                    this->_table[hashValue] = entry;
                else
                    previous->_next = entry;
            } else
                entry->_value = value;
        }

        void put(const MapEntry& pair) noexcept {
            uint32 hashValue = this->_hashFunction[*pair.getFirst()];
            HashNode* previous = nullptr;
            HashNode* entry = this->_table[hashValue];

            while( entry != nullptr && entry->_key != *pair.getFirst() ) {
                previous = entry;
                entry = entry->_next;
            }

            if( entry == nullptr ) {
                entry = new HashNode (*pair.getFirst(), *pair.getSecond());
                if( previous == nullptr )
                    this->_table[hashValue] = entry;
                else
                    previous->_next = entry;
            } else
                entry->_value = *pair.getSecond();
        }

        void remove(const K &key) noexcept {
            uint32 hashValue = this->_hashFunction(key);
            HashNode *previous = nullptr;
            HashNode *entry = this->_table[hashValue];

            while( entry != nullptr && entry->_key != key ) {
                previous = entry;
                entry = entry->_next;
            }

            if( entry == nullptr )
                return;
            else {
                if( previous == nullptr )
                    this->_table[hashValue] = entry->_next;
                else
                    previous->_next = entry->_next;
                delete entry;
            }
        }

        engine::Array<K*> getKeys() noexcept {
            engine::Array<K*> set;

            for(std::size_t i = 0; i < DEFAULT_TABLE_SIZE; i++) {
                HashNode *entry = this->_table[i];

                while(entry != nullptr) {
                    set += &(entry->_key);
                    entry = entry->_next;
                }
            }

            return set;
        }

        engine::Array<V*> getValues() noexcept {
            engine::Array<V*> set;

            for(std::size_t i = 0; i < DEFAULT_TABLE_SIZE; i++) {
                HashNode *entry = this->_table[i];

                while(entry != nullptr) {
                    set += &(entry->_value);
                    entry = entry->_next;
                }
            }

            return set;
        }

        engine::Array< MapEntry* > getEntries() const noexcept {
            engine::Array< MapEntry* > set;

            for(std::size_t i = 0; i < DEFAULT_TABLE_SIZE; i++) {
                HashNode *entry = this->_table[i];

                while(entry != nullptr) {
                    set += new MapEntry( &(entry->_key), &(entry->_value) );
                    entry = entry->_next;
                }
            }

            return set;
        }

    private:
        static engine::String stringMapEntry(const MapEntry& entry) noexcept {
            return engine::String()
                .append("{ k = ")
                .append(*entry.getFirst())
                .append(", v = ")
                .append(*entry.getSecond())
                .append(" }");
        }

    public:
        friend std::ostream& operator << (std::ostream& f, const HashMap& map) noexcept {
            engine::Array< MapEntry* > set = map.getEntries();

            f << " Map : [ ";

            if(set.getLength() > 0) {
                for (std::size_t i = 0; i < set.getLength() - 1; i++) {
//                    f << set[i]->toString() << ", ";
                    f << HashMap::stringMapEntry(* set[i]) << ", ";
                }

//                f << set[set.getLength() - 1]->toString();
                f << HashMap::stringMapEntry(* set[set.getLength()-1]);
            }

            return (f << " ] ");
        }

    private:
        HashNode ** _table;
        F _hashFunction;
    };

}

#endif //ENG1_MAP_H
