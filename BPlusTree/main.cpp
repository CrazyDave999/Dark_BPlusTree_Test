#include "bplus.h"
#include "Dark/inout"
#include "string.h"
#include <filesystem>

size_t hash_str(const char *str) {
    static size_t fix_random = rand() * rand();
    size_t __h = fix_random;
    while(*str) { __h = __h * 137 + *(str++); }
    return __h;
}

signed main() {
    using tree = dark::bpt <size_t,int,1023,3000,2>;
    typename tree::return_list data;
    typename tree::iterator    iter;
    std::filesystem::create_directory("output");
    tree t("output/a");
    int n = dark::read <int> ();
    dark::string <68> str;
    while(n--) {
        dark::read(str.str);
        if(str.str[0] == 'i') {
            dark::read(str.str);
            t.insert(hash_str(str.base()),dark::read <int> ());
        } else if(str.str[0] == 'd') {
            dark::read(str.str);
            t.erase(hash_str(str.base()),dark::read <int> ());
        } else {
            dark::read(str.str);
            data.clear();
            t.find(hash_str(str.base()),data);
            if(data.empty()) puts("null");
            else {
                for(auto iter : data) dark::print(iter,' ');
                putchar('\n');
            }
            // size_t __h = hash_str(str.base());
            // iter = t.find(__h);
            // if(!iter.valid() || iter->key != __h) puts("null");
            // else {
            //     do {
            //         dark::print(iter->val,' '); ++iter;
            //     } while(iter.valid() && iter->key == __h);
            //     putchar('\n');
            // }
        }
    }
    return 0;
}
