#include <Rcpp.h>
using namespace Rcpp;
//[[Rcpp::export]]
IntegerVector cpplb(NumericVector samp, NumericVector sref) {
  int nobs = samp.size();
  IntegerVector ans(nobs);
  for (int i = 0; i < samp.size(); ++i)
    ans[i] = std::lower_bound(sref.begin(), sref.end(), samp[i]) - sref.begin();
  return ans;
}

//[[Rcpp::export]]
IntegerVector cppcp(NumericVector samp, NumericVector ref, IntegerVector ord) {
  int nobs = samp.size();
  IntegerVector ans(nobs);
  for (int i = 0, j = 0; i < nobs; ++i) {
    int ind(ord[i] - 1); // C++ uses 0-based indices
    double ssampi(samp[ind]);
    while (ref[j] < ssampi && j < ref.size()) ++j;
    ans[ind] = j;     // j is the 1-based index of the lower bound
  }
  return ans;
}

//[[Rcpp::export]]
NumericVector cppsort(NumericVector v) {
    NumericVector sv(clone(v));
    std::sort(sv.begin(), sv.end());
    return sv;
}
