namespace pgn
{

class IRefObject
{
public:
    virtual unsigned addRef() = 0;
    virtual unsigned release() = 0;

protected:
    virtual ~IRefObject() {}
};

} /* namespace pgn */

