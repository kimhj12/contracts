#include <eosiolib/eosio.hpp>

using namespace eosio;

CONTRACT test: public contract {
    public:
        using contract::contract;

        ACTION hi(name user) {
            address_index forhi(get_self(), get_self().value);
            auto itr = forhi.require_find(user.value, "X");
            check(itr != forhi.end(), "X");
            print("hello, ",user);
 
        }

        ACTION insert(name user){
            check(has_auth(get_self()),"x");
            //require_auth(get_self());

            address_index forInsert(get_self(), get_self().value);

            auto itr = forInsert.find(user.value);
            
            check(itr == forInsert.end(), "already exists");

            forInsert.emplace(get_self(), [&](auto& row) {
                row.user = user;
            });

            print("insert success");
            }

         ACTION remove(name user) {
             check(has_auth(get_self()), "X");

             address_index forRemove(get_self(), get_self().value);
             
             auto itr = forRemove.require_find(user.value, "no account");
             
             forRemove.erase(itr);
            
            print("remove success");
            
            }

    private:

    struct [[eosio::table]] allowance {

        name user;

        uint64_t primary_key() const { return user.value; }

    };

    typedef multi_index<"allowance"_n, allowance> address_index;

};