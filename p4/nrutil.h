#ifndef _NR_UTILS_H
#define _NR_UTILS_H
  #if defined(__STDC__) || defined(ANSI) || defined(NRANSI)
    void nrerror(char error_text[]);
    int *ivector(long nl, long nh);
    float **matrix(long nrl, long nrh, long ncl, long nch);
    void free_ivector(int *v, long nl, long nh);
  #else
  void nrerror();
  #endif
#endif
