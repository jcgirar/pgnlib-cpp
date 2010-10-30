#include "ref_object.hpp"

namespace pgn
{

class IParser : public IRefObject
{
public:
    static IParser* create(char const* pgnfile /* utf8 */);
};

} /* namespace pgn */

