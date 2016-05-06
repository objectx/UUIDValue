
#include "common.hpp"
#include <UUIDValue.hpp>

namespace {
    void check_uuid (const UUIDValue::uuid_t &uuid) {
        INFO ("UUID: " << UUIDValue::ToString (uuid)) ;
        REQUIRE ((uuid [6] >> 4) == 4) ;
        REQUIRE ((uuid [8] >> 6) == 2) ;
    }
}

SCENARIO ("The generated UUID values is UUID Ver.4" "[UUID]") {
    GIVEN ("An UUID") {
        auto uuid = UUIDValue::NewUUID () ;

        WHEN ("Check size") {
            THEN ("Should be 16") {
                REQUIRE (uuid.size () == 16) ;
            }
        }
        WHEN ("Check Version") {
            THEN ("Should be ver.4") {
                check_uuid (uuid) ;
            }
        }
    }
}

SCENARIO ("All of generated UUID values are distinct" "[UUID]") {
    GIVEN ("100,000 UUID values") {
        const size_t count = 100000 ;
        std::vector<UUIDValue::uuid_t>  uuids ;
        uuids.reserve (count) ;
        for (int i = 0 ; i < count ; ++i) {
            uuids.emplace_back (UUIDValue::NewUUID ()) ;
        }
        REQUIRE (uuids.size () == count) ;
        WHEN ("When uniquify the result") {
            std::sort (uuids.begin (), uuids.end ()) ;
            auto it = std::unique (uuids.begin (), uuids.end ()) ;
            THEN ("# of unique entries should be the same as original.") {
                REQUIRE (std::distance (uuids.begin (), it) == uuids.size ()) ;
            }
            AND_THEN ("All of generated uuids should be ver.4") {
                for (auto const &v : uuids) {
                    check_uuid (v) ;
                }
            }
        }
    }
}
