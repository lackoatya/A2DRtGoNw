#ifndef ENGINE_PROCESSOR_RESULT_INTERFACE_HPP_
#define ENGINE_PROCESSOR_RESULT_INTERFACE_HPP_

namespace Engine {
namespace Processor {
template <class ResultType>
class ResultInterface {
  public:
    inline explicit ResultInterface(ResultType const& _result) : result_(_result) { }
    inline ResultInterface(void) = delete;
    inline ResultInterface(ResultInterface && _other)
      : result_(_other.result_) { }
    inline ResultInterface(ResultInterface const& _other)
      : result_(_other.result_) { }
    inline ResultInterface & operator=(ResultInterface && _other) {
      result_ = _other.result_;
      return *this;
    }
    inline ResultInterface & operator=(ResultInterface const& _other) {
      result_ = _other.result_;
      return *this;
    }
    inline virtual ~ResultInterface(void) = default;

    inline ResultType result(void) const { return result_; }

    virtual bool IsValid(void) const = 0;

  protected:
    inline void set_result(ResultType _result) { result_ = _result; }

  private:
    ResultType result_;
};
}
}

#endif