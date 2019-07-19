#include <eosiolib/eosio.hpp>

using namespace eosio;


CONTRACT count: public contract {
    public:

        using contract::contract;

        ACTION countuser(name user, uint64_t count) {
            require_auth(get_self());
            address_index forUser(get_self(), get_self().value);
            auto itr = forUser.find(user.value);

            if( itr == forUser.end() ) {
                forUser.emplace(user,[&](auto& row ) {
                    row.user = user;
                    row.count = 1;
                });
                print("already exist");
                
            } else {
                forUser.modify(itr, user,[&](auto& row) {
                    row.user = user;
                    row.count++;
                });
                print("countuser success!!");
            }
            print(itr->user, " ", itr->count); 
            
        }

        ACTION findcount(uint64_t count) {
            address_index addresses(get_self(), get_self().value);
            auto forSecondary = addresses.get_index<"bycount"_n>();
            auto itr = forSecondary.require_find(count, "no count");
            print(itr->user);
        }

        ACTION eraseall() {
            address_index forErase(get_self(), get_self().value);
            auto itr = forErase

            print("eraseall success");
        }

    private:
    
    struct [[eosio::table]] counttable {

        name user;
        uint64_t count;


        uint64_t primary_key() const { return user.value; }
        uint64_t by_count() const {return count;}

    };


    typedef multi_index<"count"_n, counttable,
    indexed_by<"bycount"_n, const_mem_fun<counttable, uint64_t, &counttable::by_count>> > address_index;

};