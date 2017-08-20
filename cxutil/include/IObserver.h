/**************************************************************************************************************//**
 *
 * Interface for implementing an observer.
 *
 * @file    IObserver.h
 * @author  Éric Poirier
 * @version 1.0
 * @date    August, 2017
 *
 ******************************************************************************************************************/

#ifndef IOBSERVER_H_516B2B88_CC83_49D3_8D69_D7AC6A4F72E2
#define IOBSERVER_H_516B2B88_CC83_49D3_8D69_D7AC6A4F72E2

#include <memory>


// Forward declaration:
namespace cxutil
{
    class ISubject;
} // namespace cxutil

namespace cxutil
{

class IObserver
{
public:
    virtual ~IObserver() = default;

    virtual void update( ISubject* p_subject ) = 0;
};

}; // namespace cxutil

#endif /* IOBSERVER_H_516B2B88_CC83_49D3_8D69_D7AC6A4F72E2 */