#include <inttypes.h>

/// \class AveragingDataSet
///
/// Buffers number of readings and returns rolling average values. Length of
/// window to average is given by macŕo AVG_WINDOW
///
class AveragingDataSet {
public:
  /// Initializes store by reserving memory for requested bufer size and filling
  /// the whole buffer with given value.
  ///
  /// \param size
  ///    Buffer size
  ///
  /// \param initialValue
  ///    Initial value
  AveragingDataSet(uint16_t size, int16_t initialValue);

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
