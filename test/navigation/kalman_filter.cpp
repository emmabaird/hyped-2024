#include <iostream>

#include <gtest/gtest.h>

#include <navigation/control/consts.hpp>
#include <navigation/filtering/kalman_filter.hpp>
#include <navigation/filtering/kalman_matrices.hpp>
#include <utils/manual_time.hpp>

namespace hyped::test {

TEST(KalmanFilter, construction)
{
  using KalmanFilter     = navigation::KalmanFilter;
  const auto manual_time = std::make_shared<utils::ManualTime>();
  navigation::StateVector initial_state(navigation::StateVector::Zero());
  navigation::ErrorCovarianceMatrix initial_error_covariance;
  KalmanFilter kalman_filter(
    initial_state,
    navigation::ErrorCovarianceMatrix::Zero(),  // TODOLater: If initial position not known exactly,
                                                // tune

    navigation::kStateTransitionMatrix,
    navigation::kControlMatrix,
    navigation::kErrorCovarianceMatrix,
    navigation::measurement_matrix,
    navigation::kMeasurementNoiseCovarianceMatrix);

  navigation::MeasurementVector measurement;
  measurement << 1, 1;
  navigation::ControlInput control_input(navigation::ControlInput::Zero());

  // TODOLater: dont be lazy, do the maths and check!!

  for (int i = 0; i < 10; ++i) {
    measurement << 1 + i, 1;
    kalman_filter.filter(measurement, control_input);

    navigation::StateVector state_estimate = kalman_filter.getStateEstimate();

    std::cout << "State estimate: " << state_estimate << std::endl;
  }
}

}  // namespace hyped::test
