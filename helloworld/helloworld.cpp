#include <eosiolib/eosio.hpp>

using namespace eosio;

CONTRACT helloworld: public contract{
    public:
        using contract::contract;

        ACTION hi(name user) {
            require_auth(user);
            print("hello, ", user);    
         }
            //check(has_auth(get_self()) || has_auth("moonmoon1234"_n), "you aint a contract deployer!!");
            
            // bool isTrue = has_auth(get_self()) || has_auth("hahahoho1234"_n);
            // check(isTrue, "you aint a contract deployer!!")

            // == require_auth(user)

            //has_auth() -> true or false

            //require_auth(get_self);
            //check(has_auth(get_self(), "missing authority"));

         ACTION getaccount(name user){
            require_auth(get_self());
            print(is_account(user));
        }

        
    private:
};