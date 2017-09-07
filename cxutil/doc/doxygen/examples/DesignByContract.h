#include "ContractException.h"
#include "IEnforceContract.h"

class PositiveValue : public IEnforceContract
{

public:

    PositiveValue(int p_value)
    {
        PRECONDITION(p_value >= 0); // Should be true before anything is done.

        m_value = p_value;          // For the sake of the example only, no
                                    // initialization list has been used.

        if(m_value >= 0)
            m_isPositive = true;

        POSTCONDITION(m_value >= 0);    // Should be true after the operation is done

        INVARIANTS();       // Checks both invariants defined in the
                            // checkInvariant() method below. They should ALWAYS be
                            // true no matter what, otherwise the object could
                            // be left in an invalid state.
    }

private:

    // Needs to be defined by the developper:
    void checkInvariant() const
    {
        INVARIANT(m_value >= 0);           // A first, single, invariant.
        INVARIANT(m_isPositive = true);    // A second, single, invariant.
    }

    // member variables:
    int     m_value;
    bool    m_isPositive;

};
