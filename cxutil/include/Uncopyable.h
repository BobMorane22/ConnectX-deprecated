#ifndef UNCOPYABLE_H_1DAF4EB3_1243_455D_B4D1_9F7DA136B04E
#define UNCOPYABLE_H_1DAF4EB3_1243_455D_B4D1_9F7DA136B04E

namespace cxutil
{

class Uncopyable
{
protected:
     Uncopyable() = default;
    ~Uncopyable() = default;

private:
    Uncopyable( const Uncopyable& p_object )            = delete;
    Uncopyable& operator=( const Uncopyable& p_object ) = delete;
};

} // namespace cxutil

#endif /* UNCOPYABLE_H_1DAF4EB3_1243_455D_B4D1_9F7DA136B04E */