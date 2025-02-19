#ifndef ZB_RESULT_H
#define ZB_RESULT_H

#include <cassert>

template <typename T, typename E>
class ZBResult {

public:
  ZBResult(const T& ok) : payload_type(PayloadType::Ok) {
    new (&payload.ok_value) T(ok);
  }

  ZBResult(const E& err) : payload_type(PayloadType::Err) {
    new (&payload.err_value) E(err);
  }

  ZBResult() : ZBResult(E()) {}

  inline bool is_ok() const {
    return payload_type == PayloadType::Ok;
  }

  inline bool is_error() const {
    return !is_ok();
  }

  T& unwrap() {
    assert(payload_type == PayloadType::Ok);
    return payload.ok_value;
  }

  E& unwrap_error() {
    assert(payload_type == PayloadType::Err);
    return payload.err_value;
  }

  ~ZBResult() {
    switch (payload_type) {
      case PayloadType::Ok:
        payload.ok_value.~T();
        break;
      case PayloadType::Err:
        payload.err_value.~E();
        break;
      default:
        assert(false);
        break;
    }
  }

private:
  enum class PayloadType {Ok, Err} payload_type;
  
  union Payload {
    T ok_value;
    E err_value;

    Payload() {}
    ~Payload() {}
  } payload;

};

#endif