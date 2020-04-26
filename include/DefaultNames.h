//
// Created by red on 4/26/20.
//

#ifndef SQLITEMATE_DEFAULTNAMES_H
#define SQLITEMATE_DEFAULTNAMES_H

#include <cstdint>
#include <map>
#include <optional>
#include <algorithm>

namespace sqlite::utilities {

    /** Enumerates all default (and, thus, potentially hardcoded) named entities
     *
     */
    enum class DefaultNames : std::uint8_t {
        notDefined = 0,
        requestFile,
        responseFile,
        dbFile
    };

    /** Provides the conversions
     *
     */
    class DefaultNamesConverter{
    public:

        static std::optional<std::string> ToString(const DefaultNames& _defaultNames)
        {
            const auto it = m_map.find(_defaultNames);

            if(it != std::cend(m_map))
                return it->second;

            return {};
        }

    private:
        static inline std::map<DefaultNames, std::string> m_map{{DefaultNames::notDefined, "notDefined"},
                                                                {DefaultNames::requestFile, "requestFile"},
                                                                {DefaultNames::responseFile, "responseFile"},
                                                                {DefaultNames::dbFile, "dbFile"}};
    };
}

#endif //SQLITEMATE_DEFAULTNAMES_H
