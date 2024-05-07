module;

#include <string>

#include "Conf/Conf.h"
#include "MaaFramework/MaaPort.h"

MAA_SUPPRESS_BOOST_WARNINGS_BEGIN
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
MAA_SUPPRESS_BOOST_WARNINGS_END

export module MaaUtils_Uuid;

MAA_NS_BEGIN

export inline std::string make_uuid()
{
    static boost::uuids::random_generator uuid_generator;
    return boost::uuids::to_string(uuid_generator());
}

MAA_NS_END
