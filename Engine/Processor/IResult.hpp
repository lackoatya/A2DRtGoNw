#ifndef ENGINE_PROCESSOR_IRESULT_HPP_
#define ENGINE_PROCESSOR_IRESULT_HPP_

namespace Engine {
namespace Processor {
template < class ResultType >
class IResult {
  public:
    inline explicit IResult(ResultType const& _result) : m_result(_result) { }
    inline IResult(IResult && _other) : m_result(_other.m_result) { }
    inline IResult(IResult const& _other) : m_result(_other.m_result) { }
    inline IResult & operator=(IResult && _other) { m_result = _other.m_result; return *this; }
    inline IResult & operator=(IResult const& _other) { m_result = _other.m_result; return *this; }
    inline virtual ~IResult(void) { }

    inline ResultType result(void) const { return m_result; }

    virtual bool IsValid(void) const = 0;

  protected:
    ResultType m_result;
};
}
}

#endif