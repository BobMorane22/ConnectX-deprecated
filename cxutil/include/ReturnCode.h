#ifndef RETURNCODE_H_98A72660_A669_42ED_8459_55193BA7032F
#define RETURNCODE_H_98A72660_A669_42ED_8459_55193BA7032F

#include <string>

class ostream;

namespace cxutil
{

class ReturnCode final
{
public:

    static const std::string NO_MESSAGE;

    enum class Code: int
    {
        OK,       /* Action executes as expected.                                        */
        WARNING,  /* Action does NOT execute as expected. Executable may not be unstable */
        ERROR,    /* Action does NOT execute as expected. Executable is unstable.        */
        CANCEL    /* Action is canceled.                                                 */
    };

     ReturnCode( Code p_code = Code::ERROR, const std::string p_message = NO_MESSAGE );
    ~ReturnCode();

    bool        isOk();
    bool        isWarning();
    bool        isError();
    bool        isCancelled();

    bool        holdsMessage() const;
    bool        isTested() const;

    std::string message() const;
    Code        code() const;

private:

    bool        m_tested   { false };
    Code        m_code     { Code::ERROR };
    std::string m_message;
};

} // cxutil

#endif /* RETURNCODE_H_98A72660_A669_42ED_8459_55193BA7032F */