/**************************************************************************************************************//**
 *
 * Interface for implementing a subject.
 *
 * @file    ISubject.h
 * @author  Éric Poirier
 * @version 1.0
 * @date    August, 2017
 *
 ******************************************************************************************************************/

#ifndef ISUBJECT_H_56D25704_804C_4CDF_B21_EAD8AF51BF36
#define ISUBJECT_H_56D25704_804C_4CDF_B21_EAD8AF51BF36

#include <list>

#include "IObserver.h"

namespace cxutil
{

class ISubject
{
public:
    virtual ~ISubject() = 0;

    void registerObserver( IObserver* p_observer );
    void removeObserver( IObserver* p_observer );
    void notifyObservers();

private:
    std::list< IObserver* const > m_observers; ///< A collection of all registered observers.
};

}; // namespace cxutil

#endif /* ISUBJECT_H_56D25704_804C_4CDF_B21_EAD8AF51BF36 */