#ifndef ENGINE_CORE_RESULT_H_
#define ENGINE_CORE_RESULT_H_

namespace Engine {
namespace Core {
template <class ResultType>
class ProcessableResultInterface {
  public:
    inline explicit ProcessableResultInterface(ResultType const& _result) : result_(_result) { }
    inline ProcessableResultInterface(void) = delete;
    inline ProcessableResultInterface(ProcessableResultInterface && _other)
        : result_(_other.result_) { }
    inline ProcessableResultInterface(ProcessableResultInterface const& _other)
        : result_(_other.result_) { }
    inline ProcessableResultInterface & operator=(ProcessableResultInterface && _other) {
      result_ = _other.result_;
      return *this;
    }
    inline ProcessableResultInterface & operator=(ProcessableResultInterface const& _other) {
      result_ = _other.result_;
      return *this;
    }
    inline virtual ~ProcessableResultInterface(void) = default;

    inline ResultType result(void) const { return result_; }

    virtual bool Valid(void) const = 0;

  protected:
    inline void set_result(ResultType _result) { result_ = _result; }

  private:
     ResultType result_;
};
}
}

#endif