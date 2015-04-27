#include <inttypes.h>

/// \class DataBuffer
///
/// Buffers number of readings and allow querying various statistics of them.
/// Supported queries are average value calculation and peak to peak amplitude
/// calculation.
///
/// Buffer size is configurable on buffer initialization. Buffer is cyclic, so
/// the oldest value is evicted when new one is added.
class DataBuffer {
public:
  /// Initializes store by reserving memory for requested bufer size and filling
  /// the whole buffer with given value.
  ///
  /// \param size
  ///    Buffer size
  ///
  /// \param initialValue
  ///    Initial value
  DataBuffer(uint16_t size, int16_t initialValue);

  /// Adds given value to dataset. Values must be requested using appropriate
  /// function.
  ///
  /// \param value
  ///    New value
  void add(int16_t value);

  /// Returns current rolling average.
  ///
  /// \return
  ///    Rolling average value
  int16_t average();

  /// Returns peak to peak amplitude of currently stored values.
  ///
  /// \return
  ///    Peak to peak amplitude
  int16_t peakToPeak();

private:
  // Buffer for values
  int16_t * buffer;

  // Buffer size
  uint16_t size;
  uint16_t cursor;
};
