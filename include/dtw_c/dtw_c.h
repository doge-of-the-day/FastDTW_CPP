#ifndef DTW_C_H
#define DTW_C_H
#ifdef __cplusplus
extern "C" {
#endif
void apply_fdtw_c(const float *seq_a, const unsigned int size_a,
                  const float *seq_b, const unsigned int size_b,
                  double *distance);

void apply_ddtw_c(const double *seq_a, const unsigned int size_a,
                  const double *seq_b, const unsigned int size_b,
                  double *distance);
#ifdef __cplusplus
}
#endif

#endif // DTW_C_H

